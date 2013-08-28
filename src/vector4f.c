#include "vector4f.h"

extern vector4f_t vector4f_new(float x, float y, float z, float w);
extern float vector4_dot(vector4f_t a, vector4f_t b);
extern float vector4_length(vector4f_t a);
extern vector4f_t vector4_normalize(vector4f_t a);
extern vector4f_t vector4_homogenize(vector4f_t a);
extern vector4f_t vector4_add(vector4f_t a, vector4f_t b);
extern vector4f_t vector4_sub(vector4f_t a, vector4f_t b);
extern vector4f_t vector4_mult(vector4f_t a, vector4f_t b);
extern vector4f_t vector4_scale(vector4f_t a, float s);
extern int vector4_equal(vector4f_t a, vector4f_t b);
