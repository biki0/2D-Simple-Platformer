#include "LoadSprite.hpp"


std::vector<SDL_Texture*> LoadSprite::load_sprite_sheet(SDL_Renderer* m_renderer, std::string image_path, int TILE_SIZE) {

	std::vector<SDL_Texture*> textures;

	SDL_Surface* sprite_sheet_surface = IMG_Load(image_path.c_str());
	if (sprite_sheet_surface == NULL) {
		std::cout << "Unable to load sprite. Error: " << IMG_GetError() << "\n";
	}

	SDL_Texture* sprite_sheet_texture = SDL_CreateTextureFromSurface(m_renderer, sprite_sheet_surface);

	int tile_rows = sprite_sheet_surface->h / TILE_SIZE;
	int tile_cols = sprite_sheet_surface->w / TILE_SIZE;


	for (int y = 0; y < tile_rows; ++y) {
		for (int x = 0; x < tile_cols; ++x) {
			SDL_Rect tile_rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			// Create a texture from the sprite sheet with the specified source rectangle
			SDL_Texture* tile_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TILE_SIZE, TILE_SIZE);
			SDL_SetRenderTarget(m_renderer, tile_texture);
			SDL_RenderCopy(m_renderer, sprite_sheet_texture, &tile_rect, nullptr);
			SDL_SetRenderTarget(m_renderer, nullptr);

			textures.push_back(tile_texture);
		}
	}

	SDL_FreeSurface(sprite_sheet_surface);
	SDL_DestroyTexture(sprite_sheet_texture);

	return textures;
}

std::vector<SDL_Texture*> LoadSprite::load_individual_sprite(SDL_Renderer* m_renderer, std::string image_path) {

	std::vector<SDL_Texture*> textures;
	//std::string image_path = "C:/Users/bikas/Downloads/ezgif-4-96e3e3297b-png-32x32-sprite-png";

	for (const auto& entry : std::filesystem::directory_iterator(image_path)) {
		if (entry.is_regular_file() && entry.path().extension() == ".png") {
			SDL_Surface* surface = IMG_Load(entry.path().string().c_str());
			if (!surface) {
				std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
			}
			SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
			SDL_FreeSurface(surface);
			if (!texture) {
				std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
			}
			textures.push_back(texture);
		}
	}

	return textures;

}
