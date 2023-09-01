#include "Player.hpp"

Player::Player(SDL_Renderer* renderer) {

	m_renderer = renderer;
	m_player = new Entity(m_renderer);

    m_width = 64;
    m_height = 64;

    m_player->add_animation_component("assets/player_animation.png");
	m_player->add_position_component(32, 32, m_width/2, m_height/2);

    m_pos_x = m_player->get_position_component().get_x();
    m_pos_y = m_player->get_position_component().get_y();

    m_player->add_collider_component(32, 32, m_pos_x, m_pos_y);


    m_vel_x = 0.f;
    m_vel_y = 300.f;
    m_acceleration_x = 250.f;
    m_acceleration_y = 700.f;
    m_gravity = 5.f;
    m_is_jumping = false;
    m_jump_force = 2.f;
    m_on_ground = true;
}

Player::~Player() {
    delete m_player;
	SDL_DestroyRenderer(m_renderer);
}

Entity& Player::get_player() {
    return *m_player;
}

void Player::handle_event() {

    const Uint8* key_states = SDL_GetKeyboardState(NULL);

    m_vel_x = 0.f;

    if (m_vel_x == 0) {
        m_player->get_animation_component().play_frame(0, 0 * m_height / 2, m_width/2, m_height/2, 200, 2);
    }

    if (key_states[SDL_SCANCODE_D]) {
        m_vel_x += m_acceleration_x;
        m_player->get_animation_component().set_flip(SDL_FLIP_NONE);
        m_player->get_animation_component().play_frame(0, 3 * m_height / 2, m_width/2, m_height/2, 100, 8);
    }

    if (key_states[SDL_SCANCODE_A]) {
        m_vel_x -= m_acceleration_x;
        m_player->get_animation_component().set_flip(SDL_FLIP_HORIZONTAL);
        m_player->get_animation_component().play_frame(0, 3 * m_height/2, m_width / 2, m_height / 2, 100, 8);
    }

    if ((key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_SPACE])) {
        if (m_is_jumping != true && m_on_ground) {
            m_gravity = 2.3f;
            m_vel_y = -m_acceleration_y*m_jump_force;
            m_player->get_animation_component().play_frame(0, 5 * m_height / 2, m_width / 2, m_height / 2, 100, 8);
            m_is_jumping = true;
            m_on_ground = false;

        }
    }

    if (key_states[SDL_SCANCODE_R]) {
        m_player->get_animation_component().play_frame(0, 8 * m_height / 2, m_width / 2, m_height / 2, 50, 8);
        m_player->get_collider_component().set_dimensions(50, 50);
    }
    else {
        m_player->get_collider_component().set_dimensions(32, 32);
    }

    if (key_states[SDL_SCANCODE_X]) {
        m_pos_x = 0;
        m_pos_y = 0;
    }


}

void Player::set_pos_x(float x) {
    m_pos_x = x;
}

void Player::set_pos_y(float y) {
    m_pos_y = y;
}

int Player::get_x() {
    return m_pos_x;
}
int Player::get_y() {
    return m_pos_y;
}

int Player::get_vel_x() {
    return m_vel_x;
}

int Player::get_vel_y() {
    return m_vel_y;
}

void Player::update_pos_x() {

    m_pos_x += m_vel_x * m_dt;
    m_player->get_collider_component().set_x(m_pos_x);

}

void Player::update_pos_y() {

    m_pos_y += m_vel_y * m_dt;
    m_player->get_collider_component().set_y(m_pos_y);

}

void Player::x_col(bool col) {

    if (col) {
        m_pos_x -= m_vel_x * m_dt;
        m_player->get_collider_component().set_x(m_pos_x);
        //m_on_ground = true;
        //m_is_jumping = false;
        m_gravity = 5.f;
    }

}

void Player::y_col(bool col) {

    if (col) {
        m_pos_y -= m_vel_y * m_dt;
        m_player->get_collider_component().set_y(m_pos_y);
        m_vel_y = 0;
        m_on_ground = true;
        m_is_jumping = false;
        m_gravity = 5.f;
    }

}

void Player::update(float dt) {
    
    handle_event();
    
    m_dt = dt;

    m_vel_y += m_gravity;
    m_player->get_position_component().set_position(m_pos_x, m_pos_y);
    m_player->get_collider_component().set_x(m_pos_x);
    m_player->get_collider_component().set_y(m_pos_y);
    
   /* std::cout << m_player->get_collider_component().get_collider_bounding_box().w << ", " <<
                 m_player->get_collider_component().get_collider_bounding_box().h << "\n";*/

    //std::cout << m_pos_x << ", " << m_pos_y << "\n";

}

void Player::render() {

	m_player->render();

}


//m_pos_x += m_vel_x * m_dt;
//m_player->get_collider_component().set_x(m_pos_x);

//if (col){
//    m_pos_x -= m_vel_x * m_dt;
//    m_player->get_collider_component().set_x(m_pos_x);
//    std::cout << "XDx" << "\n";
//}


//m_pos_y += m_vel_y * m_dt;
//m_player->get_collider_component().set_y(m_pos_y);

//if (col) {
//    m_pos_y -= m_vel_y * m_dt;
//    m_player->get_collider_component().set_y(m_pos_y);
//    std::cout << "XDy" << "\n";
//    m_vel_y = 0;
//}