//
// Created by Mateusz Pysera on 08/03/2021.
//

#ifndef DANTE_PP2_FILE_UTILS_H
#define DANTE_PP2_FILE_UTILS_H

#endif //DANTE_PP2_FILE_UTILS_H

int file_size_from_path(const char *path);
int file_size_from_file(FILE *f);
void clean_stdin(void);
int read_file(const char *filename);