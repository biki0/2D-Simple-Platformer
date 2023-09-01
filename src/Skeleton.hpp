#pragma once

#include <iostream>
#include <string>
#include <map>

#include <SDL.h>

#include "Entity.hpp"
#include "Player.hpp"


class Skeleton {

	public:

		Skeleton(SDL_Renderer* renderer);
		~Skeleton();

		Entity& get_entity();

		void follow_player(Entity* player);

		void update(float dt);
		void render();


	private:
		
		void move();

		SDL_Renderer* m_renderer;

		Entity* m_skeleton;

		float m_pos_x;
		float m_pos_y;

		bool m_moving_right;

		float m_dt;

};