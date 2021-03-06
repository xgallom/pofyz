//
// Created by xgallom on 3/25/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_ROOTPATH_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_ROOTPATH_H

#include "vector.h"

#define PROGRAM_NAME_INDEX 0
#define PROGRAM_NAME "2020_LS_zadanie_A3"

void initializeRootPath(int argc, char *argv[]);
void cleanupRootPath(void);

const char *rootPath(void);
struct Vector pathFor(const char *relativePath);

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_ROOTPATH_H
