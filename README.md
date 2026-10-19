# Proyecto 2 — Procesador de Imágenes PGM

**CS6003 Programación II — Laboratorio — UTEC — 2026-II**

Material base del Proyecto Final de Laboratorio. Resuelve la entrada y salida de
archivos para que puedas empezar el proyecto desde el primer día, sin esperar a
la Sesión 14.

## Empieza por aquí

| Documento | Qué contiene |
|---|---|
| [CONSIGNA.md](CONSIGNA.md) | El enunciado: qué construir, el reparto por integrante, entregables y rúbrica. |
| [GUIA_ENTORNO.md](GUIA_ENTORNO.md) | **Lectura obligatoria.** Cómo obtener imágenes PGM, dónde ubicarlas y cómo ver tus resultados. |

## Contenido del repositorio

| Archivo | Para qué sirve | ¿Se evalúa? |
|---|---|---|
| `pgm_io/pgm_io.h` · `pgm_io.cpp` | Lee y escribe imágenes PGM en texto (`P2`). Cópialo a tu proyecto y úsalo tal cual. | No |
| `ejemplo_uso.cpp` | Demostración mínima: carga, imprime, invierte y guarda. | No |
| `herramientas/pgm2bmp.cpp` | Convierte un `.pgm` a `.bmp` para verlo en el visor del sistema y tomar capturas. | No |
| `imagenes/juguete8x8.pgm` | Imagen 8×8 que cabe en la consola. Para depurar filtros a mano. | — |
| `imagenes/patron.pgm` | Patrón 128×128 con bordes rectos y curvos. Para probar Sobel. | — |
| `imagenes/retrato.pgm` | Fotografía real 256×256 en escala de grises. | — |

Lo que se evalúa es **tu** código: la clase `Imagen`, sus operadores, la jerarquía
de filtros y el polimorfismo. El módulo `pgm_io` es solo la puerta de entrada al
problema.

## Probarlo en 30 segundos

Abre la carpeta en CLion y ejecuta el target `ejemplo_uso` **desde el desplegable
de la barra de herramientas** (no con el triangulito verde que aparece al lado
del `main`). Debe imprimir la matriz 8×8 y generar `retrato_negativo.pgm`.

Desde terminal:

```bash
g++ -std=c++17 ejemplo_uso.cpp pgm_io/pgm_io.cpp -o ejemplo_uso
./ejemplo_uso
```

## El error más común: "No se pudo abrir el archivo"

Tu programa no busca las imágenes donde está el código fuente, sino en el
directorio de trabajo con el que arranca el ejecutable. Según el entorno y la
versión del IDE ese directorio puede ser la carpeta del proyecto o la carpeta de
compilación, y por eso `leerPGM("imagenes/retrato.pgm")` a veces funciona y a
veces no.

La solución es dejar la imagen disponible en los dos sitios: mantén `imagenes/`
en la raíz del proyecto **y** conserva en tu `CMakeLists.txt` la línea que la
copia al directorio de compilación en cada build:

```cmake
file(COPY ${CMAKE_SOURCE_DIR}/imagenes DESTINATION ${CMAKE_BINARY_DIR})
```

El detalle completo está en [GUIA_ENTORNO.md](GUIA_ENTORNO.md).

## Qué sí te toca programar de archivos

Después de la **Sesión 14 (Archivos)** deberás implementar por tu cuenta:

- `leerPGMBinario` y `escribirPGMBinario` para la variante binaria `P5`.
- La bitácora en disco con el historial de operaciones aplicadas a cada imagen.

Las firmas están declaradas y comentadas al final de `pgm_io.h`.

## Entrega

En el `.zip` incluye tus archivos `.cpp` y `.h`, el módulo `pgm_io` y las
imágenes de prueba. **No incluyas** la carpeta de compilación ni la herramienta
`pgm2bmp`.
