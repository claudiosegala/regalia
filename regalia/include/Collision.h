#pragma once

#include <Circle.h>
#include <Shape.h>
#include <Rect.h>
#include <Util.h>
#include <Vec2.h>

class Collision {
public:
	static inline bool IsColliding(Shape* a, Shape* b, float angleOfA, float angleOfB) {
		if (a->Is("Rect")) {
			auto _a = static_cast<Rect*>(a);

			if (b->Is("Rect")) {
				auto _b = static_cast<Rect*>(b);
				return IsColliding(*_a, *_b, angleOfA, angleOfB);
			} else {
				auto _b = static_cast<Circle*>(b);
				return IsColliding(*_a, *_b, angleOfA, angleOfB);
			}
		} else {
			auto _a = static_cast<Circle*>(a);

			if (b->Is("Rect")) {
				auto _b = static_cast<Rect*>(b);
				return IsColliding(*_a, *_b, angleOfA, angleOfB);
			} else {
				auto _b = static_cast<Circle*>(b);
				return IsColliding(*_a, *_b);
			}
		}
	}

	// Observação: IsColliding espera ângulos em radianos!
	// Para usar graus, forneça a sua própria implementação de Rotate,
	// ou transforme os ângulos no corpo de IsColliding.
	static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
		Vec2 A[] = {
			Vec2(a.vector.x, a.vector.y + a.height),
			Vec2(a.vector.x + a.width, a.vector.y + a.height),
			Vec2(a.vector.x + a.width, a.vector.y),
			Vec2(a.vector.x, a.vector.y)
		};
		Vec2 B[] = {
			Vec2(b.vector.x, b.vector.y + b.height),
			Vec2(b.vector.x + b.width, b.vector.y + b.height),
			Vec2(b.vector.x + b.width, b.vector.y),
			Vec2(b.vector.x, b.vector.y)
		};

		for (auto& v : A) {
			v = Rotate(v - a.Center(), angleOfA) + a.Center();
		}

		for (auto& v : B) {
			v = Rotate(v - b.Center(), angleOfB) + b.Center();
		}

		Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

		for (auto& axis : axes) {
			float P[4];

			for (int i = 0; i < 4; ++i)
				P[i] = Dot(A[i], axis);

			float minA = *std::min_element(P, P + 4);
			float maxA = *std::max_element(P, P + 4);

			for (int i = 0; i < 4; ++i)
				P[i] = Dot(B[i], axis);

			float minB = *std::min_element(P, P + 4);
			float maxB = *std::max_element(P, P + 4);

			if (maxA < minB || minA > maxB)
				return false;
		}

		return true;
	}

	static inline bool IsColliding(Rect& a, Circle& b, float angleOfA, float angleOfB) {
		return IsColliding(b, a, angleOfB, angleOfA);
	}

	static inline bool IsColliding(Circle& a, Rect& b, float angleOfA, float angleOfB) {
		// TODO: implement
		UNUSED(a);
		UNUSED(b);
		UNUSED(angleOfA);
		UNUSED(angleOfB);
		return false;
	}

	static inline bool IsColliding(Circle& a, Circle& b) {
		return Vec2::Distance(a.center, b.center) < a.radius + b.radius;
	}

private:
	static inline float Mag(const Vec2& p) {
		return std::sqrt(p.x * p.x + p.y * p.y);
	}

	static inline Vec2 Norm(const Vec2& p) {
		return p * (1.f / Mag(p));
	}

	static inline float Dot(const Vec2& a, const Vec2& b) {
		return a.x * b.x + a.y * b.y;
	}

	static inline Vec2 Rotate(const Vec2& p, float angle) {
		float cs = std::cos(angle), sn = std::sin(angle);
		return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
	}
};