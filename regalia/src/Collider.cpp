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

Collider::Collider(GameObject& go, Rect* shape, Vec2 scale, Vec2 offset)
    : Component(go)
    , rect(shape)
    , scale(scale)
    , offset(offset) {
}

void Collider::UpdateFather(unsigned dt) {
	UNUSED(dt);
	auto& box = associated.box;

	box.width /= scale.x;
	box.height /= scale.y;
	box.SetCenter(rect->Center() - offset.GetRotate(associated.angle));
}

// TODO: verify if this is correct
void Collider::Update(unsigned dt) {
	UNUSED(dt);

	if (rect == nullptr) {
		return;
	}

	const auto& box = associated.box;

	rect->width = associated.box.width * scale.x;
	rect->height = associated.box.height * scale.y;
	rect->SetCenter(box.Center() + offset.GetRotate(associated.angle));
}

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::Center()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
	RenderBox(associated.box, 255, 0, 0);

	if (rect->Is("Rect")) {
		RenderBox(*rect, 0, 255, 0);
	}
}

void Collider::RenderBox(const Rect& box, int r, int g, int b) {
#ifdef DEBUG
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

	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), Uint8(r), Uint8(g), Uint8(b), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif // DEBUG
}

void Collider::SetScale(Vec2 _scale) {
	scale = _scale;
}

void Collider::SetOffset(Vec2 _offset) {
	offset = _offset;
}
