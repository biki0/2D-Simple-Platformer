#pragma once

#include <iostream>

#include <SDL.h>

class PositionComponent {

    public:
        PositionComponent(float x, float y, int w, int h);
        ~PositionComponent();

        void set_position(float x, float y);
        void set_x(float x);
        void set_y(float y);

        int get_width();
        int get_height();
        int get_x();
        int get_y();

        SDL_Rect& get_position_component();


    private:

        SDL_Rect m_rect;
        


};