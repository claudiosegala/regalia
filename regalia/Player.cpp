#include "Player.h"

Player::Player(GameObject& go) : Component(go) {
	this->associated.AddComponent(this->spriteArray[stateAnimation])
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
