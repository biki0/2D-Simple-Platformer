#include "Enemy.hpp"


Enemy::Enemy(SDL_Renderer* renderer) {
	
	m_renderer = renderer;

	m_enemies["skeleton"] = new Entity(m_renderer);
	m_enemies["skeleton"]->add_animation_component("assets/monsters/skeleton.png");
	m_enemies["skeleton"]->add_position_component(500, 200, 150, 150);
	m_enemies["skeleton"]->add_collider_component(150, 150, 500, 200, true);
	m_enemies["skeleton"]->get_collider_component().set_all(9, -4, 0, -9);
	

}

Enemy::~Enemy() {

	for (auto e : m_enemies) {
		delete e.second;
	}

}

Entity& Enemy::get_enemy(std::string enemy_name) {
	return *m_enemies[enemy_name];
}

//NOT GOING TO WORK. MAKE CLASS FOR EACH ENEMY...


void Enemy::update(Player* player) {

	
	int pos = m_enemies["skeleton"]->get_position_component().get_x();
	if ( (pos-50) < player->get_x() && (pos + 150) > player->get_x()) {
		if (player->get_x()-64 < pos) {
			m_enemies["skeleton"]->get_animation_component().set_flip(SDL_FLIP_HORIZONTAL);
		}
		else {
			m_enemies["skeleton"]->get_animation_component().set_flip(SDL_FLIP_NONE);
		}
		m_enemies["skeleton"]->get_animation_component().play_frame(0, 0 * 150, 150, 150, 100, 8);
	}
	else {
		m_enemies["skeleton"]->get_animation_component().set_flip(SDL_FLIP_NONE);
		m_enemies["skeleton"]->get_animation_component().play_frame(0, 5 * 150, 150, 150, 200, 4);
		
	}



}

void Enemy::render() {

	for (auto e = m_enemies.begin(); e != m_enemies.end(); ++e) {
		e->second->render();
		
	}

	//m_enemies["skeleton"]->render();

}

