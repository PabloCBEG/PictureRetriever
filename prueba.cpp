#include <string.h>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
//#include "boost/filesystem.hpp"
#include "filesystem.hpp"

//const char* todas_las_imagenes;
std::string todas_las_imagenes;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::cerr;
using std::filesystem::current_path;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile

int main()
{
    int indice;
    std::vector<string> lista_archivos;
    //std::string path;
    //cin >> path;
    //for (const auto & entry : fs::directory_iterator(path))
    //    std::cout << entry.path() << std::endl;

    //create a new folder for the pictures

    //cout << "Current working directory: " << cwd << endl;
    //const char* cwd = "carpetaNueva";
    //std::string cwd = "carpetaNueva";
    //todas_las_imagenes = cwd.append("/todas_las_imagenes"); //could be done using "+" instead of append(), but latter is faster
                                                            //new folder name: "todas_las_imagenes", in order to store pictures
    
    char dire[5] = "pepe";
    char* todas_las_imagenes = dire;
    const char * anado = "/carpetanueva";
    const char * ruta = strcat(todas_las_imagenes,anado);
    cout << ruta;
    if(_mkdir(ruta) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado"; //just for debugging

    //searching for .jpg images (to be extended to any image extension: .jpeg, .tiff, .png)

    /*indice = 0;
    while(lista_archivos)
    {
      if(PathFindExtension(lista_archivos[indice]) == ".jpg")

    }*/

}
