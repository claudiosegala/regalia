#include <pch.h>
#include <State.h>

State::State()
    : objectArray() {
	started = false;
	quitRequested = false;
	popRequested = 0;
}

State::~State() {
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	objectArray.emplace_back(go);

	if (started) {
		go->Start();
	}

	return objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	auto f = [&](const std::shared_ptr<GameObject>& _go) {
		return _go.get() == go;
	};

	auto ptr = std::find_if(objectArray.begin(), objectArray.end(), f);

	return ptr != objectArray.end()
	    ? std::weak_ptr<GameObject>(*ptr)
	    : std::weak_ptr<GameObject>();
}

int State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::RenderArray() {
	for (auto i = 0; i < (int)objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

void State::StartArray() {
	for (auto i = 0; i < (int)objectArray.size(); i++) {
		objectArray[i]->Start();
	}
}

void State::UpdateArray(unsigned dt) {
	for (auto i = 0; i < (int)objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
}

void State::PruneArray() {
	auto it = std::remove_if(objectArray.begin(), objectArray.end(), [&](std::shared_ptr<GameObject>& o) {
		return o->IsDead();
	});

	objectArray.erase(it, objectArray.end());
}