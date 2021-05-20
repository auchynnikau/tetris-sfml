#include <SFML/Graphics.hpp>

using namespace sf;

const int HEIGHT = 20;
const int WIDTH = 10;

int field[HEIGHT][WIDTH] = { 0 };

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	int x, y;
} a[4], b[4];

int main()
{
	RenderWindow window(VideoMode(320, 480), "The Game!");

	Texture texture;
	texture.loadFromFile(".\\images\\tiles.png");

	Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0;
	bool rotate = 0;
	float timer = 0, delay = 0.3;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) rotate = true;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;
			}
		}

		// movement
		for (int i = 0; i < 4; i++) {
			a[i].x += dx;
		}

		// rotation
		if (rotate)
		{
			Point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 1;
			timer = 0;
		}

		int n = 3;

		if (a[0].x == 0) {
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}

		dx = 0;
		rotate = 0;

		window.clear(Color::White);

		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(sprite);
		}

		window.display();
	}
	return 0;
}
