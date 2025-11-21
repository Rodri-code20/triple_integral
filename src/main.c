#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "integracion.h"
#include "densidades.h"

int main(void) {
    int metodo;
    int tipo_densidad;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    int Nx = 0, Ny = 0, Nz = 0;
    long N_muestras = 0;
    double a = 0.0, b = 0.0, c = 0.0;  // parámetros lineales
    double masa, x_bar, y_bar, z_bar;
    double tiempo;
    clock_t start, end;

    printf("==== Integracion triple ====\n");

    /* 1. Elegir metodo */
    printf("Metodo (1 = Riemann, 2 = Monte Carlo): ");
    scanf("%d", &metodo);

    /* 2. Tipo de densidad */
    printf("Tipo de densidad:\n");
    printf(" 1) Constante: rho = 1\n");
    printf(" 2) Lineal:    rho = a x + b y + c z\n");
    printf(" 3) Gaussiana: rho = exp(-(x^2 + y^2 + z^2))\n");
    printf("Opcion: ");
    scanf("%d", &tipo_densidad);

    if (tipo_densidad == 2) {
        printf("Ingrese a, b, c para la densidad lineal:\n");
        printf("a = ");
        scanf("%lf", &a);
        printf("b = ");
        scanf("%lf", &b);
        printf("c = ");
        scanf("%lf", &c);
    }

    /* 3. Limites de integracion */
    printf("Ingrese limites en x [xmin xmax]: ");
    scanf("%lf %lf", &xmin, &xmax);

    printf("Ingrese limites en y [ymin ymax]: ");
    scanf("%lf %lf", &ymin, &ymax);

    printf("Ingrese limites en z [zmin zmax]: ");
    scanf("%lf %lf", &zmin, &zmax);

    /* 4. Parametros del metodo */
    if (metodo == 1) {
        printf("Numero de subdivisiones Nx Ny Nz (Riemann): ");
        scanf("%d %d %d", &Nx, &Ny, &Nz);
    } else if (metodo == 2) {
        printf("Numero de muestras N (Monte Carlo): ");
        scanf("%ld", &N_muestras);
        /* Semilla para rand(): usar el reloj */
        srand((unsigned int)time(NULL));
    } else {
        printf("Metodo no valido.\n");
        return 1;
    }

    /* 5. Medir tiempo de ejecucion */
    start = clock();

    int status = 0;
    if (metodo == 1) {
        status = integrar_riemann(tipo_densidad,
                                  a, b, c,
                                  xmin, xmax,
                                  ymin, ymax,
                                  zmin, zmax,
                                  Nx, Ny, Nz,
                                  &masa, &x_bar, &y_bar, &z_bar);
    } else {
        status = integrar_montecarlo(tipo_densidad,
                                     a, b, c,
                                     xmin, xmax,
                                     ymin, ymax,
                                     zmin, zmax,
                                     N_muestras,
                                     &masa, &x_bar, &y_bar, &z_bar);
    }

    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;

    if (status != 0) {
        printf("Error en el calculo de la integral.\n");
        return 1;
    }

    /* 6. Mostrar resultados en pantalla */
    printf("\n=== Resultados ===\n");
    printf("Masa total M   = %.10f\n", masa);
    printf("Centro de masa = (%.10f, %.10f, %.10f)\n",
           x_bar, y_bar, z_bar);
    printf("Tiempo         = %.6f s\n", tiempo);

    /* 7. Escribir resultados en archivo CSV */
    const char *nombre_metodo =
        (metodo == 1) ? "Riemann" : "MonteCarlo";

    const char *nombre_densidad;
    switch (tipo_densidad) {
        case 1: nombre_densidad = "Constante"; break;
        case 2: nombre_densidad = "Lineal";    break;
        case 3: nombre_densidad = "Gaussiana"; break;
        default: nombre_densidad = "Desconocida"; break;
    }

    FILE *f = fopen("resultados.csv", "a");
    if (!f) {
        perror("No se pudo abrir resultados.csv");
        return 1;
    }

    /* Formato pedido:
     * Metodo, Densidad, Nx, Ny, Nz, M, x_bar, y_bar, z_bar, Tiempo
     */
    fprintf(f, "%s,%s,%d,%d,%d,%.10f,%.10f,%.10f,%.10f,%.6f\n",
            nombre_metodo,
            nombre_densidad,
            Nx, Ny, Nz,
            masa, x_bar, y_bar, z_bar, tiempo);

    fclose(f);

    printf("\nResultados guardados en resultados.csv\n");

    return 0;
}

