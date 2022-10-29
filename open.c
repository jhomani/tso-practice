#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Driver code
void red () {
  printf("\033[1;31m");
}

void reset () {
  printf("\033[0m");
}


int main() {
        FILE* pointer;
        char fileLine;
        char path[100];

        scanf("%s", &path);
 
        pointer = fopen(path, "r");

        if (NULL == pointer) {
            red();
            printf("Path not found!");
            reset();
        }

        do {
                fileLine = fgetc(pointer);
                printf("%c", fileLine);

        } while (fileLine != EOF);

        fclose(pointer);

        return 0;
}
