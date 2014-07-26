#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <stdio.h>
#include <math.h>

/*
 * A standard 4 component vector
 */
typedef struct vector4f_t {
	float x, y, z, w;
} vector4f_t;

/*
 * Create a vector4
 */
inline vector4f_t vector4f_new(float x, float y, float z, float w){
	vector4f_t v = { .x = x, .y = y, .z = z, .w = w };
	return v;
}
/*
 * Perform the dot product
 */
inline float vector4f_dot(vector4f_t a, vector4f_t b){
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
/*
 * Get the length of the vector
 */
inline float vector4f_length(vector4f_t a){
	return sqrtf(vector4f_dot(a, a));
}
/*
 * Get the normalized version of the vector
 */
inline vector4f_t vector4f_normalize(vector4f_t a){
	float len = vector4f_length(a);
	return vector4f_new(a.x / len, a.y / len, a.z / len, a.w / len);
}
/*
 * Get the homogenized version of the vector
 */
inline vector4f_t vector4f_homogenize(vector4f_t a){
	if (a.w == 0){
		return a;
	}
	return vector4f_new(a.x / a.w, a.y / a.w, a.z / a.w, 1);
}
/*
 * Add two vectors
 */
inline vector4f_t vector4f_add(vector4f_t a, vector4f_t b){
	return vector4f_new(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
/*
 * Subtract two vectors
 */
inline vector4f_t vector4f_sub(vector4f_t a, vector4f_t b){
	return vector4f_new(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
/*
 * Multiply two vectors
 */
inline vector4f_t vector4f_mult(vector4f_t a, vector4f_t b){
	return vector4f_new(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
/*
 * Scale a vector
 */
inline vector4f_t vector4f_scale(vector4f_t a, float s){
	return vector4f_new(a.x * s, a.y * s, a.z * s, a.w * s);
}
/*
 * Test elements of the vectors for equality, if all are
 * equal returns 1, otherwise 0
 */
inline int vector4f_equal(vector4f_t a, vector4f_t b){
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
/*
 * Set the field of a vector based on its numeric index
 * At times it's really useful to treat a vector as an array of
 * floats, this lets us do that
 */
inline void vector4f_set_idx(vector4f_t *v, int i, float val){
	if (i == 0){
		v->x = val;
	}
	else if (i == 1){
		v->y = val;
	}
	else if (i == 2){
		v->z = val;
	}
	else {
		v->w = val;
	}
}
/*
 * Get the field of a vector based on its numeric index
 */
inline float vector4f_get_idx(vector4f_t v, int i){
	if (i == 0){
		return v.x;
	}
	else if (i == 1){
		return v.y;
	}
	else if (i == 2){
		return v.z;
	}
	else {
		return v.w;
	}
}
/*
 * Print a vector 4
 */
inline void vector4f_print(vector4f_t v){
	printf("vector4f (%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w);
}

#endif
