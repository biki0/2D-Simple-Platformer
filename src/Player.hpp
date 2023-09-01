#pragma once

#include <iostream>

#include <SDL.h>

#include "Entity.hpp"

class Player {

	public:

		Player(SDL_Renderer* renderer);
		~Player();

		Entity& get_player();

		void set_pos_x(float x);
		void set_pos_y(float y);

		int get_x();
		int get_y();
		int get_vel_x();
		int get_vel_y();

		void update_pos_x();
		void update_pos_y();
		void x_col(bool col);
		void y_col(bool col);
		


		void handle_event();
		void update(float dt);
		void render();
		

	private:

		SDL_Renderer* m_renderer;
		
		Entity* m_player;

		int m_width;
		int m_height;

		float m_pos_x;
		float m_pos_y;
		float m_vel_x;
		float m_vel_y;
		float m_acceleration_x;
		float m_acceleration_y;
		float m_gravity;
		float m_dt;
		bool m_is_jumping;
		float m_jump_force;
		bool m_on_ground;


};