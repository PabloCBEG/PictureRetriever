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
//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile



int main()
{
    int indice;
    std::vector<std::filesystem::path> lista_archivos;// = (std::vector<string>)malloc(1000000*sizeof(string));

    //create a new folder for the pictures
    std::filesystem::path cwd = current_path(); //store current directory name in pointer to char cwd
    ///cout << "Current working directory: " << cwd << endl;
    //todas_las_imagenes = cwd.append("\\todas_las_imagenes");
    cwd /= "todas_las_imagenes";
    ///cout << "Current working directory: " << cwd << endl;
    /*if(mkdir(cwd) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado"; //just for debugging*/
    if(create_directory(cwd) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado"; //just for debugging

//***************************************************************************************************************

    //searching for .jpg images (to be extended to any image extension: .jpeg, .tiff, .png)
    for (const auto & file : recursive_directory_iterator(cwd))// /= "..")) //ojo: cwd deberia ser tipo string?
    {
        lista_archivos.push_back(file.path());  //adding new found file to the end of the vector
    }

    std::filesystem::copy_file((const std::filesystem::path) cwd /= "Almonte 04.jpg", cwd /= "todas_las_imagenes", true);

    /*for(indice = 0; indice < lista_archivos.size(); indice++)
    {
      if((std::filesystem::path(lista_archivos.at(indice)).extension() == ".jpg") || (std::filesystem::path(lista_archivos.at(indice)).extension() == ".JPG"))
        //std::cout << lista_archivos.at(indice) << "\n"; //for debugging purpose
        std::filesystem::copy_file(lista_archivos.at(indice), cwd, true);// /= "todas_las_imagenes");//, std::filesystem::copy_options::overwrite_existing);
    }*/

}
