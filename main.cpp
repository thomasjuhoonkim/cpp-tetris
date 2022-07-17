#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(320, 480), "The Game!");
	
	Texture t;
	t.loadFromFile("images/tiles.png");
	
	Sprite s(t);
	
	while (window.isOpen())
	{
		Event e;
		while(window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
				
		}
		window.clear(Color::White);
		window.draw(s);
		window.display();
	}
	
	return 0;
}
