#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

// Función que determina el tipo de archivo según su contenido
string tipo(string palabra, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll) {
    if(palabra == ".exe") { cant_exe++; return "exe"; }
    else if(palabra == ".sys") { cant_sys++; return "sys"; }
    else if(palabra == ".dll") { cant_dll++; return "dll"; }
    else if(palabra == "log" || palabra == "distancia:" || palabra == "fecha:") { cant_pist++; return "log"; }
    else { return "basura"; }
}

// Función que mueve el archivo a la carpeta correspondiente y lo renombra
void file_copy(const fs::path& ruta, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll, int &cant_basura, string file_type) {
    fs::path ruta_destino;

    if(file_type == "exe")
        ruta_destino = fs::path("Output/System/Programs") / ("Programa" + to_string(cant_exe) + ".exe");
    else if(file_type == "sys")
        ruta_destino = fs::path("Output/System/Drivers") / ("Driver" + to_string(cant_sys) + ".sys");
    else if(file_type == "dll")
        ruta_destino = fs::path("Output/System/Dynamic Link-Library") / ("Dll" + to_string(cant_dll) + ".dll");
    else if(file_type == "log")
        ruta_destino = fs::path("Output/Pistas") / ("Pista" + to_string(cant_pist) + ".txt");
    else // basura
        ruta_destino = fs::path("Output/Basura") / ("Basura" + to_string(cant_basura) + ruta.extension().string());

    try {
        fs::copy_file(ruta, ruta_destino, fs::copy_options::overwrite_existing);
        fs::remove(ruta);  // Borra el archivo original (mover en lugar de copiar)
    } catch (const fs::filesystem_error& e) {
        cerr << "Error copiando " << ruta << " -> " << ruta_destino << "\n" << e.what() << endl;
    }
}

// Función que lee el archivo y determina su tipo según su contenido
string Lectura(const fs::path& ruta, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll) {
    ifstream archivo(ruta);
    if(!archivo.is_open()) return "basura";

    string linea;
    string file_type = "basura";

    while(getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra;
        while(ss >> palabra) {
            string temp = tipo(palabra, cant_pist, cant_exe, cant_sys, cant_dll);
            if(temp != "basura") {
                file_type = temp;
                break; // Encontró un tipo válido
            }
        }
        if(file_type != "basura") break;
    }

    archivo.close();
    return file_type;
}

int main() {
    int cant_pist = 0, cant_exe = 0, cant_sys = 0, cant_dll = 0, cant_basura = 0;

    string Ruta;
    cout << "Introduce la ruta del directorio: ";
    getline(cin, Ruta);
    fs::path directorio(Ruta);

    // Verifica si el directorio existe
    if(!fs::exists(directorio)) {
        cout << "El directorio no existe." << endl;
        return 0;
    }

    // Crea las carpetas de Output si no existen
    if(!fs::exists("Output")) {
        fs::create_directory("Output");
        fs::create_directory("Output/System");
        fs::create_directory("Output/System/Drivers");
        fs::create_directory("Output/System/Programs");
        fs::create_directory("Output/System/Dynamic Link-Library");
        fs::create_directory("Output/Pistas");
        fs::create_directory("Output/Basura");
        cout << "Carpeta Output creada con éxito." << endl;
    } else {
        cout << "La carpeta Output ya existe." << endl;
    }

    // Recorre el directorio y subdirectorios
    for(const auto& Archivo : fs::recursive_directory_iterator(directorio)) {
        if(is_regular_file(Archivo)) {
            string tipo_archivo = Lectura(Archivo.path(), cant_pist, cant_exe, cant_sys, cant_dll);
            if(tipo_archivo != "basura")
                file_copy(Archivo.path(), cant_pist, cant_exe, cant_sys, cant_dll, cant_basura, tipo_archivo);
            else {
                cant_basura++;
                file_copy(Archivo.path(), cant_pist, cant_exe, cant_sys, cant_dll, cant_basura, "basura");
            }
        }
    }

    // Resumen
    cout << "pista: " << cant_pist << " - exe: " << cant_exe << " - sys: " << cant_sys
         << " - dll: " << cant_dll << " - basura: " << cant_basura << endl;

    return 0;
}
