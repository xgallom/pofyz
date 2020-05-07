//
// Created by xgallom on 3/25/20.
//

#include "stringOptionTables.h"

const char *StringOptionsTable[STRINGOPTION_COUNT] = {
#define DEF(name) [STRINGOPTION_##name] = #name
		DEF(temperature),
		DEF(name),
#undef DEF
};

const char *StringOptionsDetailsTable[STRINGOPTION_COUNT][STRINGOPTIONS_DETAILS_COUNT] = {
#define DEF(name, desc) [STRINGOPTION_##name] = {[STRINGOPTIONS_DETAILS_DESC] = desc}
		DEF(temperature, "Path of a source text file with [x,T] data points"),
		DEF(name, "Name of the simulation"),
#undef DEF
};
