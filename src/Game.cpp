#include "Game.hpp"

Game::Game() {
	init_window();
    init_object();
}

Game::~Game(){
    delete m_player;
    delete m_level1;
    delete m_level_editor;
    

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::init_window(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }

    m_window = SDL_CreateWindow("Best Platformer Ever!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH, 900, SDL_WINDOW_RESIZABLE);

    if (m_window == NULL){
        std::cout << "window failed to init. Error: " << SDL_GetError() << "\n";
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::init_object() {
    
    m_player = new Player(m_renderer);
    m_level1 = new LevelMap(m_renderer);

    m_level_editor = new LevelEditor(m_renderer);

    

    m_skeleton = new Skeleton(m_renderer);

}

void Game::handle_event() {

    while (SDL_PollEvent(&m_event)) {
        
        if (m_event.type == SDL_QUIT) {
            m_game_running = false;
        }
        if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE) {
            m_game_running = false;
        }
        if (m_event.type == SDL_KEYDOWN) {
            switch (m_event.key.keysym.sym) {
                case SDLK_s: {
                    if (m_level_editor->get_edit_mode()) {
                        m_level_editor->save_map("level1.txt");
                        m_level1->load_map();
                    }
                }
            }
        }
        if (m_event.type == SDL_MOUSEBUTTONDOWN) {
            if (m_event.button.button == SDL_BUTTON_LEFT) {
                if (!m_level_editor->get_edit_mode()) {
                    int mouse_x = m_event.button.x;
                    int mouse_y = m_event.button.y;
                    m_player->set_pos_x(mouse_x);
                    m_player->set_pos_y(mouse_y);
                }
            }
        
        }
      
        m_level_editor->handle_event(m_event);

    }

}



void Game::update(){

    if (!m_level_editor->get_edit_mode()) {

        m_level1->check_player_collision(m_player);
        //m_level1->check_enemy_collision(m_skeleton);


        m_player->update(m_dt);

        
        //m_skeleton->follow_player(&m_player->get_player());

        //m_skeleton->update(m_dt);




        //m_player->update_pos_x();
        //m_player->x_col(m_level1->check_collision(m_player->get_x(), m_player->get_y()));

        //m_player->update_pos_y();
        //m_player->y_col(m_level1->check_collision(m_player->get_x(), m_player->get_y()));
    }

   
    

}

void Game::render(){
    
    SDL_SetRenderDrawColor(m_renderer, 238, 202, 132, 255);
    SDL_RenderClear(m_renderer);

    if (m_level_editor->get_edit_mode()) {
        m_level_editor->render();
    }
    else {
        m_level1->render();
    }

    m_player->render();

    
    //m_skeleton->render();


    SDL_RenderPresent(m_renderer);


}

void Game::run() {

    m_current_time = 0.f;
    m_previous_time = 0.f;
    m_dt = 0.f;

	while (m_game_running) {
        
        m_current_time = SDL_GetTicks();
        m_dt = (m_current_time - m_previous_time) / 1000;
        m_previous_time = m_current_time;

        handle_event();
		update();
		render();

	}

}



