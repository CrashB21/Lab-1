#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;
namespace fs = filesystem;

//


// Lee lo que hay dentro de un archivo. se le entrega el path del archivo
void Lectura(const fs::path& ruta) {

    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}


int main() {

    string Ruta;
    cout << "Introduce la ruta del directorio: ";

    fs::path carpeta = "Output";


    getline(cin, Ruta);
    fs::path directorio(Ruta);

    // Verifica si el directorio existe.
    if(fs::exists(directorio)) {
        
        cout << "El directorio existe." << endl;
    } else {
        cout << "El directorio no existe." << endl; 
        return 0;
    }

    // Verifica si la carpeta Output ya existe, si no, la crea.
    if (fs::exists(carpeta)) {
        std::cout << "La carpeta Output ya existe.\n";
    } else {
    
        fs::create_directory("Output");                   
        fs::create_directory("Output/System");            
        fs::create_directory("Output/System/Drivers");  
        fs::create_directory("Output/System/Programs");
        fs::create_directory("Output/System/Dynamic Link-Library");
        fs::create_directory("Output/Pista");
        fs::create_directory("Output/Basura");

        cout << "Carpeta Output creada con éxito." << endl;

    }
    
    // Recorre el directorio y sus subdirectorios.
    for (const auto& Archivo : fs::recursive_directory_iterator(directorio)){

        cout << Archivo.path() << endl;

        if (is_regular_file(Archivo)) 
        {
            cout <<"Es un archvio : " << Archivo.path().filename()<< endl;
            Lectura(Archivo.path());
        }
        else 
        {
            cout <<"Es un directorio : " << Archivo.path().filename() << endl;
        }
    }
    
    return 0;
}