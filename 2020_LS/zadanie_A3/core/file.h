//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_FILE_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_FILE_H

#include <stdio.h>

FILE *file(const char *filePath, const char *flags);
FILE *rootFile(const char *filePath, const char *flags);
void close(FILE *file);

size_t lineCount(FILE *file);
fpos_t filePosition(FILE *file);
void setFilePosition(FILE *file, const fpos_t *position);

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_FILE_H
