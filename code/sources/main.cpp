
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "Scene.hpp"

int main()
{
	// Window size
	const int WINDOW_WIDTH  = 1164;
	const int WINDOW_HEIGHT = 412;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Box2D Assignment", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);	
	
	// Scene creation
	Scene scene((size_t)WINDOW_WIDTH, (size_t)WINDOW_HEIGHT);
	
	float delta_time = 0.015f;	// ~60 fps
	bool running = true;

	do
	{
		// Process window events:
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
		}

		// Update:		
		scene.update(delta_time);

		// Render:
		window.clear();
		scene.render(window);
		window.display();
		
	} while (running);

	return EXIT_SUCCESS;

}