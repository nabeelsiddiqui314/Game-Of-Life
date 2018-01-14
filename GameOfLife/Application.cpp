#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_mainWindow.create(sf::VideoMode(1000, 620), "Conway's Game Of Life", sf::Style::Close);
	srand(time(NULL));
	for (unsigned short int x = 0; x < 52; x++) {
		for (unsigned short int y = 0; y < 33; y++) {
			m_cells[x][y] = new Cell({ (x * 20) - 20, (y * 20) - 20 }, { 20, 20 });
			if (x == 0 || x == 51 || y == 0 || y == 32) {
				// makes dead cells
			}
			else if (rand() % 5 == 0) {
				//m_cells[x][y]->SetState(ALIVE);
			}
		}
	}
	m_cells[20][10]->SetState(ALIVE);
	m_cells[20][11]->SetState(ALIVE);
	m_cells[20][12]->SetState(ALIVE);
}


void Application::Run() {
	while (m_mainWindow.isOpen()) {
		sf::Event evnt;
		while (m_mainWindow.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				m_mainWindow.close();
			}
		}
		m_mainWindow.clear();

		if (m_deltaTime.getElapsedTime().asMilliseconds() > 150) {
			this->Update();
			m_deltaTime.restart();
		}
		this->Render();

		m_mainWindow.display();
	}
}

void Application::Update() {
	for (unsigned short int y = 0; y < 33; y++) {
		for (unsigned short int x = 0; x < 52; x++) {
			if (x == 0 || x == 51 || y == 0 || y == 32) {
				m_cells[x][y]->SetState(DEAD);
			}
			else {
				switch (m_cells[x][y]->GetState()) {
				case ALIVE:
					if (CountNeighbors(x, y) < 2 || CountNeighbors(x, y) > 3) {
						m_cells[x][y]->SetState(DEAD);
					}
					break;
				case DEAD:
					if (CountNeighbors(x, y) == 3) {
						m_cells[x][y]->SetState(ALIVE);
					}
					break;
				}
			}
		}
	}
}

void Application::Render() {
	for (unsigned short int x = 1; x < 51; x++) {
		for (unsigned short int y = 1; y < 32; y++) {
			m_cells[x][y]->Render(m_mainWindow);
		}
	}
}

int Application::CountNeighbors(const int Cx, const int Cy) const {
	int neighbors = 0;
	for (unsigned short int x = Cx-1; x != Cx+2; x++) {
		for (unsigned short int y = Cy-1; y != Cy+2; y++) {
			if (m_cells[x][y]->GetState() == ALIVE) {
				neighbors++;
			}
		}
	}
	if (m_cells[Cx][Cy]->GetState() == ALIVE) {
		neighbors--;
	}
	return neighbors;
}

Application::~Application() {
	for (unsigned short int x = 0; x < 52; x++) {
		for (unsigned short int y = 0; y < 33; y++) {
			delete m_cells[x][y];
		}
	}
}
