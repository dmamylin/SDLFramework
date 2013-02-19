#define _INCLUDE_MATH
#include "SDLExtension.h"

int main(void)
{
    SDLWindow window;
    SDLBitmap img;

    window.Initialize(800, 600, false, "Test window");    
    img.SetBitmap("test.bmp");
    img.SetColorKey(0xFFFFFF);
    
    while( window.Run() )
    {
        window.BeginScene(0x0);
        img.Draw(window.GetDisplaySurface(), point2<s32>(200, 200));
        window.EndScene();
    }

    window.Release();
    
    return 0;
}