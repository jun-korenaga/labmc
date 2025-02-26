/*
 * parameter.cc
 *
 * Jun Korenaga
 * Summer 2008
 */

#include "labmc_nr.h"
#include "parameter.h"

long Parameter::idum = long(-(abs(1)+1));

Parameter::Parameter(double val, const char* str, bool scaling)
    : distr(0.0, 1.0)
{
    val_ = val;
    min_ = val;
    range_ = 0.0;
    name_ = str;
    is_fixed = true;
    is_scaling = scaling;
    gen.seed(idum);
}

Parameter::Parameter(double min, double max, const char* str, bool scaling)
{
    min_ = min;
    range_ = max-min;
    name_ = str;
    is_fixed = false;
    is_scaling = scaling;
}

void Parameter::randomize()
{
    if (!is_fixed){
	val_ = min_+distr(gen)*range_;
    }
}

