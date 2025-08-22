# README

## Descripción general

Este programa en C++ utiliza la biblioteca estándar y la de filesystem para interactuar con el sistema de archivos. Permite al usuario ingresar la ruta de un directorio, verifica su existencia, crea una estructura de carpetas de salida y recorre todos los archivos y subdirectorios, mostrando su contenido si son archivos.

---

## Explicación de las funciones

### Lectura(const fs::path& ruta)
- **Propósito:** Lee y muestra el contenido de un archivo de texto.
- **Funcionamiento:**
  - Recibe la ruta de un archivo.
  - Abre el archivo usando `ifstream`.
  - Si no se puede abrir, muestra un error.
  - Si se abre correctamente, lee línea por línea y muestra el contenido en consola.

### main()
- **Propósito:** Es el punto de entrada del programa y gestiona el flujo principal.
- **Funcionamiento:**
  1. Solicita al usuario la ruta de un directorio.
  2. Verifica si el directorio existe:
     - Si existe, continúa.
     - Si no existe, termina el programa.
  3. Verifica si la carpeta `Output` existe:
     - Si no existe, la crea junto con varias subcarpetas (`System`, `Drivers`, `Programs`, `Dynamic Link-Library`, `Pista`, `Basura`).
  4. Recorre el directorio y sus subdirectorios usando `recursive_directory_iterator`:
     - Si encuentra un archivo, muestra su nombre y llama a la función `Lectura` para mostrar su contenido.
     - Si encuentra un directorio, muestra su nombre.

---

## Flujo interno
1. El usuario ingresa la ruta de un directorio.
2. El programa verifica la existencia del directorio y de la carpeta de salida.
3. Si es necesario, crea la estructura de carpetas de salida.
4. Recorre todos los archivos y subdirectorios del directorio indicado.
5. Muestra el nombre y contenido de cada archivo, y el nombre de cada subdirectorio.

---

## Requisitos
- Compilador C++17 o superior (por el uso de `<filesystem>`).

## Ejecución
1. Compila el archivo:
   ```bash
   g++ -std=c++17 lab1.cpp -o programa
   ```
2. Ejecuta el programa:
   ```bash
   ./programa
   ```
3. Ingresa la ruta del directorio que deseas analizar cuando el programa lo solicite.

---

## Notas
- El programa solo muestra el contenido de archivos de texto.
- La estructura de carpetas `Output` se crea en el directorio actual si no existe.

---

