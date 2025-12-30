#include "camera.h"
#include "hittable_list.h"
#include "color.h"
#include "sphere.h"
#include "util/log.hpp"
#include "util/profiler.hpp"
#include "util/random.hpp"
#include "raytracer.hpp"

void many_balls() {
    auto s = sample_start("many_balls init");
    hittable_list world;

    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(Point3f(0,-1000,0), 1000, ground_material));

    int lambertianCount{1}, metalCount{1}, dialectricCount{1};

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Rand::random<Float>();
            Point3f center(a + 0.9*Rand::random<Float>(), 0.2, b + 0.9*Rand::random<Float>());

            if (length(center - Point3f(4, 0.2, 0)) > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    ++lambertianCount;
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = Rand::random<Float>(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    ++metalCount;
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    ++dialectricCount;
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(Point3f(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(Point3f(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(Point3f(4, 1, 0), 1.0, material3));

    LOG_DEBUG("Lambertian count = {}", lambertianCount);
    LOG_DEBUG("Metal count = {}", metalCount);
    LOG_DEBUG("Dialectric count = {}", dialectricCount);

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = Point3f(13,2,3);
    cam.lookat   = Point3f(0,0,0);
    cam.vup      = Vector3f(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    sample_end(s.release());

    cam.render(world);
}
