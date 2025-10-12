#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3 &center, double radius)
        : center(center), radius(std::fmax(0, radius))
        {}

    bool hit(const ray &r, 
             interval ray_t,
             hit_record &rec) const override {
        vec3 oc = center - r.orig;

        /*
        * Original code
        *
        * auto a = dot(r.dir, r.dir);
        * auto b = -2.0 * dot(r.dir, oc);
        * auto c = dot(oc, oc) - radius*radius;
        * auto discriminant = b*b - 4*a*c;
        */

        auto a = r.dir.lengthSquared();
        auto h = dot(r.dir, oc);
        auto c = oc.lengthSquared() - radius*radius;

        auto discriminant = h*h - a*c;

        if (discriminant < 0) return false;

        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};



#endif
