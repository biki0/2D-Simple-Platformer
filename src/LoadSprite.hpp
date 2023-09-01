#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>


class LoadSprite {

	public:

		static std::vector<SDL_Texture*> load_sprite_sheet(SDL_Renderer* m_renderer, std::string image_path, int TILE_SIZE);
		static std::vector<SDL_Texture*> load_individual_sprite(SDL_Renderer* m_renderer, std::string image_path);

	private:



};