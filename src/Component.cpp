#include <Component.h>

Component::Component(GameObject& go) : associated(go) {}

Component::~Component() {}

void Component::Start() {}

void Component::NotifyCollision(GameObject& go) {
    UNUSED(go);
}