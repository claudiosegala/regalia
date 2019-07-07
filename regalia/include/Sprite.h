#pragma once

#include <Component.h>
#include <Vec2.h>
#include <functional>

class Sprite : public Component {
public:
	enum class Direction {
		Original,
		Flip,
		Keep
	};

	Sprite(GameObject& go, const std::string& file);

	Sprite(GameObject& go, const SpriteSheetData* spriteSheetData);

	~Sprite();

	void Open(const std::string& file);

	void Open(const SpriteSheetData* _spriteSheetData);

	void SetClip(int, int, int, int);

	void SetClip();

	void SetBox();

	void SetScale(float, float);

	void SetAnimation(int animationId);

	void SetAnimationDirX(Direction dirX);

	// Run the selected animation once, then calls the callback function
	void RunAnimation(int animationId, std::function<void()> callback = nullptr);

	Vec2 GetScale() const;

	void Update(unsigned dt) override;

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

	SDL_Rect clipRect {};

	// Animation
	const SpriteSheetData* spriteSheetData = nullptr;

	int animationOnce = -1;

	std::function<void()> animationFinishedCallback = nullptr;

	int frameCount = 1;

	int currentFrame = 0;

	unsigned timeElapsed = 0;

	int currentAnimationId = 0;

	bool flipAnimationX = false;
};
