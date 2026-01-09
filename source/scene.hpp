#pragma once

#include "camera.h"
#include "sphere.h"

struct Scene {
    Scene(Spheres list, camera cam)
    : world(list), camera(cam) {
        camera.initialize();
    }

    Spheres world;
    camera camera;
};
