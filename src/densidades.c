#include <math.h>
#include "densidades.h"

double densidad_constante(double x, double y, double z) {
    return 1.0;
}

double densidad_lineal(double x, double y, double z,
                       double a, double b, double c) {
    return a * x + b * y + c * z;
}

double densidad_gaussiana(double x, double y, double z) {
    return exp(-(x*x + y*y + z*z));
}

