#include "pch.h"
#include "CollisionDisc.h"

bool CollisionDisc::IsColliding(Circle circle) {
	// TODO: implement
	return false;
}

bool CollisionDisc::IsColliding(Rect) {
	// TODO: implement
	return false;
}

bool CollisionDisc::IsType(std::string type) {
	return (type == "CollisionDisc");
}
