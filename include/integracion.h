#ifndef INTEGRACION_H
#define INTEGRACION_H

/* tipo_densidad:
 * 1 -> constante
 * 2 -> lineal
 * 3 -> gaussiana
 *
 * a,b,c sólo se usan en el caso lineal.
 */

/* Método de Riemann tridimensional.
 * Divide el bloque [xmin,xmax]x[ymin,ymax]x[zmin,zmax] en
 * Nx, Ny, Nz subintervalos y evalúa en los centros.
 *
 * Devuelve:
 *  - masa total en *masa
 *  - coordenadas del centro de masa en *x_bar, *y_bar, *z_bar
 */
int integrar_riemann(int tipo_densidad,
                     double a, double b, double c,
                     double xmin, double xmax,
                     double ymin, double ymax,
                     double zmin, double zmax,
                     int Nx, int Ny, int Nz,
                     double *masa,
                     double *x_bar, double *y_bar, double *z_bar);

/* Método de Monte Carlo.
 * Genera N puntos aleatorios dentro del bloque y usa el promedio.
 *
 * n_muestras = número total de puntos aleatorios.
 */
int integrar_montecarlo(int tipo_densidad,
                        double a, double b, double c,
                        double xmin, double xmax,
                        double ymin, double ymax,
                        double zmin, double zmax,
                        long n_muestras,
                        double *masa,
                        double *x_bar, double *y_bar, double *z_bar);

#endif
