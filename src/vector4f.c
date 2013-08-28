#include "vector4f.h"

extern vector4f_t vector4f_new(float x, float y, float z, float w);
extern float vector4f_dot(vector4f_t a, vector4f_t b);
extern float vector4f_length(vector4f_t a);
extern vector4f_t vector4f_normalize(vector4f_t a);
extern vector4f_t vector4f_homogenize(vector4f_t a);
extern vector4f_t vector4f_add(vector4f_t a, vector4f_t b);
extern vector4f_t vector4f_sub(vector4f_t a, vector4f_t b);
extern vector4f_t vector4f_mult(vector4f_t a, vector4f_t b);
extern vector4f_t vector4f_scale(vector4f_t a, float s);
extern int vector4f_equal(vector4f_t a, vector4f_t b);
extern void vector4f_set_idx(vector4f_t *v, int i, float val);
extern float vector4f_get_idx(vector4f_t v, int i);
extern void vector4f_print(vector4f_t v);
