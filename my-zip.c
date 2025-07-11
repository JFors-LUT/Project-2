#include <stdio.h>
#include <stdlib.h>

  

void zip_file(const char *filename, int *char_counter, int *previous_char , int is_last) {


    FILE *filepointer = fopen(filename, "r");
    // check if filename can be opened
    if (filepointer == NULL) {
        fprintf(stderr, "my-zip: cannot open file");
        exit(1);
    }

    //writing 4 byte integer
    size_t item_size = 4;
    //number of items to write, one 4 byte integer
    size_t item_count = 1;

    int current_char; 

    // read characters from the file one by one
    while ((current_char = fgetc(filepointer)) != EOF) {
       //first character to read
        if (*previous_char == EOF) {
            *previous_char = current_char;
            *char_counter = 1;
        //same char increases count
        } else if (current_char == *previous_char) {
            (*char_counter)++;
        } else {
                // write 4-byte count
                fwrite(char_counter, item_size, item_count, stdout);
                // write the character if new != previous 
                fputc(*previous_char, stdout);
            
                // reset for new character
                *previous_char = current_char;
                *char_counter = 1;
        }
    }

    // handle final run
    if (is_last && *previous_char != EOF) {
        fwrite(char_counter, item_size, item_count, stdout);
        fputc(*previous_char, stdout);
    }

    fclose(filepointer);
}

int main(int argc, char *argv[]) {
       if (argc < 2) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

     // initialize to EOF to handle first character and character count between files correctly
    int previous_char = EOF; 
    int char_counter = 0;

    // Loop through files provided in command line arguments
    //file arguments start from index 1, 0 is the program name
    for (int file = 1; file < argc; file++) {
        int is_last = (file == argc - 1);
        zip_file(argv[file], &char_counter, &previous_char, is_last);
    }

    return 0;
}