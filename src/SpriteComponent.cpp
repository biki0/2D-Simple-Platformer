#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(SDL_Renderer* renderer, std::string sprite_path) {
    m_renderer = renderer;

    SDL_Surface* temp_surface = IMG_Load(sprite_path.c_str());

    if (temp_surface == NULL) {
        std::cout << "Unable to load sprite" << "\n";
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

}

SpriteComponent::SpriteComponent(SDL_Renderer* renderer, SDL_Texture* texture) {
    m_renderer = renderer;
    m_texture = texture;
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(m_texture);
}


SDL_Texture* SpriteComponent::get_sprite_component(){
    return m_texture;
}




