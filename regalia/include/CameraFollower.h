#pragma once

#include <Component.h>
#include <GameObject.h>

class CameraFollower : public Component {
public:
	CameraFollower(GameObject&);

	void Update(unsigned dt) override;

	void Render() override;
};