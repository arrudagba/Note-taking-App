#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>

#define INITIAL_SIZE 1024

char* buffer = NULL; 
size_t size = INITIAL_SIZE;
size_t length = 0;

void writeonscreen(LfFont *ptr) { 
    if (!buffer) {
        buffer = (char *)malloc(INITIAL_SIZE * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to allocate memory");
            return;
        }
        buffer[0] = '\0'; 
    }

    lf_push_font(ptr);
    lf_text(buffer);
    lf_pop_font();
}

void char_callback(GLFWwindow* window, unsigned int codepoint) { 
    if (length + 1 >= size) {
        size *= 2;
        buffer = (char *)realloc(buffer, size * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to reallocate memory");
            return;
        }
    }

    int bytes = wctomb(&buffer[length], codepoint);
    if (bytes >= 0) {
        length += bytes;
        buffer[length] = '\0';
    } else {
        fprintf(stderr, "Conversion failed: Multibyte ou caractere largo inválido\n");
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) { 
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        if (length + 1 >= size) {
            size *= 2;
            buffer = (char *)realloc(buffer, size * sizeof(char));
            if (buffer == NULL) {
                perror("Failed to reallocate memory");
                return;
            }
        }
        buffer[length++] = '\n';
        buffer[length] = '\0';
    }

    if (key == GLFW_KEY_BACKSPACE && action != GLFW_RELEASE && length > 0) {
        int bytes_to_erase = 1;
        while (length - bytes_to_erase > 0 && (buffer[length - bytes_to_erase] & 0xC0) == 0x80) {
            bytes_to_erase++;
        }

        length -= bytes_to_erase;
        buffer[length] = '\0';
    }
}

