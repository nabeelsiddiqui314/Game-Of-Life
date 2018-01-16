#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_mainWindow.create(sf::VideoMode(m_cellWidth * (m_cellNumX - 2), m_cellWidth * (m_cellNumY - 2)), "Conway's Game Of Life", sf::Style::Close);
	srand(time(NULL));
	
	for (unsigned short int x = 0; x < m_cellNumX; x++) {
		for (unsigned short int y = 0; y < m_cellNumY; y++) {
			m_cells[x][y] = new Cell({ (x * m_cellWidth) - m_cellWidth, (y * m_cellWidth) - m_cellWidth }, { m_cellWidth, m_cellWidth });
		}
	}

	m_font.loadFromFile("./fonts/fancy.ttf");
	m_generationText.setFont(m_font);
	m_generationText.setPosition({0.0f, 0.0f});
	m_generationText.setCharacterSize(15u);
	m_generationText.setFillColor(sf::Color(15, 15, 255));

	m_promptText.setFont(m_font);
	m_promptText.setString("Press E to manually generate live cells OR \n press R to randomly generate live cells");
	m_promptText.setPosition({ 50.0f, 10.0f });
	m_promptText.setCharacterSize(25u);
	m_promptText.setFillColor(sf::Color(15, 105, 255));
}


void Application::Run() {
	while (m_mainWindow.isOpen()) {
		sf::Event evnt;
		while (m_mainWindow.pollEvent(evnt)) {
			this->pollEvent(evnt);
			if (evnt.type == sf::Event::Closed) {
				m_mainWindow.close();
			}
		}
		m_mainWindow.clear();

		if (m_hasBegun) {
			if (m_deltaTime.getElapsedTime().asMilliseconds() > 100) {
				this->Update();
				m_deltaTime.restart();
			}
		}
		this->Render();

		m_mainWindow.display();
	}
}

void Application::pollEvent(sf::Event& evnt) {
	switch (evnt.type) {
	case sf::Event::KeyPressed:
		if (!m_hasBegun) { // these cant run during the simulation
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				m_mode = EDIT;
				// editable (will add)
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				m_mode = RANDOM;
				this->KillAll();
				this->SetRandomToAlive();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (m_hasBegun) { // if the simulation stopped
				this->KillAll();
				m_mode = NONE;
			}

			if (m_mode != NONE || m_hasBegun) {
				m_hasBegun = !m_hasBegun;
				m_generation = 0;
				m_generationText.setString(""); // make generation text disappear
			}
		}
		break;
	}
}

void Application::Update() {
	for (unsigned short int x = 0; x < m_cellNumX; x++) {
		for (unsigned short int y = 0; y < m_cellNumY; y++) {
			if (x == 0 || x == m_cellNumX - 1 || y == 0 || y == m_cellNumY -1) {
				m_cells[x][y]->SetState(DEAD);
			}
			else {
				switch (m_cells[x][y]->GetState()) {
				case ALIVE:
					if (CountNeighbors(x, y) < 2 || CountNeighbors(x, y) > 3) {
						this->AddToDeathList(x, y);
					}
					break;
				case DEAD:
					if (CountNeighbors(x, y) == 3) {
						this->AddToBirthList(x, y);
					}
					break;
				}
			}
		}
	}
	SpawnAndKill(); // the cells are spawned and killed once a generation

	m_generation++;
	m_generationText.setString("Generation: " + std::to_string(m_generation));
}

void Application::Render() {
	for (unsigned short int x = 1; x < m_cellNumX - 1; x++) {
		for (unsigned short int y = 1; y < m_cellNumY - 1; y++) {
			m_cells[x][y]->Render(m_mainWindow);
		}
	}
	m_mainWindow.draw(m_generationText);
	if (m_mode == NONE) m_mainWindow.draw(m_promptText);
}

void Application::SetRandomToAlive() {
	for (unsigned short int x = 0; x < m_cellNumX; x++) {
		for (unsigned short int y = 0; y < m_cellNumY; y++) {
			if (x == 0 || x == m_cellNumX - 1 || y == 0 || y == m_cellNumY - 1) {
				// makes dead cells
			}
			else if (rand() % 100 < 25) {
				m_cells[x][y]->SetState(ALIVE);
			}
		}
	}
}

void Application::KillAll() {
	for (unsigned short int x = 0; x < m_cellNumX; x++) {
		for (unsigned short int y = 0; y < m_cellNumY; y++) {
			m_cells[x][y]->SetState(DEAD);
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

void Application::AddToDeathList(int x, int y) {
	m_killCoords.emplace_back(sf::Vector2i(x, y));
}	

void Application::AddToBirthList(int x, int y) {
	m_birthCoords.emplace_back(sf::Vector2i(x, y));
}

void Application::SpawnAndKill() {
	for (auto& it : m_birthCoords) {
		m_cells[it.x][it.y]->SetState(ALIVE);
	}
	for (auto& it : m_killCoords) {
		m_cells[it.x][it.y]->SetState(DEAD);
	}
	m_birthCoords.clear();
	m_killCoords.clear();
}

Application::~Application() {
	for (unsigned short int x = 0; x < m_cellNumX; x++) {
		for (unsigned short int y = 0; y < m_cellNumY; y++) {
			delete m_cells[x][y];
		}
	}
}
