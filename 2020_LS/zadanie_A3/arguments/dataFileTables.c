//
// Created by xgallom on 3/25/20.
//

#include "dataFileTables.h"

const char *DataFilesTable[DATAFILE_COUNT] = {
#define DEF(dataFile) [DATAFILE_##dataFile] = #dataFile
		DEF(temperature)
#undef DEF
};

const char *DataFilesDetailsTable[DATAFILE_COUNT][DATAFILES_DETAILS_COUNT] = {
#define DEF(dataFile, desc) [DATAFILE_##dataFile] = {desc}
		DEF(temperature, "Source for a text file with [x,T] data points")
#undef DEF
};
