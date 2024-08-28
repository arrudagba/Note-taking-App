#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 1024

int main() {
    char *buffer = (char *)malloc(INITIAL_SIZE * sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    size_t size = INITIAL_SIZE;
    size_t length = 0;
    char c;

    printf("Enter text (Ctrl+D to end):\n");
    while ((c = getchar()) != EOF) {
        if (length + 1 >= size) {
            size *= 2;
            buffer = (char *)realloc(buffer, size * sizeof(char));
            if (buffer == NULL) {
                perror("Failed to reallocate memory");
                return EXIT_FAILURE;
            }
        }
        buffer[length++] = c;
    }
    buffer[length] = '\0';  // Null-terminate the string

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fwrite(buffer, sizeof(char), length, file);
    fclose(file);
    free(buffer);

    printf("Text written to output.txt\n");
    return EXIT_SUCCESS;
}
