#include <pch.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Util.h>

CameraFollower::CameraFollower(GameObject& go)
    : Component(go) {}

void CameraFollower::Update(float dt) {
	UNUSED(dt);

	associated.box.vector = Camera::pos;
}

void CameraFollower::Render() {}
