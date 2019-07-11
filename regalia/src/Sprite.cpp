#include <pch.h>
#include <Camera.h>
#include <Game.h>
#include <Number.h>
#include <Resources.h>
#include <Sprite.h>
#include <utility>

Sprite::Sprite(GameObject& go, const std::string& file)
    : Component(go) {

	Open(file);
}

Sprite::Sprite(GameObject& go, const SpriteSheetData* spriteSheetData, int initialAnimationId)
    : Component(go)
    , spriteSheetData(spriteSheetData)
    , currentAnimationId(initialAnimationId) {

	Open(spriteSheetData->file);

	frameCount = spriteSheetData->GetNumberOfFrames(currentAnimationId);

	spriteSheetData->AssertSize(width, height);
}

Sprite::~Sprite() {}

void Sprite::Open(const std::string& file) {
	texture = Resources::GetImage(file);

	std::tie(width, height) = Resources::QueryImage(texture.get());

	SetClip();
	SetBox();
}

void Sprite::Open(const SpriteSheetData* _spriteSheetData) {
	this->spriteSheetData = _spriteSheetData;

	Open(spriteSheetData->file);

	frameCount = spriteSheetData->GetNumberOfFrames(currentAnimationId);

	spriteSheetData->AssertSize(width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect = { x, y, w, h };
}

void Sprite::SetClip() {
	if (spriteSheetData == nullptr) {
		SetClip(0, 0, width, height);
	} else {
		clipRect = spriteSheetData->GetAnimationRect(currentAnimationId, currentFrame);
	}
}

void Sprite::SetBox() {
	auto frameWidth = GetWidth();
	auto frameHeight = GetHeight();

	associated.box.width = float(frameWidth);
	associated.box.height = float(frameHeight);
}

void Sprite::SetScale(float x, float y) {
	x = Number::Zero(x) ? scale.x : x;
	y = Number::Zero(y) ? scale.y : y;

	scale = Vec2(x, y);

	SetClip();
	SetBox();
}

void Sprite::SetAnimation(int animationId) {
	if (spriteSheetData == nullptr) {
		throw std::runtime_error("Trying to set a animation id in a sprite that doesn't have animation");
	}

	if (animationId == currentAnimationId) {
		return;
	}

	currentAnimationId = animationId;
	currentFrame = 0;
	frameCount = spriteSheetData->GetNumberOfFrames(currentAnimationId);
	timeElapsed = spriteSheetData->frameTime; // Force the sprite to be updated now
}

void Sprite::SetAnimationDirX(Direction dirX) {
	if (dirX == Direction::Original) {
		flipAnimationX = false;
	} else if (dirX == Direction::Flip) {
		flipAnimationX = true;
	} // else keep previous direction
}

void Sprite::RunAnimation(int animationId, std::function<void()> callback) {
	animationOnce = animationId;
	animationFinishedCallback = std::move(callback);
}

Vec2 Sprite::GetScale() const {
	return scale;
}

void Sprite::Update(unsigned dt) {
	if (spriteSheetData == nullptr) {
		return;
	}

	timeElapsed += dt;

	if (animationOnce != -1) {
		if (animationOnce != currentAnimationId) {
			SetAnimation(animationOnce);
			animationOnce = -1;
		}
	}

	if (timeElapsed >= spriteSheetData->frameTime) {
		timeElapsed = 0;

		if (spriteSheetData->selfDestruct && currentFrame == frameCount) {
			associated.RequestDelete();
			return;
		}

		currentFrame = (currentFrame + 1) % frameCount;

		if (currentFrame == 0 && animationFinishedCallback != nullptr) {
			animationFinishedCallback();
			animationFinishedCallback = nullptr;
		}

		SetClip();
	}
}

void Sprite::Render() {
	auto x = int(associated.box.vector.x - Camera::pos.x);
	auto y = int(associated.box.vector.y - Camera::pos.y);

	Render(x, y);
}

void Sprite::Render(float _x, float _y) {
	auto x = int(_x);
	auto y = int(_y);

	Render(x, y);
}

void Sprite::Render(int x, int y) {
	if (associated.hide) {
		return;
	}

	auto game = Game::GetInstance();
	auto srcRect = clipRect;
	auto flip = flipAnimationX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Rect dstRect {
		x,
		y,
		int(srcRect.w * scale.x),
		int(srcRect.h * scale.y)
	};

	auto err = SDL_RenderCopyEx(game->GetRenderer(), texture.get(), &srcRect, &dstRect, (associated.angle * 180) / Number::Pi, nullptr, flip);

	if (err < 0) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

int Sprite::GetWidth() const {
	auto frameWidth = spriteSheetData == nullptr ? width : spriteSheetData->GetFrameWidth();
	return int(frameWidth * scale.x);
}

int Sprite::GetHeight() const {
	return int(float(height) * scale.y);
}

bool Sprite::IsOpen() const {
	return (texture != nullptr);
}
