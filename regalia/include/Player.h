#pragma once

#include <Component.h>
#include <Vec2.h>

class Player : public Component {
	public:

		Player(GameObject&);

		void Update(float);

		void Render();

		bool Is(std::string);

	private:

		enum class PlayerState {
			IDLE,
			RUNNING,
			JUMPING,
			FALLING,
			ATTACKING,
			HANGING // wall slide
		};

		PlayerState stateAnimation;

		int hp;

		Vec2 speed;

		//PersonaTypes persona; // which persona

};