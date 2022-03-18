#include <string.h>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
#include <algorithm>
//#include <fstream>
//#include <winbase.h>
#include <filesystem>

//const char* todas_las_imagenes;
//std::filesystem::path todas_las_imagenes;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::cerr;
using std::for_each;
using std::filesystem::create_directory;
using std::filesystem::current_path;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::copy_options;
//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile

namespace fs = std::filesystem;

int main()
{
    int indice;
    std::vector<fs::path> lista_archivos;// = (std::vector<string>)malloc(1000000*sizeof(string));

    //create a new folder for the pictures
    fs::path cwd = current_path(); //store current directory name in pointer to char cwd
    ///cout << "Current working directory: " << cwd << endl;
    //todas_las_imagenes = cwd.append("\\todas_las_imagenes");
    fs::path aux = cwd;
    cwd /= "todas_las_imagenes";
    fs::path aux2 = cwd;
    ///cout << "Current working directory: " << cwd << endl;
    /*if(mkdir(cwd) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado"; //just for debugging*/
    if(create_directory(cwd) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado" << endl; //just for debugging

//***************************************************************************************************************
    recursive_directory_iterator it;

    //searching for .jpg images (to be extended to any image extension: .jpeg, .tiff, .png)
    for (const auto & file : it = recursive_directory_iterator(aux))
    {
        if(fs::current_path().filename() == "todas_las_imagenes")
          it.disable_recursion_pending();
        lista_archivos.push_back(file.path());  //adding new found file to the end of the vector
    }

    char* index;
    fs::path exten;
    fs::path imagen;

    for(indice = 0; indice < lista_archivos.size(); indice++)
    {
      cwd = aux2;
      if((fs::path(lista_archivos.at(indice)).extension() == ".jpg") || (fs::path(lista_archivos.at(indice)).extension() == ".JPG") || (fs::path(lista_archivos.at(indice)).extension() == ".png") || (fs::path(lista_archivos.at(indice)).extension() == ".PNG") || (fs::path(lista_archivos.at(indice)).extension() == ".tiff") || (fs::path(lista_archivos.at(indice)).extension() == ".TIFF") || (fs::path(lista_archivos.at(indice)).extension() == ".jfif") || (fs::path(lista_archivos.at(indice)).extension() == ".JFIF") || (fs::path(lista_archivos.at(indice)).extension() == ".jpeg") || (fs::path(lista_archivos.at(indice)).extension() == ".JPEG"))
      {
        std::cout << lista_archivos.at(indice) << "\n"; //for debugging purpose
        //indice = (char16_t)indice; //won't work
        //char imagen[30] = "Imagen";
        //std::sprintf(index, "%d", indice);
        //strcat(imagen, index);
        //exten = lista_archivos.at(indice).extension();
        //strcat(imagen, (string)exten);
        //strcat(imagen, ".jpg");
        
        imagen = lista_archivos.at(indice).filename();
        std::cout << imagen << endl;

        // Show all errors concerning filesystem
        try{
        fs::copy_file((const fs::path)lista_archivos.at(indice), cwd /= imagen, copy_options::overwrite_existing);
        } catch(fs::filesystem_error& e)
        {
          std::cout << "Error: " << e.what() << endl;
        }
        
        //cout << index << endl;
        //fs::copy_file(lista_archivos.at(indice), cwd, true);// /= "todas_las_imagenes");//, fs::copy_options::overwrite_existing);
      }
    }

    cout << "Lista terminada" << endl;
    //create_directory(cwd /= "Imagen1"); //for debugging

    cout << "Imagen guardada" << endl;  //for debugging

    /*for(indice = 0; indice < lista_archivos.size(); indice++)
    {
      if((fs::path(lista_archivos.at(indice)).extension() == ".jpg") || (fs::path(lista_archivos.at(indice)).extension() == ".JPG"))
        std::cout << lista_archivos.at(indice) << "\n"; //for debugging purpose
        fs::copy_file(lista_archivos.at(indice), cwd, true);// /= "todas_las_imagenes");//, fs::copy_options::overwrite_existing);
    }*/

}
