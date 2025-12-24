raytracer

image examples are in the images directory

what i made (from scratch :P) so far:

call stack profiler

```
~/C/P/P/raytracer/source main ❱ make render
./compiledCode  > ../images/"image.ppm"
[ 0 main.cpp:9 ] Starting raytracing:
[ 0.267 ./camera.h:67 ] Finished ray tracing in 267ms

-------------------------------------------------------------------
  name                             calls            sec      prop
-------------------------------------------------------------------
  main                                1          0.268    100.00%
    many_balls init                   1          0.000      0.02%
    render                            1          0.268     99.97%
      initialize                      1          0.000      0.00%
      get_ray                     90000          0.004      1.45%
      ray_color                   90000          0.221     82.45%
        ray_color::hit           241284          0.198     73.79%
        lambertian::scatter      102282          0.007      2.50%
        dielectric::scatter       15587          0.001      0.25%
        metal::scatter            33549          0.002      0.91%
      write_color                 90000          0.034     12.58%
-------------------------------------------------------------------

[ 0.267 main.cpp:22 ] Finished render succesfully, shutting down logging

******************************************************
```

logger (imagine that DEBUG/WARNING/ERROR/FATAL are displayed in green/yellow/red/red) writes to stderr and a log file if specified

```
[ 0 main.cpp:9 ] Starting raytracing:
[ 0 util/log.cpp:102 ] testing log verbose
[ 0 util/log.cpp:103 ] DEBUG testing log debug
[ 0 util/log.cpp:104 ] WARNING testing log warning
[ 0 util/log.cpp:105 ] ERROR testing log error
[ 0 util/log.cpp:106 ] FATAL testing log fatal
```

errors and stack trace printing

```
[ 0 util/error.cpp:46 ] WARNING : util/error.cpp:86:10: warning (with loc): file='util/error.cpp' line=86 col=10
stack trace:
1   compiledCode    0x0000000100cef47c        processError(ErrorLevel, FileLoc const*, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const&) + 328
2   compiledCode    0x0000000100cef94c        void warning<std::__1::basic_string_view<char, std::__1::char_traits<char>>&, int&, int&>(FileLoc const*, std::__1::basic_format_string<char, std::__1::type_identity<std::__1::basic_string_view<char, std::__1::char_traits<char>>&>::type, std::__1::type_identity<int&>::type, std::__1::type_identity<int&>::type>, std::__1::basic_string_view<char, std::__1::char_traits<char>>&, int&, int&) + 288
3   compiledCode    0x0000000100cef7c0        testErrors() + 128
4   compiledCode    0x0000000100cdc858        main + 100
5   dyld            0x0000000181dceb98        start + 6076

[ 0 util/error.cpp:48 ] ERROR : error (no loc): test 2
stack trace:
1   compiledCode    0x0000000100cef47c        processError(ErrorLevel, FileLoc const*, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const&) + 328
2   compiledCode    0x0000000100cf1400        void error<char const (&) [5], int>(FileLoc const*, std::__1::basic_format_string<char, std::__1::type_identity<char const (&) [5]>::type, std::__1::type_identity<int>::type>, char const (&) [5], int&&) + 320
3   compiledCode    0x0000000100cef7e8        testErrors() + 168
4   compiledCode    0x0000000100cdc858        main + 100
```
5   dyld            0x0000000181dceb98        start + 6076

and smaller things like custom asserts that combine multiple of the above features
