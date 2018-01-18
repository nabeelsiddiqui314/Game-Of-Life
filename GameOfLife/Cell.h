#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum State {
	ALIVE,
	DEAD
};

class Cell
{
public:
	Cell(sf::Image& img, const sf::Vector2i& pos, const sf::Vector2i& size);
	~Cell();
public:
	void SetState(const State& state);
	const State GetState() const;
	void SpawnByClick(sf::RenderWindow& window, int offset = 0);
private:
	State m_state = DEAD;
	sf::Image& m_pixels;
	sf::Vector2i m_pos;
	sf::Vector2i m_size;
	sf::Color m_cellColor;
};

