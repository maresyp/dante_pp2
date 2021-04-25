//
// Created by Mateusz Pysera on 09/03/2021.
//

#ifndef DANTE_PP2_FILE_STRUCT_UTILS_H
#define DANTE_PP2_FILE_STRUCT_UTILS_H

#endif //DANTE_PP2_FILE_STRUCT_UTILS_H
struct point_t { int x; int y; };
struct point_t;
struct file_t;
struct rectangle_t;
struct circle_t;
struct triangle_t;
struct figure_t;

int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int save_points_b(const char *filename, const struct point_t* p, unsigned int N);
int load_point_t(const char *filename, struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);
void show(const struct point_t* p);
struct point_t* read(struct point_t* p);
struct point_t* set(struct point_t* p, int x, int y);

float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);

void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);

int sort_by_area(struct figure_t **figures, int size);

struct file_t;
int open_file(struct file_t* f, const char *filename);
struct file_t* find_min(const struct file_t* files, int size);
void close_file(struct file_t* f);
int file_size_from_file(FILE *f);
