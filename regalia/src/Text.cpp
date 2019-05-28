#include <pch.h>
#include <Camera.h>
#include <Game.h>
#include <Number.h>
#include <Resources.h>
#include <Text.h>

Text::Text(GameObject& go, const std::string& file, int size, TextStyle style, const std::string& text, SDL_Color color)
    : Component(go)
    , text(text)
    , style(style)
    , fontFile(file)
    , fontSize(size)
    , color(color) {
	this->font = Resources::GetText(this->fontFile, this->fontSize);
	this->texture = nullptr;
	this->timer = nullptr;

	RemakeTexture();
}

Text::~Text() {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}

	if (this->timer != nullptr) {
		delete this->timer;
	}
}

void Text::Update(float dt) {
	if (this->timer != nullptr) {
		this->timer->Update(dt);

		if (this->timer->Get() > 0.0f) {
			this->associated.RequestDelete();
		}
	}
}

void Text::Render() {
	if (this->texture == nullptr)
		return;

	auto game = Game::GetInstance();

	SDL_Rect srcRect {
		static_cast<int>(0),
		static_cast<int>(0),
		static_cast<int>(this->associated.box.width),
		static_cast<int>(this->associated.box.height)
	};

	SDL_Rect dstRect {
		static_cast<int>(this->associated.box.vector.x - Camera::pos.x),
		static_cast<int>(this->associated.box.vector.y - Camera::pos.y),
		static_cast<int>(this->associated.box.width),
		static_cast<int>(this->associated.box.height)
	};

	auto err = SDL_RenderCopyEx(game->GetRenderer(), this->texture, &srcRect, &dstRect, (this->associated.angle * 180) / Number::Pi, nullptr, SDL_FLIP_NONE);

	if (err < 0) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Text::SetText(const std::string& text) {
	this->text = text;

	Text::RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontFile(const std::string& file) {
	this->fontFile = file;
	RemakeTexture();
}

void Text::SetFontSize(int size) {
	this->fontSize = size;
	RemakeTexture();
}

void Text::SetFadeOut(float t) {
	this->timer = new Timer();
	this->timer->SetStart(-t);
}

void Text::RemakeTexture() {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}

	this->font = Resources::GetText(this->fontFile, this->fontSize);

	SDL_Surface* aux = nullptr;
	auto game = Game::GetInstance();
	auto renderer = game->GetRenderer();

	switch (this->style) {
	case TextStyle::SOLID:
		aux = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
		break;
	case TextStyle::SHADED:
		aux = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->color, SDL_Color { 0, 0, 0, 0 });
		break;
	case TextStyle::BLENDED:
		aux = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->color);
		break;
	}

	this->texture = SDL_CreateTextureFromSurface(renderer, aux);

	if (this->texture == nullptr) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}

	int w, h;
	std::tie(w, h) = Resources::QueryImage(this->texture);
	this->associated.box.width = static_cast<float>(w);
	this->associated.box.height = static_cast<float>(h);

	SDL_FreeSurface(aux);
}