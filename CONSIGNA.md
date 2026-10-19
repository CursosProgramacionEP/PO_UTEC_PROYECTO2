# Proyecto 2 de Laboratorio — Procesador de Imágenes en Escala de Grises

**Programación II (CS6003) — Pregrado 2026-II**

| | |
|---|---|
| **Entrega** | Lunes 16 de noviembre de 2026, 07:00 a.m. (Semana 15) |
| **Sustentación** | Sesión de laboratorio de la Semana 15 |
| **Puntaje total** | 20 puntos |
| **Modalidad** | Grupos de 3 estudiantes |

> **Antes de programar, lee la [Guía de Entorno](GUIA_ENTORNO.md) (lectura obligatoria).** Explica cómo obtener imágenes PGM, dónde ubicarlas para que el programa las encuentre y cómo visualizar los resultados. **No se concederán prórrogas por problemas de entorno que estén resueltos en esa guía.**

## 1. Indicaciones generales

- **Paradigma obligatorio:** Programación Orientada a Objetos en C++ (`.h` y `.cpp` por clase). **No se aceptan soluciones procedurales** ni clases que sean solo contenedores de funciones sueltas.
- **Restricción de librerías:** prohibido el uso de librerías de procesamiento de imágenes (OpenCV, CImg, stb_image y similares). El cómputo central se programa desde cero. Sí está permitido `std::vector` y el resto de la STL vista en clase.
- **Material base:** este repositorio entrega el módulo `pgm_io`, tres imágenes de prueba y una herramienta de conversión.
- **Plataforma de entrega:** Gradescope (integrado en Canvas). Un solo integrante sube la entrega y registra a sus compañeros.

## 2. Competencias evaluadas

- **ABET-COM-01:** analizar un problema computacional complejo y aplicar principios de computación y otras disciplinas relevantes para identificar soluciones.
- **TEC-01:** resolver situaciones de su entorno, utilizando herramientas computacionales e Inteligencia Artificial de manera ética y declarada.

## 3. Enunciado

Una imagen en escala de grises es, estructuralmente, una matriz de enteros: cada posición guarda la intensidad de un píxel entre 0 (negro) y 255 (blanco). El formato **PGM** (*Portable Gray Map*) almacena exactamente eso en texto plano, precedido de la firma `P2`, las dimensiones y el valor máximo.

Se requiere diseñar e implementar en **C++ orientado a objetos** una aplicación de consola que cargue una imagen PGM, le aplique una secuencia de filtros seleccionados por el usuario y guarde el resultado. El programa debe ofrecer un menú o intérprete de comandos que permita:

1. Cargar y guardar imágenes en formato PGM.
2. Aplicar transformaciones puntuales mediante **operadores sobrecargados**.
3. Aplicar filtros de la jerarquía de clases, encadenables, resueltos **polimórficamente**.
4. Consultar la bitácora de operaciones aplicadas y persistirla en disco.
5. Salir liberando toda la memoria reservada.

## 4. Requerimientos técnicos y reparto por integrante

El proyecto se divide en tres áreas de responsabilidad técnica. Cada integrante responde por la suya en la sustentación, y el grupo responde por la integración.

### 4.1. Integrante 1 — Clase `Imagen`, memoria dinámica y sobrecarga de operadores

- **Clase `Imagen`:** encapsula una matriz dinámica bidimensional (`int**` con `new[]`/`delete[]`), alto, ancho y valor máximo. Atributos privados, acceso por métodos.
- **Regla de tres completa:** constructor parametrizado, **constructor de copia profunda**, **operador de asignación** y **destructor**. Se exige **cero fugas de memoria**; copiar una imagen no debe compartir punteros con el original.
- **Operadores sobrecargados** (mínimo): `+` y `-` con un escalar (brillo), `-` entre dos imágenes (diferencia absoluta), `*` con un factor real (contraste), `~` (negativo), `==` y `!=` (comparación píxel a píxel), y `()` para acceder a un píxel con validación de rango. Todos deben saturar los valores al rango `[0, maxVal]`.
- **Funciones amigas:** `operator<<` y `operator>>` declarados `friend` para volcar y leer la imagen en formato PGM sobre un flujo.

### 4.2. Integrante 2 — Jerarquía de filtros, herencia, polimorfismo y plantillas

- **Clase base abstracta `Filtro`:** con `virtual Imagen aplicar(const Imagen&) const = 0`, un método `nombre()` y **destructor virtual**. No instanciable.
- **Mínimo cinco clases derivadas:** `Umbral` (binarización), `Media` (suavizado), `Sobel` (detección de bordes), `EspejoHorizontal` y `Rotar90`. El manejo de los píxeles del borde en los filtros de convolución debe estar decidido y **justificado en el informe**.
- **Polimorfismo real:** una colección `std::vector<Filtro*>` que representa la cadena de filtros y se aplica recorriendo punteros a la clase base, sin preguntar por el tipo concreto. **No se acepta** resolver con `if`/`switch` sobre un identificador de filtro.
- **Plantillas:** una clase genérica `Matriz<T>` usada como soporte de la imagen, o `Kernel<N>` para las máscaras de convolución de tamaño fijo.

### 4.3. Integrante 3 — Relaciones entre clases, persistencia y pruebas

- **Clase `Editor`:** **contiene** una `Imagen` (composición: nace y muere con el editor) y **agrega** punteros a `Filtro` (agregación: los filtros existen con independencia del editor). La distinción debe sustentarse con un diagrama UML en el informe.
- **Interfaz de consola:** menú o intérprete de comandos que permita cargar, encadenar filtros, deshacer la última operación, guardar y salir, con validación de toda entrada del usuario.
- **Archivos (Sesión 14):** implementar la lectura y escritura del **formato binario `P5`**, además del `P2` entregado, y una **bitácora en disco** con el historial de operaciones aplicadas a cada imagen, que pueda recargarse en una ejecución posterior.
- **Batería de pruebas:** casos documentados sobre `juguete8x8.pgm` (verificable a mano, píxel a píxel) y sobre `patron.pgm`, incluyendo al menos un caso de error controlado (archivo inexistente, dimensiones incompatibles, parámetro fuera de rango).

### 4.4. Bonificación opcional (hasta 1 punto, sobre nota máxima de 20)

Histograma de la imagen con ecualización, o filtro de mediana con ordenamiento propio.

## 5. Video explicativo en YouTube (máx. 12 minutos)

Cada grupo graba y sube un video a YouTube (modo *No listado* o *Público*). El enlace debe figurar en la **primera página del informe en PDF**.

- **Duración máxima:** 12 minutos (~4 minutos por estudiante).
- **Cámara encendida:** los tres integrantes se presentan y explican su propia área.
- **Demostración de código en vivo:** jerarquía de clases, operadores sobrecargados, uso polimórfico de la cadena de filtros y liberación de memoria.
- **Ejecución en vivo:** compilar y procesar `retrato.pgm` mostrando el antes y el después de al menos tres filtros encadenados.

En la sesión de laboratorio de la semana 15 habrá además una **ronda oral de 5 minutos por grupo**, con preguntas individuales sobre el código entregado.

## 6. Entregables en Gradescope (vía Canvas)

1. **Informe técnico en PDF:** carátula con integrantes y **enlace al video**, diagrama UML de clases y relaciones, justificación del manejo de bordes, capturas de las imágenes antes y después de cada filtro, casos de prueba, **declaración ética del uso de fuentes e IA**, conclusiones y recomendaciones.
2. **Código fuente (`.zip`):** archivos `.cpp` y `.h` que compilen con `g++ -std=c++17` sin advertencias. Incluir el módulo `pgm_io` y las imágenes de prueba. **No incluir** la carpeta de compilación.

## 7. Rúbrica de evaluación (20 puntos)

| Criterio | Excelente | Adecuado | Mínimo | Insuficiente | Pts |
|---|---|---|---|---|---|
| **1. Algoritmo y diseño POO** *(grupal)* | Diseño de clases correcto y fiel a la implementación: jerarquía bien abstraída, relaciones justificadas y polimorfismo aplicado. **(6)** | Errores menores de diseño que no afectan significativamente el resultado. **(5)** | Errores que afectan parcialmente el resultado, o polimorfismo simulado con condicionales. **(3)** | Múltiples errores, o solución procedural encubierta en clases. **(1)** | /6 |
| **2. Código C++** *(individual)* | Compila sin advertencias, ordenado y fiel al diseño. Regla de tres completa, operadores saturados y sin fugas de memoria. **(4)** | Errores menores que no alteran el flujo principal. **(3)** | Errores que afectan parcialmente el resultado, o presenta fugas de memoria. **(2)** | Múltiples errores graves o no compila. **(1)** | /4 |
| **3. Presentación escrita** *(grupal)* | Informe ordenado y completo: UML, pruebas, capturas antes/después, enlace al video y declaración de fuentes e IA. **(4)** | Contiene las secciones principales pero sin énfasis en pruebas ni conclusiones. **(3)** | Contiene menos de la mitad de las secciones, incluyendo conclusiones. **(2)** | Informe deficiente, sin conclusiones o no entregado. **(1)** | /4 |
| **4. Presentación oral** *(individual)* | Presenta su área adecuadamente y responde las preguntas del profesor de forma lógica y coherente. **(6)** | Presenta adecuadamente pero no responde todas las preguntas con coherencia. **(3)** | No presenta adecuadamente pero responde las preguntas con coherencia. **(2)** | No presenta adecuadamente ni responde, o no se presenta. **(0)** | /6 |
| | | | | **NOTA FINAL** | **/20** |
