#pragma once
#include <SFML/Graphics.hpp>

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
private:
	sf::RenderWindow m_mainWindow;
};

