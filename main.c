#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>
#include "filehandling.h"

#define WIN_MARGIN 20.0f

static int winw = 1280, winh = 720;
static LfFont titlefont;
static LfFont buttonfont;

static void rendertopbar(){
  lf_push_font(&titlefont);
  lf_text("Notepad");
  lf_pop_font();

  lf_push_font(&buttonfont);
  {
    const float width = 110.0f;
    const float height = 5.0f;
    
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 2.0f);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    props.color = (LfColor){74,177,74,255};
    props.border_width = 0.0f;
    props.corner_radius = 7.0f;
    lf_push_style_props(props);
    lf_set_line_should_overflow(false);


    if(lf_button_fixed("New File", width, height) == LF_CLICKED){
      createfile();
    } 
    lf_set_line_should_overflow(true);
    lf_pop_style_props();  
  }
  lf_pop_font();

  lf_push_font(&buttonfont);
  {
    const float width = 110.0f;
    const float height = 5.0f;
    
    lf_set_ptr_x_absolute(winw - (width * 2.5f) - WIN_MARGIN * 2.0f);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    props.color = (LfColor){74,177,169,255};
    props.border_width = 0.0f;
    props.corner_radius = 7.0f;
    lf_push_style_props(props);
    lf_set_line_should_overflow(false);
       
    if(lf_button_fixed("Open File", width, height) == LF_CLICKED){
      openfile();
    } 
    lf_set_line_should_overflow(true);
      lf_pop_style_props();  
    }
    lf_pop_font();
}

int main(void) {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(winw, winh, "Notes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    lf_init_glfw(winw, winh,window);
    
    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter-bold.ttf", 30);
    buttonfont = lf_load_font("./fonts/inter.ttf", 15);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.07f, 0.07f, 0.07f, 0.07f);

        lf_begin();
        
        //div topbar
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), false);

        rendertopbar();

        lf_div_end();

        //div text
        LfUIElementProps props = lf_get_theme().div_props;
        props.corner_radius = 10.0f;
        props.color = (LfColor){30,30,30,255};
        lf_push_style_props(props);
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN + 50.0f}), ((vec2s){(winw - 50.0f) - WIN_MARGIN * 2.0f, (winh - 50.0f) - WIN_MARGIN * 2.0f}), true);
        

        lf_pop_style_props();
        lf_div_end();

        lf_end();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    lf_free_font(&titlefont);
    lf_free_font(&buttonfont);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//gcc -o main  main.c filehandling.c -lleif -lglfw -lm -lGL -lclipboard -lxcb
