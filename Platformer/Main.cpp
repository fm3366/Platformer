#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
using namespace sf;
float offsetX = 0, offsetY = 0;
const int H = 15;
const int W = 150;
String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                          0                                                                                                         0",
"0                                          0                                                                                                         0",
"0c                                         0                                                                                                         0",
"0kkkkkkkkkkk                               0                                                                                                         0",
"0             kkkkkkk                      0                                                                                                         0",
"0                      kk                  0                                                                                                         0",
"0                         k                0                                                                                                         0",
"0                          kk              0                                                                                                         0",
"0                             k            0                                                                                                         0",
"0                              kkk         0                                                                                                         0",
"0                        ck       k        0                                                                                                         0",
"0                       kkk         kk   t 0                                                                                                         0",
"0        g g  g         kkk              - 0                                                                                                         0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	int keyes;

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(65, 600, 60, 64);
		dx = dy = 0.1;
		currentFrame = 0;
		keyes = 0;
		Texture key;
	}
	void update(float time)
	{
		rect.left += dx * time;
		Collision(0);
		if (!onGround)
			dy = dy + 0.0005*time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);
		currentFrame += time * 0.005;
		if (currentFrame > 3)
			currentFrame -= 3;
		if (dx > 0)
			sprite.setTextureRect(IntRect(10 + 94 * int(currentFrame), 20, 82, 76));
		if (dx < 0)
			sprite.setTextureRect(IntRect(10 + 94 * int(currentFrame) + 82, 20, -82, 76));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}
	void Collision(int num)
	{

		for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r'))
				{
					if (dy > 0 && num == 1)
					{
						rect.top = i * 64 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 64 + 64;   dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 64 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 64 + 64;
					}
				}
				if (TileMap[i][j] == 'c')
				{
					TileMap[i][j] = ' ';
					keyes++;
					
				}
			}

	}
	int getkey()
	{
		return keyes;
	}
};

class ENEMY
{
public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;
	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 64, 64);
		dx = 0.05;
		currentFrame = 0;
		life = true;
	}
	void update(float time)
	{
		rect.left += dx * time;
		Collision();
		//currentFrame += time * 0.005;
		//if (currentFrame > 2) 
		//	currentFrame -= 2;
		sprite.setTextureRect(IntRect(528, 147, 51, 72));
		if (!life)
			sprite.setTextureRect(IntRect(477, 278, 51, 72));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}
	void Collision()
	{
		for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'k'))
				{
					if (dx > 0)
					{
						rect.left = j * 64 - rect.width; dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 64 + 64;  dx *= -1;
					}

				}
	}
};

int main()
{
	RenderWindow window(VideoMode(1440, 960), "Project!");
	Texture tileSet;
	tileSet.loadFromFile("platformPack_tilesheet.png");
	Texture hero;
	hero.loadFromFile("platformerPack_character.png");
	Texture enem;
	enem.loadFromFile("enemies.png");
	PLAYER Hero(hero);
	ENEMY  enemy;
	enemy.set(enem, 19 * 64, 14 * 64 - 72);
	Sprite tile(tileSet);
	
	Sprite Keyimage(tileSet);
	Keyimage.setTextureRect(IntRect(512, 256, 64, 64));
	Keyimage.setPosition(1376, 0);
	
	
	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);

	Music music;
	music.openFromFile("Mario_Theme.ogg");
	music.play();

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
			Hero.dx = -0.1;

		if (Keyboard::isKeyPressed(Keyboard::Right))
			Hero.dx = 0.1;

		if (Keyboard::isKeyPressed(Keyboard::Up))
			if (Hero.onGround)
			{
				Hero.dy = -0.43;
				Hero.onGround = false;
				sound.play();
			}

		Hero.update(time);
		enemy.update(time);


		if (Hero.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (Hero.dy > 0) { enemy.dx = 0; Hero.dy = -0.2; enemy.life = false; }
				else Hero.sprite.setColor(Color::Red);
			}
		}
		if (Hero.rect.left > 200) offsetX = Hero.rect.left - 200;

		window.clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')
					tile.setTextureRect(IntRect(192, 64, 64, 64)); //���

				if (TileMap[i][j] == 'k')
					tile.setTextureRect(IntRect(192, 256, 64, 64)); // ����� �� ������ �������

				if (TileMap[i][j] == 'c')
					tile.setTextureRect(IntRect(512, 256, 64, 64)); // ����

				if (TileMap[i][j] == 't')
					tile.setTextureRect(IntRect(448, 318, 64, 128)); // �����

				if (TileMap[i][j] == 'g')
					tile.setTextureRect(IntRect(0, 320, 64, 64));// ����

				if (TileMap[i][j] == '0')
					tile.setTextureRect(IntRect(256, 256, 64, 64)); // ���� �����

				if (TileMap[i][j] == ' ' || TileMap[i][j] == '-')
					continue;

				tile.setPosition(j * 64 - offsetX, i * 64 - offsetY);
				window.draw(tile);
			}
		if (Hero.getkey() != 0)
			window.draw(Keyimage);
		window.draw(Hero.sprite);
		window.draw(enemy.sprite);

		window.display();
	}

	return 0;
}