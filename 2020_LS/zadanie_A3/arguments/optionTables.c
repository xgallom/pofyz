//
// Created by xgallom on 4/16/20.
//

#include "optionTables.h"

const char *OptionsTable[OPTION_COUNT] = {
#define DEF(option) [OPTION_##option] = #option
		DEF(polynomialDegree)
#undef DEF
};

const char *OptionsDetailsTable[OPTION_COUNT][OPTIONS_DETAILS_COUNT] = {
#define DEF(option, desc) [OPTION_##option] = {desc}
		DEF(polynomialDegree, "Degree of polynomials to generate to interpolate data")
#undef DEF
};
