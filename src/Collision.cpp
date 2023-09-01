#include "Collision.hpp"


Collision::Collision() {

}
Collision::~Collision() {

}

bool Collision::AABB(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    int offset = a.w - a.h;
    if (offset < 0) {
        offset = -offset;
    }

    //leftA = a.x+9;
    //rightA = a.x + a.w-9;
    //topA = a.y+4;
    //bottomA = a.y + a.h;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;



    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;



    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}

bool Collision::AABB(SDL_Rect a, SDL_Point bx, SDL_Point by) {

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x+9;
    rightA = a.x + a.w-9;
    topA = a.y+4;
    bottomA = a.y + a.h;



    //Calculate the sides of rect B
    leftB = bx.x;
    rightB = bx.y;
    topB = by.x;
    bottomB = by.y;



    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;

}

bool Collision::is_colliding(Entity* player, std::vector<Entity*> lmap) {
    //for (int i = 0; i < lmap->get_tiles_size(); ++i) {
    //    if (&lmap->get_map()[i]->get_collider_component() != NULL) {
    //        if (AABB(player->get_player().get_collider_component().get_collider_bounding_box(),
    //            lmap->get_map()[i]->get_collider_component().get_collider_bounding_box())) {
    //            return true;
    //        }
    //    }
    //}

    for (int i = 0; i < lmap.size(); ++i) {
        if (&lmap[i]->get_collider_component() != NULL) {
            if (AABB(player->get_collider_component().get_collider_bounding_box(),
                lmap[i]->get_collider_component().get_x_point(),
                lmap[i]->get_collider_component().get_y_point())) {
                return true;
            }
        }
    }


    return false;
}

//void Collision::check_collision(Player* player, LevelMap* lmap) {
//    
//    //player->update_pos_x();
//    //player->x_col(is_colliding(player, lmap));
//
//    //player->update_pos_y();
//    //player->y_col(is_colliding(player, lmap));
//
//    
//
//}


