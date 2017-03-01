#include "data.h"

Matrix projmatrix = Zeros(4, 4);

double left = -0.5, right = 0.5, bottom = -0.5, top = 0.5;
int nearnum = 1, farnum = 10;
bool projtype = true;