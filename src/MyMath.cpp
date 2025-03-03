#include "MyMath.h"
#include <limits>
#include <algorithm>

Vec2::Vec2(float x_, float y_) : x(x_), y(y_) {}

Vec2& Vec2::operator+=(const Vec2& op2)
{
    x += op2.x;
    y += op2.y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& op2)
{
    x -= op2.x;
    y -= op2.y;
    return *this;
}

bool Vec2::operator==(const Vec2& op2)
{
    if (x != op2.x || y != op2.y)
        return false;
    return true;
}

float Vec2::getLength() const
{
    return std::sqrt(x * x + y * y);
}

Vec2 operator+(const Vec2& op1, const Vec2& op2)
{
    return { op1.x + op2.x, op1.y + op2.y };
}

Vec2 operator-(const Vec2& op1, const Vec2& op2)
{
    return { op1.x - op2.x, op1.y - op2.y };
}

Vec2 operator/(const Vec2& op1, const float& op2)
{
    return { op1.x / op2, op1.y / op2 };
}

Vec2 operator*(const Vec2& op1, const float& op2)
{
    return { op1.x * op2, op1.y * op2 };
}

Vec2 operator*(const float& op1, const Vec2& op2)
{
    return op2 * op1;
}

float dotProduct(const Vec2& op1, const Vec2& op2)
{
    return op1.x * op2.x + op1.y * op2.y;
}


bool doesIntersect(const AABB& b1, const AABB& b2)
{
    return !(b1.max.x < b2.min.x ||
        b1.min.x > b2.max.x ||
        b1.max.y < b2.min.y ||
        b1.min.y > b2.max.y);
}

bool doesIntersect(const OBB& obb1, const OBB& obb2)
{
    auto corners1 = obb1.getCorners();
    auto corners2 = obb2.getCorners();

    std::vector<Vec2> axes(4);

    Vec2 edge1 = corners1[1] - corners1[0];
    Vec2 edge2 = corners1[3] - corners1[0];

    float edge1Length = edge1.getLength();
    float edge2Length = edge2.getLength();

    if (edge1Length > 0) edge1 = edge1 * (1.0f / edge1Length);
    if (edge2Length > 0) edge2 = edge2 * (1.0f / edge2Length);

    axes[0] = { -edge1.y, edge1.x };
    axes[1] = { -edge2.y, edge2.x };

    edge1 = corners2[1] - corners2[0];
    edge2 = corners2[3] - corners2[0];

    edge1Length = edge1.getLength();
    edge2Length = edge2.getLength();

    if (edge1Length > 0) edge1 = edge1 * (1.0f / edge1Length);
    if (edge2Length > 0) edge2 = edge2 * (1.0f / edge2Length);

    axes[2] = { -edge1.y, edge1.x };
    axes[3] = { -edge2.y, edge2.x };

 
    for (const auto& axis : axes) {

        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::lowest();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::lowest();

        for (const auto& corner : corners1) {
            float projection = dotProduct(corner, axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (const auto& corner : corners2) {
            float projection = dotProduct(corner, axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    return true;
}

std::vector<Vec2> OBB::getCorners() const {
    std::vector<Vec2> corners(4);

    Vec2 tl = { -extents.x, -extents.y };
    Vec2 tr = { extents.x, -extents.y };
    Vec2 br = { extents.x, extents.y };
    Vec2 bl = { -extents.x, extents.y };

    float cosAngle = std::cos(rotation);
    float sinAngle = std::sin(rotation);

    auto rotatePoint = [&](const Vec2& point) -> Vec2 {
        return {
            point.x * cosAngle - point.y * sinAngle,
            point.x * sinAngle + point.y * cosAngle
        };
        };

    corners[0] = rotatePoint(tl) + center;
    corners[1] = rotatePoint(tr) + center;
    corners[2] = rotatePoint(br) + center;
    corners[3] = rotatePoint(bl) + center;

    return corners;
}

AABB OBB::toAABB() const {
    auto corners = getCorners();

    Vec2 min = corners[0];
    Vec2 max = corners[0];

    for (size_t i = 1; i < corners.size(); ++i) {
        min.x = std::min(min.x, corners[i].x);
        min.y = std::min(min.y, corners[i].y);
        max.x = std::max(max.x, corners[i].x);
        max.y = std::max(max.y, corners[i].y);
    }

    return { min, max };
}