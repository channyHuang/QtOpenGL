#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

class Vector3
{
public:
    union {
        struct {
            float x, y, z;
        };
        float data[3];
    };

    Vector3() : x(0), y(0), z(0) {}
    Vector3(const float v) : x(v), y(v), z(v) {}
    Vector3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
    ~Vector3() {}

    inline float &operator[](const int axis) {
        return data[axis];
    }

    inline const float &operator[](const int axis) const {
        return data[axis];
    }

    void operator=(const Vector3 &v) { x = v.x; y = v.y; z = v.z; }

    Vector3 operator+(const Vector3 &v) {
        return Vector3 (x + v.x, y + v.y, z + v.z);
    }

    Vector3 &operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3 operator-(const Vector3 &v) {
        return Vector3 (x - v.x, y - v.y, z - v.z);
    }

    Vector3 &operator -= (const Vector3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    Vector3 operator/(const Vector3 &v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) return *this;
        return Vector3 (x / v.x, y / v.y, z / v.z);
    }

    Vector3 operator*(const Vector3 &v) {
        return Vector3 (x * v.x, y * v.y, z * v.z);
    }

    Vector3 operator+(const float v) {
        return *this + Vector3(v);
    }

    Vector3 operator-(const float v) {
        return *this - Vector3(v);
    }

    Vector3 operator/(const float v) {
        return *this / Vector3(v);
    }

    Vector3 operator*(const float v) {
        return *this * Vector3(v);
    }

    float dot(const Vector3 &v) const {
        return (x * v.x + y * v.y + z * v.z);
    }

    Vector3 cross(const Vector3 &v) {
        return Vector3(y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x);
    }

    float volumn() {
        return x * y * z;
    }

    float len() {
        return std::sqrt(x * x + y * y + z * z);
    }

    float lenSqr() const {
        return (x * x + y * y + z * z);
    }

    float distanceTo(const Vector3 &v) {
        return (*this - v).len();
    }

    void normalize() {
        float length = this->len();
        if (length == 0) length = 1.0f;
        x /= length;
        y /= length;
        z /= length;
    }

    std::string toString() {
        std::string str = "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        return str;
    }

    friend Vector3 operator*(const float k, const Vector3 &p)
    {
        return Vector3(k * p.x, k * p.y, k * p.z);
    }

    friend Vector3 operator/(const float k, const Vector3 &p) {
        return Vector3(k / p.x, k / p.y, k / p.z);
    }
};
