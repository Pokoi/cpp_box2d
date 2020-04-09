
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>

#include "T2DPhysicWorld.hpp"
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"

#include "car.hpp"
#include "Geometry.hpp"
#include "InteractuableGeometry.hpp"

int main()
{
	const int WINDOW_WIDTH  = 960;
	const int WINDOW_HEIGHT = 480;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Box2D Assignment", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);	

	T2DPhysicWorld world(glm::vec2{ 0.f,-10.f });	
	
	Car car(world);	
	Geometry solid_geometry ((size_t)WINDOW_WIDTH, (size_t)WINDOW_HEIGHT, world);
	InteractuableGeometry receive_platform ((size_t)WINDOW_WIDTH, (size_t)WINDOW_HEIGHT, world);

	T2DPhysicBody body2(world, T2DPhysicBody::body_types::STATIC, {0,1});
	T2DPhysicCollider collider2(body2, glm::vec2{ 0,0 }, glm::vec2{ 0,0 }, glm::vec2{ 800,0 }, sf::Color::Red, 1.f, 0.f, 0.f);


	sf::Clock timer;
	float delta_time = 0.015f;	// ~60 fps
	bool running = true;

	do
	{
		timer.restart();

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
		world.get_world()->Step(delta_time, 8, 4);
		car.update(delta_time);

		// Render:
		window.clear();

		solid_geometry.render(window);
		receive_platform.render(window);
		car.render(window);
		body2.render(window);

		window.display();

		delta_time = (delta_time + timer.getElapsedTime().asSeconds()) * 0.5f;
	} while (running);

	return EXIT_SUCCESS;

}