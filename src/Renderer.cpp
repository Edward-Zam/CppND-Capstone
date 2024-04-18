#include <iostream>
#include "Renderer.hpp"

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
    
}

void Renderer::UpdateScreen()
{

}

void Renderer::DrawRectangle(const int x, const int y, const int width, const int height, const Color color)
{

}

void Renderer::DrawRectangleOutline(const int x, const int y, const int width, const int height, const Color color)
{

}

void Renderer::GetKeyPress()
{

}

bool Renderer::HasPlayerQuit()
{

}


void Renderer::SetRenderColor(const Color color)
{

}
