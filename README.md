# PictureRetriever
Algorithm that allows user to automatically copy all images in a directory (&amp; branches) to a folder.
*This will be done by including compiled programs (.cpp, .o) in a batchfile so as to being able to execute it from cmd window
OR
in Python*
It was finally done just by building .cpp program, getting an executable

The action includes:
1. Searching for .jpg / .png / .tiff : easily extensible to other kind of image files (parameter inside *if* statement)
2. Creating new folder in parent directory
3. Copying all those images in the new folder

*Aim: make it portable. i.e. NOT using std::filesystem nor any boost dependencies
*Aim: make it w Python
