#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include "interval.h"
#include "util/vecmath.hpp"
#include "ray.hpp"
#include "raytracer.hpp"

class material;

struct hit_record {
    Point3f p;
    Normal3f normal;
    std::shared_ptr<material> mat;
    Float t;
    bool front_face;

    void set_face_normal(const Ray &r, const Normal3f &outward_normal) {
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(r.d, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

struct hittable {
    virtual ~hittable() = default;
    virtual bool hit(const Ray &r, 
                     interval ray_t,
                     hit_record &rec) const = 0;
};

#endif
