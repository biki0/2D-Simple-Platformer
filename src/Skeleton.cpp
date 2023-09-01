#include "Skeleton.hpp"

Skeleton::Skeleton(SDL_Renderer* renderer) {

	m_renderer = renderer;

	m_skeleton = new Entity(m_renderer);
	m_skeleton->add_animation_component("assets/monsters/skeleton.png");
	m_skeleton->add_position_component(500, 200, 150, 150);
	m_skeleton->add_collider_component(150, 150, 500, 200, true);
	m_skeleton->get_collider_component().set_all(9, -4, 0, -9);

	m_pos_x = m_skeleton->get_position_component().get_x();
	m_pos_y = m_skeleton->get_position_component().get_y();


	m_moving_right = true;

}

Skeleton::~Skeleton() {

	delete m_skeleton;

}

Entity& Skeleton::get_entity() {
	return *m_skeleton;
}


void Skeleton::move() {

	
	if (m_moving_right) {

		//m_pos_x += 1;
		//if (m_pos_x + 150 > 1280) {
			//m_moving_right = false;
			m_skeleton->get_animation_component().set_flip(SDL_FLIP_HORIZONTAL);
			m_skeleton->get_animation_component().play_frame(0, 5 * 150, 150, 150, 500, 4);
		//}

	}
	else {
		//m_pos_x -= 1;
		//if (m_pos_x < 0) {
			//m_moving_right = true;
			m_skeleton->get_animation_component().set_flip(SDL_FLIP_NONE);
			m_skeleton->get_animation_component().play_frame(0, 5 * 150, 150, 150, 500, 4);
		//}
	}

}

void Skeleton::follow_player(Entity* player) {

	int dx = player->get_position_component().get_x() - m_pos_x;
	int dy = player->get_position_component().get_y() - m_pos_y;

	double distance = std::sqrt(dx * dx + dy * dy);

	if (distance > 0) {
		double dir_x = dx / distance;
		double dir_y = dy / distance;



		m_pos_x += static_cast<int>(2 * dir_x);
		m_pos_y += static_cast<int>(2 * dir_y);
	}



}

void Skeleton::update(float dt) {


	move();
	m_dt = dt;




	m_skeleton->get_position_component().set_position(m_pos_x, m_pos_y);
	m_skeleton->get_collider_component().set_x(m_pos_x);
	m_skeleton->get_collider_component().set_y(m_pos_y);


}


void Skeleton::render() {

	m_skeleton->render();

}

