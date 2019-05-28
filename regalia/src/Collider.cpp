#include <pch.h>
#include <Circle.h>
#include <Collider.h>
#include <Util.h>
#include <Rect.h>
#include <Vec2.h>

#ifdef DEBUG
#include <Camera.h>
#include <Game.h>
#endif // DEBUG

Collider::Collider(GameObject& go, Shape* shape, Vec2 scale, Vec2 offset)
    : Component(go)
	, shape(shape)
	, scale(scale)
	, offset(offset) {
}

void Collider::Update(float dt) {
	UNUSED(dt);

	if (this->shape == nullptr) {
		return;
	}

	const auto& box = this->associated.box;

	if (this->shape->Is("Rect")) {
		auto rect = static_cast<Rect*>(this->shape);
		(*rect) = box;
		rect->width *= this->scale.x;
		rect->height *= this->scale.y;
		rect->SetCenter(box.Center());
		(*rect) += this->offset.GetRotate(this->associated.angle);
	} else {
		auto circle = static_cast<Circle*>(this->shape);

		circle->center = box.Center() + this->offset.GetRotate(this->associated.angle);
		// TODO: verify if this is ok
		circle->radius = box.MaxRadius() * this->scale.x;
	}
}

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::Center()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
	const auto& box = associated.box;

	const Vec2 center(box.Center());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.vector.x, box.vector.y) - center).GetRotate(associated.angle) + center - Camera::pos;

	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vec2(box.vector.x + box.width, box.vector.y) - center).GetRotate(associated.angle) + center - Camera::pos;

	points[1] = { (int)point.x, (int)point.y };

	point = (Vec2(box.vector.x + box.width, box.vector.y + box.height) - center).GetRotate(associated.angle) + center - Camera::pos;

	points[2] = { (int)point.x, (int)point.y };

	point = (Vec2(box.vector.x, box.vector.y + box.height) - center).GetRotate(associated.angle) + center - Camera::pos;

	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif // DEBUG
}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}
