//
// Created by xgallom on 3/25/20.
//

#include "stringOptionTables.h"

const char *StringOptionsTable[STRINGOPTION_COUNT] = {
#define DEF(option) [STRINGOPTION_##option] = #option
		DEF(temperature),
		DEF(name),
#undef DEF
};

const char *StringOptionsDetailsTable[STRINGOPTION_COUNT][STRINGOPTIONS_DETAILS_COUNT] = {
#define DEF(option, desc) [STRINGOPTION_##option] = {desc}
		DEF(temperature, "Path of a source text file with [x,T] data points"),
		DEF(name, "Name of the simulation"),
#undef DEF
};
