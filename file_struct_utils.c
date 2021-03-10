//
// Created by Mateusz Pysera on 09/03/2021.
//
#include <stdio.h>
#include <math.h>

struct point_t {
    int x;
    int y;
};

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

struct file_t {
    FILE *f;
    int size;
};

