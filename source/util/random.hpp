#pragma once

#include <random>

template <typename T>
class Random {
public:
    Random(T min = (T)0, T max = (T)1)
    : prng(get_engine()), dis(min, max) 
    {/* empty ctor */}

    inline T random() { return dis(prng); }

private:
    using eng = std::mt19937_64;

    static eng& get_engine() {
        static thread_local eng engine{ std::random_device{}() };
        return engine;
    }

    eng& prng;
    std::uniform_real_distribution<T> dis;
};
