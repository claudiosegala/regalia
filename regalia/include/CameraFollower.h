#pragma once

#include <Component.h>
#include <GameObject.h>

class CameraFollower : public Component {
public:
	CameraFollower(GameObject&);

	void Update(float dt) override;

	void Render() override;
};