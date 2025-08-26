    #include <iostream>
    #include <filesystem>
    #include <string>
    #include <fstream>

    using namespace std;
    namespace fs = filesystem;

    //

    string tipo(string palabra, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll, int &cant_basura){
        if(palabra == ".exe"){
            cant_exe++;
            return "exe";
        }
        else if(palabra == ".sys"){
            cant_sys++;
            return "sys";
        }
        else if(palabra == ".dll"){
            cant_dll++;
            return "dll";
        }
        else if(palabra == "log"){
            cant_pist++;
            return "log";
        }
        else if(palabra == "distancia:"){
            cant_pist++;
            return "log";
        }   
        else if(palabra == "fecha:"){
            cant_pist++;
            return "log";
        }
        else{
            return "basura";
        }
    }

    void file_copy(const fs::path& ruta, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll, int &cant_basura, string file_type){
        // string ruta_destino, nombre_final;
        fs::path ruta_destino;

        if(file_type == "exe"){
            // ruta_destino = "Output/System/Programs/Programa" + to_string(cant_exe) + ".exe";
            ruta_destino = fs::path("Output/System/Programs") / ("Programa" + to_string(cant_exe) + ".exe");
            // nombre_final = "Programa" + cant_exe;
            
        }
        else if(file_type == "sys"){
            // ruta_destino = "Output/System/Drivers/Driver" + to_string(cant_sys) + ".sys";
            ruta_destino = fs::path("Output/System/Drivers") / ("Driver" + to_string(cant_sys) + ".sys");
            // nombre_final = "Driver" + cant_sys;
        }
        else if(file_type == "dll"){
            // ruta_destino = "Output/System/Dynamic Link-Library/dll" + to_string(cant_dll) + ".dll";
            ruta_destino = fs::path("Output/System/Dynamic Link-Library") / ("Dll" + to_string(cant_dll) + ".dll");
            // nombre_final = "dll" + cant_dll;
        }
        else if(file_type == "log"){
            // ruta_destino = "Output/Pistas/Pista" + to_string(cant_pist) + ".txt";
            ruta_destino = fs::path("Output/Pistas") / ("Pista" + to_string(cant_dll) + ".txt");
            // nombre_final = 
        }
        else if(file_type == "basura"){
            // ruta_destino = "Output/Basura/Basura" + to_string(cant_basura) + ".txt";
            ruta_destino = fs::path("Output/Basura") / ("Basura" + to_string(cant_basura) + ruta.extension().string());
            // nombre_final = 
        }

        try {
            fs::copy_file(ruta, ruta_destino, fs::copy_options::overwrite_existing);
        } catch (const fs::filesystem_error& e) {
            cerr << "Error copiando " << ruta << " -> " << ruta_destino << "\n"
                << e.what() << endl;
        }

        return;

    }

    // Lee lo que hay dentro de un archivo. se le entrega el path del archivo
    void Lectura(const fs::path& ruta, int &cant_pist, int &cant_exe, int &cant_sys, int &cant_dll, int &cant_basura) {

        ifstream archivo(ruta);
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo: " << ruta << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string palabra, file_type_temp, file_type;
            while(ss >> palabra){
                file_type_temp = tipo(palabra, cant_pist, cant_exe, cant_sys, cant_dll, cant_basura);
                if(file_type_temp != "basura"){
                    file_type = file_type_temp;
                    // cout << ruta << " " << file_type << endl;
                    file_copy(ruta, cant_pist, cant_exe, cant_sys, cant_dll, cant_basura, file_type);
                    // CREAR ARCHIVO;
                    archivo.close();
                    return;
                }
            }
            file_type = "basura";
            cant_basura++;
            file_copy(ruta, cant_pist, cant_exe, cant_sys, cant_dll, cant_basura, file_type);
            // cout << linea << endl;

        }
        archivo.close();
        return;
    }



    int main() {


        int cant_pist = 0, cant_exe = 0, cant_sys = 0, cant_dll = 0, cant_basura = 0;
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
            fs::create_directory("Output/Pistas");
            fs::create_directory("Output/Basura");

            cout << "Carpeta Output creada con éxito." << endl;

        }
        
        // Recorre el directorio y sus subdirectorios.
        for (const auto& Archivo : fs::recursive_directory_iterator(directorio)){

            // cout << Archivo.path() << endl;

            if (is_regular_file(Archivo)) 
            {
                // cout <<"Es un archvio : " << Archivo.path().filename()<< endl;
                Lectura(Archivo.path(), cant_pist, cant_exe, cant_sys, cant_dll, cant_basura);
            }
            else 
            {
                // cout <<"Es un directorio : " << Archivo.path().filename() << endl;
            }
        }

        cout << "pista: " << cant_pist << " - exe: " << cant_exe << " - sys: " << cant_sys << " - ddl: " << cant_dll << " - basura: " << cant_basura;
        
        return 0;
    }