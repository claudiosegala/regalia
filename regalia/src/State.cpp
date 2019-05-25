#include <pch.h>
#include <State.h>

State::State()
    : objectArray() {
	this->started = false;
	this->quitRequested = false;
	this->popRequested = 0;
}

State::~State() {
	this->objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	this->objectArray.emplace_back(go);

	if (this->started) {
		go->Start();
	}

	return this->objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	auto f = [&](const std::shared_ptr<GameObject>& _go) {
		return _go.get() == go;
	};

	auto ptr = std::find_if(this->objectArray.begin(), this->objectArray.end(), f);

	return ptr != this->objectArray.end()
	    ? std::weak_ptr<GameObject>(*ptr)
	    : std::weak_ptr<GameObject>();
}

int State::PopRequested() {
	return this->popRequested;
}

bool State::QuitRequested() {
	return this->quitRequested;
}

void State::RenderArray() {
	for (auto i = 0; i < (int)this->objectArray.size(); i++) {
		this->objectArray[i]->Render();
	}
}

void State::StartArray() {
	for (auto i = 0; i < (int)this->objectArray.size(); i++) {
		this->objectArray[i]->Start();
	}
}

void State::UpdateArray(float dt) {
	for (auto i = 0; i < (int)this->objectArray.size(); i++) {
		this->objectArray[i]->Update(dt);
	}
}

void State::PruneArray() {
	auto it = std::remove_if(this->objectArray.begin(), this->objectArray.end(), [&](std::shared_ptr<GameObject>& o) {
		return o->IsDead();
	});

	this->objectArray.erase(it, this->objectArray.end());
}