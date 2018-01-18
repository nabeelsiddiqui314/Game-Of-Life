#include "stdafx.h"
#include "Cell.h"


Cell::Cell(sf::Image& img, const sf::Vector2i& pos, const sf::Vector2i& size) 
: m_pixels(img)
, m_pos(pos)
, m_size(size) {
	
}

void Cell::SetState(const State& state) {
	if (state == DEAD) m_cellColor = sf::Color(220, 220 , 220);
	else m_cellColor = sf::Color(100, 200, 100);
	m_state = state;
	for (unsigned int x = m_pos.x; x < m_pos.x + m_size.x; x++) {
		for (unsigned int y = m_pos.y; y < m_pos.y + m_size.y; y++) {
			m_pixels.setPixel(x, y, m_cellColor);
		}
	}
}

const State Cell::GetState() const {
	return m_state;
}

void Cell::SpawnByClick(sf::RenderWindow& window, int offset) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (sf::Mouse::getPosition(window).x > m_pos.x - offset &&
			sf::Mouse::getPosition(window).x < m_pos.x + m_size.x - offset &&
			sf::Mouse::getPosition(window).y > m_pos.y - offset &&
			sf::Mouse::getPosition(window).y < m_pos.y + m_size.y - offset) {
			this->SetState(ALIVE);
		}
	}
}

Cell::~Cell() {

}
