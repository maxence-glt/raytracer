#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "main.h"
#include "material.h"
#include "vec3.h"

struct camera {
    double aspect_ratio = 1.0;
    int    image_width = 100;
    int    image_height;

    int    samples_per_pixel = 10;
    double pixel_samples_scale;

    /*
     * Camera viewing variables
     * vfov - vertical view angle
     * lookfrom/lookat - point camera is looking from/at
     * vup - camera-relative "up" direction
     * u/v/w = camera frame basis vectors
     */
    double vfov = 90;
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = point3(0, 1, 0);
    vec3 u, v, w;

    double defocus_angle = 0;
    double focus_dist = 10;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    point3 center;
    point3 pixel00_loc;

    vec3   pixel_delta_u;
    vec3   pixel_delta_v;

    void render(const hittable &world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        auto t1 = high_resolution_clock::now();

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_samples_scale*pixel_color);
            }
        }

        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        std::clog << "\rFinished ray tracing in " << ms_int.count() << "ms\n";
    }

    void initialize() {
        image_height = std::max(int(image_width / aspect_ratio), 1);
        center = point3(0, 0, 0);
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        // Determine viewport dimensions
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2.0 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

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

        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    int max_depth = 10;

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);
        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_dir = pixel_sample - ray_origin;
        return ray(ray_origin, ray_dir);
    }

    color ray_color(const ray &r0, const hittable& world) const {
        ray r = r0;
        color throughput(1.0, 1.0, 1.0);

        for (int depth = 0; depth < max_depth; ++depth) {
            hit_record rec;
            if (!world.hit(r, interval(0.001, infinity), rec))
                break;

            color attenuation;
            if (!rec.mat->scatter(r, rec, attenuation, r))
                return color(0.0, 0.0, 0.0);

            throughput = throughput * attenuation;
        }

        vec3 unit_direction = unit_vector(r.dir);
        auto a = 0.5*(unit_direction.y() + 1.0);
        color lerp = (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.3, 0.7, 1.0);

        return lerp * throughput;
    }


    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
};


#endif
