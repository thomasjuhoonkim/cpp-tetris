#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int PIXELS_PER_BLOCK = 18;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{int x,y;} a[4], b[4];

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

bool check()
{
	for (int i=0;i<4;i++)
		if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;
		
	return 1;
};

int main()
{
	srand(time(0));
	
	RenderWindow window(VideoMode(320, 480), "The Game!");
	
	Texture t;
	t.loadFromFile("images/tiles.png");
	
	Sprite s(t);
	s.setTextureRect(IntRect(0,0,PIXELS_PER_BLOCK,PIXELS_PER_BLOCK));
	
	int dx=0; bool rotate=0; int colorNum=1;
	float timer=0,delay=0.3;
	
	Clock clock;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;
		
		Event e;
		while(window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
				
			if (e.type == Event::KeyPressed)
				if (e.key.code==Keyboard::Up) rotate=true;
				else if (e.key.code==Keyboard::Left) dx=-1;
				else if (e.key.code==Keyboard::Right) dx=1;
		}
		
		//// <- Move -> ////
		for (int i=0;i<4;i++) a[i].x+=dx;
		if(!check()) for (int i=0;i<4;i++) a[i]=b[i];
		
		//////Rotate//////
		if (rotate)
		{
			Point p = a[1]; //center of rotation
			for (int i=0;i<4;i++)
			{
				int x = a[i].y-p.y;
				int y = a[i].x-p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
		}
		
		////////Tick////////
		if (timer>delay)
		{
			for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }
			
			if (!check())
			{
				for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;
				
				colorNum=1+rand()%7;
				int n=rand()%7;
				printf("%i",n);
				for (int i=0;i<4;i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer=0;
		}
		
		dx=0; rotate=0;
		
		//////////draw//////////
		window.clear(Color::White);
		
		for (int i=0;i<M;i++)
			for (int j=0;j<N;j++)
			{
				if (field[i][j]==0) continue;
				s.setPosition(j*PIXELS_PER_BLOCK,i*PIXELS_PER_BLOCK);
				window.draw(s);
			}
		
		for (int i=0;i<4;i++)
		{
			s.setPosition(a[i].x*PIXELS_PER_BLOCK,a[i].y*PIXELS_PER_BLOCK);
			window.draw(s);
		}
		window.display();
	}
	
	return 0;
}
