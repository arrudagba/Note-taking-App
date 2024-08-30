#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>

extern char* buffer; 

void writeonscreen(LfFont *ptr); 
void char_callback(GLFWwindow* window, unsigned int codepoint); 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); 

