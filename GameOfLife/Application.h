#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

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

	int CountNeighbors(const int Cx, const int Cy) const;

	void AddToDeathList(int x, int y);
	void AddToBirthList(int x, int y);

	void SpawnAndKill();
private:
	sf::RenderWindow m_mainWindow;
	Cell* m_cells[72][44];
	sf::Clock m_deltaTime;

	std::vector<sf::Vector2i> m_killCoords;
	std::vector<sf::Vector2i> m_birthCoords;

	const int m_cellNumX = 72;
	const int m_cellNumY = 44;
	const int m_cellWidth = 15;
};

