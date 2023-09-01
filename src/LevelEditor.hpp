#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>

#include "LoadSprite.hpp"


class LevelEditor {

	public:

		LevelEditor(SDL_Renderer* renderer);
		~LevelEditor();

		bool get_edit_mode();

		void save_map(std::string file_name="level1.txt");

		void handle_event(SDL_Event& event);
		void render();

	private:

		//LoadSprite m_load_sprite;

		void load_map(std::string file_name);

		std::vector<SDL_Texture*> load_sprite_sheet();
		std::vector<SDL_Texture*> load_individual_sprite();

		void load_textures(bool is_spritesheet);
		
		void load_texture_thumbnails();
		void select_tile(int x, int y);
		void preview_texture();


		SDL_Renderer* m_renderer;

		std::vector<SDL_Rect> m_placed_tile_rectangles;
		std::vector<SDL_Texture*> m_tile_textures;
		std::vector<std::vector<int>> m_map_grid;
		
		bool col_active;

		SDL_Texture* m_preview_texture;
		SDL_Point m_selected_tile_index;

		std::vector<SDL_Rect> m_texture_thumbnails;

		bool m_tile_edit_mode;
		bool m_preview;
		int m_current_tile;
		
		int m_prev_mouse_x;
		int m_prev_mouse_y;

		int tile_rows = 0;
		int tile_cols = 0;


		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;
		const int TILE_SIZE = 32;
		const int GRID_WIDTH = SCREEN_WIDTH / TILE_SIZE;
		const int GRID_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
		const int TEXTURE_BAR_HEIGHT = 64;
};