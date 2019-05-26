#pragma once

#include <Component.h>
#include <Vec2.h>

class Sprite : public Component {
public:
	Sprite(GameObject&, const std::string&);

	Sprite(GameObject&, const SpriteSheetData* spriteSheetData);

	~Sprite();

	void Open(const std::string&);

	void SetClip(int, int, int, int);

	void SetClip();

	void SetBox();

	void SetScale(float, float);

	void SetNextAnimation(int animationId, bool flipAnimation);

	Vec2 GetScale() const;

	void Update(float) override;

	void Render() override;

	void Render(int, int);

	void Render(float, float);

	int GetWidth() const;

	int GetHeight() const;

	bool IsOpen() const;

private:
	int width = 0;

	int height = 0;

	Vec2 scale = { 1, 1 };

	std::shared_ptr<SDL_Texture> texture = nullptr;

	SDL_Rect clipRect{};

	// Animation
	const SpriteSheetData* spriteSheetData = nullptr;

	int frameCount = 1;

	int currentFrame = 0;

	float timeElapsed = 0;

	int currentAnimationId = 0;

	int nextAnimationId = 0;

	bool flipAnimation = false;
};
