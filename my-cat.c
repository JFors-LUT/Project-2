#include <stdio.h>
#include <stdlib.h>

//Set buffer size for reading file in chunks
#define BUFFER_SIZE 1024    

void print_file(const char *filename) {
    FILE *filepointer = fopen(filename, "r");
    // check if filename can be opened
    if (filepointer == NULL) {
        fprintf(stderr, "my-cat: cannot open file");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    //get BUFFER_SIZE chars from file to buffer through filepointer and print buffer
    while (fgets(buffer, BUFFER_SIZE, filepointer) != NULL) {
        printf("%s", buffer);
    }

    fclose(filepointer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    // Loop through files provided in command line arguments
    //file arguments start from index 1, 0 is the program name
    for (int file = 1; file < argc; file++) {
        print_file(argv[file]);
    }

    return 0;
}