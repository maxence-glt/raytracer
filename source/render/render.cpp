#include "render.hpp"

void render(const Scene &scene) {
    PROFILE_SCOPE("render");

    auto cam = scene.camera;

    std::cout << "P3\n" << cam.image_width << ' ' << cam.image_height << "\n255\n";
    auto t1 = curr_time();

    for (int j = 0; j < cam.image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (cam.image_height - j) << ' ' << std::flush;

        for (int i = 0; i < cam.image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < cam.samples_per_pixel; ++sample) {
                Ray r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, scene.world);
            }
            write_color(std::cout, cam.pixel_samples_scale*pixel_color);
        }
    }

    auto t2 = curr_time();
    auto ms_int = diff_time<milliseconds>(t1, t2);
    std::print(stderr, "\n");
    LOG_VERBOSE("Finished ray tracing in {}ms", ms_int.count());
}
