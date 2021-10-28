#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <fstream>

#include "sphere.h"

void generatePPM() {
    const int image_width = 200;
    const int image_height = 100;

    std::ofstream ofs("ppmImage.ppm");

    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / image_width;
            auto g = double(j) / image_height;
            auto b = 0.2;
            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    ofs.close();
}

void generatePPM_vector() {
    const int image_width = 200;
    const int image_height = 100;

    std::ofstream ofs("ppmImage.ppm");

    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Vector3 color(i * 1.f / image_width, j * 1.f / image_height, 0.2f);

            int ir = static_cast<int>(255.999 * color.x);
            int ig = static_cast<int>(255.999 * color.y);
            int ib = static_cast<int>(255.999 * color.z);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    ofs.close();
}

Vector3 rayColor(Ray ray) {
    float t = (ray.getDirection().getNormalized().y + 1.f) * 0.5f;
    return (1.f - t) * Vector3(1.f) + t * Vector3(0.2f, 0.8f, 1.f);
}

void generatePPM_ray() {
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
            Vector3 color = rayColor(r);

            int ir = static_cast<int>(255.999 * color.x);
            int ig = static_cast<int>(255.999 * color.y);
            int ib = static_cast<int>(255.999 * color.z);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    ofs.close();
}

bool hitSphere(Sphere sphere, Ray ray) {
    Vector3 oc = sphere.getCenter() - ray.getOriginPos();
    auto a = ray.getDirection().dot(ray.getDirection());
    auto b = 2.0 * oc.dot(ray.getDirection());
    auto c = oc.dot(oc) - sphere.getRadiusSqr();
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

Vector3 rayColor_sphere(Ray ray) {
    Sphere sphere(Vector3(0, 0, -1), 0.5f);
    if (hitSphere(sphere, ray))
        return Vector3(1, 0, 0);
    Vector3 vRayDirNormal = ray.getDirection().getNormalized();
    auto t = 0.5f * (vRayDirNormal.y + 1.0f);
    return (1.f - t) * Vector3(1.f) + t * Vector3(0.2f, 0.8f, 1.f);
}

void generatePPM_ray_sphere() {
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
            Vector3 color = rayColor_sphere(r);

            int ir = static_cast<int>(255.999 * color.x);
            int ig = static_cast<int>(255.999 * color.y);
            int ib = static_cast<int>(255.999 * color.z);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    ofs.close();
}

float hitSphere_value(Sphere sphere, Ray ray) {
    Vector3 oc = ray.getOriginPos() - sphere.getCenter();
    auto a = ray.getDirection().dot(ray.getDirection());
    auto b = 2.0 * oc.dot(ray.getDirection());
    auto c = oc.dot(oc) - sphere.getRadiusSqr();
    auto discriminant = b*b - 4*a*c;
    return (discriminant < 0 ? -1.f : ((-b - std::sqrt(discriminant)) / (2.f * a)));
}

Vector3 rayColor_sphere_value(Ray ray) {
    Sphere sphere(Vector3(0, 0, -1), 0.5f);
    float t = hitSphere_value(sphere, ray);
    //qDebug() << t;
    if (t > 0) {
        Vector3 vNormal = (ray.at(t) - Vector3(0,0,-1)).getNormalized();
        return 0.5 * (vNormal + 1.f);
    }
    Vector3 vRayDirNormal = ray.getDirection().getNormalized();
    t = 0.5f * (vRayDirNormal.y + 1.0f);
    return (1.f - t) * Vector3(1.f) + t * Vector3(0.2f, 0.8f, 1.f);
}

void generatePPM_ray_sphere_value() {
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
            Vector3 color = rayColor_sphere_value(r);

            int ir = static_cast<int>(255.999 * color.x);
            int ig = static_cast<int>(255.999 * color.y);
            int ib = static_cast<int>(255.999 * color.z);
            ofs << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    ofs.close();
}


int maint(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //test1
    //generatePPM_vector();

    //test2
    //generatePPM_ray();

    //test3
    //generatePPM_ray_sphere();

    //test4
    generatePPM_ray_sphere_value();
    return a.exec();
}
