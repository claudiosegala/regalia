#include <pch.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Constants.h>

CameraFollower::CameraFollower(GameObject& go) : Component(go) {}

void CameraFollower::Update(float dt) {
    UNUSED(dt);

    this->associated.box.vector = Camera::pos;
}

void CameraFollower::Render() {}

bool CameraFollower::Is(std::string type) {
    return (type == "CameraFollower");
}