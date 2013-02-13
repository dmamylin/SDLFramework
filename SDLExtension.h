/*
  Copyright (C) 2011 - 2012 by Dmitry Mamylin

  This source code is distributed for free and may be modified, redistributed, and
  incorporated in other projects (commerical, non-commerical and open-source)
  without restriction.  No attribution to the author is required.  There is
  no requirement to make the source code available (no share-alike required.)

  This source code is distributed "AS IS", with no warranty expressed or implied.
  The user assumes all risks related to quality, accuracy and fitness of use.

  Retain this copyright notice and add your own copyrights and revisions above
  this notice.
*/

#ifndef SDL_EXT_H
#define SDL_EXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifdef _WIN32
    #undef main
    #pragma comment(lib, "SDL.lib")
    //#pragma comment(lib, "SDLmain.lib")
    #pragma comment(lib, "SDL_ttf.lib")
#endif

#include "utilities/CTimer.h"
#include "math/points/point2.h"
#include "containers/color3.h"
#include "containers/rect2.h"
#include "SDLTypes.h"
#include "SDLWindow.h"

#endif