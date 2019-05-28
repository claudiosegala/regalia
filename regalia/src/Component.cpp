#include <pch.h>
#include <Component.h>
#include <Util.h>

Component::Component(GameObject& go)
    : associated(go) {}

Component::~Component() {}

void Component::Start() {}

void Component::NotifyCollision(GameObject& go) {
	UNUSED(go);
}