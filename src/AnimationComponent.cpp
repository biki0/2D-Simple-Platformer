#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(SDL_Renderer* renderer, std::string sprite_path) {

	m_renderer = renderer;

	SDL_Surface* temp_surface = IMG_Load(sprite_path.c_str());

	if (temp_surface == NULL) {
		std::cout << "Unable to load sprite" << "\n";
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, temp_surface);

	SDL_FreeSurface(temp_surface);

}

AnimationComponent::~AnimationComponent() {
	SDL_DestroyTexture(m_texture);
}

void AnimationComponent::init(int x, int y, int w, int h) {
	m_dst.x = x;
	m_dst.y = y;
	m_dst.w = w;
	m_dst.h = h;
}

void AnimationComponent::update_pos(int x, int y) {
	m_dst.x = x;
	m_dst.y = y;
}

void AnimationComponent::set_flip(SDL_RendererFlip flip) {
	m_flip = flip;
}

void AnimationComponent::play_frame(int x, int y, int w, int h, int speed, int total_frame) {
	m_src.x = x + w * static_cast<int>((SDL_GetTicks() / speed) % total_frame);
	m_src.y = y;
	m_src.w = w;
	m_src.h = h;
}

SDL_Texture* AnimationComponent::get_texture() {
	return m_texture;
}

SDL_Rect& AnimationComponent::get_src_rect() {
	return m_src;
}

SDL_RendererFlip AnimationComponent::get_flip() {
	return m_flip;
}

void AnimationComponent::render() {
	SDL_RenderCopyEx(m_renderer, m_texture, &m_src, &m_dst, NULL, NULL, m_flip);
}





