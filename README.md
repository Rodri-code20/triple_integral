# Proyecto: Cálculo de Masa y Centro de Masa mediante Integración Triple

Este proyecto implementa el cálculo numérico de la masa total y el centro de masa de un cuerpo tridimensional utilizando métodos de integración numérica.

---

## Métodos Numéricos Implementados

- **Riemann Tridimensional**  
  Divide el volumen en subregiones cúbicas y evalúa la densidad en los centros.

- **Monte Carlo**  
  Genera puntos aleatorios dentro del dominio y estima la integral mediante promedios.

El usuario puede seleccionar el método desde el menú principal.

---

## Modelos de Densidad

El programa incluye tres funciones de densidad:

1. **Constante:**  
   \[
   \rho(x, y, z) = 1
   \]

2. **Lineal:**  
   \[
   \rho(x, y, z) = ax + by + cz
   \]

3. **Gaussiana:**  
   \[
   \rho(x, y, z) = e^{-(x^2 + y^2 + z^2)}
   \]

Los parámetros \(a, b, c\) se ingresan desde consola en el caso lineal.

---
