#include <string.h>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::cerr;
using std::for_each;
using fs::create_directory;
using fs::current_path;
using fs::directory_iterator;
using fs::recursive_directory_iterator;
using fs::copy_options;

//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile

void createfolder(fs::path& , fs::path& , fs::path& );

int main()
{
    int indice;
    std::vector<fs::path> lista_archivos;     //vector variable used to store filepaths of all files in directory

    fs::path cwd; fs::path aux; fs::path aux2;
    createfolder(cwd, aux, aux2);

    recursive_directory_iterator it;  //variable of type rec.dir.iterator so it can be used as a "pointer" to the current directory when iterating

    //searching for .jpg images, extended to any image extension: .jpeg, .tiff, .png, .jfif
    for (const auto & file : it = recursive_directory_iterator(aux))
    {
        if(fs::current_path().filename() == "todas_las_imagenes")
          it.disable_recursion_pending();
        lista_archivos.push_back(file.path());  //adding new found file to the end of the vector
    }

    fs::path imagen;

    for(indice = 0; indice < lista_archivos.size(); indice++)
    {
      cwd = aux2;
      if((fs::path(lista_archivos.at(indice)).extension() == ".jpg") || (fs::path(lista_archivos.at(indice)).extension() == ".JPG") || (fs::path(lista_archivos.at(indice)).extension() == ".png") || (fs::path(lista_archivos.at(indice)).extension() == ".PNG") || (fs::path(lista_archivos.at(indice)).extension() == ".tiff") || (fs::path(lista_archivos.at(indice)).extension() == ".TIFF") || (fs::path(lista_archivos.at(indice)).extension() == ".jfif") || (fs::path(lista_archivos.at(indice)).extension() == ".JFIF") || (fs::path(lista_archivos.at(indice)).extension() == ".jpeg") || (fs::path(lista_archivos.at(indice)).extension() == ".JPEG"))
      {
        std::cout << lista_archivos.at(indice) << "\n"; //for debugging purpose
        
        imagen = lista_archivos.at(indice).filename();
        std::cout << imagen << endl;

        // Show all errors concerning filesystem
        try{
        fs::copy_file((const fs::path)lista_archivos.at(indice), cwd /= imagen, copy_options::overwrite_existing);
        } catch(fs::filesystem_error& e)
        {
          std::cout << "Error: " << e.what() << endl;
        }
      }
    }

}

void createfolder(fs::path& cwd, fs::path& aux, fs::path& aux2)
{
  //create a new folder for the pictures
    cwd = current_path();                       //store current directory name in pointer to char cwd
    aux = cwd;                                  //auxiliar variable for future operations
    cwd /= "todas_las_imagenes";                //append new folder name to current directory path
    aux2 = cwd;                                 //save this path too, for the future (for cwd'll be later manipulated)

    if(create_directory(cwd) == -1)             //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado" << endl; //just for debugging

    std::vector<fs::path> values {cwd, aux, aux2};
}