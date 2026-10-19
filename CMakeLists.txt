cmake_minimum_required(VERSION 3.15)
project(Proyecto2_ProcesadorImagenes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Programa de demostracion del modulo de lectura/escritura PGM.
add_executable(ejemplo_uso ejemplo_uso.cpp pgm_io/pgm_io.cpp)

# Herramienta auxiliar para convertir PGM a BMP y poder ver el resultado.
add_executable(pgm2bmp herramientas/pgm2bmp.cpp pgm_io/pgm_io.cpp)

# El ejecutable arranca con un directorio de trabajo que, segun el entorno y la
# version del IDE, puede ser la carpeta del proyecto o la de compilacion. Copiar
# imagenes/ al directorio de compilacion cubre el segundo caso y evita el error
# "No se pudo abrir el archivo".
file(COPY ${CMAKE_SOURCE_DIR}/imagenes DESTINATION ${CMAKE_BINARY_DIR})
