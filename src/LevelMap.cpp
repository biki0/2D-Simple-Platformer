#include "LevelMap.hpp"

LevelMap::LevelMap(SDL_Renderer* renderer) {
	
    m_renderer = renderer;

    m_map_grid = std::vector<std::vector<int>>(SCREEN_WIDTH, std::vector<int>(SCREEN_HEIGHT, -1));


	//m_background.push_back(new SpriteComponent(m_renderer, "assets/background/bg_1.png"));
	//m_background.push_back(new SpriteComponent(m_renderer, "assets/background/bg_2.png"));
	//m_background.push_back(new SpriteComponent(m_renderer, "assets/background/bg_3.png"));

    m_background = LoadSprite::load_individual_sprite(m_renderer, "assets/ind_sprite2/background");
    std::cout << "SIZE" << m_background.size() << "\n";

    load_textures(false);
    load_map();

}

LevelMap::~LevelMap() {

	for (auto bg : m_background) {
        SDL_DestroyTexture(bg);
	}

    for (auto gm : m_game_map) {
        delete gm;
    }

    for (auto t : m_tile_textures) {
        SDL_DestroyTexture(t);
    }

    SDL_DestroyRenderer(m_renderer);
}



void LevelMap::load_textures(bool is_spritesheet) {

    if (is_spritesheet) {
        m_tile_textures = LoadSprite::load_sprite_sheet(m_renderer, "assets/tileset5.png", TILE_SIZE);
    }
    else {
        m_tile_textures = LoadSprite::load_individual_sprite(m_renderer, "assets/ind_sprite2");
    }


}

void LevelMap::load_map() {

    std::string file_name = "level1.txt";

    std::cout << "map loaded. from" << " : " << file_name << "\n";

    file_name = "assets/maps/" + file_name;

    std::ifstream in_file(file_name);

    if (!in_file.is_open()) {
        std::cerr << "Failed to open file for reading: " << file_name << std::endl;
        return;
    }

    m_game_map.clear();

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int tile_index;
            in_file >> tile_index;

            if (tile_index == 29 || tile_index == 30 || tile_index == 31) {
                m_map_grid[x][y] = tile_index;
                Entity* tile_entity = new Entity(m_renderer);
                tile_entity->add_sprite_component(m_tile_textures[tile_index]);
                tile_entity->add_position_component(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                tile_entity->add_collider_component(32, 32, x * TILE_SIZE, y * TILE_SIZE, true);
                tile_entity->get_collider_component().set_all(9, -4, 0, -9);
                m_game_map.push_back(tile_entity);
            }
            if (tile_index != -1) {
                m_map_grid[x][y] = tile_index;
                Entity* tile_entity = new Entity(m_renderer);
                tile_entity->add_sprite_component(m_tile_textures[tile_index]);
                tile_entity->add_position_component(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                tile_entity->add_collider_component(32, 32, x * TILE_SIZE, y * TILE_SIZE);
                //tile_entity->get_collider_component().set_all(0, 0, 0, 0);
                m_game_map.push_back(tile_entity);
            }

        }
    }


    in_file.close();

}


int LevelMap::get_tiles_size() {
    return m_game_map.size();
}


std::vector<Entity*>& LevelMap::get_map() {
    return m_game_map;
}


void LevelMap::check_player_collision(Player* player) {

    player->update_pos_x();
    player->x_col(Collision::is_colliding(&player->get_player(), m_game_map));

    player->update_pos_y();
    player->y_col(Collision::is_colliding(&player->get_player(), m_game_map));

}

void LevelMap::check_enemy_collision(Skeleton* skeleton) {

    
    

}


void LevelMap::render() {
	for (auto bg : m_background) {
		SDL_RenderCopy(m_renderer, bg, NULL, NULL);
	}

    for (auto gm : m_game_map) {
        gm->render();
    }

}