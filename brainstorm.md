# Components
Para identificar as classes derivadas de Component podemos usar as funções a seguir.
> Obs: Setar a macro NDEBUG no visual studio quando for compilar para release, essa macro remove os asserts.

```c++
inline unsigned GetNextComponentId() {
	static auto lastId = 0u;
	return lastId++;
}


template <typename T>
unsigned GetComponentTypeId() {
	static_assert(std::is_base_of<Component, T>::value, "");
	static auto typeId = GetNextComponentId();
	assert(typeId < Constants::NUMBER_OF_COMPONENTS_TYPES);
	return typeId;
}
```



# GameObject

```c++
class GameObject {
public:
	Rect box;
	float angleDeg;

	GameObject();
	~GameObject();

	void Start();
	void Update(float dt);
	void Render();
	bool IsDead() const;
	void RequestDelete();
	void RemoveComponent(const Component* cpt);
	Vec2 GetPosition() const;
	void NotifyCollision(GameObject& other);

	template <class T, class ... TArgs>
	T* AddComponent(TArgs&& ... args);

	template <class T>
	T* GetComponent() const;


private:
	std::vector<std::unique_ptr<Component>> components;
	std::array<Component*, Constants::NUMBER_OF_COMPONENTS_TYPES> componentsArray{};

	bool isDead = false;
	bool started = false;
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
```

O AddComponent permite que components sejam adicionados sem ter de dar 'new' e passar o gameObject como parâmetro toda vez, como mostrado no exemplo a seguir.

```c++
	associated.AddComponent<Sprite>(sprite, frameCount, frameTime);
	associated.AddComponent<Collider>();
```

Como o GameObject tem dois ponteiros para o mesmo Component, um em ``` std::vector<std::unique_ptr<Component>> components;``` e outro em ``` std::array<Component*, Constants::NUMBER_OF_COMPONENTS_TYPES> componentsArray{};```, o método ```RemoveComponent() ``` também teve de ser alterado para remover os dois ponteiros.

```c++
void GameObject::RemoveComponent(const Component* cpt) {
	auto it = std::find_if(components.begin(), components.end(),
	                       [&cpt](const std::unique_ptr<Component>& c) { return c.get() == cpt; });

	if (it != components.end()) {
		components.erase(it);
	}

	for (auto& component : componentsArray) {
		if (component == cpt) {
			component = nullptr;
		}
	}
}
```
