#include <string>
#include <iostream>
#include <filesystem>
#include <direct.h>
#include <unistd.h>
#include <exception>
#include <vector>
namespace fs = std::filesystem;
const char* todas_las_imagenes;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;
using std::filesystem::recursive_directory_iterator;

namespace fs = std::filesystem;

//This is the source for Picture Retriever algorithm
//It'll work it all out, being called from a batchfile

int main()
{
    int indice;
    std::vector<string> lista_archivos;
    std::string path;
    cin >> path;
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;

    //create a new folder for the pictures
    //cout << "Current working directory: " << current_path() << endl;
    char *cwd = get_current_dir_name();
    cout << "Current working directory: " << cwd << endl;
    todas_las_imagenes = cwd.append("/todas_las_imagenes"); //could be done using "+" instead of append(), but latter is faster
    if(mkdir(todas_las_imagenes) == -1) //rmdir for removing
      cerr << "Error al crear el directorio: " << strerror(errno) << endl;
    else cout << "Directorio generado";

    //searching for .jpg images (to be extended to any image extension: .jpeg, .tiff, .png)
    for (const auto & file : recursive_directory_iterator(cwd)) //ojo: ¿cwd deberia ser tipo string?
    {
        //cout << file.path() << endl;
        lista_archivos.push_back(file.path());  //adding new found file to the end of the vector
    }
    indice = 0;
    while(lista_archivos)
    {
      if(PathFindExtension(lista_archivos[indice]) == ".jpg")

    }

    free(cwd);  //get_current_dir_name makes dynamic memory allocation, so I must free it after I'm done using it

    //copying files to folder
    fs::path sourceFile = "path/to/sourceFile.ext";
    fs::path targetParent = "path/to/target";
}
