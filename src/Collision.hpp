#pragma once

#include <iostream>
#include <cmath>

#include <SDL.h>

#include "Entity.hpp"

class Collision {

	public:
		Collision();
		~Collision();
		//bool is_colliding(Player* player, LevelMap* lmap);
		static bool is_colliding(Entity* player, std::vector<Entity*> lmap);
		//void check_collision(Player *player, LevelMap *lmap);

	private:
		static bool AABB(SDL_Rect a, SDL_Rect b);
		static bool AABB(SDL_Rect a, SDL_Point bx, SDL_Point by);

};