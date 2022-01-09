# RayTracing
A project about Ray Tracing.
First step was to figure out how the algorithm works and follow the guide and implement it on the CPU, it works currently but its very slow. Takes about 30s to run it at 3/2 aspect ratio with 400 width, 10 depth bouncing and 400 samples per ray after splitting it up to be run in parallel ion different threads.
This is currently implemented in the `main` branch.

Second step is to figure out how compute shaders work and this will be done in a separate branch, `metalRayTracer`.

## Source material
Follows the tutorial [RayTracingInOneWeekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

Follow up tutorial [Metal Ray Tracer](https://sergeyreznik.github.io/metal-ray-tracer/).

## Organization
Will try to follow the tutorial, and split each commit into each segment of the guide, so its easy to go back and look at a specific step.

## Compile metal Shader
```
xcrun -sdk macosx metal -c compute.metal -o compute.air
xcrun -sdk macosx metallib compute.air -o compute.metallib
```

## Goals
- Learn about Ray Tracing.
- Port it over to compute shaders.
- Create a library of it that is reusable.