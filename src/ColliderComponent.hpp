#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>

class ColliderComponent {

    public:
        ColliderComponent(bool collidable = false);
        ColliderComponent(int w, int h, int x, int y, bool collidable=false);
        ~ColliderComponent();

        void set_absolute_position(int x, int y);
        void set_dimensions(int w, int h);

        void set_x(int x);
        void set_y(int y);

        void set_left(int offset = 0);
        void set_right(int offset = 0);
        void set_top(int offset = 0);
        void set_bottom(int offset = 0);
        void set_all(int l, int r, int t, int b);

        SDL_Point get_x_point();
        SDL_Point get_y_point();

        bool is_collidable();

        SDL_Rect& get_collider_bounding_box();
        SDL_bool is_colliding(ColliderComponent& collider);

        

    private:
        SDL_Rect* m_rectangle;
        bool m_collidable;

        int left;
        int right;
        int top;
        int bottom;

};