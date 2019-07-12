#pragma once

#include <Component.h>
#include <Interfaces.h>
#include <Vec2.h>
#include "PlayState.h"

class Bullet : public Component {
public:
	int shooterId;

	Bullet(GameObject& go, BulletData& data, PlayState* play_state);

	void Update(unsigned dt) override;

	void Render() override;

	void NotifyCollision(GameObject& go) override;

	int GetDamage();

private:

	PlayState* play_state;

	int damage;

	int level;

	Vec2 speed;

	bool invincible;

	Constants::PersonaType personaType;

	void LoadAssets(BulletData& data);

	void MoveAndBounce(unsigned dt);

	void Die();
};
