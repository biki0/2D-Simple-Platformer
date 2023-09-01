#include "PositionComponent.hpp"

PositionComponent::PositionComponent(float x, float y, int w, int h){
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

PositionComponent::~PositionComponent() {

}

void PositionComponent::set_position(float x, float y) {
    m_rect.x = x;
    m_rect.y = y;
}

void PositionComponent::set_x(float x) {
    m_rect.x = x;
}

void PositionComponent::set_y(float y) {
    m_rect.y = y;
}

int PositionComponent::get_width() {
    return m_rect.w;
}

int PositionComponent::get_height() {
    return m_rect.h;
}

int PositionComponent::get_x() {
    return m_rect.x;
}

int PositionComponent::get_y() {
    return m_rect.y;
}

SDL_Rect& PositionComponent::get_position_component() {
    return m_rect;
}



