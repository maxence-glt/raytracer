#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"
#include "util/profiler.hpp"
#include "util/vecmath.hpp"
#include "util/timing.hpp"
#include "util/log.hpp"
#include "util/math.hpp"
#include <iostream>

struct camera {
    Float  aspect_ratio = 1.0;
    int    image_width = 100;
    int    image_height;

    int    samples_per_pixel = 10;
    Float  pixel_samples_scale;

    /*
     * Camera viewing variables
     * vfov - vertical view angle
     * lookfrom/lookat - point camera is looking from/at
     * vup - camera-relative "up" direction
     * u/v/w = camera frame basis vectors
     */
    Float vfov = 90;
    Point3f lookfrom{0, 0, 0};
    Point3f lookat{0, 0, -1};
    Vector3f vup{0, 1, 0};
    Vector3f u, v, w;

    Float defocus_angle = 0;
    Float focus_dist = 10;
    Vector3f defocus_disk_u;
    Vector3f defocus_disk_v;

    Point3f center;
    Point3f pixel00_loc;

    Vector3f pixel_delta_u;
    Vector3f pixel_delta_v;

    void render(const hittable &world) {
        PROFILE_SCOPE("render");
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        auto t1 = curr_time();

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_samples_scale*pixel_color);
            }
        }

        auto t2 = curr_time();
        auto ms_int = diff_time<milliseconds>(t1, t2);
        std::print(stderr, "\n");
        LOG_VERBOSE("Finished ray tracing in {}ms", ms_int.count());
    }

    void initialize() {
        PROFILE_SCOPE("initialize");
        image_height = std::max(int(image_width / aspect_ratio), 1);
        center = Point3f(0, 0, 0);
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        // Determine viewport dimensions
        auto theta = radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2.f * h * focus_dist;
        auto viewport_width = viewport_height * (Float(image_width)/image_height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel
        auto viewport_upper_left = center 
                                   - (focus_dist * w)
                                   - viewport_u/2
                                   - viewport_v/2;

        pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
        auto defocus_radius = focus_dist * std::tan(radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    int max_depth = 10;

    Ray get_ray(int i, int j) const {
        PROFILE_SCOPE("get_ray");
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                            + ((i + offset.x) * pixel_delta_u)
                            + ((j + offset.y) * pixel_delta_v);
        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_dir = pixel_sample - ray_origin;
        return Ray(ray_origin, ray_dir);
    }

    color ray_color(const Ray &r0, const hittable &world) const {
        PROFILE_SCOPE("ray_color");
        Ray r = r0;
        color throughput(1.0, 1.0, 1.0);

        for (int depth = 0; depth < max_depth; ++depth) {
            hit_record rec;
            auto s = sample_start("ray_color::hit");
            if (!world.hit(r, interval(0.001, infinity), rec))
                break;
            sample_end(s.release());

            color attenuation;
            auto s2 = sample_start("ray_color::scatter");
            if (!rec.mat->scatter(r, rec, attenuation, r))
                return color(0.0, 0.0, 0.0);
            sample_end(s2.release());

            throughput *= attenuation;
        }

        Vector3f unit_direction = unit_vector(r.d);
        Float t = 0.5*(unit_direction.y + 1.0);
        color lerp = (1.f - t)*color(1.0, 1.0, 1.0) + t*color(0.3, 0.7, 1.0);

        return lerp * throughput;
    }


    Vector3f sample_square() const {
        return Vector3f(Rand::random<Float>() - 0.5, Rand::random<Float>() - 0.5, 0);
    }

    Point3f defocus_disk_sample() const {
        auto p = random_in_unit_disk<Float>();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
};


#endif
