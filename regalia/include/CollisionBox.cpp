#include <pch.h>
#include <CollisionBox.h>

bool CollisionBox::IsColliding(Circle circle) {
	// TODO: compare this box with the circle
	return false;
}

bool CollisionBox::IsColliding(Rect box) {
	// TODO: compare this box with this other box
	return false;
}

bool CollisionBox::IsType(std::string type) {
	return (type == "CollisionBox");
}
