#pragma once
#include "SpritePosInfo.h"
#include <map>
#include <memory>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

using std::get;
using std::shared_ptr;
using std::make_shared;
using std::map;
//enum obj_type
//{
//	enemy,
//	hero,
//	bomb,
//	bullet,
//	ufo,
//	game_pause,
//};
class Objects
{
public:
	Objects();
	~Objects();
	void InitSprite(sf::Texture& texture);
	string		m_name;
	//obj_type	m_type;
	SpritePosInfo m_normal;
	shared_ptr<sf::Sprite> m_normal_sprite;

	map<string,SpritePosInfo> m_n;
	map<string, shared_ptr<sf::Sprite>> m_n_sprites;

	map<string, SpritePosInfo> m_down;
	map<string, shared_ptr<sf::Sprite>> m_down_sprites;

	map<string, SpritePosInfo> m_browup;
	map<string, shared_ptr<sf::Sprite>> m_browup_sprites;

	map<string, SpritePosInfo> m_hit;
	map<string, shared_ptr<sf::Sprite>> m_hit_sprites;

	SpritePosInfo m_press;
	shared_ptr<sf::Sprite> m_press_sprite;

	string		m_pressname;
};

