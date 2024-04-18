#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

// I, J, L, O, S, T, Z
enum Color {CYAN, BLUE, ORANGE, YELLOW, GREEN, MAGENTA, AMBER};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void InitializeGraphics();
    void ClearScreen();
    void UpdateScreen();
    void DrawRectangle(const int x, const int y, const int width, const int height, const Color color);
    void DrawRectangleOutline(const int x, const int y, const int width, const int height, const Color color);
    void GetKeyPress();
    bool HasPlayerQuit();

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    void SetRenderColor(const Color color);
};

#endif