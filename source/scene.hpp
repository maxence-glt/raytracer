#pragma once

#include "camera.h"
#include "hittable_list.h"

struct Scene {
    Scene(hittable_list list, camera cam)
    : world(list), camera(cam) {
        camera.initialize();
    }

    hittable_list world;
    camera camera;
};
