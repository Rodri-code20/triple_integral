#include <stdlib.h>
#include "integracion.h"
#include "densidades.h"

/* Función auxiliar: evalúa la densidad según el tipo */
static double evaluar_densidad(int tipo,
                               double x, double y, double z,
                               double a, double b, double c) {
    switch (tipo) {
        case 1:
            return densidad_constante(x, y, z);
        case 2:
            return densidad_lineal(x, y, z, a, b, c);
        case 3:
            return densidad_gaussiana(x, y, z);
        default:
            return 0.0; /* tipo inválido */
    }
}

int integrar_riemann(int tipo_densidad,
                     double a, double b, double c,
                     double xmin, double xmax,
                     double ymin, double ymax,
                     double zmin, double zmax,
                     int Nx, int Ny, int Nz,
                     double *masa,
                     double *x_bar, double *y_bar, double *z_bar) {

    if (Nx <= 0 || Ny <= 0 || Nz <= 0) return -1;

    double dx = (xmax - xmin) / Nx;
    double dy = (ymax - ymin) / Ny;
    double dz = (zmax - zmin) / Nz;
    double dV = dx * dy * dz;

    double suma_rho = 0.0;
    double suma_xrho = 0.0;
    double suma_yrho = 0.0;
    double suma_zrho = 0.0;

    for (int i = 0; i < Nx; ++i) {
        double x = xmin + (i + 0.5) * dx;  // centro en x
        for (int j = 0; j < Ny; ++j) {
            double y = ymin + (j + 0.5) * dy;  // centro en y
            for (int k = 0; k < Nz; ++k) {
                double z = zmin + (k + 0.5) * dz;  // centro en z

                double rho = evaluar_densidad(tipo_densidad,
                                              x, y, z, a, b, c);

                double contrib = rho * dV;

                suma_rho  += contrib;
                suma_xrho += x * contrib;
                suma_yrho += y * contrib;
                suma_zrho += z * contrib;
            }
        }
    }

    *masa  = suma_rho;
    *x_bar = suma_xrho / *masa;
    *y_bar = suma_yrho / *masa;
    *z_bar = suma_zrho / *masa;

    return 0;
}

int integrar_montecarlo(int tipo_densidad,
                        double a, double b, double c,
                        double xmin, double xmax,
                        double ymin, double ymax,
                        double zmin, double zmax,
                        long n_muestras,
                        double *masa,
                        double *x_bar, double *y_bar, double *z_bar) {

    if (n_muestras <= 0) return -1;

    double V = (xmax - xmin) * (ymax - ymin) * (zmax - zmin);

    double suma_rho = 0.0;
    double suma_xrho = 0.0;
    double suma_yrho = 0.0;
    double suma_zrho = 0.0;

    for (long n = 0; n < n_muestras; ++n) {
        double rx = (double)rand() / (double)RAND_MAX;
        double ry = (double)rand() / (double)RAND_MAX;
        double rz = (double)rand() / (double)RAND_MAX;

        double x = xmin + rx * (xmax - xmin);
        double y = ymin + ry * (ymax - ymin);
        double z = zmin + rz * (zmax - zmin);

        double rho = evaluar_densidad(tipo_densidad,
                                      x, y, z, a, b, c);

        suma_rho  += rho;
        suma_xrho += x * rho;
        suma_yrho += y * rho;
        suma_zrho += z * rho;
    }

    double prom_rho  = suma_rho  / (double)n_muestras;
    double prom_xrho = suma_xrho / (double)n_muestras;
    double prom_yrho = suma_yrho / (double)n_muestras;
    double prom_zrho = suma_zrho / (double)n_muestras;

    /* Integral ≈ V * promedio */
    double M  = V * prom_rho;
    double Ix = V * prom_xrho;
    double Iy = V * prom_yrho;
    double Iz = V * prom_zrho;

    *masa  = M;
    *x_bar = Ix / M;
    *y_bar = Iy / M;
    *z_bar = Iz / M;

    return 0;
}

