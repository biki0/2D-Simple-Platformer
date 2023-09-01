#include "Entity.hpp"

Entity::Entity(SDL_Renderer* renderer) {
    m_renderer = renderer;
    m_sprite = NULL;
    m_position = NULL;
    m_collider = NULL;
    m_animated_sprite = NULL;
}

Entity::~Entity() {
    delete m_sprite;
    delete m_animated_sprite;
    delete m_position;
    delete m_collider;
    SDL_DestroyRenderer(m_renderer);
}

void Entity::add_sprite_component(std::string sprite_path) {
    if (m_animated_sprite == NULL) {
        m_sprite = new SpriteComponent(m_renderer, sprite_path);
    }
}
void Entity::add_sprite_component(SDL_Texture* texture) {
    if (m_animated_sprite == NULL) {
        m_sprite = new SpriteComponent(m_renderer, texture);
    }
}


void Entity::add_animation_component(std::string sprite_path) {
    if (m_sprite == NULL) {
        m_animated_sprite = new AnimationComponent(m_renderer, sprite_path);
    }
}

void Entity::add_position_component(int x, int y, int w, int h) {
    m_position = new PositionComponent(x, y, w, h);

}

void Entity::add_collider_component(bool collidable) {
    m_collider = new ColliderComponent(collidable);
}

void Entity::add_collider_component(int w, int h, int x, int y, bool collidable) {
    m_collider = new ColliderComponent(w, h, x, y, collidable);
}


SpriteComponent& Entity::get_sprite_component() {
    return *m_sprite;
}

AnimationComponent& Entity::get_animation_component() {
    return *m_animated_sprite;
}

PositionComponent& Entity::get_position_component() {
    return *m_position;
}

ColliderComponent& Entity::get_collider_component() {
    return *m_collider;
}

void Entity::render() {
    if (m_animated_sprite == NULL) {
        SDL_RenderCopy(m_renderer, m_sprite->get_sprite_component(), NULL, &m_position->get_position_component());
    }
    else {
        SDL_RenderCopyEx(m_renderer, m_animated_sprite->get_texture(), &m_animated_sprite->get_src_rect(),
                         &m_position->get_position_component(), NULL, NULL, m_animated_sprite->get_flip());
    }
}







