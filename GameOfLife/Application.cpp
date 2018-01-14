#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_mainWindow.create(sf::VideoMode(1000, 620), "Conway's Game Of Life", sf::Style::Close);
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

		this->Update();
		this->Render();

		m_mainWindow.display();
	}
}

void Application::Update() {
	
}

void Application::Render() {
	
}

Application::~Application() {

}
