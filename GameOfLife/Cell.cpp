#include "stdafx.h"
#include "Cell.h"


Cell::Cell(const sf::Vector2i& pos, const sf::Vector2i& size) {
	m_cell.setPosition((sf::Vector2f)pos);
	m_cell.setSize((sf::Vector2f)size);
	m_cell.setFillColor(sf::Color::White);
}

void Cell::SetState(const State& state) {
	m_state = state;
	m_cell.setFillColor({(sf::Uint8)state, (sf::Uint8)state, (sf::Uint8)state});
}

const State Cell::GetState() const {
	return m_state;
}

void Cell::Render(sf::RenderWindow& window) {
	window.draw(m_cell);
}

Cell::~Cell() {

}
