#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

enum Mode {
	NONE,
	EDIT,
	RANDOM
};

class Application
{
public:
	Application();
	~Application();
public:
	void Run();
private:
	void Update();
	void Render();

	void SetRandomToAlive();
	void KillAll();

	int CountNeighbors(const int Cx, const int Cy) const;

	void AddToDeathList(int x, int y);
	void AddToBirthList(int x, int y);

	void SpawnAndKill();

	void pollEvent(sf::Event& evnt);
private:
	sf::RenderWindow m_mainWindow;

	sf::RectangleShape m_quadBoard;
	sf::Texture        m_quadBoardTex;
	sf::Image          m_pixels;

	Cell* m_cells[192][124];

	sf::Clock m_deltaTime;

	Mode m_mode = NONE;

	std::vector<sf::Vector2i> m_killCoords;
	std::vector<sf::Vector2i> m_birthCoords;

	unsigned long long int m_generation = 0;
	sf::Font               m_font;
	sf::Text               m_generationText;
	sf::Text               m_promptText;

	const int m_cellNumX = 192;
	const int m_cellNumY = 124;
	const int m_cellWidth = 5;

	bool m_hasBegun = false;
};

