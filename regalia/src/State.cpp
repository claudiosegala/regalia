#include <State.h>

State::State() : objectArray() {
    this->started = false;
    this->quitRequested = false;
    this->popRequested = false;
}

State::~State() {
    this->objectArray.clear();
}

bool State::HasComponent(std::string type) {
    for (auto object : this->objectArray) {
        if (object->GetComponent(type) != nullptr) {
            return true;
        }
    }

    return false;
}

std::weak_ptr<GameObject> State::AddObject (GameObject* gameObject) {
    this->objectArray.emplace_back(gameObject);

    if (this->started) {
        gameObject->Start();
    }

    return this->objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* gameObject) {
    auto f = [&](const std::shared_ptr<GameObject>& _go) {
        return _go.get() == gameObject;
    };

    auto ptr = std::find_if(this->objectArray.begin(), this->objectArray.end(), f);

    return ptr != this->objectArray.end() 
        ? std::weak_ptr<GameObject>(*ptr)
        : std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return this->popRequested;
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::RenderArray() {
    for (auto i = 0; i < (int) this->objectArray.size(); i++) {
        this->objectArray[i]->Render();
    }
}

void State::StartArray() {
    for (auto i = 0; i < (int) this->objectArray.size(); i++) {
        this->objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for (auto i = 0; i < (int) this->objectArray.size(); i++) {
        this->objectArray[i]->Update(dt);
    }
}

void State::PruneArray() {
    auto it = std::remove_if(this->objectArray.begin(), this->objectArray.end(), [&] (std::shared_ptr<GameObject>& o) { 
        return o->IsDead();
    });

    this->objectArray.erase(it, this->objectArray.end());
}