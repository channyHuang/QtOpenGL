#ifndef SPHERE_H
#define SPHERE_H

#include "hitResult.h"

class Sphere
{
public:
    Sphere() {};
    Sphere(const Vector3 &vCenter, float fRadius)
        : m_vCenter(vCenter), m_fRadius(fRadius) {}
    ~Sphere() {}

    Vector3 getCenter() { return m_vCenter; }
    float getRadius() { return m_fRadius; }

    float getRadiusSqr() { return m_fRadius * m_fRadius; }

    virtual bool hit(Ray ray, float fmin, float fmax, HitResult &hitResult);

private:
    Vector3 m_vCenter;
    float m_fRadius;
};

#endif // SPHERE_H
