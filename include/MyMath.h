#pragma once

#include <vector>
#include <cmath>

struct Vec2
{

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x_, float y_);

    float x;
    float y;

    Vec2& operator+=(const Vec2& op2);
    Vec2& operator-=(const Vec2& op2);
    bool operator==(const Vec2& op2);
    float getLength() const;
};

Vec2 operator+(const Vec2& op1, const Vec2& op2);
Vec2 operator-(const Vec2& op1, const Vec2& op2);
Vec2 operator/(const Vec2& op1, const float& op2);
Vec2 operator*(const Vec2& op1, const float& op2);
Vec2 operator*(const float& op1, const Vec2& op2);

float dotProduct(const Vec2& op1, const Vec2& op2);

struct AABB
{
    Vec2 min;
    Vec2 max;
};

struct OBB {
    // Constructeur par défaut
    OBB() : center(), extents(), rotation(0.0f) {}

    OBB(const Vec2& center_, const Vec2& extents_, float rotation_)
        : center(center_), extents(extents_), rotation(rotation_) {}

    Vec2 center;
    Vec2 extents;
    float rotation;

    static OBB fromAABB(const AABB& aabb, float angle = 0.0f) {
        Vec2 center = (aabb.min + aabb.max) / 2.0f;
        Vec2 extents = (aabb.max - aabb.min) / 2.0f;
        return { center, extents, angle };
    }

    std::vector<Vec2> getCorners() const;

    AABB toAABB() const;
};


bool doesIntersect(const AABB& b1, const AABB& b2);
bool doesIntersect(const OBB& obb1, const OBB& obb2);