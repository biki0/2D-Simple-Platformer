#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

class AnimationComponent {

	public:
		
		AnimationComponent(SDL_Renderer* renderer, std::string sprite_path);
		~AnimationComponent();

		void init(int x, int y, int w, int h);
		void update_pos(int x, int y);
		void set_flip(SDL_RendererFlip flip);

		void play_frame(int x, int y, int w, int h, int speed, int total_frame);

		SDL_Texture* get_texture();
		SDL_Rect& get_src_rect();
		SDL_RendererFlip get_flip();

		void render();

	private:
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;

		SDL_Rect m_src;
		SDL_Rect m_dst;

		SDL_RendererFlip m_flip;
};