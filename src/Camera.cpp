#include <Camera.h>
#include <Game.h>
#include <InputManager.h>

float const Camera::pace = 1500.0f;

Vec2 Camera::pos;

Vec2 Camera::speed;

GameObject* Camera::focus;

void Camera::Reset () {
    Camera::pos.Reset();
}

void Camera::Follow (GameObject* newFocus) {
    Camera::focus = newFocus;
}

void Camera::Unfollow() {
    Camera::Follow(nullptr);
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        // Follows the game object
        auto center = Camera::focus->box.Center();
        auto centerWindow = Vec2(Game::windowWidth, Game::windowHeight) / 2;

        Camera::pos = center - centerWindow;
        return;
    }

    Camera::speed = Camera::GetMovement() * dt * Camera::pace;
    Camera::pos += Camera::speed;
}

Vec2 Camera::GetMovement() {
    auto& in  = InputManager::GetInstance();
    
    auto right = in.IsKeyDown(RIGHT_ARROW_KEY);
    auto left = in.IsKeyDown(LEFT_ARROW_KEY);
    auto up = in.IsKeyDown(UP_ARROW_KEY);
    auto down = in.IsKeyDown(DOWN_ARROW_KEY);

    float x = right ? 1.0f : (left ? -1.0f : 0.0f);
    float y = down ? 1.0f : (up ? -1.0f : 0.0f);

    return Vec2(x, y);
}
