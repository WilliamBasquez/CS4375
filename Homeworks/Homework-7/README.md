#Homework 7: File Systems

The function *dirtree* takes a path, a starting number of spaces (to indent directories and subdirectories), and a character to represent whether or not to print the name of the current directory.
The approach taken was a recursive one, just so that we can take advantage of the "return where we left off before a new call" mechanism.

On the *main* function, we call the function *getcwd()* so that no matter where we run this program, we always have the current directory
Hence, there's no need to specify that every time.

The reason behind the *currentPrinted* parameter is to ensure that we do print the current directory and not only the subdirectories within the current one.
