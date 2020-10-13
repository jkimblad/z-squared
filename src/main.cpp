#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <complex>

const int MAX_FPS = 60;
const int MICROSECS_PER_FRAME = 1000000 / MAX_FPS;

int normalize_complex(int cmplx, int max_size) {
	return cmplx * (max_size / 2 / 10) + (max_size / 2);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Program",
				sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);

	std::complex<int> cordinates(3, 3);
	sf::CircleShape circle(50);
	circle.setFillColor(sf::Color(100, 250, 10));

	sf::Clock clock;
	u_int elapsed = 0;
	while (window.isOpen()) {
		elapsed += clock.getElapsedTime().asMicroseconds();
		clock.restart();

		window.clear(sf::Color::White);
		// Draw stuff here
		window.draw(circle);
		window.display();

		// Update loop
		while (elapsed > MICROSECS_PER_FRAME) {
			// Do something cool
			circle.setPosition(
			    normalize_complex(cordinates.real(), 640) -
				(circle.getLocalBounds().width / 2),
			    normalize_complex(-1 * cordinates.imag(), 480) -
				(circle.getLocalBounds().height / 2));

			elapsed -= MICROSECS_PER_FRAME;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			window.draw(circle);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	return EXIT_SUCCESS;
}

