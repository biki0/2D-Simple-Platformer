#pragma once

#include <iostream>

#include <SDL.h>

#include "Player.hpp"
#include "LevelMap.hpp"
#include "Collision.hpp"
#include "LevelEditor.hpp"
#include "Enemy.hpp"
#include "Skeleton.hpp"


class Game {

	public:
		Game();
		~Game();


		void run();

	private:
		void init_window();
		void init_object();

		void handle_event();
		void update();
		void render();

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Event m_event;
		
		Player* m_player;

		LevelMap* m_level1;

		LevelEditor* m_level_editor;

		
		Skeleton* m_skeleton;


		bool m_game_running = true;
		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;
		float m_current_time;
		float m_previous_time;
		float m_dt;

};