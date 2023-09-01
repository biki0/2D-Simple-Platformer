#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>


class SpriteComponent {

    public:
        SpriteComponent(SDL_Renderer* renderer, std::string sprite_path);
        SpriteComponent(SDL_Renderer* renderer, SDL_Texture* texture);
        ~SpriteComponent();

        SDL_Texture* get_sprite_component();

    private:
        SDL_Renderer* m_renderer;

        SDL_Texture* m_texture;


};