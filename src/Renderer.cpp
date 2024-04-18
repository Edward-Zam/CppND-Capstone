#include <iostream>
#include "Renderer.h"

using namespace std;

Renderer::Renderer()
{
    _renderer = nullptr;
    _window = nullptr;
    InitializeGraphics();
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = nullptr;
    _window = nullptr;
    SDL_Quit();
}

void Renderer::InitializeGraphics()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cerr <<"Error initializing SDL! SDL Error: " << SDL_GetError() << endl;
        return;
    }
    _window = SDL_CreateWindow("CppND Capstone: Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
        cerr <<"Error initializing SDL! SDL Error: " << SDL_GetError() << endl;
        return;
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr)
    {
        cerr <<"Error initializing SDL! SDL Error: " << SDL_GetError() << endl;
        return;
    }
}

void Renderer::ClearScreen()
{
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(_renderer);
}

void Renderer::UpdateScreen()
{
    SDL_RenderPresent(_renderer);
}

void Renderer::DrawRectangle(const int x, const int y, const int width, const int height, const Color color)
{
    SDL_Rect blockArea = {x, y, width, height};
    SetRenderColor(color);
    SDL_RenderFillRect(_renderer, &blockArea);
}

void Renderer::DrawRectangleOutline(const int x, const int y, const int width, const int height, const Color color)
{
    SDL_Rect outlineArea = {x, y, width, height};
    SetRenderColor(color);
    SDL_RenderDrawRect(_renderer, &outlineArea);
}

int Renderer::GetKeyPress()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
                return e.key.keysym.sym;
            case SDL_QUIT:
                exit(1);
        }
    }
    return -1;
}

bool Renderer::HasPlayerQuit()
{
    return false;
}

void Renderer::SetRenderColor(const Color color)
{
    switch (color)
    {
        case CYAN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0xFF, 0xFF);
            break;
        case BLUE:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
            break;
        case ORANGE:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x7F, 0x00, 0xFF);
            break;
        case YELLOW:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0x00, 0xFF);
            break;
        case GREEN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0x00, 0xFF);
            break;
        case PURPLE:
            SDL_SetRenderDrawColor(_renderer, 0x80, 0x00, 0x80, 0xFF);
            break;
        case RED:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
            break;
        case AMBER:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xBF, 0xF0, 0xFF);
            break;
    }
}
