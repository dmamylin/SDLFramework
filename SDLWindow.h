#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "SDLInput.h"

class SDLWindow
{
    friend class SDLRenderer;

	private:
		SDL_Surface*        display;
        SDLInput            inputManager;
		bool	            isRun;
        bool                isFullScr;
		
	public:
		SDLWindow() :
          isRun(true), display(NULL) { }

        void Initialize(const rect2<u16>&, const bool, const char*);
        void Initialize(const u16, const u16, const bool, const char*);
        void Release(void);
        void BeginScene(const u32);
        void BeginScene(const color3<u8>&);
        void EndScene(void);
        
        inline void SetCursorVisible(bool flag) { SDL_ShowCursor(int(flag)); }
        inline void Stop(void)                  { isRun = false;             }        

        //Get methods
        inline u16          GetWidth(void)          const { return display->w + 1; }
        inline u16          GetHeight(void)         const { return display->h + 1; }
        inline SDL_Surface* GetDisplaySurface(void) const { return display;        }
               bool         Run(void);

        //IO routine
        //Keyboard
        inline bool IsKeyDown(SDLKey key)    const { return inputManager.keyboardState[key] != INPUT_UP; }
        inline bool IsKeyUp(SDLKey key)      const { return inputManager.keyboardState[key] == INPUT_UP; }
               bool IsKeyPressed(SDLKey key);
               bool IsActive(void);
        //Mouse
        bool IsMouseDown(u8) const;
        bool IsMouseUp(u8)   const;
        bool IsMousePressed(u8);
        void SetMousePosition(const point2<u16>& newPos) { SDL_WarpMouse(newPos.x, newPos.y); }
        point2<s32> GetMousePosition(void);
};

void SDLWindow::Initialize(const rect2<u16>& resolution, const bool full, const char* caption)
{
    u32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF | (full ? SDL_FULLSCREEN : 0);

    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ||
         !SDL_VideoModeOK((s32)resolution.width, (s32)resolution.height, 32, flags) )
    {
        puts("Unable to init SDL");
        exit(1);
    }

    SDL_WM_SetCaption(caption, NULL);

    display = SDL_SetVideoMode(resolution.width, resolution.height, 32, flags);

    if ( !display )
    {
        puts("Unable to create device");
        SDL_Quit();
        exit(1);
    }
}

inline void SDLWindow::Initialize(const u16 w, const u16 h, const bool full, const char* caption)
{
    Initialize( rect2<u16>(w, h), full, caption );
}

inline void SDLWindow::Release(void)
{
    SDL_FreeSurface(display);
    SDL_Quit();
}

inline void SDLWindow::BeginScene(const u32 color)
{        
    SDL_FillRect(display, NULL, color);
}

inline void SDLWindow::BeginScene(const color3<u8>& color)
{
    BeginScene(SDL_MapRGB(display->format, color.r, color.g, color.b));
}

inline void SDLWindow::EndScene(void)
{
    SDL_UpdateRect(display, 0, 0, display->w + 1, display->h + 1);
    SDL_Flip(display);
}

inline bool SDLWindow::Run(void)
{
    if ( !inputManager.CatchEvents() )
        Stop();

    return isRun;
}

inline bool SDLWindow::IsKeyPressed(SDLKey key)
{
    bool result = inputManager.keyboardState[key] == INPUT_PRESSED;
    if (result)
        inputManager.keyboardState[key] = INPUT_DOWN;

    return result;
}

inline bool SDLWindow::IsActive(void)
{    
    return inputManager.activeState.focus && inputManager.activeState.input;
}

inline bool SDLWindow::IsMouseDown(u8 button) const
{
    if ( (button == 0) || (button > 3) )
        return false;
    return inputManager.mouseState[button - 1] != INPUT_UP;
}

inline bool SDLWindow::IsMouseUp(u8 button) const
{
    if ( (button == 0) || (button > 3) )
        return false;
    return inputManager.mouseState[button - 1] == INPUT_UP;
}

inline bool SDLWindow::IsMousePressed(u8 button)
{
    if ( (button == 0) || (button > 3) )
        return false;

    bool result = (inputManager.mouseState[button - 1] == INPUT_PRESSED);

    if (result)
        inputManager.mouseState[button - 1] = INPUT_DOWN;

    return result;
}

point2<s32> SDLWindow::GetMousePosition(void)
{
    s32 x, y;

    x = y = 0;
    SDL_GetMouseState(&x, &y);

    return point2<s32>(x, y);
}

#endif