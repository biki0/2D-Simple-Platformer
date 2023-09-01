#include "LevelEditor.hpp"

LevelEditor::LevelEditor(SDL_Renderer* renderer) {
	
	m_renderer = renderer;

	m_map_grid = std::vector<std::vector<int>>(GRID_WIDTH, std::vector<int>(GRID_HEIGHT, -1));

	m_current_tile = 0;
	m_tile_edit_mode = false;
	m_preview = false;

	m_selected_tile_index = { -1, -1 };

	

	load_textures(false);
	//preview_texture();
	load_texture_thumbnails();

}

LevelEditor::~LevelEditor() {

	for (auto t : m_tile_textures) {
		SDL_DestroyTexture(t);
	}
	SDL_DestroyTexture(m_preview_texture);

}

bool LevelEditor::get_edit_mode() {
	return m_tile_edit_mode;
}

void LevelEditor::save_map(std::string file_name) {
	std::cout << "\nmap saved. to" << " : " << file_name << "\n";

	file_name = "assets/maps/" + file_name;

	std::ofstream out_file(file_name);

	if (!out_file.is_open()) {
		std::cerr << "\nFailed to open file for writing: " << file_name << "\n";
		return;
	}

	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			out_file << m_map_grid[x][y] << " ";
		}
		out_file << "\n";
	}

	out_file.close();

}

void LevelEditor::load_map(std::string file_name) {
	std::cout << "\nmap loaded. from " << " : " << file_name << "\n";

	file_name = "assets/maps/" + file_name;

	std::ifstream in_file(file_name);

	if (!in_file.is_open()) {
		std::cerr << "Failed to open file for reading: " << file_name << std::endl;
		return;
	}

	m_placed_tile_rectangles.clear();

	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			int tile_index;
			in_file >> tile_index;

			if (tile_index != -1) {
				m_map_grid[x][y] = tile_index;

				SDL_Rect dest_rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				m_placed_tile_rectangles.push_back(dest_rect);
				
			}
		}
	}


	in_file.close();

}


std::vector<SDL_Texture*> LevelEditor::load_sprite_sheet() {

	std::vector<SDL_Texture*> textures;

	SDL_Surface* sprite_sheet_surface = IMG_Load("assets/tileset5.png");
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

std::vector<SDL_Texture*> LevelEditor::load_individual_sprite() {

	std::vector<SDL_Texture*> textures;
	std::string image_path = "C:/Users/bikas/Downloads/ezgif-4-96e3e3297b-png-32x32-sprite-png";

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

void LevelEditor::load_textures(bool is_spritesheet) {

	if (is_spritesheet) {
		m_tile_textures = LoadSprite::load_sprite_sheet(m_renderer, "assets/tileset5.png", TILE_SIZE);
	}
	else {
		m_tile_textures = LoadSprite::load_individual_sprite(m_renderer, "assets/ind_sprite2");
	}


}

void LevelEditor::load_texture_thumbnails() {
	
	//int thumbnail_width = SCREEN_WIDTH / m_tile_textures.size();
	//int thumbnail_height = TEXTURE_BAR_HEIGHT;

	//for (size_t i = 0; i < m_tile_textures.size(); ++i) {
	//	SDL_Rect thumbnailRect = { static_cast<int>(i) * thumbnail_width, SCREEN_HEIGHT - TEXTURE_BAR_HEIGHT, thumbnail_height, thumbnail_height };
	//	m_texture_thumbnails.push_back(thumbnailRect);
	//}

	int thumbnail_width = TILE_SIZE;  
	int thumbnail_height = TEXTURE_BAR_HEIGHT;
	int spacing = 5;  

	int num_columns = (SCREEN_WIDTH + spacing) / (thumbnail_width + spacing);  

	int total_textures = m_tile_textures.size();
	int total_rows = (total_textures + num_columns - 1) / num_columns; 

	for (int i = 0; i < m_tile_textures.size(); ++i) {
		int row = i / num_columns;
		int col = i % num_columns;

		int x_position = col * (thumbnail_width + spacing);
		int y_position = SCREEN_HEIGHT - TEXTURE_BAR_HEIGHT + row * (thumbnail_height + spacing)+75;

		SDL_Rect thumbnail_rect = { x_position, y_position, thumbnail_width, thumbnail_height };
		m_texture_thumbnails.push_back(thumbnail_rect);
	}

}

void LevelEditor::select_tile(int x, int y) {

	m_selected_tile_index.x = x / TILE_SIZE;
	m_selected_tile_index.y = y / TILE_SIZE;
	if (m_selected_tile_index.x >= GRID_WIDTH || m_selected_tile_index.y >= GRID_HEIGHT) {
		m_selected_tile_index = { -1, -1 };
	}

}

void LevelEditor::preview_texture() {

	if (m_current_tile >= 0 && m_current_tile < m_tile_textures.size()) {
		m_preview_texture = m_tile_textures[m_current_tile];
	}
	else {
		m_preview_texture = NULL;
	}

}

void LevelEditor::handle_event(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_e: { // Press 'E' to toggle tile edit mode
				m_tile_edit_mode = !m_tile_edit_mode;
				std::cout << "Edit mode : " << std::boolalpha << m_tile_edit_mode << "\n";
				load_map("level1.txt");
				preview_texture(); 
				break;
			}
			//case SDLK_s: { // Press 'S' to save
			//	if(m_tile_edit_mode) save_map("level1.txt"); 
			//	break;
			//}
			case SDLK_l: {
				if (m_tile_edit_mode) load_map("level1.txt");
				break; // Press 'L' to load
			}
			case SDLK_p: {
				m_preview = !m_preview;
				break;
			}
			default: {
				break;
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouse_x = event.button.x;
		int mouse_y = event.button.y;

		if (m_tile_edit_mode) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				select_tile(mouse_x, mouse_y);
				if (mouse_y >= SCREEN_HEIGHT - TEXTURE_BAR_HEIGHT) {
					SDL_Point m_pos = { mouse_x, mouse_y };
					for (int i = 0; i < m_texture_thumbnails.size(); ++i) {
						if (SDL_PointInRect(&m_pos, &m_texture_thumbnails[i])) {
							m_current_tile = static_cast<int>(i);
							std::cout << "selected tile index: " << m_current_tile << "\n";
							preview_texture();
							break;
						}
					}
				}
			}
		}

	}

	//place selected tile onto grid
	if (m_tile_edit_mode && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		if (m_selected_tile_index.x != -1 && m_selected_tile_index.y != -1) {
			if (mouse_x >= 0 && mouse_x < SCREEN_WIDTH && mouse_y >= 0 && mouse_y < SCREEN_HEIGHT) {
				int grid_x = mouse_x / TILE_SIZE;
				int grid_y = mouse_y / TILE_SIZE;

				if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
					m_map_grid[grid_x][grid_y] = m_current_tile;
					
					SDL_Rect dest_rect = { grid_x * TILE_SIZE, grid_y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
					m_placed_tile_rectangles.push_back(dest_rect);
					//std::cout << "x: " << dest_rect.x << ", " << "y: " << dest_rect.y << "\n";
				}
			}
		}
	}

	//select already placed tile instead of clicking on the thumbnail
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		int grid_x = mouse_x / TILE_SIZE;
		int grid_y = mouse_y / TILE_SIZE;

		if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
			m_current_tile = m_map_grid[grid_x][grid_y];
			std::cout << "selected tile index: " << m_current_tile << "\n";
			preview_texture();
		}
	}

	if (m_tile_edit_mode && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		if (m_selected_tile_index.x != -1 && m_selected_tile_index.y != -1) {
			if (mouse_x >= 0 && mouse_x < SCREEN_WIDTH && mouse_y >= 0 && mouse_y < SCREEN_HEIGHT) {
				int grid_x = mouse_x / TILE_SIZE;
				int grid_y = mouse_y / TILE_SIZE;

				if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
					if (m_prev_mouse_x == -1 && m_prev_mouse_y == -1) {
						m_prev_mouse_x = grid_x;
						m_prev_mouse_y = grid_y;
					}

					int start_x = std::min(m_prev_mouse_x, grid_x);
					int end_x = std::max(m_prev_mouse_x, grid_x);
					int start_y = std::min(m_prev_mouse_y, grid_y);
					int end_y = std::max(m_prev_mouse_y, grid_y);

					for (int x = start_x; x <= end_x; ++x) {
						for (int y = start_y; y <= end_y; ++y) {
							m_map_grid[x][y] = -1;
							
						}
					}

					m_prev_mouse_x = grid_x;
					m_prev_mouse_y = grid_y;
				}
			}
		}
	}
	else {
		m_prev_mouse_x = -1;
		m_prev_mouse_y = -1;
	}

}

void LevelEditor::render() {

	for (int i = 0; i < m_placed_tile_rectangles.size(); ++i) {
		SDL_Rect dest_rect = m_placed_tile_rectangles[i];
		int tile_index = m_map_grid[dest_rect.x / TILE_SIZE][dest_rect.y / TILE_SIZE];

		if (tile_index >= 0 && tile_index < m_tile_textures.size()) {
			SDL_RenderCopy(m_renderer, m_tile_textures[tile_index], nullptr, &dest_rect);
		}
	}

	if (m_tile_edit_mode) {
		
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_Rect preview_rect = { mouse_x - TILE_SIZE / 2, mouse_y - TILE_SIZE / 2, TILE_SIZE, TILE_SIZE };
		SDL_RenderCopy(m_renderer, m_preview_texture, nullptr, &preview_rect);
		
		//drawing grid on screen
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); 
		for (int x = 0; x < GRID_WIDTH; ++x) {
			SDL_RenderDrawLine(m_renderer, x * TILE_SIZE, 0, x * TILE_SIZE, SCREEN_HEIGHT);
		}
		for (int y = 0; y < GRID_HEIGHT; ++y) {
			SDL_RenderDrawLine(m_renderer, 0, y * TILE_SIZE, SCREEN_WIDTH, y * TILE_SIZE);
		}


	}

	//SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	//SDL_Rect bar_rect = { 0, SCREEN_HEIGHT - TEXTURE_BAR_HEIGHT, SCREEN_WIDTH, TEXTURE_BAR_HEIGHT };
	//SDL_RenderFillRect(m_renderer, &bar_rect);

	for (int i = 0; i < m_tile_textures.size(); ++i) {
		SDL_RenderCopy(m_renderer, m_tile_textures[i], nullptr, &m_texture_thumbnails[i]);
	}


}








