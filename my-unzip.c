#include <stdio.h>
#include <stdlib.h>

  

void unzip_file(const char *filename) {
    FILE *filepointer = fopen(filename, "r");
    // check if filename can be opened
    if (filepointer == NULL) {
        exit(1);
    }

    //writing 4 byte integer
    size_t item_size = 4;
    //number of items to write, one 4 byte integer
    size_t item_count = 1;

    int char_count; 
    char ch;

    // read item_size bytes from the file and store to char_count
    while ((fread(&char_count, item_size, item_count, filepointer)) == 1) {
        // read the character that follows the count and check for EOF
        ch = fgetc(filepointer);
        if (ch == EOF) {
            exit(1);
        }
        // write the character char_count times to standard output
        for (int i = 0; i < char_count; i++) {
            printf("%c", ch);
        }

    }

    fclose(filepointer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Loop through files provided in command line arguments
    //file arguments start from index 1, 0 is the program name
    for (int file = 1; file < argc; file++) {
        unzip_file(argv[file]);
    }

    return 0;
}