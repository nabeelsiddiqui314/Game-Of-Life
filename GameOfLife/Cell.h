#pragma once
#include <SFML/Graphics.hpp>

enum State {
	ALIVE = 0,
	DEAD = 255
};

class Cell
{
public:
	Cell(const sf::Vector2i& pos, const sf::Vector2i& size);
	~Cell();
public:
	void SetState(const State& state);
	const State GetState() const;
	void Render(sf::RenderWindow& window);
private:
	State m_state = DEAD;
	sf::RectangleShape m_cell;
};

