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

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		int n = 3;
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

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
