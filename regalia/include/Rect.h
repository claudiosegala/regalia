#pragma once

#include <Logger.h>
#include <Constants.h>
#include <Vec2.h>

#include <tuple>

class Rect {
    public:

        Vec2 vector;

        float width;

        float height;

        Rect();

        Rect(Vec2, float, float);

        Rect(float, float, float, float);

        Vec2 Center() const;

        float CenterDistance(const Rect&) const;

        void SetCenter(const Vec2&);

        bool IsInside(const Vec2&) const;

        std::tuple<Vec2, Vec2> GetPoints() const;

        Rect operator+ (const Vec2&) const;

        void operator+= (const Vec2&);

        Rect operator- (const Vec2&) const;

        void operator-= (const Vec2&);

        Rect operator* (float) const;

        void operator*= (float);

        friend std::ostream& operator<<(std::ostream &os, const  Rect& n);

        friend std::istream& operator>>(std::istream &is, Rect& n);
};