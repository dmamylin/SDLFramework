#ifndef SDL_INPUT_H
#define SDL_INPUT_H

enum
{
    INPUT_UP        = 0,
    INPUT_DOWN      = 1,
    INPUT_PRESSED   = 2
};

class SDLInput
{
    friend class SDLWindow;

    struct
    {
        bool input;
        bool mouse;
        bool focus; //minimized or not
    } activeState;

    SDL_Event    message;
    u8           keyboardState[256];
    u8           mouseState[3];

    SDLInput();
    ~SDLInput() { }

    bool CatchEvents(void);
    bool OnEvent(void);
};

SDLInput::SDLInput()
{
    activeState.focus = activeState.input = activeState.mouse = true;

    for (u16 i = 0; i < 256; i++)
        keyboardState[i] = INPUT_UP;

    mouseState[0] = mouseState[1] = mouseState[2] = 0;
}

inline bool SDLInput::CatchEvents(void)
{
    while ( SDL_PollEvent(&message) )
        if ( !OnEvent() )
            return false;

    return true;
}

bool SDLInput::OnEvent(void)
{
    switch ( message.type )
    {
        case SDL_ACTIVEEVENT:
            {
                if ( message.active.state & SDL_APPACTIVE )
                {
                    if ( message.active.gain )
                        activeState.focus = true;
                    else
                        activeState.focus = false;
                }
                else if ( message.active.state & SDL_APPINPUTFOCUS )
                {
                    if ( message.active.gain )
                        activeState.input = true;
                    else
                        activeState.input = false;
                }
                else if ( message.active.state & SDL_APPMOUSEFOCUS )
                {
                    if ( message.active.gain )
                        activeState.mouse = true;
                    else
                        activeState.mouse = false;
                }
            } break;

        case SDL_KEYDOWN:
            {
                keyboardState[message.key.keysym.sym] = INPUT_PRESSED;
            } break;

        case SDL_KEYUP:
            {
                keyboardState[message.key.keysym.sym] = INPUT_UP;
            } break;

        case SDL_MOUSEBUTTONDOWN:
            {                
                mouseState[message.button.button - 1] = INPUT_PRESSED;
            } break;

        case SDL_MOUSEBUTTONUP:
            {
                mouseState[message.button.button - 1] = INPUT_UP;
            } break;

        case SDL_SYSWMEVENT:
            {
                message.syswm.msg;
            } break;

        case SDL_QUIT:
            {
                return false;
            } break;

        default: break;
    }

    return true;
}

#endif