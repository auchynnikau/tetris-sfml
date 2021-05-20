#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int HEIGHT = 20;
const int WIDTH = 10;

int field[HEIGHT][WIDTH] = { 0 };

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	int x, y;
} a[4], b[4];

bool check()
{
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT || field[a[i].y][a[i].x]) {
			return 0;
		}
	}

	return 1;
};

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(230, 400), "Tetris");

	Texture texture;
	texture.loadFromFile(".\\images\\tiles.png");

	Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0, colorNum = 1, n = rand() % 7;
	bool rotate = 0, beginGame = true;
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

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			delay = 0.05;
		}

		// movement
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
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

			if (!check()) { 
				for (int i = 0; i < 4; i++) {
					a[i] = b[i];
				}
			}

		}

		// falling down
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { 
				b[i] = a[i];
				a[i].y += 1;
			}

			if (!check())
			{
				for (int i = 0; i < 4; i++) {
					field[b[i].y][b[i].x] = colorNum;
				}

				colorNum = 1 + rand() % 7;
				n = rand() % 7;

				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}

			}

			timer = 0;
		}

		// line check
		int k = HEIGHT - 1;

		for (int i = HEIGHT - 1; i > 0; i--)
		{
			int count = 0;

			for (int j = 0; j < WIDTH; j++)
			{
				if (field[i][j]) {
					count++;
				}

				field[k][j] = field[i][j];
			}

			if (count < WIDTH) {
				k--;
			}
		}

		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;

			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}

		dx = 0;
		rotate = 0;
		delay = 0.3;

		// render
		window.clear(Color::White);
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(28, 31);
				window.draw(sprite);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			sprite.move(28, 31);

			window.draw(sprite);
		}
		
		window.display();
	}

	return 0;
}
