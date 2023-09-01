#pragma once

#include <iostream>
#include <string>
#include <map>

#include <SDL.h>

#include "Entity.hpp"
#include "Player.hpp"

class Enemy {

	public:
		Enemy(SDL_Renderer* renderer);
		~Enemy();


		Entity& get_enemy(std::string enemy_name);

		void update(Player* player);
		void render();


	private:

		SDL_Renderer* m_renderer;


		std::map<std::string, Entity*> m_enemies;

};