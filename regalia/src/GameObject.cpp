#include <pch.h>
#include <Component.h>
#include <GameObject.h>

GameObject::GameObject() {
	started = false;
	isDead = false;
	angle = 0.0f;
}

GameObject::~GameObject() {
	components.clear();
}

void GameObject::Start() {
	for (auto& component : components) {
		component->Start();
	}

	started = true;
}

void GameObject::Update(float dt) {
	for (auto i = int(components.size() - 1); i >= 0; i--) {
		components[i]->Update(dt);
	}
}

void GameObject::Render() {
	for (auto& component : components) {
		component->Render();
	}
}

bool GameObject::IsDead() const {
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