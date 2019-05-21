# Menu State

To show the menu options (Play, Story, Credits)

### Path

ArrowDown → Go up on option

ArrowUp → Go down on option

X → Push Option

# Credits State

To show an image of us.

### Path

O → MenuState → Pop itself

# Story State

To show a text with the story

### Path

ArrowDown → Go up on text

ArrowUp → Go down on text

O → Menu State → Pop Itself

# Play State

The fight is in here

```c++
class PlayState : State {
    public:
    
    	Update(float dt) {
            f(dt);
        }
    
    	UpdateLoading (float) {
            // Imprime na tela o READY 3, 2, 1
            f = UpdateStuff;
        }

    	UpdateStuff (float) {
            
        }
    	
    private:
    
    	Func f; // ponteiro para funcao do Update
}
```



### Path

SELECT → ScoreTable (PAUSE) → add ScoreTable

"Time Up" → ScoreTable (SET_ENDED) → add ScoreTable

"Set end" → ScoreTable (SET_ENDED) → add ScoreTable

"Last set end" → ScoreTable(MATCH_ENDED) → add ScoreTable

# Score State

Control sets and pause. Shows score of the current match

### Path

R1 → continue (if in PAUSE) → Pop itself

R2 → restart → Pop itself, Pop PlayState, Push PlayState

L1 → next set (if SET_ENDED) → Pop itself, Pop PlayState, Push PlayState

L2 → quit → RequestQuit

# Constants file
```c++
#pragma once

namespace Constants
{
    namespace Play
    {
        const float SET_TIME = ;
        const int NUMBER_OF_SETS = 5;
    }
    
    namespace Persona {
        // Pode ser feito usando o valor do enum como índice para array.
        // Será usado para carregar os assets de cada persona.
        const enum {
            PERSONA1 = "PERSONA1",
            PERSONA2 = "PERSONA2",
            PERSONA3 = "PERSONA3",
            PERSONA4 = "PERSONA4"
        }
    }
    // ...
    
}
```

# Game Meta Data
```c++
class GameMetaData {
    public:
    	// state control
    	static int popRequested; // number of states to pop
    	static bool quitRequested;
    
		//Set control
        static bool Finished;
        static int Set;
        enum ResultType {
            NONE,
            PLAYER1_VICTORY,
            PLAYER2_VICTORY
        };
        static ResultType Result[Constants::Play::NUMBER_OF_SETS];
    	static std::unique_ptr<Player> player1 = nullptr;
    	static std::unique_ptr<Player> player2 = nullptr;
}
```
# Player

> We must update the GameObject parameters when a component is added to it, not only when the component is created.

```c++
class Player : Component {
    public:
        int hp;
    	
    	Vec2 speed;
    	
    	enum PlayerState {
            IDLE,
            RUNNING,
            JUMPING,
            FALLING,
            ATTACKING,
            HANGING // wall slide
        }
    
    	PlayerState stateAnimation;
    
    	Player () {
            associated->AddComponent(spriteArray[stateAnimation])
        }
    
    	std::shared_ptr<Sprite> spriteArray[PlayerState.size()];
    
    	Update () {
            associated.RemoveSprite();
            associated.AddComponent(spriteArray[stateAnimation]);
        }
    
        PersonaTypes persona; // which persona

        IsMainObject() { return true; } // identify the main object
}
```

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

Como o GameObject tem dois ponteiros para o mesmo Component, um em ```c++ std::vector<std::unique_ptr<Component>> components;``` e outro em ```c++ std::array<Component*, Constants::NUMBER_OF_COMPONENTS_TYPES> componentsArray{};```, o método ```RemoveComponent() ``` também teve de ser alterado para remover os dois ponteiros.

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


# Bullet

```c++
class Bullet : Component {

}
```




# O que deseja mudar

+ Claudio -> Quero mudar State para Page o nome
+ Adicionar ReplaceComponent(std::string type, Component* comp)
