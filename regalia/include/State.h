#pragma once

#include <GameObject.h>

class State {
public:
	State();

	virtual ~State();

	virtual void LoadAssets() = 0;

	virtual void Update(unsigned dt) = 0;

	virtual void Render() = 0;

	virtual void Start() = 0;

	virtual void Pause() = 0;

	virtual void Resume() = 0;

	virtual std::weak_ptr<GameObject> AddObject(GameObject*);

	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject*);

	int PopRequested();

	bool QuitRequested();

protected:
	bool started = false;

	bool quitRequested = false;

	int popRequested = 0;

	virtual void RenderArray();

	void StartArray();

	virtual void UpdateArray(unsigned dt);

	void PruneArray();

	std::vector<std::shared_ptr<GameObject>> objectArray;
};