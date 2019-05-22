#ifndef PCH_H
#define PCH_H

//#define VS_LEAK_CHECK
#ifdef VS_LEAK_CHECK
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
    #define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

// SDL
#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#else
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#endif

// C++ Standard Library
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <ctime>
#include <memory>
#include <cmath>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <stack>
#include <array>

// Disable asserts when not in debug
#ifndef _DEBUG
#define NDEBUG
#endif
#include <cassert>

#endif //PCH_H
