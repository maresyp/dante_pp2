#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_struct_utils.h"

struct point_t {
    int x;
    int y;
};
struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};
struct circle_t
{
    struct point_t c;
    float r;
};
struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};
enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};
struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

int main(){
    /*
    struct figure_t figures[] = { { .type = TRIANGLE, .triangle = { .p1 = { -15, 16 }, .p2 = { -5, 2 }, .p3 = { -19, -11 } } }, { .type = RECTANGLE, .rect = { .p = { 5, 0 }, .width = 26, .height = 25 } }, { .type = CIRCLE, .circ = { .c = { -9, 5 }, .r = 25.21297299176959 } } };
    struct figure_t *ptr[3];

    for (int i = 0; i < 3; ++i)
        ptr[i] = &figures[i];
    int res = sort_by_area(ptr, 3);
    */
    struct figure_t figures[50];
    struct figure_t *ptr[50];
    int arr_size = 0;

    for (int i = 0; i < 50; ++i) {
        int tmp;
        if (scanf("%d", &tmp) != 1) {
            printf("Incorrect input");
            return 1;
        } else {
            if (tmp == 0) break;
            switch (tmp) {
                case 1:
                    printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3):");
                    struct figure_t figure;
                    figure.type = TRIANGLE;
                    struct triangle_t triangle;
                    if (scanf("%d %d %d %d %d %d",
                              &triangle.p1.x,
                              &triangle.p1.y,
                              &triangle.p2.x,
                              &triangle.p2.y,
                              &triangle.p3.x,
                              &triangle.p3.y ) != 6) {
                        printf("Incorrect input");
                        return 1;
                    } else {
                        // TODO: add Triangle to figures
                        figure.triangle = triangle;
                        *ptr = &figure;
                        arr_size++;
                    }
                    break;
                case 2:
                    printf("Enter coordinates of a rectangle along with its dimensions (x y width height):");
                    struct rectangle_t rectangle;
                    if (scanf("%d %d %d %d",
                              &rectangle.p.x,
                              &rectangle.p.y,
                              &rectangle.width,
                              &rectangle.height ) != 4) {
                        printf("Incorrect input");
                        return 1;
                    } else {
                        // TODO: add rectangle to figures
                        arr_size++;
                    }
                    break;
                case 3:
                    printf("Enter coordinates and radius of a circle:");
                    struct circle_t circle;
                    if (scanf("%d %d %f",
                              &circle.c.x,
                              &circle.c.y,
                              &circle.r ) != 3) {
                        printf("Incorrect input");
                        return 1;
                    } else {
                        // TODO: add circle to figures
                        arr_size++;
                    }
                default: break;
            }
        }
    }
    // TODO: check for correct data and sort
    // TODO: print all figures in sorted order
    return 0;
}
