#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define ERROR    3

/** Colors to print on console **/
void reset () {
  printf("\033[0m");
}

void printRed (const char *format) {
	printf("\033[1;31m");
	printf("\n⋆⋆⋆ ERROR ⋆⋆⋆\n\n>> ");
	printf(format);
	printf("\n\n");
	reset();
}
void printCyan (const char *format) {
	printf("\033[0;36m");
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
int readFile(char path[100]) {
        FILE* file;
        char fileLine;
 
        file = fopen(path, "r");

        if (NULL == file) {
            printRed("Incorrect file path, please check file path!");
	    return ERROR;
        }

        while ((fileLine = fgetc(file)) != EOF) {
		printf("%c", fileLine);
	}

        fclose(file);

	return OK;
}

/*
 * Function to change current location 
 */
int changeLocation(char path[100]) {
	if(chdir(path) < 0) {
            printRed("Incorrect location, please check it!");
	}
}

/*
 * Function to clear console 
 */
int clearConsole() {
	printf("\e[1;1H\e[2J");
}

/*
 * Function to show manual
 */
int showManual() {
	printf(
		"This are available commands\n\n"
		"list: To list files where you are located\n"
		"view [path]: To show file content\n"
		"change [path]: To change location\n"
		"exit: To close program\n"
		"clear: To clear console\n"
		"help: To show all availables commands\n"
	);
}


/*
 * get user input line as single string
 */
static int getLine (char *buff, size_t sz) {
    int ch, extra;

    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while(((ch = getchar()) != '\n') && (ch != EOF)) extra = 1;

        return (extra == 1) ? TOO_LONG : OK;
    }

    // To remove bread line
    buff[strlen(buff) - 1] = '\0';

    return OK;
}

int main(void) {
	char inputLine[50];

	while(1) {
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));

		printCyan(strcat(cwd, "➤ "));
		getLine(inputLine, sizeof(inputLine));

		char* command = strtok(inputLine, " ");
		char* argument = strtok(NULL, " ");;

		if(command != NULL) {
			if(strcmp(command, "exit") == 0)
				exit(EXIT_SUCCESS);
			else if(strcmp(command, "list") == 0)
				listFiles();
			else if(strcmp(command, "help") == 0)
				showManual();
			else if(strcmp(command, "clear") == 0)
				clearConsole(); 
			else if(strcmp(command, "view") == 0 && argument != NULL)
				readFile(argument);
			else if(strcmp(command, "change") == 0 && argument != NULL)
				changeLocation(argument);
			else
				printRed(
					"Invalid command \n\n"
					"Enter 'help' to cheack available commands"
				);

		}

	}

	return(0);
}

