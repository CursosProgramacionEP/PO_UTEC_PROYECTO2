/*
 * pgm2bmp - Convierte una imagen PGM en texto (P2) a BMP, para poder abrirla
 * con el visor de imagenes de Windows o macOS y tomar capturas para el informe.
 *
 * Es una herramienta auxiliar, independiente del proyecto. No forma parte de lo
 * evaluado y no debe incluirse en el .zip de entrega.
 *
 * Compilar:  g++ -std=c++17 pgm2bmp.cpp ../pgm_io/pgm_io.cpp -o pgm2bmp
 * Usar:      ./pgm2bmp salida.pgm salida.bmp
 */

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "../pgm_io/pgm_io.h"

namespace {

void escribirLE16(std::ofstream& salida, uint16_t valor) {
    salida.put(static_cast<char>(valor & 0xFF));
    salida.put(static_cast<char>((valor >> 8) & 0xFF));
}

void escribirLE32(std::ofstream& salida, uint32_t valor) {
    for (int i = 0; i < 4; ++i) {
        salida.put(static_cast<char>((valor >> (8 * i)) & 0xFF));
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: pgm2bmp <entrada.pgm> <salida.bmp>\n";
        return 1;
    }

    int alto = 0;
    int ancho = 0;
    int maxVal = 0;
    int** pixeles = leerPGM(argv[1], alto, ancho, maxVal);
    if (pixeles == nullptr) {
        return 1;
    }

    // Cada fila del BMP se rellena hasta un multiplo de 4 bytes.
    const int bytesPorFila = ancho * 3;
    const int relleno = (4 - (bytesPorFila % 4)) % 4;
    const uint32_t tamDatos = static_cast<uint32_t>((bytesPorFila + relleno) * alto);
    const uint32_t desplazamiento = 54;

    std::ofstream salida(argv[2], std::ios::binary);
    if (!salida) {
        std::cerr << "No se pudo crear: " << argv[2] << "\n";
        liberarPGM(pixeles, alto);
        return 1;
    }

    salida.put('B');
    salida.put('M');
    escribirLE32(salida, desplazamiento + tamDatos);
    escribirLE16(salida, 0);
    escribirLE16(salida, 0);
    escribirLE32(salida, desplazamiento);

    escribirLE32(salida, 40);
    escribirLE32(salida, static_cast<uint32_t>(ancho));
    escribirLE32(salida, static_cast<uint32_t>(alto));
    escribirLE16(salida, 1);
    escribirLE16(salida, 24);
    escribirLE32(salida, 0);
    escribirLE32(salida, tamDatos);
    escribirLE32(salida, 2835);
    escribirLE32(salida, 2835);
    escribirLE32(salida, 0);
    escribirLE32(salida, 0);

    // El BMP almacena las filas de abajo hacia arriba.
    for (int fila = alto - 1; fila >= 0; --fila) {
        for (int columna = 0; columna < ancho; ++columna) {
            int gris = pixeles[fila][columna];
            if (maxVal != 255) {
                gris = (gris * 255) / maxVal;
            }
            const char byte = static_cast<char>(gris);
            salida.put(byte);
            salida.put(byte);
            salida.put(byte);
        }
        for (int i = 0; i < relleno; ++i) {
            salida.put(0);
        }
    }

    liberarPGM(pixeles, alto);
    std::cout << "Convertido: " << argv[1] << " -> " << argv[2] << " ("
              << ancho << "x" << alto << ")\n";
    return 0;
}
