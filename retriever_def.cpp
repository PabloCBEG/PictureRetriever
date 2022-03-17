#include <string.h>
#include <stdint.h>
#include <iostream>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
#include <filesystem>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::cerr;
using std::filesystem::create_directory;
using std::filesystem::current_path;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile

int main()
{
    int indice;

    //create a new folder for the pictures
    std::filesystem::path cwd = current_path(); //store current directory name in pointer to char cwd

    cwd /= "todas_las_imagenes";

    if(create_directory(cwd) == -1) //both create directory and check it was succesful //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado"; //just for debugging

//*******************************************************

    
