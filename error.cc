/*
 * error.cc
 *
 * Jun Korenaga, MIT/WHOI
 * January 1999
 */

#include <iostream>
#include <cstdlib>
#include "error.h"

void error(const std::string& s)
{
    std::cerr << s << '\n';
    exit(1);
}

