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
private:
	sf::RenderWindow m_mainWindow;
	Cell* m_cells[52][33];
	sf::Clock m_deltaTime;
};

