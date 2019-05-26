#ifndef PCH_H
#define PCH_H

//#define VS_LEAK_CHECK
#ifdef VS_LEAK_CHECK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
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
#include <algorithm>
#include <array>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>

// Disable asserts when not in debug
#ifndef _DEBUG
#define NDEBUG
#endif
#include <cassert>

#endif //PCH_H
