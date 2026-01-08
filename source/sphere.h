#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.hpp"
#include "util/vecmath.hpp"

class sphere : public hittable {
public:
    sphere(const Point3f &center, float radius, std::shared_ptr<material> mat)
        : center(center), radius(std::fmax(0, radius)), mat(mat)
        {}

    bool hit(const Ray &r, 
             interval ray_t,
             hit_record &rec) const override {
        Vector3f oc = center - r.o;

        auto a = lengthSquared(r.d);
        auto b = dot(r.d, oc);
        auto c = lengthSquared(oc) - radius*radius;

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
        Normal3f outward_normal = Normal3f(rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    Point3f center;
    float radius;
    std::shared_ptr<material> mat;
};



#endif
