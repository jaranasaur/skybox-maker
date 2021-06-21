#ifndef VEC_H
#define VEC_H

#define _USE_MATH_DEFINES
#include <math.h>

struct Vec3 {
  Vec3() {
    x = y = z = 0.0f;
  }

  Vec3(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
  }

  float x, y, z;
};

#define vec3Add(v0, v1, vSum) \
vSum.x = v0.x + v1.x;\
vSum.y = v0.y + v1.y;\
vSum.z = v0.z + v1.z;

// subtracts v1 from v0
#define vec3Subtract(v0, v1, vDiff)\
vDiff.x = v0.x - v1.x;\
vDiff.y = v0.y - v1.y;\
vDiff.z = v0.z - v1.z;

#define vec3Scale(v, scale, vScaled)\
vScaled.x = v.x * scale;\
vScaled.y = v.y * scale;\
vScaled.z = v.z * scale;

// hypot
inline float vec3Dist(Vec3 v0, Vec3 v1) {
  Vec3 diff;
  vec3Subtract(v0, v1, diff);
  return sqrtf(
    diff.x * diff.x +
    diff.y * diff.y +
    diff.z * diff.z
  );
}

// VEC_H
#endif