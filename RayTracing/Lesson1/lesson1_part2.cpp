#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <fstream>

#include "sphere.h"

Vector3 rayColor_hitResult(Ray ray) {
    Sphere sphere(Vector3(0, 0, -1), 0.5f);
    HitResult hitResult;
    bool bHit = sphere.hit(ray, 0, 1, hitResult);
    if (bHit) {
        return hitResult.m_vNormal;
    }
    Vector3 vRayDirNormal = ray.getDirection().getNormalized();
    float t = 0.5f * (vRayDirNormal.y + 1.0f);
    return (1.f - t) * Vector3(1.f) + t * Vector3(0.2f, 0.8f, 1.f);
}


void generatePPM_hitResult() {
    const int image_width = 200;
    const int image_height = 100;

    std::ofstream ofs("ppmImage.ppm");

    ofs << "P3\n" << image_width << " " << image_height << "\n255\n";
    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            Vector3 color = rayColor_hitResult(r);

            int ir = static_cast<int>(255.999 * color.x);
            int ig = static_cast<int>(255.999 * color.y);
            int ib = static_cast<int>(255.999 * color.z);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    ofs.close();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //test4
    generatePPM_hitResult();
    return a.exec();
}
