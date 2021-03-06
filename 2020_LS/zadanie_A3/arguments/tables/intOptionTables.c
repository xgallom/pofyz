//
// Created by xgallom on 4/16/20.
//

#include "intOptionTables.h"

const char *IntOptionsTable[INTOPTION_COUNT] = {
#define DEF(name) [INTOPTION_##name] = #name
		DEF(polynomialDegree)
#undef DEF
};

const char *IntOptionsDetailsTable[INTOPTION_COUNT][INTOPTIONS_DETAILS_COUNT] = {
#define DEF(name, desc) [INTOPTION_##name] = {[INTOPTIONS_DETAILS_DESC] = desc}
		DEF(polynomialDegree, "Degree of polynomials to generate to interpolate data")
#undef DEF
};
