#include "pch.h"
#include "Player.h"
#include "Constants.h"
#include "GameObject.h"

Player::Player(GameObject& go) : Component(go) {
}

void Player::Update(float dt) {
	UNUSED(dt);

	// change Player State
	// update sprite
	// actions if necessary
}

void Player::Render() {

}

bool Player::Is(std::string type) {
	return (type == "Player");
}
