#include <pch.h>
#include <Component.h>
#include <GameObject.h>

GameObject::GameObject() {
	this->started = false;
	this->isDead = false;
	this->angle = 0.0f;
}

GameObject::~GameObject() {
	this->box.~Rect();
	this->components.clear();
}

void GameObject::Start() {
	for (auto& component : this->components) {
		component->Start();
	}

	this->started = true;
}

void GameObject::Update(float dt) {
	for (auto& component : this->components) {
		component->Update(dt);
	}
}

void GameObject::Render() {
	for (auto& component : this->components) {
		component->Render();
	}
}

bool GameObject::IsDead() {
	return this->isDead;
}

void GameObject::RequestDelete() {
	this->isDead = true;
}

void GameObject::AddComponent(Component* component) {
	this->components.emplace_back(component);

	if (this->started) {
		component->Start();
	}
}

void GameObject::RemoveComponent(const Component* cpt) {
	auto it = std::remove_if(this->components.begin(), this->components.end(), [&cpt](const std::unique_ptr<Component>& c) {
		return c.get() == cpt;
	});

	if (it != components.end()) {
		this->components.erase(it);
	}

	for (auto& component : componentsArray) {
		if (component == cpt) {
			component = nullptr;
		}
	}
}

void GameObject::NotifyCollision(GameObject& other) {
	for (int i = 0; i < (int)this->components.size(); i++) {
		this->components[i]->NotifyCollision(other);
	}
}