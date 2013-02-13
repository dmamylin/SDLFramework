#ifndef SDL_BITMAP_H
#define SDL_BITMAP_H

class SDLBitmap
{
private:
    SDL_Surface* surface;

public:
    SDLBitmap() { surface = NULL; }
    SDLBitmap(const char* file) { surface = SDL_LoadBMP(file); }

    ~SDLBitmap() { SDL_FreeSurface(surface); }

    SDL_Surface* GetSurface(void) { return surface; }

    bool SetBitmap(const char* file);
    void Draw(SDL_Surface* dst, const point2<s32> position);
    void SetColorKey(const u32 key) { if (surface) SDL_SetColorKey(surface, SDL_SRCCOLORKEY, key); }
};

bool SDLBitmap::SetBitmap(const char* file)
{
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP(file);

    return surface != NULL;
}

void SDLBitmap::Draw(SDL_Surface* dst, const point2<s32> position)
{
    SDL_Rect rect = { position.x, position.y };

    SDL_BlitSurface(surface, NULL, dst, &rect);
}

#endif