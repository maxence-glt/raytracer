#pragma once

#include "hittable.h"
#include "ray.hpp"
#include "util/vecmath.hpp"

struct Body {
    Point3f center;
    Float radius;
};

struct Spheres {
    std::vector<Body> centers;
    std::vector<std::shared_ptr<material>> materials;
};

inline bool hit(const Body &sphere, const Ray &r, 
         const interval &ray_t, hit_record &rec) {
    Vector3f oc = sphere.center - r.o;
    auto a = lengthSquared(r.d);
    auto b = dot(r.d, oc);
    auto c = lengthSquared(oc) - sphere.radius*sphere.radius;

    auto discriminant = b*b - a*c;

    if (discriminant < 0) return false;

    auto sqrtd = std::sqrt(discriminant);
    auto root = (b - sqrtd) / a;

    if (!ray_t.surrounds(root)) {
        root = (b + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r(rec.t);
    Normal3f outward_normal = Normal3f(rec.p - sphere.center) / sphere.radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
