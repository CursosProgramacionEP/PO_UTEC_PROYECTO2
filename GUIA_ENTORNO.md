# Guía de Entorno del Proyecto 2

**CS6003 Programación II — Laboratorio — UTEC — 2026-II**

Cómo obtener imágenes PGM, dónde ubicarlas y cómo ver tus resultados.
**Lectura obligatoria antes de empezar el proyecto.**

---

## 01 · Qué es una imagen PGM

Una imagen en escala de grises es, por dentro, una matriz de enteros: cada
posición guarda la intensidad de un píxel entre 0 (negro) y 255 (blanco). El
formato PGM (*Portable Gray Map*) guarda exactamente eso en texto plano, así que
puedes abrir una imagen con cualquier editor de texto y leer sus píxeles.

Un archivo PGM completo de 4 columnas por 3 filas se ve así:

```
P2
4 3
255
0    50   100  255
60   120  180  240
10   90   170  200
```

La firma `P2`, el ancho y el alto, el valor máximo y luego los píxeles.

Esa matriz es la misma estructura que manejaste en el Proyecto 1 con punteros y
memoria dinámica. La diferencia es que ahora el resultado se puede ver.

## 02 · El material base que recibes

Este repositorio contiene la entrada y salida de archivos ya resuelta, para que
puedas empezar sin esperar a la Sesión 14.

| Archivo | Para qué sirve | ¿Se evalúa? |
|---|---|---|
| `pgm_io/pgm_io.h` · `pgm_io.cpp` | Lee y escribe imágenes PGM en texto. Cópialo a tu proyecto y úsalo tal cual. | No |
| `ejemplo_uso.cpp` | Demostración mínima: carga, imprime, invierte y guarda. | No |
| `herramientas/pgm2bmp.cpp` | Convierte un `.pgm` a `.bmp` para verlo y tomar capturas del informe. | No |
| `imagenes/juguete8x8.pgm` | Imagen 8×8 que cabe en la consola. Para depurar filtros a mano. | — |
| `imagenes/patron.pgm` | Patrón 128×128 con bordes rectos y curvos. Para probar Sobel. | — |
| `imagenes/retrato.pgm` | Fotografía real 256×256 en escala de grises. | — |

> Lo que se evalúa es tu código: la clase `Imagen`, sus operadores, la jerarquía
> de filtros y el polimorfismo. El módulo `pgm_io` es solo la puerta de entrada
> al problema.

## 03 · Comprobar que todo funciona

Antes de escribir una sola clase, confirma que puedes leer una imagen. Toma dos
minutos y te ahorra horas.

### Desde CLion

1. Abre la carpeta del proyecto con **Archivo → Abrir**. CLion detecta el
   `CMakeLists.txt` y configura el proyecto solo.
2. En el desplegable de la barra de herramientas, arriba a la derecha, elige el
   target `ejemplo_uso`.
3. Ejecuta con el **botón ▶ de la barra de herramientas**. No uses el triangulito
   verde que aparece al costado de la línea del `main`: ese atajo compila un
   archivo suelto, sin el resto del proyecto, y produce errores de enlazado.

Debe imprimir la matriz 8×8 en la consola y generar el archivo
`retrato_negativo.pgm`.

### Desde la terminal

```bash
g++ -std=c++17 ejemplo_uso.cpp pgm_io/pgm_io.cpp -o ejemplo_uso
./ejemplo_uso
```

> **Si CLion muestra errores de enlazado:** recarga el proyecto con
> **Archivo → Volver a cargar el proyecto CMake** y vuelve a ejecutar desde el
> desplegable de la barra de herramientas. Es la causa del 90 % de los errores de
> enlazado en el curso.

## 04 · El error más común: "No se pudo abrir el archivo"

Tu programa no busca las imágenes donde está el código fuente, sino en el
**directorio de trabajo** con el que arranca el ejecutable. Según el entorno y la
versión del IDE ese directorio puede ser la carpeta del proyecto o la carpeta de
compilación, y por eso `leerPGM("imagenes/retrato.pgm")` a veces funciona y a
veces no.

La solución es dejar la imagen disponible en los dos sitios. Son dos medidas y
ambas vienen ya aplicadas en el material base:

- Mantén la carpeta `imagenes/` en la raíz del proyecto, junto al `CMakeLists.txt`.
- Conserva en tu `CMakeLists.txt` la línea que copia esa carpeta al directorio de
  compilación en cada build:

```cmake
file(COPY ${CMAKE_SOURCE_DIR}/imagenes DESTINATION ${CMAKE_BINARY_DIR})
```

Si creas tu proyecto desde cero, copia esa línea. Es la que evita el error.

Si aun así falla, fija el directorio de trabajo a mano: **Ejecutar → Editar
configuraciones**, selecciona tu target y en la pestaña **Configuración** escribe
la ruta en el campo **Directorio de trabajo**.

> Los mensajes de error del módulo `pgm_io` te dicen qué pasó: si el archivo no
> existe, si la firma no es `P2` o si el archivo está truncado. Léelos antes de
> suponer que tu código está mal.

## 05 · Usar tus propias fotografías

Cualquier foto en JPG o PNG se convierte a PGM con GIMP, que es gratuito y
funciona en Windows, macOS y Linux.

1. Abre tu imagen en GIMP.
2. Conviértela a grises: **Imagen → Modo → Escala de grises**.
3. Reduce el tamaño a 256×256 o menos con **Imagen → Escalar la imagen**. En texto
   plano una foto de 1000×1000 pesa varios megabytes y vuelve lenta cada prueba.
4. Usa **Archivo → Exportar como…** y escribe el nombre terminado en `.pgm`.
5. En el diálogo de exportación, en **Formato de datos** (*Data formatting*),
   elige **ASCII**, no Crudo (*Raw*). El módulo lee el formato `P2` de texto; el
   crudo es `P5` y todavía no lo soportas.
6. Guarda el archivo dentro de la carpeta `imagenes/` de tu proyecto.

> **Comprobación rápida:** abre el archivo exportado con un editor de texto. Si la
> primera línea dice `P2` y luego ves números, está bien. Si ves caracteres
> ilegibles, exportaste en formato crudo: repite el paso 5.

## 06 · Ver el resultado de tus filtros

El visor de imágenes de Windows y la Vista Previa de macOS no abren archivos PGM.
Tienes dos caminos:

- Abrir el `.pgm` directamente en GIMP, que sí lo reconoce.
- Convertirlo a BMP con la herramienta incluida y abrir el `.bmp` con el visor del
  sistema. Es el camino cómodo para las capturas del informe.

```bash
g++ -std=c++17 herramientas/pgm2bmp.cpp pgm_io/pgm_io.cpp -o pgm2bmp
./pgm2bmp salida.pgm salida.bmp
```

Mientras desarrollas, no conviertas cada prueba. Trabaja con `juguete8x8.pgm` e
imprime la matriz en la consola: ocho filas de ocho números se revisan a ojo y te
dicen de inmediato si tu filtro hace lo que crees.

## 07 · Qué te toca programar de archivos

El módulo `pgm_io` resuelve el formato de texto `P2`. Después de la **Sesión 14**
deberás implementar por tu cuenta, como parte de lo evaluado:

- La lectura y escritura del formato binario `P5`, cuya única diferencia es que
  los píxeles van como bytes crudos en vez de números en texto. Requiere abrir el
  flujo con `std::ios::binary` y usar `read` y `write`.
- La bitácora en disco con el historial de operaciones aplicadas a cada imagen,
  que pueda recargarse en una ejecución posterior.

Las firmas de las dos funciones binarias están declaradas y comentadas al final
de `pgm_io.h`.

## 08 · Qué entregar

- Tus archivos `.cpp` y `.h`, el módulo `pgm_io` y las imágenes de prueba, en un
  solo `.zip`.
- Deben compilar con `g++ -std=c++17` sin advertencias.
- **No incluyas** la carpeta de compilación (`cmake-build-debug`) ni la
  herramienta `pgm2bmp`.

## 09 · Enlaces rápidos

| Recurso | Enlace |
|---|---|
| GIMP (descarga) | https://www.gimp.org/downloads/ |
| Exportar a PNM/PGM — documentación de GIMP | https://docs.gimp.org/3.2/en/file-pnm-export.html |
| Directorio de trabajo en CLion | https://www.jetbrains.com/help/clion/run-debug-configuration-application.html |
| Especificación del formato PGM | https://netpbm.sourceforge.net/doc/pgm.html |
