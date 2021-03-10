//
// Created by Mateusz Pysera on 09/03/2021.
//

#ifndef DANTE_PP2_FILE_STRUCT_UTILS_H
#define DANTE_PP2_FILE_STRUCT_UTILS_H

#endif //DANTE_PP2_FILE_STRUCT_UTILS_H

struct point_t;
struct file_t;
int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int load_point_t(const char *filename, struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);
void show(const struct point_t* p);
struct point_t* read(struct point_t* p);
struct point_t* set(struct point_t* p, int x, int y);
