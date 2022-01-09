
#include <metal_stdlib>
using namespace metal;

kernel void add(const device float2 *in [[ buffer(0) ]],
                device float  *out [[ buffer(1) ]],
                uint id [[ thread_position_in_grid ]]) {
  float x = in[id].x;
  float y = in[id].y;
  out[id] = x + y;
}