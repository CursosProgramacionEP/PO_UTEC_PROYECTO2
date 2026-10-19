/*
 * ejemplo_uso - Demostracion minima del modulo pgm_io.
 *
 * Carga una imagen, imprime la de juguete en consola, aplica un negativo
 * (pixel = maxVal - pixel) y guarda el resultado.
 *
 * NO es la arquitectura del proyecto: aqui todo es procedural a proposito.
 * El Proyecto 2 pide encapsular esta matriz en la clase Imagen, con sus
 * constructores, destructor y operadores sobrecargados.
 */

#include <iomanip>
#include <iostream>

#include "pgm_io/pgm_io.h"

void imprimirEnConsola(int** pixeles, int alto, int ancho) {
    for (int fila = 0; fila < alto; ++fila) {
        for (int columna = 0; columna < ancho; ++columna) {
            std::cout << std::setw(4) << pixeles[fila][columna];
        }
        std::cout << "\n";
    }
}

int main() {
    int alto = 0;
    int ancho = 0;
    int maxVal = 0;

    // 1. Una imagen pequenia se verifica a ojo directamente en la consola.
    int** juguete = leerPGM("imagenes/juguete8x8.pgm", alto, ancho, maxVal);
    if (juguete == nullptr) {
        return 1;
    }
    std::cout << "juguete8x8.pgm  (" << ancho << "x" << alto
              << ", maxVal=" << maxVal << ")\n";
    imprimirEnConsola(juguete, alto, ancho);
    liberarPGM(juguete, alto);

    // 2. La misma logica sobre una fotografia real.
    int** foto = leerPGM("imagenes/retrato.pgm", alto, ancho, maxVal);
    if (foto == nullptr) {
        return 1;
    }
    std::cout << "\nretrato.pgm cargado: " << ancho << "x" << alto << "\n";

    int** negativo = asignarMatriz(alto, ancho);
    for (int fila = 0; fila < alto; ++fila) {
        for (int columna = 0; columna < ancho; ++columna) {
            negativo[fila][columna] = maxVal - foto[fila][columna];
        }
    }

    if (escribirPGM("retrato_negativo.pgm", negativo, alto, ancho, maxVal)) {
        std::cout << "Escrito: retrato_negativo.pgm\n";
    }

    liberarPGM(foto, alto);
    liberarPGM(negativo, alto);
    return 0;
}
