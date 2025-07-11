#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void search_stdin(const char *searchterm) {
    char *line = NULL;
    size_t len = 0;

    //getline() to manage arbitary line length
    //function gets stdin from user and outputs if line includes searchterm
    while (getline(&line, &len, stdin) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }
    //free alloced memory once getline has done its thing
    free(line);

}

//give the function pointers to the file and searchterm
void print_line(const char *searchterm, const char *filename) {
    FILE *filepointer = fopen(filename, "r");
    // check if filename can be opened
    if (filepointer == NULL) {
        fprintf(stderr, "my-grep: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    // Read each line from the file, let getline allocate memory
    while (getline(&line, &len, filepointer) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }
    //free getline allocated memory
    free(line);
    fclose(filepointer);
}

int main(int argc, char *argv[]) {

    // no file provided
    if (argc < 2) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc == 2) {
        //function to read from user input stdin
        search_stdin(argv[1]);
    }
    // Loop through files provided in command line arguments
    //file arguments start from index 2, 1 is searchtern, 0 is the program name
    if (argc > 2){
        for (int file = 2; file < argc; file++) {
            print_line(argv[1], argv[file]);
        }
    }

    return 0;
}