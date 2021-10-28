#include "sphere.h"

bool Sphere::hit(Ray ray, float fmin, float fmax, HitResult &hitResult) {
    Vector3 oc = ray.getOriginPos() - getCenter();
    auto a = ray.getDirection().dot(ray.getDirection());
    auto b = 2.0 * oc.dot(ray.getDirection());
    auto c = oc.dot(oc) - getRadiusSqr();
    auto discriminant = b*b - 4*a*c;

    if (discriminant > 0) {
        auto fDist = (-b - std::sqrt(discriminant)) / (2.f * a);
        if (fDist > fmin && fDist < fmax) {
            hitResult.m_fDist = fDist;
            hitResult.m_vPoint = ray.at(fDist);
            //hitResult.m_vNormal = (hitResult.m_vPoint - getCenter()) / getRadius();
            Vector3 outward_normal = (hitResult.m_vPoint - getCenter()) / getRadius();
            hitResult.set_face_normal(ray, outward_normal);
            return true;
        }
        fDist = (-b + std::sqrt(discriminant)) / (2.f * a);
        if (fDist > fmin && fDist < fmax) {
            hitResult.m_fDist = fDist;
            hitResult.m_vPoint = ray.at(fDist);
            //hitResult.m_vNormal = (hitResult.m_vPoint - getCenter()) / getRadius();
            Vector3 outward_normal = (hitResult.m_vPoint - getCenter()) / getRadius();
            hitResult.set_face_normal(ray, outward_normal);
            return true;
        }
    }
    return false;
}
