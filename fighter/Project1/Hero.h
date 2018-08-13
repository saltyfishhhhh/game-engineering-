#pragma once
#include "comm.h"
#include "Objects.h"
#include "SFML/System/Vector2.hpp"
class Hero
{
public:
	Hero();
	~Hero();
	int m_index = 0; // hero index, can set = 0 ; 1;
	body_status m_status = alive;
	int m_status_sprite_index = 0;
	sf::Vector2i m_pos = sf::Vector2i(0,0);
	Objects*	m_obj = nullptr;
	std::tuple<int, int> m_size;
};

