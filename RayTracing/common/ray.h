#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray
{
public:
    Ray() {}
    Ray(const Vector3 &vOriginPos, const Vector3 &vDir)
        : m_vOriginPos(vOriginPos), m_vDir(vDir) {}
    ~Ray() {}

    Vector3 getOriginPos() const { return m_vOriginPos; }
    Vector3 getDirection() const { return m_vDir; }
    Vector3 at(float t) { return m_vOriginPos + t * m_vDir; }
private:
    Vector3 m_vOriginPos, m_vDir;
};

#endif // RAY_H
