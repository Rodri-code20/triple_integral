	#ifndef DENSIDADES_H
#define DENSIDADES_H

/* Tipos de densidad:
 * 1 -> constante: rho(x,y,z) = 1
 * 2 -> lineal:    rho(x,y,z) = a x + b y + c z
 * 3 -> gaussiana: rho(x,y,z) = exp( -(x^2 + y^2 + z^2) )
 */

double densidad_constante(double x, double y, double z);

double densidad_lineal(double x, double y, double z,
                       double a, double b, double c);

double densidad_gaussiana(double x, double y, double z);

#endif

