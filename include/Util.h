#include <iostream>
#include <cmath>

/////////////
// DEBUG
/////////////

#define W(x) std::cerr << "\033[31m" << #x << "=" << x << "\033[0m" << "\n";

/////////////
// UTIL
/////////////

#define UNUSED(x)   (void)x
#define EQUAL(x, y) fabs(x - y) < EPS
#define RAND        static_cast <float> (rand()) / static_cast <float> (RAND_MAX) // 0.0 to 1.0

/////////////
// MATH
/////////////

#define PI  (float) 3.141592653589793
#define TAO (float) 2.0 * PI
#define EPS 0.00001

/////////////
// COLOR
/////////////

#define RED            "\x1b[31m"
#define GREEN          "\x1b[32m"
#define YELLOW         "\x1b[33m"
#define BLUE           "\x1b[34m"
#define MAGENTA        "\x1b[35m"
#define CYAN           "\x1b[36m"
#define RESET          "\x1b[0m"

/////////////
// SDL KEY & MOUSE
/////////////

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define SPACE_BAR         SDLK_SPACE

#define A_KEY   SDLK_a
#define D_KEY   SDLK_d
#define W_KEY   SDLK_w
#define S_KEY   SDLK_s

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT