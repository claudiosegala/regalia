#pragma once
#include <Constants.h>

class GameObject;

class Component {
public:
	Component(GameObject& go);

	virtual ~Component();

	virtual void Start();

	virtual void NotifyCollision(GameObject& go);

	virtual void Update(unsigned dt) = 0;

	virtual void Render() = 0;

protected:
	GameObject& associated;
};

inline unsigned GetNextComponentId() {
	static auto lastId = 0u;
	return lastId++;
}

template <typename T>
unsigned GetComponentTypeId() {
	static_assert(std::is_base_of<Component, T>::value, "Invalid base type");
	static auto typeId = GetNextComponentId();
	assert(typeId < Constants::NumberOfComponentsTypes);
	return typeId;
}
