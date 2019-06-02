#pragma once

#include <Component.h>
#include <Text.h>
#include <Timer.h>

class Text : public Component {
public:
	enum class TextStyle {
		SOLID,
		SHADED,
		BLENDED
	};

	Text(GameObject& go, const std::string& file, int size, TextStyle style, const std::string& text, SDL_Color color);

	~Text();

	void Update(unsigned dt) override;

	void Render() override;

	void SetText(const std::string& _text);

	void SetColor(SDL_Color _color);

	void SetStyle(TextStyle _style);

	void SetFontFile(const std::string& file);

	void SetFontSize(int size);

	void SetFadeOut(unsigned t);

private:
	std::shared_ptr<TTF_Font> font;

	SDL_Texture* texture;

	std::string text;

	TextStyle style;

	std::string fontFile;

	int fontSize;

	SDL_Color color;

	void RemakeTexture();
};