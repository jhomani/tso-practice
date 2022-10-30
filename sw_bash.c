#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

/** Colors to print on console **/
void reset () {
  printf("\033[0m");
}

void printRed (const char *format) {
	printf("\033[1;31m");
	printf(format);
	reset();
}
void printCyan (const char *format) {
	printf("\033[0;36m");
	printf(format);
	reset();
}

void printPurple (const char *format) {
	printf("\033[0;35m");
	printf(format);
	reset();
}

/*
 * Function to list files in currente directory
 */
void listFiles() {
    DIR *directory;
    struct dirent *currect;
    directory = opendir(".");

    if (directory != NULL) {
        while ((currect = readdir(directory)) != NULL) {
                char *name;
                name = currect->d_name;

                if(strcmp(name, ".") && strcmp(name, "..")) { // ask to teacker

                        if(currect->d_type == 4 ) {
				printf("\033[0;34m");
			} 

                        printf("%s\n", currect->d_name);

                        printf("\033[0m");
                }
        }

        closedir(directory);
    }
}


/*
 * Function to read file given name
 */
void readFile(char path[100]) {
        FILE* file;
        char fileLine;
 
        file = fopen(path, "r");

        if (NULL == file) {
            printRed("Path not found!");
        }

        while ((fileLine = fgetc(file)) != EOF) {
		printf("%c", fileLine);
	}

        fclose(file);
}

/*
 * Function to change current location 
 */
int changeLocation(char path[100]) {
	if(chdir(path) < 0) {
	    //exit(EXIT_FAILURE); handle error
	}
}


static int getLine (/*char *prmpt,*/ char *buff, size_t sz) {
    int ch, extra;
    //size_t *sz = sizeof(buff);

    // Get line with buffer overrun protection.
//    if (prmpt != NULL) {
//        printf ("%s", prmpt);
//        fflush (stdout);
//    }

    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while(((ch = getchar()) != '\n') && (ch != EOF)) extra = 1;

        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff) - 1] = '\0';

    return OK;
}


int main(void) {
	char inputLine[50];
	char argument[50];

	while(1) {
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));

		printCyan(strcat(cwd, "➤ "));
		getLine(inputLine, sizeof(inputLine));

		char* command = strtok(inputLine, " ");
		char* argument = strtok(NULL, " ");;

		if(command != NULL) {
			if(strcmp(command, "exit") == 0) exit(EXIT_SUCCESS);
			else if(strcmp(command, "list") == 0) listFiles();
			else if(strcmp(command, "view") == 0 && argument != NULL) readFile(argument);
			else if(strcmp(command, "change") == 0 && argument != NULL) changeLocation(argument);

			//printf("command: %s\n", command);
			//printf("argument: %s\n", argument);
		}

	}

	return(0);
}

