
# Proyecto: Clasificador y Organizador de Archivos

## Descripción General
Este programa en C++ recorre un directorio y sus subdirectorios, lee el contenido de cada archivo y los clasifica según su tipo (programa, driver, dll, pista o basura). Los archivos se mueven y renombran en una estructura de carpetas llamada `Output`, donde quedan organizados por tipo.

## ¿Cómo funciona el código?
- El usuario indica la ruta del directorio a analizar.
- El programa verifica si la carpeta `Output` existe; si no, la crea junto con sus subcarpetas.
- Recorre todos los archivos del directorio y subdirectorios:
	- Lee el contenido de cada archivo.
	- Determina el tipo de archivo según palabras clave o extensión.
	- Mueve y renombra el archivo a la carpeta correspondiente en `Output`.
	- Si no coincide con ningún tipo, lo mueve a la carpeta `Basura`.
- Al finalizar, muestra un resumen con la cantidad de archivos procesados de cada tipo.

## Instrucciones de Uso
1. **Coloca la ruta del directorio a analizar en el archivo `input.txt`**
	 - Ejemplo de contenido de `input.txt`:
		 ```
		 archivos_de_prueba
		 ```
2. **Abre una terminal en la carpeta del proyecto.**
3. **Ejecuta el siguiente comando:**
	 ```bash
	 make run
	 ```
	 Esto compilará y ejecutará el programa, leyendo la ruta desde `input.txt`.
4. **El programa creará una carpeta `Output`** en la raíz del proyecto, donde se guardarán y organizarán todos los archivos procesados.

## Requisitos
- Compilador C++17 o superior (por el uso de `<filesystem>`).
- Sistema operativo Linux recomendado.

## Notas
- Los archivos originales se eliminan después de ser movidos.
- Los archivos se renombran según su tipo y contador.
- Si tienes dudas, revisa el código fuente o consulta a tu compañero.
