#pragma once
#include "comm.h"
#include "Objects.h"
#include "SFML/System/Vector2.hpp"
class Enemy
{
public:
	Enemy();
	~Enemy();
	int m_index = 0; //enemy index  = 0; 1; 2;
	body_status m_status = alive;
	int m_status_sprite_index = 0;
	sf::Vector2i m_pos = sf::Vector2i(0, 0);
	std::tuple<int, int> m_size;
	Objects*	m_obj = nullptr;
};

