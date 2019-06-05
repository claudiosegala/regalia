#pragma once

#include <Rect.h>
#include <Constants.h>
#include <Component.h>

class GameObject {
public:
	GameObject();

	~GameObject();

	void Start();

	void Update(unsigned dt);

	void Render();

	bool IsDead() const;

	void RequestDelete();

	template <class T, class... TArgs>
	T* AddComponent(TArgs&&... args);

	void RemoveComponent(const Component*);

	template <class T>
	T* GetComponent() const;

	void NotifyCollision(GameObject&);

	Rect box;

	Rect hitbox;

	float angle = 0.0f;

	bool hide = false;

private:
	bool started = false;

	bool isDead = false;

	std::vector<std::unique_ptr<Component>> components;

	std::array<Component*, Constants::NumberOfComponentsTypes> componentsArray {};
};

template <class T, class... TArgs>
T* GameObject::AddComponent(TArgs&&... args) {

	auto cpt = new T(*this, std::forward<TArgs>(args)...);

	components.emplace_back(cpt);
	componentsArray[GetComponentTypeId<T>()] = cpt;

	if (started) {
		cpt->Start();
	}

	return cpt;
}

template <class T>
T* GameObject::GetComponent() const {
	static_assert(std::is_base_of<Component, T>::value, "Invalid type");
	return static_cast<T*>(componentsArray[GetComponentTypeId<T>()]);
}
