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
	font = Resources::GetText(fontFile, fontSize);
	texture = nullptr;
	timer = nullptr;

	RemakeTexture();
}

Text::~Text() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	delete timer;
}

void Text::Update(float dt) {
	if (timer != nullptr) {
		timer->Update(dt);

		if (timer->Get() > 0.0f) {
			associated.RequestDelete();
		}
	}
}

void Text::Render() {
	if (texture == nullptr)
		return;

	auto game = Game::GetInstance();

	SDL_Rect srcRect {
		static_cast<int>(0),
		static_cast<int>(0),
		static_cast<int>(associated.box.width),
		static_cast<int>(associated.box.height)
	};

	SDL_Rect dstRect {
		static_cast<int>(associated.box.vector.x - Camera::pos.x),
		static_cast<int>(associated.box.vector.y - Camera::pos.y),
		static_cast<int>(associated.box.width),
		static_cast<int>(associated.box.height)
	};

	auto err = SDL_RenderCopyEx(game->GetRenderer(), texture, &srcRect, &dstRect, (associated.angle * 180) / Number::Pi, nullptr, SDL_FLIP_NONE);

	if (err < 0) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Text::SetText(const std::string& _text) {
	text = _text;
	Text::RemakeTexture();
}

void Text::SetColor(SDL_Color _color) {
	color = _color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle _style) {
	style = _style;
	RemakeTexture();
}

void Text::SetFontFile(const std::string& file) {
	fontFile = file;
	RemakeTexture();
}

void Text::SetFontSize(int size) {
	fontSize = size;
	RemakeTexture();
}

void Text::SetFadeOut(float t) {
	timer = new Timer();
	timer->SetStart(-t);
}

void Text::RemakeTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	font = Resources::GetText(fontFile, fontSize);

	SDL_Surface* aux = nullptr;
	auto game = Game::GetInstance();
	auto renderer = game->GetRenderer();

	switch (style) {
	case TextStyle::SOLID:
		aux = TTF_RenderText_Solid(font.get(), text.c_str(), color);
		break;
	case TextStyle::SHADED:
		aux = TTF_RenderText_Shaded(font.get(), text.c_str(), color, Constants::Colors::Black);
		break;
	case TextStyle::BLENDED:
		aux = TTF_RenderText_Blended(font.get(), text.c_str(), color);
		break;
	}

	if (aux == nullptr) {
		throw std::runtime_error("TTF_RenderText fail!");
	}

	associated.box.width = float(aux->w);
	associated.box.height = float(aux->h);

	texture = SDL_CreateTextureFromSurface(renderer, aux);

	if (texture == nullptr) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}

	SDL_FreeSurface(aux);
}