#include <string.h>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <sys/stat.h>

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
//It'll work it all out. When built, generates an executable which works ON WINDOWS

//Functions
void createfolder(fs::path& , fs::path& , fs::path& );
void iteratefolder(std::vector<fs::path>& , fs::path& );
void seekforimages(fs::path& , fs::path& , fs::path& , std::vector<fs::path>& );

size_t getFilesize(const std::string& );

void filterlist(std::vector<fs::path>& );

int main()
{
    std::vector<fs::path> lista_archivos;     //vector variable used to store filepaths of all files in directory
    fs::path cwd; fs::path aux; fs::path aux2;

    createfolder(cwd, aux, aux2);

    iteratefolder(lista_archivos, aux);
  //cout << "todo bien" << endl;
  
  //cout << "todo bien" << endl;
    seekforimages(cwd, aux2, lista_archivos);
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
    else ;//cout << "Directorio generado" << endl; //just for debugging

    std::vector<fs::path> values {cwd, aux, aux2};
}

void iteratefolder(std::vector<fs::path>& lista_archivos, fs::path& aux)
{
  //iterates current dir; generates a path list
  recursive_directory_iterator it;  //variable of type rec.dir.iterator so it can be used as a "pointer" to the current directory when iterating
  //searching for .jpg images, extended to any image extension: .jpeg, .tiff, .png, .jfif
  for (const auto & file : it = recursive_directory_iterator(aux))
  {
    lista_archivos.push_back(file.path());  //adding new found file to the end of the vector

    if((file.path().extension() == ".jpg") ||
      (file.path().extension() == ".JPG") ||
      (file.path().extension() == ".png") ||
      (file.path().extension() == ".PNG") ||
      (file.path().extension() == ".tiff") ||
      (file.path().extension() == ".TIFF") ||
      (file.path().extension() == ".jfif") ||
      (file.path().extension() == ".JFIF") ||
      (file.path().extension() == ".jpeg") ||
      (file.path().extension() == ".JPEG"));
    else 
    {
      lista_archivos.pop_back();
    }
    
    if(fs::current_path().filename() == "todas_las_imagenes") //not entering newly created folder, for I'd found duplicates
      it.disable_recursion_pending();
      
  }
}

void filterlist(std::vector<fs::path>& lista_archivos)
{
  int i, j;
  for(i = 0; i < lista_archivos.size(); i++)
  {
    for(j = 0; j < lista_archivos.size(); j++)
    {
      if(lista_archivos.at(i).filename() == lista_archivos.at(j).filename() && i != j)
      {
        if()
      }
    }
  }
}

void seekforimages(fs::path& cwd, fs::path& aux2, std::vector<fs::path>& lista_archivos)
{
  //looks for the images and COPIES them to the desired folder (new folder created)

  int indice;
  fs::path imagen;

  cwd = aux2;

  for(indice = 0; indice < lista_archivos.size(); indice++)
  {
    imagen = lista_archivos.at(indice).filename();

    fs::path imagen_aux;

    // Show all errors concerning filesystem
    try{

        fs::copy_file((const fs::path)lista_archivos.at(indice), cwd /= imagen, copy_options::overwrite_existing);

        //fs::copy_file((const fs::path)lista_archivos.at(indice), cwd /= imagen, copy_options::skip_existing);
    } catch(fs::filesystem_error& e)  //arreglar: o comparar size, o no overwrite, sino duplicar.
    {                                 //o comparando fecha de captura (metadata, detalles)
      std::cout << "Error: " << e.what() << endl;
    }
  }
}

/*size_t getFilesize(const std::string& nombre)
{
  struct stat st;
  if(stat(nombre.c_str(), &st) != 0)
  {
    return 0;
  }
  return st.st_size;
}*/

//to check filesize:
/*
  Create a new vector object: there we'll store different file sizes.
  Compare new file name to the whole list of already registered files. ONLY images.
  IF two files have same name, we'll compare their sizes.
*/