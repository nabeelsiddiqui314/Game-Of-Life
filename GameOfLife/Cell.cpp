#include "stdafx.h"
#include "Cell.h"


Cell::Cell(sf::Image& img, const sf::Vector2i& pos, const sf::Vector2i& size) 
: m_pixels(img)
, m_pos(pos)
, m_size(size) {
	
}

void Cell::SetState(const State& state) {
	m_state = state;
	for (unsigned int x = m_pos.x; x < m_pos.x + m_size.x; x++) {
		for (unsigned int y = m_pos.y; y < m_pos.y + m_size.y; y++) {
			m_pixels.setPixel(x, y, sf::Color(state, state, state));
		}
	}
}

const State Cell::GetState() const {
	return m_state;
}

Cell::~Cell() {

}
