#include <assert.h>
#include <math.h>
#include "matrix4f_stack.h"
#include "vertex_list.h"
#include "microgl.h"
#include "microgl_driver.h"

microgl_driver_t *mgl_active_driver = NULL;

void plot_pixel(unsigned x, unsigned y, float z, vector4f_t *color){
	if (x > mgl_active_driver->width || y > mgl_active_driver->height){
		return;
	}
	//If depth test passes plot it
	if (z < mgl_active_driver->depth_buffer[y * mgl_active_driver->width + x]){
		mgl_active_driver->depth_buffer[y * mgl_active_driver->width + x] = z;
		uint32_t *c = &mgl_active_driver->color_buffer[y * mgl_active_driver->width + x];
		uint8_t r = (uint8_t)(color->x * 255);
		uint8_t g = (uint8_t)(color->y * 255);
		uint8_t b = (uint8_t)(color->z * 255);
		SET_RED(*c, r);
		SET_GREEN(*c, g);
		SET_BLUE(*c, b);
	}
}
/*
 * Get the parametric distance of (x, y) along the line from a to b in 2D
 */
float parametric_coord(const vector4f_t *a, const vector4f_t *b, float x, float y){
	return (a->y - b->y) * x + (b->x - a->x) * y + a->x * b->y - b->x * a->y;
}
/*
 * Rasterize a triangle to the screen
 */
void draw_tri(const vertex_t *a, const vertex_t *b, const vertex_t *c){
	float alpha_denom = parametric_coord(&b->pos, &c->pos, a->pos.x, a->pos.y);
	float beta_denom = parametric_coord(&a->pos, &c->pos, b->pos.x, b->pos.y);
	float gamma_denom = parametric_coord(&a->pos, &b->pos, c->pos.x, c->pos.y);

	int x_min = fminf(fminf(a->pos.x, b->pos.x), c->pos.x);
	int x_max = fmaxf(fmaxf(a->pos.x, b->pos.x), c->pos.x);
	int y_min = fminf(fminf(a->pos.y, b->pos.y), c->pos.y);
	int y_max = fmaxf(fmaxf(a->pos.y, b->pos.y), c->pos.y);
	for (int x = x_min; x < x_max; ++x){
		for (int y = y_min; y < y_max; ++y){
			float alpha = parametric_coord(&b->pos, &c->pos, x, y) / alpha_denom;
			float beta = parametric_coord(&a->pos, &c->pos, x, y) / beta_denom;
			float gamma = parametric_coord(&a->pos, &b->pos, x, y) / gamma_denom;

			if (alpha >= 0 && beta >= 0 && gamma >= 0){
				//Check shared edge
				float a_shared = parametric_coord(&b->pos, &c->pos, 0, 0);
				float b_shared = parametric_coord(&a->pos, &c->pos, 0, 0);
				float g_shared = parametric_coord(&a->pos, &b->pos, 0, 0);
				if ((alpha > 0 || alpha_denom * a_shared > 0)
					&& (beta > 0 || beta_denom * b_shared > 0)
					&& (gamma > 0 || gamma_denom * g_shared > 0))
				{
					float z = a->pos.z * alpha + b->pos.z * beta + c->pos.z * gamma;
					vector4f_t color = vector4f_add(vector4f_add(vector4f_scale(a->color, alpha),
						vector4f_scale(b->color, beta)), vector4f_scale(c->color, gamma));
					plot_pixel(x, y, z, &color);
				}
			}
		}
	}
}
/*
 * Transform the vertices of a triangle into raster space
 * and draw them
 */
void transform_and_draw_tri(vertex_t a, vertex_t b, vertex_t c){
	assert(mgl_active_driver != NULL);
	int w = mgl_active_driver->width;
	int h = mgl_active_driver->height;
	matrix4f_t to_raster = matrix4f_identity();
	to_raster.columns[0] = vector4f_new(w / 2, 0, 0, 0);
	to_raster.columns[1] = vector4f_new(0, h / 2, 0, 0);
	to_raster.columns[3] = vector4f_new((w - 1) / 2, (h - 1) / 2, 0, 1);

	matrix4f_t proj;
	matrix4f_mult(&to_raster, &mgl_active_driver->projection.top->matrix, &proj);
	a.pos = vector4f_homogenize(matrix4f_mult_vec(&proj, a.pos));
	b.pos = vector4f_homogenize(matrix4f_mult_vec(&proj, b.pos));
	c.pos = vector4f_homogenize(matrix4f_mult_vec(&proj, c.pos));
	draw_tri(&a, &b, &c);
}

void mgl_begin(poly_mode mode){
	assert(mgl_active_driver != NULL);
	mgl_active_driver->mode = mode;
}
void mgl_end(){
	assert(mgl_active_driver != NULL);
	//If we're drawing quads then just convert it too two triangles
	if (mgl_active_driver->mode == QUADS){
		vertex_list_push_back(&mgl_active_driver->vertex_list,
			mgl_active_driver->vertex_list.vertices[mgl_active_driver->vertex_list.size - 2]);
		//The first vert is now at size - 4 - 1 since we just pushed one on
		vertex_list_push_back(&mgl_active_driver->vertex_list,
			mgl_active_driver->vertex_list.vertices[mgl_active_driver->vertex_list.size - 5]);
	}
	//Draw the triangles
	for (size_t i = 0; i < mgl_active_driver->vertex_list.size; i += 3){
		transform_and_draw_tri(mgl_active_driver->vertex_list.vertices[i],
			mgl_active_driver->vertex_list.vertices[i + 1],
			mgl_active_driver->vertex_list.vertices[i + 2]);
	}
	mgl_active_driver->mode = NONE;
}
void mgl_vertex2(float x, float y){
	assert(mgl_active_driver != NULL && mgl_active_driver->mode != NONE);
	vector4f_t p = matrix4f_mult_vec(&mgl_active_driver->model_view.top->matrix,
		vector4f_new(x, y, 0, 1));
	vertex_list_push_back(&mgl_active_driver->vertex_list,
		vertex_new(p, mgl_active_driver->active_color));
}
void mgl_vertex3(float x, float y, float z){
	assert(mgl_active_driver != NULL && mgl_active_driver->mode != NONE);
	vector4f_t p = matrix4f_mult_vec(&mgl_active_driver->model_view.top->matrix,
		vector4f_new(x, y, z, 1));
	vertex_list_push_back(&mgl_active_driver->vertex_list,
		vertex_new(p, mgl_active_driver->active_color));
}
void mgl_color(float r, float g, float b){
	assert(mgl_active_driver != NULL);
	mgl_active_driver->active_color = vector4f_new(r, g, b, 1);
}
void mgl_matrix_mode(matrix_mode mode){
	assert(mgl_active_driver != NULL);
	switch (mode){
		case MODELVIEW:
			mgl_active_driver->stack_ptr = &mgl_active_driver->model_view;
			break;
		case PROJECTION:
			mgl_active_driver->stack_ptr = &mgl_active_driver->projection;
			break;
	}
}
void mgl_push_matrix(){
	assert(mgl_active_driver != NULL);
	matrix4f_stack_push(mgl_active_driver->stack_ptr,
		mgl_active_driver->stack_ptr->top->matrix);
}
void mgl_pop_matrix(){
	assert(mgl_active_driver != NULL);
	matrix4f_stack_pop(mgl_active_driver->stack_ptr);
}
void mgl_load_identity(){
	assert(mgl_active_driver != NULL);
	mgl_active_driver->stack_ptr->top->matrix = matrix4f_identity();
}
void mgl_load_matrix(matrix4f_t matrix){
	assert(mgl_active_driver != NULL);
	mgl_active_driver->stack_ptr->top->matrix = matrix;
}
void mgl_translate(float x, float y, float z){
	assert(mgl_active_driver != NULL);
	matrix4f_t t = matrix4f_identity();
	t.columns[3] = vector4f_new(x, y, z, 1);
	matrix4f_t c = matrix4f_new();
	matrix4f_mult(&mgl_active_driver->stack_ptr->top->matrix, &t, &c);
	mgl_active_driver->stack_ptr->top->matrix = c;
}
void mgl_rotate(float angle, float x, float y, float z){
	assert(mgl_active_driver != NULL);
	vector4f_t v = vector4f_normalize(vector4f_new(x, y, z, 0));
	float rad = angle * 3.14 / 180;
	float s = sinf(rad);
	float c = cosf(rad);

	matrix4f_t r = matrix4f_identity();
	r.columns[0] = vector4f_new(powf(v.x, 2) * (1 - c) + c,
		v.y * v.x * (1 - c) + v.z * s,
		v.x * v.z * (1 - c) - v.y * s, 0);
	r.columns[1] = vector4f_new(v.x * v.y * (1 - c) - v.z * s,
		powf(v.y, 2) * (1 - c) + c,
		v.y * v.z * (1 - c) + v.x * s, 0);
	r.columns[2] = vector4f_new(v.x * v.z * (1 - c) + v.y * s,
		v.y * v.z * (1 - c) - v.x * s,
		powf(v.z, 2) * (1 - c) + c, 0);

	matrix4f_t a = matrix4f_new();
	matrix4f_mult(&mgl_active_driver->stack_ptr->top->matrix, &r, &a);
	mgl_active_driver->stack_ptr->top->matrix = a;
}
void mgl_scale(float x, float y, float z){
	assert(mgl_active_driver != NULL);
	matrix4f_t s = matrix4f_identity();
	s.columns[0].x = x;
	s.columns[1].y = y;
	s.columns[2].z = z;
	matrix4f_t c = matrix4f_new();
	matrix4f_mult(&mgl_active_driver->stack_ptr->top->matrix, &s, &c);
	mgl_active_driver->stack_ptr->top->matrix = c;
}
void mgl_frustum(float left, float right, float bottom, float top,
	float near, float far)
{
	assert(mgl_active_driver != NULL);
	matrix4f_t f = matrix4f_identity();

	f.columns[0] = vector4f_new((2 * near) / (right - left), 0, 0, 0);
	f.columns[1] = vector4f_new(0, (2 * near) / (top - bottom), 0, 0);
	f.columns[2] = vector4f_new((right + left) / (right - left),
		(top + bottom) / (top - bottom),
		-(far + near) / (far - near), -1);
	f.columns[3] = vector4f_new(0, 0, -(2 * far * near) / (far - near), 0);

	matrix4f_t c = matrix4f_new();
	matrix4f_mult(&mgl_active_driver->stack_ptr->top->matrix, &f, &c);
	mgl_active_driver->stack_ptr->top->matrix = c;
}
void mgl_ortho(float left, float right, float bottom, float top,
	float near, float far)
{
	assert(mgl_active_driver != NULL);
	matrix4f_t o = matrix4f_identity();

	o.columns[0] = vector4f_new(2 / (right - left), 0, 0, 0);
	o.columns[1] = vector4f_new(0, 2 / (top - bottom), 0, 0);
	o.columns[2] = vector4f_new(0, 0, -2 / (far - near), 0);
	o.columns[3] = vector4f_new(-(right + left) / (right - left),
		-(top + bottom) / (top - bottom),
		-(far + near) / (far - near), 1);

	matrix4f_t c = matrix4f_new();
	matrix4f_mult(&mgl_active_driver->stack_ptr->top->matrix, &o, &c);
	mgl_active_driver->stack_ptr->top->matrix = c;
}

