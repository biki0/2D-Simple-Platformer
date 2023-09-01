#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"
#include "ColliderComponent.hpp"
#include "AnimationComponent.hpp"

class Entity {

    public:
        Entity(SDL_Renderer* renderer);
        ~Entity();

        void add_sprite_component(std::string sprite_path);
        void add_sprite_component(SDL_Texture* texture);
        void add_animation_component(std::string sprite_path);
        void add_position_component(int x, int y, int w, int h);
        void add_collider_component(bool collidable = false);
        void add_collider_component(int w, int h, int x, int y, bool collidable=false);


        SpriteComponent& get_sprite_component();
        AnimationComponent& get_animation_component();
        PositionComponent& get_position_component();
        ColliderComponent& get_collider_component();
        

        void render();

    private:
        SDL_Renderer* m_renderer;

        SpriteComponent* m_sprite;
        AnimationComponent* m_animated_sprite;
        PositionComponent* m_position;
        ColliderComponent* m_collider;


};