#include <pch.h>
#include <Camera.h>
#include <Constants.h>
#include <Game.h>
#include <Resources.h>
#include <Sprite.h>

Sprite::Sprite(GameObject& go, const std::string& file, int frameCount, float frameTime, float secondsToSelfDestruct)
    : Component(go)
    , selfDestructCount() {
	this->texture = nullptr;
	this->scale = Vec2(1, 1);
	this->frameCount = frameCount;
	this->currentFrame = 0;
	this->timeElapsed = 0.0;
	this->frameTime = frameTime;
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	this->associated.angle = 0.0f;
	this->clipRect = { 0, 0, 0, 0 };
	this->height = 0;
	this->width = 0;

	Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(const std::string& file) {
	this->texture = Resources::GetImage(file);

	std::tie(this->width, this->height) = Resources::QueryImage(this->texture.get());

	SetClip();
	SetBox();
}

void Sprite::SetClip(int x, int y, int w, int h) {
	this->clipRect = { x, y, w, h };
}

void Sprite::SetClip() {
	auto frameWidth = this->width / this->frameCount;
	auto frameHeight = this->height;

	SetClip(frameWidth * this->currentFrame, 0, frameWidth, frameHeight);
}

void Sprite::SetBox() {
	auto frameWidth = GetWidth();
	auto frameHeight = GetHeight();

	this->associated.box.width = static_cast<float>(frameWidth);
	this->associated.box.height = static_cast<float>(frameHeight);
}

void Sprite::SetScale(float x, float y) {
	x = EQUAL(x, 0) ? this->scale.x : x;
	y = EQUAL(y, 0) ? this->scale.y : y;

	this->scale = Vec2(x, y);

	SetClip();
	SetBox();
}

Vec2 Sprite::GetScale() {
	return this->scale;
}

void Sprite::SetFrame(int frame) {
	this->currentFrame = frame;

	SetClip();
}

void Sprite::SetFrameCount(int frameCount) {
	this->currentFrame = 0;
	this->frameCount = frameCount;

	SetClip();
	SetBox();
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}

void Sprite::Update(float dt) {
	if (secondsToSelfDestruct > 0) {
		this->selfDestructCount.Update(dt);

		if (this->selfDestructCount.Get() >= secondsToSelfDestruct) {
			this->associated.RequestDelete();
			return;
		}
	}

	this->timeElapsed += dt;

	if (this->timeElapsed > this->frameTime) {
		this->timeElapsed -= this->frameTime;
		this->currentFrame = (this->currentFrame + 1) % this->frameCount;

		SetClip();
	}
}

void Sprite::Render() {
	auto x = static_cast<int>(this->associated.box.vector.x - Camera::pos.x);
	auto y = static_cast<int>(this->associated.box.vector.y - Camera::pos.y);

	Render(x, y);
}

void Sprite::Render(float _x, float _y) {
	auto x = static_cast<int>(_x);
	auto y = static_cast<int>(_y);

	Render(x, y);
}

void Sprite::Render(int x, int y) {
	auto game = Game::GetInstance();
	auto srcRect = this->clipRect;

	SDL_Rect dstRect {
		x,
		y,
		static_cast<int>(srcRect.w * this->scale.x),
		static_cast<int>(srcRect.h * this->scale.y)
	};

	auto err = SDL_RenderCopyEx(game->GetRenderer(), this->texture.get(), &srcRect, &dstRect, (this->associated.angle * 180) / Constants::Math::PI, nullptr, SDL_FLIP_NONE);

	if (err < 0) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}

int Sprite::GetWidth() {
	return this->width * static_cast<int>(this->scale.x) / this->frameCount;
}

int Sprite::GetHeight() {
	return this->height * static_cast<int>(this->scale.y);
}

bool Sprite::IsOpen() {
	return (this->texture != nullptr);
}