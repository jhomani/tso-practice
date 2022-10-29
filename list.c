#include <dirent.h>
#include <stdio.h>

int main(void) {
    DIR *directory;
    struct dirent *currect;

    directory = opendir(".");

    if (directory != NULL) {

        while ((currect = readdir(directory)) != NULL) {
                char *name;
                name = currect->d_name;

                if(strcmp(name, ".") == 1 && strcmp(name, "..") == 1) {

                        if(currect->d_type == 4 ) {    
                            printf("\033[0;34m");
                        }

                        printf("%s\n", currect->d_name);

                        printf("\033[0m");
                }
        }

        closedir(directory);
    }
    return(0);
}
