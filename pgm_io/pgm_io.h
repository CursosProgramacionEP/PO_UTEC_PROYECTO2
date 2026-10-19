#ifndef PGM_IO_H
#define PGM_IO_H

#include <string>

/*
 * pgm_io - Modulo de entrada/salida para imagenes PGM (Portable Gray Map).
 *
 * MATERIAL BASE DEL PROYECTO 2. No se evalua: es la puerta de entrada al
 * problema, no el problema. Copie estos dos archivos a su proyecto y use las
 * funciones tal como estan.
 *
 * Un PGM en texto ("P2") es una imagen en escala de grises guardada como
 * texto plano. Su estructura es:
 *
 *      P2
 *      <ancho> <alto>
 *      <valorMaximo>
 *      <alto x ancho enteros entre 0 y valorMaximo>
 *
 * Es decir: la imagen ES una matriz de enteros. Cada entero es la intensidad
 * de un pixel (0 = negro, valorMaximo = blanco).
 *
 * La matriz se devuelve como int** asignada con new[], indexada [fila][columna]
 * con fila en [0, alto) y columna en [0, ancho). Quien la recibe es responsable
 * de liberarla: use liberarPGM, o encapsulela en su clase Imagen y liberela en
 * el destructor.
 */

/*
 * Lee un archivo PGM en texto (P2). Devuelve la matriz de pixeles recien
 * asignada y escribe las dimensiones en alto, ancho y maxVal.
 * Devuelve nullptr si el archivo no existe, no es P2 o esta truncado;
 * en ese caso imprime el motivo en cerr y no asigna memoria.
 */
int** leerPGM(const std::string& ruta, int& alto, int& ancho, int& maxVal);

/*
 * Escribe la matriz en un archivo PGM en texto (P2).
 * Devuelve true si la escritura fue exitosa.
 */
bool escribirPGM(const std::string& ruta, int** pixeles,
                 int alto, int ancho, int maxVal);

/* Libera una matriz devuelta por leerPGM. Acepta nullptr sin hacer nada. */
void liberarPGM(int** pixeles, int alto);

/* Asigna una matriz alto x ancho inicializada en cero. Util para crear
 * imagenes de salida antes de llenarlas. */
int** asignarMatriz(int alto, int ancho);

/* ------------------------------------------------------------------------
 * PENDIENTE PARA EL ALUMNO (despues de la Sesion 14 - Archivos)
 *
 * Implemente la variante BINARIA del formato, cuya firma es "P5". Se diferencia
 * del P2 en que, tras el valor maximo y un unico caracter de espacio en blanco,
 * los pixeles van como bytes crudos (un byte por pixel cuando maxVal <= 255) en
 * lugar de numeros en texto. Requiere abrir el flujo en modo std::ios::binary y
 * usar read/write en vez del operador >>.
 *
 * int** leerPGMBinario(const std::string& ruta, int& alto, int& ancho, int& maxVal);
 * bool  escribirPGMBinario(const std::string& ruta, int** pixeles,
 *                          int alto, int ancho, int maxVal);
 * ------------------------------------------------------------------------ */

#endif
