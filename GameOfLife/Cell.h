#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum State {
	ALIVE = 0,
	DEAD = 255
};

class Cell
{
public:
	Cell(sf::Image& img, const sf::Vector2i& pos, const sf::Vector2i& size);
	~Cell();
public:
	void SetState(const State& state);
	const State GetState() const;
private:
	State m_state = DEAD;
	sf::Image& m_pixels;
	sf::Vector2i m_pos;
	sf::Vector2i m_size;
};

