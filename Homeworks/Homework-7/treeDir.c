#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h> 
#include <sys/types.h>

/*References:
1) Dr. Roach slideshows
2) https://c-for-dummies.com/blog/?p=3246
3) https://www.geeksforgeeks.org/continue-statement-cpp/
4) https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
5) https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
6) https://www.ibm.com/support/knowledgecenter/SSLTBW_2.4.0/com.ibm.zos.v2r4.bpxbd00/rbasen.htm?view=embed
7) https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-fscc/fccd0313-0364-45bd-b75c-924fd6a5662f
8) https://stackoverflow.com/questions/1371261/get-current-directory-name-without-full-path-in-a-bash-script
*/
void dirtree(char *pathname, int indent, char currentPrinted) {
    int i;
    DIR *directory;
    struct dirent *subfolder;

    //If we cannot open a directory with the given pathname, simply return
    if (!(directory = opendir(pathname)))
        return;

    //New condition to print the name of the current directory
    //We increment indent by 4 only once (since we only print the current directory once)
    //Yet, this will help keep desired pattern with the following calls' indentation
    if(currentPrinted == 0){
        if(basename(pathname) != NULL)
            printf("/%s\n", basename(pathname));
        indent += 4;
    }

    while ((subfolder = readdir(directory)) != NULL) {
        if (subfolder->d_type == DT_DIR) {
            char newPath[1000];
            //First, we check that the subfolder is the same as the current directory's name, or the the parent directory
            //If they are, we continue execution starting from the while loop, else we keep executing the rest of the code
            if (strcmp(subfolder->d_name, ".") == 0 || strcmp(subfolder->d_name, "..") == 0)
                continue;

            //We copy the current path name into the new path that will be later examined
            strcpy(newPath, pathname);
            strcat(newPath, "/");
            strcat(newPath, subfolder->d_name);

            //Append the necessary spaces, and at the end concatenate the subfolder's path into the new path
            for(i = 0; i < indent; i++)
                printf("%c", ' ');
            printf("/%s\n", subfolder->d_name);

            //Recursive call to search for the subfolders, adding 4 spaces to each subfolder
            dirtree(newPath, indent + 4, 1);
        }
    }
    //We close the main directory, for good practice.
    closedir(directory);
}

int main() {
    //Right from the beginning, we get the current path where the .c file is on
    //If the function getcwd() can get the path, we call the dirtree() function
    //Otherwise we print a message with the error
    char currPath[PATH_MAX];
    if(getcwd(currPath, sizeof(currPath)) != NULL)
        dirtree(currPath, 0, 0); //Second number must be 0 if we want to print the name of the directory we are starting with; 1 = do NOT print current directory
    else
        printf("Oops, getcwd() could not determine path\n");

    return 0;
}
