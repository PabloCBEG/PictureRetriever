#include <string.h>
#include <string>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <sys/stat.h>
#include <sstream>

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
void seekforimages(fs::path& , fs::path& , std::vector<fs::path>& , std::vector<fs::path>& );

void filterlist(std::vector<fs::path>& , std::vector<fs::path>& );

int main()
{
    std::vector<fs::path> lista_archivos;     //vector variable used to store filepaths of all files in directory
    fs::path cwd; fs::path aux; fs::path aux2;
    std::vector<fs::path> lista_archivos_aux;

    createfolder(cwd, aux, aux2);

    iteratefolder(lista_archivos, aux);

    seekforimages(cwd, aux2, lista_archivos, lista_archivos_aux);
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
      (file.path().extension() == ".JPEG") ||
      (file.path().extension() == ".svg") ||
      (file.path().extension() == ".SVG") ||
      (file.path().extension() == ".mp4") || //akes a while o coy video files
      (file.path().extension() == ".MP4") ||
      (file.path().extension() == ".mkv") ||
      (file.path().extension() == ".MKV") ||
      (file.path().extension() == ".gif") ||
      (file.path().extension() == ".GIF") ||
      (file.path().extension() == ".avi") ||
      (file.path().extension() == ".AVI") ||
      (file.path().extension() == ".mov") ||
      (file.path().extension() == ".MOV") ||
      (file.path().extension() == ".m4p") ||
      (file.path().extension() == ".M4P") ||
      (file.path().extension() == ".m4v") ||
      (file.path().extension() == ".M4V"));
    else 
    {
      lista_archivos.pop_back();
    }
    
    if(fs::current_path().filename() == "todas_las_imagenes") //not entering newly created folder, for I'd found duplicates
      it.disable_recursion_pending();
  }
  //cout << "Todo bien" << endl;
  for(int i = 0; i < lista_archivos.size(); i++){ cout << fs::path(lista_archivos.at(i)) << endl;}
}

void filterlist(std::vector<fs::path>& lista_archivos, std::vector<fs::path>& lista_archivos_aux)
{
  uint32_t i, j;
  lista_archivos_aux = lista_archivos;
  for(i = 0; i < lista_archivos.size(); i++)
  {
    for(j = 0; j < lista_archivos.size(); j++)
    {

      if(lista_archivos.at(i).filename() == lista_archivos.at(j).filename() && i != j && lista_archivos_aux.at(i).filename() == lista_archivos_aux.at(j).filename()) //fs::path(lista_archivos.at(i)).compare(lista_archivos.at(j)) && i != j
      {
        //filtering condition
        uint32_t tam1 = fs::file_size(lista_archivos.at(i));
        uint32_t tam2 = fs::file_size(lista_archivos.at(j));
        if(tam1 == tam2)
        {
          lista_archivos.erase(lista_archivos.begin() + j);
          lista_archivos_aux.erase(lista_archivos_aux.begin() + j);
        }
        else
        {
          fs::path ex = lista_archivos.at(j).extension();
          const char* indice_aux = std::to_string(i).c_str();
          fs::path nuevo = "_repeated_name_";
          nuevo += indice_aux;  //adding i index to the name guarantees no name is going to repeat:
                                //i.e., if we had 3 files w same name but different sizes,
                                //they'd be at different positions within the list, hence have different
                                //i index in for loop
          fs::path termin = nuevo += ex;
          lista_archivos_aux.at(j).replace_extension();
          //cout << lista_archivos.at(j).filename() << endl;
          lista_archivos_aux.at(j) += termin;
          //cout << lista_archivos.at(j).filename() << endl;
        }
      }
    }
  }
  //for(i = 0; i < lista_archivos.size(); i++){ cout << fs::path(lista_archivos.at(i)) << endl; cout << fs::path(lista_archivos_aux.at(i)) << endl; }
}

void seekforimages(fs::path& cwd, fs::path& aux2, std::vector<fs::path>& lista_archivos, std::vector<fs::path>& lista_archivos_aux)
{
  //looks for the images and COPIES them to the desired folder (new folder created)

  uint32_t indice;
  fs::path imagen;

  filterlist(lista_archivos, lista_archivos_aux);

  for(indice = 0; indice < lista_archivos.size(); indice++)
  {
    imagen = lista_archivos_aux.at(indice).filename();

    cwd = aux2;

    // Show all errors concerning filesystem
    try{
        fs::copy_file((const fs::path)lista_archivos.at(indice), cwd /= imagen, copy_options::overwrite_existing);
    } catch(fs::filesystem_error& e)  //arreglar: o comparar size, o no overwrite, sino duplicar.
    {                                 //o comparando fecha de captura (metadata, detalles)
      std::cout << "Error: " << e.what() << endl;
    }
  }
}