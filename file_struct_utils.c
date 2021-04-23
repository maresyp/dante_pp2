//
// Created by Mateusz Pysera on 09/03/2021.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct point_t { int x; int y; };

struct point_t* set(struct point_t* p, int x, int y) {
    if (p == NULL) return NULL;
    p->x = x;
    p->y = y;
    return p;
}

struct point_t* read(struct point_t* p) {
    if (p == NULL) return NULL;
    int x, y;
    if (scanf("%d %d", &x, &y) != 2) {
        return NULL;
    }
    return set(p, x, y);
}
void show(const struct point_t* p) {
    if (p == NULL) return;
    printf("%d %d", p->x, p->y);
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code) {
    if (err_code != NULL) *err_code = 0;
    if (p1 == NULL || p2 == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    return (float)sqrt(pow((p2->x - p1->x), 2) + pow((p2->y - p1->y), 2));
}


int save_point_b(const char *filename, const struct point_t* p) {
    if (filename == NULL || p == NULL) return 1;
    FILE *fp; fp = fopen(filename, "wb");
    if (fp == NULL) return 2;
    if (fwrite(p, sizeof(struct point_t), 1, fp) != 1) {
        fclose(fp);
        return 3;
    }
    fclose(fp);
    return 0;
}
int load_point_b(const char *filename, struct point_t* p) {
    if (filename == NULL || p == NULL) return 1;
    FILE *fp; fp = fopen(filename, "rb");
    if (fp == NULL) return 2;
    if (fread(p, sizeof(struct point_t), 1, fp) != 1) {
        fclose(fp);
        return 3;
    }
    fclose(fp);
    return 0;
}
int save_point_t(const char *filename, const struct point_t* p) {
    if (filename == NULL || p == NULL) return 1;
    FILE *fp; fp = fopen(filename, "w");
    if (fp == NULL) return 2;
    if (fprintf(fp, "%d %d", p->x, p->y) < 0) {
        fclose(fp);
        return 3;
    }
    fclose(fp);
    return 0;
}
int load_point_t(const char *filename, struct point_t* p) {
    if (filename == NULL || p == NULL) return 1;
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) return 2;
    if (fscanf(fp, "%d %d", &p->x, &p->y) != 2) {
        fclose(fp);
        return 3;
    }
    fclose(fp);
    return 0;
}

struct file_t { FILE *f; int size; };
struct rectangle_t { struct point_t p; int width; int height; };
struct circle_t { struct point_t c; float r; };
struct triangle_t { struct point_t p1; struct point_t p2; struct point_t p3; };
enum figure_types{ TRIANGLE = 1, RECTANGLE, CIRCLE };
struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

float area_triangle(const struct triangle_t *t) {
    if (t == NULL) return -1;
    float ob = (float)(0.5 * abs((t->p2.x - t->p1.x) * (t->p3.y - t->p1.y) - (t->p2.y - t->p1.y) * (t->p3.x - t->p1.x)));
    if (ob == 0) return -1; else return ob;
}
float area_rectangle(const struct rectangle_t *r) {
    if (r == NULL || r->height < 0 || r->width < 0) return -1;
    float ob = (float)(r->width * r->height);
    if (ob == 0) return -1; else return ob;
}
float area_circle(const struct circle_t *c) {
    if (c == NULL || c->r <= 0) return -1;
    return (float)(M_PI * pow(c->r, 2));
}
float area_figure(const struct figure_t *f) {
    if (f == NULL) return -1;
    switch (f->type) {
        case TRIANGLE:
            return area_triangle(&f->triangle);
        case RECTANGLE:
            return area_rectangle(&f->rect);
        case CIRCLE:
            return area_circle(&f->circ);
        default:
            return -1;
    }
}

void display_rectangle(const struct rectangle_t *rect) {
    if (rect != NULL) {
        printf("Rectangle (%d, %d), width = %d, height = %d", rect->p.x, rect->p.y, rect->width, rect->height);
    }
}
void display_triangle(const struct triangle_t *t) {
    if (t != NULL) {
        printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
    }
}
void display_circle(const struct circle_t *circ) {
    if (circ != NULL) {
        printf("Circle (%d, %d), radius = %f", circ->c.x, circ->c.y, circ->r);
    }
}
void display_figure(struct figure_t *f) {
    if (f == NULL) return;
    switch (f->type) {
        case TRIANGLE:
            display_triangle(&f->triangle); break;
        case RECTANGLE:
            display_rectangle(&f->rect); break;
        case CIRCLE:
            display_circle(&f->circ); break;
    }
}

int cmp(const void * a, const void * b) {
    float area_a = area_figure(* (struct figure_t **) a);
    float area_b = area_figure(* (struct figure_t **) b);
    if (area_a > area_b) return -1;
    if (area_a == area_b) return 0;
    if (area_a < area_b) return 1;
    return 0;
}
int sort_by_area(struct figure_t **figures, int size) {
    if (figures == NULL || size <= 0) return 1;
    for (int i = 0; i < size; ++i) {
        float res = area_figure(* (struct figure_t **) (figures + i));
        if (res == -1) return 1;
    }
    qsort(figures, size, sizeof(struct figure_t *), cmp);
    return 0;
}

int file_size_from_file(FILE *f) {
    if (f == NULL) { return -2; }
    int start_pos = (int)ftell(f);
    fseek(f, 0, SEEK_END);
    int len = (int)ftell(f);
    fseek(f, start_pos, SEEK_SET);
    return len;
}
int open_file(struct file_t* f, const char *filename) {
    if (f == NULL || filename == NULL) return 1;
    FILE *fp; fp = fopen(filename, "a");
    if (fp == NULL) return 2;
    f->f = fp;
    f->size = file_size_from_file(fp);
    return 0;
}
struct file_t* find_min(const struct file_t* files, int size) {
    if (files == NULL || size <= 0) return NULL;
    int min = 0;
    for (int i = 0; i < size; ++i) {
        if ((files + min)->size > (files + i)->size) min = i;
    }
    return (struct file_t *)(files + min);
}
void close_file(struct file_t* f) {
    if (f != NULL)
        if (f->f != NULL) fclose(f->f);
}



