#include <pch.h>
#include <Component.h>
#include <GameObject.h>

GameObject::GameObject() {
	started = false;
	isDead = false;
	angle = 0.0f;
}

GameObject::~GameObject() {
	box.~Rect();
	components.clear();
}

void GameObject::Start() {
	for (auto& component : components) {
		component->Start();
	}

	started = true;
}

void GameObject::Update(float dt) {
	for (auto& component : components) {
		component->Update(dt);
	}
}

void GameObject::Render() {
	for (auto& component : components) {
		component->Render();
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::RemoveComponent(const Component* cpt) {
	auto it = std::remove_if(components.begin(), components.end(), [&cpt](const std::unique_ptr<Component>& c) {
		return c.get() == cpt;
	});

	if (it != components.end()) {
		components.erase(it);
	}

	for (auto& component : componentsArray) {
		if (component == cpt) {
			component = nullptr;
		}
	}
}

void GameObject::NotifyCollision(GameObject& other) {
	for (int i = 0; i < (int)components.size(); i++) {
		components[i]->NotifyCollision(other);
	}
}