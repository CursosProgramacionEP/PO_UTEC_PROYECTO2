#include "pgm_io.h"

#include <fstream>
#include <iostream>
#include <string>

/*
 * Los tokens de un PGM en texto estan separados por cualquier cantidad de
 * espacios, tabulaciones o saltos de linea, y el formato admite lineas de
 * comentario que empiezan con '#'. Por eso la lectura no asume una linea por
 * fila: se consumen tokens uno por uno descartando los comentarios.
 */
namespace {

bool siguienteToken(std::istream& entrada, std::string& token) {
    while (entrada >> token) {
        if (token.empty()) {
            continue;
        }
        if (token[0] == '#') {
            std::string restoDeLinea;
            std::getline(entrada, restoDeLinea);
            continue;
        }
        return true;
    }
    return false;
}

bool siguienteEntero(std::istream& entrada, int& valor) {
    std::string token;
    if (!siguienteToken(entrada, token)) {
        return false;
    }
    try {
        size_t consumidos = 0;
        valor = std::stoi(token, &consumidos);
        return consumidos == token.size();
    } catch (...) {
        return false;
    }
}

}  // namespace

int** asignarMatriz(int alto, int ancho) {
    if (alto <= 0 || ancho <= 0) {
        return nullptr;
    }
    int** matriz = new int*[alto];
    for (int i = 0; i < alto; ++i) {
        matriz[i] = new int[ancho]();
    }
    return matriz;
}

void liberarPGM(int** pixeles, int alto) {
    if (pixeles == nullptr) {
        return;
    }
    for (int i = 0; i < alto; ++i) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
}

int** leerPGM(const std::string& ruta, int& alto, int& ancho, int& maxVal) {
    alto = 0;
    ancho = 0;
    maxVal = 0;

    std::ifstream archivo(ruta);
    if (!archivo) {
        std::cerr << "[pgm_io] No se pudo abrir el archivo: " << ruta << "\n"
                  << "[pgm_io] Revise que la imagen este en el directorio de "
                     "trabajo del ejecutable (vea la Guia de Entorno).\n";
        return nullptr;
    }

    std::string firma;
    if (!siguienteToken(archivo, firma)) {
        std::cerr << "[pgm_io] Archivo vacio: " << ruta << "\n";
        return nullptr;
    }
    if (firma != "P2") {
        std::cerr << "[pgm_io] Formato no soportado (firma '" << firma
                  << "'). Se esperaba 'P2' (PGM en texto). Si exporto desde "
                     "GIMP, marque la opcion ASCII.\n";
        return nullptr;
    }

    if (!siguienteEntero(archivo, ancho) || !siguienteEntero(archivo, alto) ||
        !siguienteEntero(archivo, maxVal)) {
        std::cerr << "[pgm_io] Cabecera incompleta en: " << ruta << "\n";
        return nullptr;
    }
    if (ancho <= 0 || alto <= 0 || maxVal <= 0) {
        std::cerr << "[pgm_io] Cabecera invalida: ancho=" << ancho
                  << " alto=" << alto << " maxVal=" << maxVal << "\n";
        ancho = alto = maxVal = 0;
        return nullptr;
    }

    int** pixeles = asignarMatriz(alto, ancho);
    for (int fila = 0; fila < alto; ++fila) {
        for (int columna = 0; columna < ancho; ++columna) {
            int valor = 0;
            if (!siguienteEntero(archivo, valor)) {
                std::cerr << "[pgm_io] Archivo truncado: se esperaban "
                          << (alto * ancho) << " pixeles y falto el de la fila "
                          << fila << ", columna " << columna << ".\n";
                liberarPGM(pixeles, alto);
                ancho = alto = maxVal = 0;
                return nullptr;
            }
            if (valor < 0) {
                valor = 0;
            }
            if (valor > maxVal) {
                valor = maxVal;
            }
            pixeles[fila][columna] = valor;
        }
    }
    return pixeles;
}

bool escribirPGM(const std::string& ruta, int** pixeles,
                 int alto, int ancho, int maxVal) {
    if (pixeles == nullptr || alto <= 0 || ancho <= 0 || maxVal <= 0) {
        std::cerr << "[pgm_io] Datos invalidos para escribir: " << ruta << "\n";
        return false;
    }

    std::ofstream archivo(ruta);
    if (!archivo) {
        std::cerr << "[pgm_io] No se pudo crear el archivo: " << ruta << "\n";
        return false;
    }

    archivo << "P2\n";
    archivo << "# Generado por el Proyecto 2 - Programacion II (CS6003)\n";
    archivo << ancho << " " << alto << "\n";
    archivo << maxVal << "\n";

    for (int fila = 0; fila < alto; ++fila) {
        for (int columna = 0; columna < ancho; ++columna) {
            int valor = pixeles[fila][columna];
            if (valor < 0) {
                valor = 0;
            }
            if (valor > maxVal) {
                valor = maxVal;
            }
            archivo << valor;
            archivo << (columna + 1 == ancho ? '\n' : ' ');
        }
    }
    return archivo.good();
}
