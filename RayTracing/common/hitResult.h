#ifndef HITRESULT_H
#define HITRESULT_H

#include "vector3.h"
#include "ray.h"

struct HitResult {
    Vector3 m_vPoint;
    Vector3 m_vNormal;
    float m_fDist;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vector3& outward_normal) {
        front_face = r.getDirection().dot(outward_normal) < 0;
        m_vNormal = front_face ? outward_normal : Vector3(0) -outward_normal;
    }
};

#endif // HITRESULT_H
