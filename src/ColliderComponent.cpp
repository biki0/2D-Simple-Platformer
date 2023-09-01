#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(bool collidable){
    m_rectangle = new SDL_Rect;
    m_rectangle->x = 0;
    m_rectangle->y = 0;
    m_rectangle->w = 0;
    m_rectangle->h = 0;
    m_collidable = collidable;
}


ColliderComponent::ColliderComponent(int w, int h, int x, int y, bool collidable) {
    m_rectangle = new SDL_Rect;
    m_rectangle->w = w;
    m_rectangle->h = h;
    m_rectangle->x = x;
    m_rectangle->y = y;
    m_collidable = collidable;
}

ColliderComponent::~ColliderComponent(){
    delete m_rectangle;
}

void ColliderComponent::set_absolute_position(int x, int y) {
    m_rectangle->x = x;
    m_rectangle->y = y;
}

void ColliderComponent::set_dimensions(int w, int h) {
    m_rectangle->w = w;
    m_rectangle->h = h;
}

void ColliderComponent::set_x(int x) {
    m_rectangle->x = x;
}

void ColliderComponent::set_y(int y) {
    m_rectangle->y = y;
}

bool ColliderComponent::is_collidable() {
    return m_collidable;
}

SDL_Rect& ColliderComponent::get_collider_bounding_box() {
    return *m_rectangle;
}

void ColliderComponent::set_left(int offset) {
    left = m_rectangle->x + offset;
}
void ColliderComponent::set_right(int offset) {
    right = m_rectangle->x + m_rectangle->w + offset;
}
void ColliderComponent::set_top(int offset) {
    top = m_rectangle->y + offset;
}
void ColliderComponent::set_bottom(int offset) {
    bottom = m_rectangle->y + m_rectangle->h + offset;
}
void ColliderComponent::set_all(int l, int r, int t, int b) {

    left = m_rectangle->x + l;
    right = m_rectangle->x + m_rectangle->w + r;
    top = m_rectangle->y + t;
    bottom = m_rectangle->y + m_rectangle->h + b;

}

SDL_Point ColliderComponent::get_x_point() {
    return { left, right };
}
SDL_Point ColliderComponent::get_y_point() {
    return { top, bottom };
}

SDL_bool ColliderComponent::is_colliding(ColliderComponent& collider) {

    if(m_rectangle == nullptr) {
        return SDL_FALSE;
    }
    const SDL_Rect* temp = collider.m_rectangle;
    if(temp == nullptr) {
        return SDL_FALSE;
    }

    //implement collision check

    return SDL_HasIntersection(m_rectangle, temp);

}

