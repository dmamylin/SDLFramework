#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

class SDLRenderer
{
private:
    SDLWindow* window; //Pointer to attached window
    f32        halfWidth; //Store center coordinates of screen
    f32        halfHeight;

    //Validate 'x' and 'y' index of pixel array to prevent seg. fault
    bool ValidateXY(const s32, const s32);
    bool ValidateXY(const f32, const f32);

    //"Logical" coordinate: x and y in range of [-1.0f, 1.0f]
    //"Screen" coordinate: native screen width and height
    point2<s32> LogicalToScreen(const point2<f32>&);
    point2<s32> LogicalToScreen(const f32, const f32);
    point2<f32> ScreenToLogical(const point2<s32>&);
    point2<f32> ScreenToLogical(const s32, const s32);

    inline void Update(void) { halfWidth  = (window->display->w - 1.0f) / 2.0f;
                               halfHeight = (window->display->h - 1.0f) / 2.0f; }

public:
    SDLRenderer() : window(NULL), halfWidth(0), halfHeight(0) { }
    SDLRenderer(SDLWindow* wnd) : window(wnd) { Update(); }
    
    ~SDLRenderer() { }
    
    //Draw point by coordinates x and y. Overloaded: f32 - logical coordinates, s32 - screen
    void DrawPoint2d(const s32, const s32, const u32);
    void DrawPoint2d(const s32, const s32, const color3<u8>&);
    void DrawPoint2d(const point2<s32>&, const color3<u8>&);
    void DrawPoint2d(const point2<s32>&, const u32);
    void DrawPoint2d(const point2<f32>&, const u32);
    void DrawPoint2d(const point2<f32>&, const color3<u8>&);
    void DrawPoint2d(const f32, const f32, const u32);
    void DrawPoint2d(const f32, const f32, const color3<u8>&);

    //Draw line by coordinates
    void DrawLine2d(const point2<s32>&, const point2<s32>&, const u32);
    void DrawLine2d(const point2<s32>&, const point2<s32>&, const color3<u8>&);
    void DrawLine2d(const point2<f32>&, const point2<s32>&, const u32);
    void DrawLine2d(const point2<f32>&, const point2<s32>&, const color3<u8>&);

    void SetWindow(SDLWindow* wnd) { window = wnd; if ( wnd ) Update(); }

    SDLWindow* GetWindow(void) const { return window; }
};

#pragma region common_realisations

inline bool SDLRenderer::ValidateXY(const s32 x, const s32 y)
{
    return ( (x < window->display->w && x >= 0) && (y < window->display->h && y >= 0) );
}

inline bool SDLRenderer::ValidateXY(const f32 x, const f32 y)
{
    return ( (x <= 1.0f && x >= -1.0f) && (y <= 1.0f && y >= -1.0f) );
}

inline point2<s32> SDLRenderer::LogicalToScreen(const point2<f32>& coord)
{
    return point2<s32>( s32(halfWidth + halfWidth * coord.x), s32(halfHeight - halfHeight * coord.y) );
}

inline point2<s32> SDLRenderer::LogicalToScreen(const f32 x, const f32 y)
{
    return LogicalToScreen( point2<f32>(x, y) );
}

inline point2<f32> SDLRenderer::ScreenToLogical(const point2<s32>& coord)
{
    return point2<f32>( (coord.x - halfWidth) / halfWidth, (halfHeight - coord.y) / halfHeight );
}

inline point2<f32> SDLRenderer::ScreenToLogical(const s32 x, const s32 y)
{
    return ScreenToLogical( point2<s32>(x, y) );
}

#pragma endregion common_realisations

#pragma region DrawPoint2d_realisation

inline void SDLRenderer::DrawPoint2d(const s32 x, const s32 y, const u32 color)
{
    if ( ValidateXY(x, y) )
        ( (u32*)(window->display->pixels) )[x + window->display->w * y] = color;
}

inline void SDLRenderer::DrawPoint2d(const s32 x, const s32 y, const color3<u8>& color)
{
    if ( ValidateXY(x, y) )
        DrawPoint2d(x, y, SDL_MapRGB(window->display->format, color.r, color.g, color.b));
}

inline void SDLRenderer::DrawPoint2d(const point2<s32>& point, const color3<u8>& color)
{
    DrawPoint2d(point.x, point.y, color);
}

inline void SDLRenderer::DrawPoint2d(const point2<s32>& point, const u32 color)
{
    DrawPoint2d(point.x, point.y, color);
}

inline void SDLRenderer::DrawPoint2d(const point2<f32>& point, const u32 color)
{
    DrawPoint2d( LogicalToScreen(point), color);
}

inline void SDLRenderer::DrawPoint2d(const point2<f32>& point, const color3<u8>& color)
{
    DrawPoint2d( LogicalToScreen(point), color);
}

inline void SDLRenderer::DrawPoint2d(const f32 x, const f32 y, const u32 color)
{
    DrawPoint2d( LogicalToScreen(point2<f32>(x, y)), color );
}

inline void SDLRenderer::DrawPoint2d(const f32 x, const f32 y, const color3<u8>& color)
{
    DrawPoint2d( LogicalToScreen(point2<f32>(x, y)), color );
}

#pragma endregion DrawPoint2d_realisation

#pragma region DrawLine2d_realisations

void SDLRenderer::DrawLine2d(const point2<s32>& from, const point2<s32>& to, const u32 color)
{ //y = kx + b
    //TODO: optimize
    s32 dx = abs(to.x - from.x);
    s32 dy = abs(to.y - from.y);
    float k, b;
    s32 start(0), end(0);

    if ( dx > dy )
    {
        k = float(from.y - to.y) / float(from.x - to.x);
        b = float(to.y) - k * to.x;

        if ( from.x < to.x ) //Bad. Very bad
        {
            start = from.x;
            end = to.x;
        }
        else
        {
            start = to.x;
            end = from.x;
        }

        for (s32 x = start; x <= end; x++)
            DrawPoint2d( x, s32(k * x + b), color );
    }
    else
    {
        k = float(from.x - to.x) / float(from.y - to.y);
        b = float(to.x) - k * to.y;

        if ( from.y < to.y ) //Its awful
        {
            start = from.y;
            end = to.y;
        }
        else
        {
            start = to.y;
            end = from.y;
        }

        for (s32 y = start; y <= end; y++)
            DrawPoint2d( s32(k * y + b), y, color );        
    }
}

inline void SDLRenderer::DrawLine2d(const point2<s32>& from, const point2<s32>& to, const color3<u8>& color)
{
    DrawLine2d( from, to, SDL_MapRGB(window->display->format, color.r, color.g, color.b) );
}

inline void SDLRenderer::DrawLine2d(const point2<f32>& from, const point2<s32>& to, const u32 color)
{
    DrawLine2d( LogicalToScreen(from), LogicalToScreen(to), color );
}

inline void SDLRenderer::DrawLine2d(const point2<f32>& from, const point2<s32>& to, const color3<u8>& color)
{
    DrawLine2d( LogicalToScreen(from), LogicalToScreen(to), color );
}

#pragma endregion DrawLine2d_realisations

#endif