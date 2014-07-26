#ifndef MICROGL_H
#define MICROGL_H

#include "matrix4f.h"

/*
 * Matrix mode options
 */
typedef enum matrix_mode {
	MODELVIEW, PROJECTION
} matrix_mode;
/*
 * Supported primitives
 */
typedef enum poly_mode {
	TRIANGLES, QUADS
} poly_mode;

/*
 * Initialize minigl and specify the width and height
 * of the surface to render too
 */
void mgl_init(int w, int h);
/*
 * Start specifying the vertices for a group of primitives
 * of type mode
 */
void mgl_begin(poly_mode mode);
/*
 * Stop specifying vertices for a group of primitives
 */
void mgl_end();
/*
 * Specify the x and y coordinates of a vertex, z is taken to be 0
 */
void mgl_vertex2(float x, float y);
/*
 * Specify the x, y and z coordinates of a vertex
 */
void mgl_vertex3(float x, float y, float z);
/*
 * Set the current color for vertices
 */
void mgl_color(float r, float g, float b);
/*
 * Set the current matrix mode
 */
void mgl_matrix_mode(matrix_mode mode);
/*
 * Push a copy of the current matrix onto
 * the active matrix stack
 */
void mgl_push_matrix();
/*
 * Pop a matrix of the top of the active matrix stack
 */
void mgl_pop_matrix();
/*
 * Replace the current matrix of the active stack
 * with the identity
 */
void mgl_load_identity();
/*
 * Replace the current matrix of the active stack
 * with the matrix passed
 */
void mgl_load_matrix(matrix4f_t matrix);
/*
 * Multiply the current matrix with the translation matrix
 * to move by x, y, z
 */
void mgl_translate(float x, float y, float z);
/*
 * Multiply the current matrix by the rotation matrix to
 * rotate by angle degrees about the axis defined by x, y, z
 */
void mgl_rotate(float angle, float x, float y, float z);
/*
 * Multiply the current matrix by the scaling matrix to
 * scale the x, y, z axes by the given factors
 */
void mgl_scale(float x, float y, float z);
/*
 * Multiply the current matrix by the perspective projection
 * matrix with the given clipping planes
 */
void mgl_frustum(float left, float right, float bottom, float top,
		float near, float far);
/*
 * Multiply the current matrix by the orthographic projection
 * matrix with the given clipping planes
 */
void mgl_ortho(float left, float right, float bottom, float top,
		float near, float far);

#endif

