#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <SDL.h>

#include "Player.hpp"
#include "Entity.hpp"
#include "LoadSprite.hpp"
#include "Collision.hpp"
#include "Skeleton.hpp"

class LevelMap {

	public:
		LevelMap(SDL_Renderer* renderer);
		~LevelMap();

		void load_textures(bool is_spritesheet);

		void load_map();

		int get_tiles_size();

		std::vector<Entity*>& get_map();


		void check_player_collision(Player* player);
		void check_enemy_collision(Skeleton* skeleton);




		void render();

	private:

		SDL_Renderer* m_renderer;

		std::vector<SDL_Texture*> m_background;
		
		std::vector<std::vector<int>> m_map_grid;

		std::vector<SDL_Texture*> m_tile_textures;
		std::vector<SDL_Rect> m_placed_tile_rectangles;
		

		std::vector<Entity*> m_game_map;



		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;
		const int TILE_SIZE = 32;
		const int GRID_WIDTH = SCREEN_WIDTH / TILE_SIZE;
		const int GRID_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;


};


