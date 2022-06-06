# PictureRetriever
Algorithm that allows user to automatically copy all images and videos in a directory (&amp; branches) to a folder.
*This will be done by including compiled programs (.cpp, .o) in a batchfile so as to being able to execute it from cmd window
OR
in Python*
It was finally done just by building .cpp program, getting an executable

The action includes:
1. Searching for .jpg / .png / .tiff : easily extensible to other kind of image files (parameter inside *if* statement)
2. Creating new folder in parent directory
3. Copying all those images in the new folder

Note:
1. Added video files
2. Won't by the moment detect equal files if they have different names. Could be added: not needed.

Further modifications:
1. It being able to eliminate copies of the same image or video when they've got different names.
2. Accessing image metadata in order to being able to check the shot date

*Aim: make it w Python

