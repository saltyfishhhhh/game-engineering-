#include "Objects.h"



Objects::Objects()
{
}


Objects::~Objects()
{
}


void Objects::InitSprite(sf::Texture& texture)
{
	if (!m_normal.m_spritName.empty())
	{
		auto a = m_normal.m_xy;
		auto b = m_normal.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_normal_sprite = make_shared<sf::Sprite>(texture, rect);
	}
	for (auto it : m_n)
	{
		auto a = it.second.m_xy;
		auto b = it.second.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_n_sprites.insert({ it.first,make_shared<sf::Sprite>(texture, rect) });
	}
	for (auto it : m_down)
	{
		auto a = it.second.m_xy;
		auto b = it.second.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_down_sprites.insert({ it.first,make_shared<sf::Sprite>(texture, rect) });
	}
	for (auto it : m_browup)
	{
		auto a = it.second.m_xy;
		auto b = it.second.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_browup_sprites.insert({ it.first,make_shared<sf::Sprite>(texture, rect) });
	}
	for (auto it : m_hit)
	{
		auto a = it.second.m_xy;
		auto b = it.second.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_hit_sprites.insert({ it.first,make_shared<sf::Sprite>(texture, rect) });
	}
	if (!m_press.m_spritName.empty())
	{
		auto a = m_press.m_xy;
		auto b = m_press.m_size;
		sf::IntRect rect{ get<0>(a), get<1>(a), get<0>(b), get<1>(b) };
		m_press_sprite = make_shared<sf::Sprite>(texture, rect);
	}
}
