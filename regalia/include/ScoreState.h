#pragma once

#include <Constants.h>
#include <GameObject.h>
#include <Music.h>
#include <State.h>

#include <string>

class ScoreState : public State {
	public:
		ScoreState();

		~ScoreState();

		void LoadAssets();

		void Update(float);

		void Render();

		void Start();

		void Pause();

		void Resume();

	private:
		Music music;
};