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
//#include <gdiplus.h>

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
using std::basic_string;

//This is the source for Picture Retriever algorithm
//It'll work it all out.

//Functions
  //create a new folder for the pictures
void createfolder(fs::path& , fs::path& , fs::path& , fs::path& );
  //iterates current dir; generates a path list
void iteratefolder(std::vector<fs::path>& , fs::path& );
  //looks for the images and COPIES them to the desired folder (new folder created)
void seekforimages(fs::path& , fs::path& , std::vector<fs::path>& , std::vector<fs::path>& );
  //filters list: removes repeated files comparing size and date of modification. Works for images and video files.
void filterlist(std::vector<fs::path>& , std::vector<fs::path>& );

int main()
{
    //variable declaration
    std::vector<fs::path> lista_archivos; //vector variable used to store filepaths of all files in directory
    fs::path targetdirectory; fs::path destinydirectory;  //added in order to being able to operate in 
                                                          //the desired (and indicated) directory
    fs::path aux; fs::path aux2;                      //axiliary variables for working w directory
                                                      //routes without losing the original value
    std::vector<fs::path> lista_archivos_aux;
    
    //program flowline
    createfolder(targetdirectory, destinydirectory, aux, aux2);

    cout << "Hold on while we work this out for you. You can keep working on something else..." << endl;

    iteratefolder(lista_archivos, aux);

    seekforimages(destinydirectory, aux2, lista_archivos, lista_archivos_aux);

    cout << "Done working. Thanks for waiting" << endl;

    system("pause");
}

void createfolder(fs::path& targetdirectory, fs::path& destinydirectory, fs::path& aux, fs::path& aux2)
{
  //create a new folder for the pictures

  std::string saux;                         //auxiliary string variable to store cin input
  //Ask for target directory
  std::cout << "Introduzca la ruta completa del directorio donde quiere realizar la busqueda: ";
  std::getline(std::cin, saux);
  targetdirectory = saux;                   //store target directory name in path cwd

  //ask for destiny directory
  std::cout << "Introduzca la ruta completa del directorio donde quiere almacenar las imagenes: ";
  std::getline(std::cin, saux);             //just in case route contains blankspaces
  destinydirectory = saux;

  aux = targetdirectory;                    //auxiliary variable for future operations
  destinydirectory /= "todas_las_imagenes"; //append new folder name to current directory path
  aux2 = destinydirectory;                  //save this path too, for the future (for cwd'll be later manipulated)

  if(create_directory(destinydirectory) == -1)  //both create directory and check it was succesful //rmdir for removing
    cerr << "Error al crear el directorio: " << strerror(errno) << endl;
  else ; cout << "Directorio generado" << endl; //just for debugging
}

void iteratefolder(std::vector<fs::path>& lista_archivos, fs::path& aux)
{
  //iterates current dir; generates a path list
  //uses targetdirectory (aux must be targetdirectory)

  recursive_directory_iterator it;  //variable of type rec.dir.iterator so it can be used as
                                    //a "pointer" to the current directory when iterating
  //searching for .jpg, .jpeg, .tiff, .png, .jfif, images, and videos
  for (const auto & file : it = recursive_directory_iterator(aux))
  {
    lista_archivos.push_back(file.path());  //adding new found file to the end of the vector

    if((file.path().extension() == ".jpg") || (file.path().extension() == ".JPG") ||
      (file.path().extension() == ".png") || (file.path().extension() == ".PNG") ||
      (file.path().extension() == ".tiff") || (file.path().extension() == ".TIFF") ||
      (file.path().extension() == ".jfif") || (file.path().extension() == ".JFIF") ||
      (file.path().extension() == ".jpeg") || (file.path().extension() == ".JPEG") ||
      (file.path().extension() == ".svg") || (file.path().extension() == ".SVG") ||
      (file.path().extension() == ".mp4") || //takes a while to copy video files
      (file.path().extension() == ".MP4") ||
      (file.path().extension() == ".mkv") || (file.path().extension() == ".MKV") ||
      (file.path().extension() == ".gif") || (file.path().extension() == ".GIF") ||
      (file.path().extension() == ".avi") || (file.path().extension() == ".AVI") ||
      (file.path().extension() == ".mov") || (file.path().extension() == ".MOV") ||
      (file.path().extension() == ".m4p") || (file.path().extension() == ".M4P") ||
      (file.path().extension() == ".m4v") || (file.path().extension() == ".M4V"));
    else 
    {
      lista_archivos.pop_back();
    }
    //cout << "Lista generada" << endl;
    if(fs::current_path().filename() == "todas_las_imagenes") //not entering newly created folder, for I'd found duplicates
      it.disable_recursion_pending();
  }
}

void filterlist(std::vector<fs::path>& lista_archivos, std::vector<fs::path>& lista_archivos_aux)
{
  //filters list: removes repeated files comparing size and date of modification. Works for images and video files.
  //              different filtering criteria should be used for document files

  uint32_t i, j;  //local indices for "for" loops
  lista_archivos_aux = lista_archivos;  //auxiliary file list used for comparison and renaming
  for(i = 0; i < lista_archivos.size(); i++)
  {
    for(j = 0; j < lista_archivos.size(); j++)
    {
      if(lista_archivos.at(i).filename() == lista_archivos.at(j).filename() && i != j && lista_archivos_aux.at(i).filename() == lista_archivos_aux.at(j).filename()) //fs::path(lista_archivos.at(i)).compare(lista_archivos.at(j)) && i != j
      {
        //filtering condition
          //sizes
        uint32_t tam1 = fs::file_size(lista_archivos.at(i));
        uint32_t tam2 = fs::file_size(lista_archivos.at(j));
          //modification date (to the sec on Windows)
        fs::file_time_type dat1 = fs::last_write_time(lista_archivos.at(i));
        fs::file_time_type dat2 = fs::last_write_time(lista_archivos.at(j)); //fs::file_time_type
        if(tam1 == tam2)// || dat1 == dat2)
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
          lista_archivos_aux.at(j) += termin;
        }
      }
    }
  }
}

void seekforimages(fs::path& destinydirectory, fs::path& aux2, std::vector<fs::path>& lista_archivos, std::vector<fs::path>& lista_archivos_aux)
{
  //looks for the images and COPIES them to the desired folder (new folder created)
  //uses destinydirectory: aux2 must be destinydirectory
  cout << "hemos llegado" << endl;
  uint32_t indice;  //index for looping file list
  fs::path imagen;  //variable to store filename and append it to destiny directory route

  //First of all, we filter the list to erase repeated files
  filterlist(lista_archivos, lista_archivos_aux);

  for(indice = 0; indice < lista_archivos.size(); indice++)
  {
    imagen = lista_archivos_aux.at(indice).filename();

    destinydirectory = aux2;

    // Show all errors concerning filesystem
    try
    {
      fs::copy_file((const fs::path)lista_archivos.at(indice),
                    destinydirectory /= imagen,
                    copy_options::overwrite_existing);  //after filtering the list, any image
                                                        //which, by chance, is repeated (probably
                                                        //won't happen) shall be overwritten
    }
    catch(fs::filesystem_error& e)
    {
      std::cout << "Error: " << e.what() << endl;
    }
  }
}