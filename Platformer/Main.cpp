#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<math.h>
#include <time.h>

using namespace sf;
bool isExit = 0;
int Zdvig = 1;
void menu(RenderWindow & window, bool &exit)
{
	Texture menuTexture1, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("111.png");
	menuTexture3.loadFromFile("333.png");
	menuBackground.loadFromFile("background.jpg");
	Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu3.setPosition(100, 130);
	menuBg.setPosition(0, 0);
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Blue);
			menuNum = 1;
		}
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Blue);
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 3)
			{
				window.close();
				isMenu = false;
				exit = 1;
			}

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu3);

		window.display();
	}
}

float offsetX = 0, offsetY = 640;
const int H = 25;
const int W = 150;
String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                k                         k                                           k                                                             0",
"0               k                          k                                           k                                                             0",
"0              k                           k                                           k                                                             0",
"0             k                            k                                           k                                                             0",
"0            k                             k                                           k                                                             0",
"0           k                              k                                           k                                                             0",
"0          k                               k                                           k                                                             0",
"0         k                                k                                           k                                                             0",
"0        k                                 k                                           k                                                             0",
"0       k                                  k                                           k                                                             0",
"0      k                                   k                                           k                                                             0",
"0     k                                    k          k                                k                                                             0",
"0c                                         k       T     k                             k                         c                                   0",
"0kkkkkkkkkkk                               k       t                                   k                         k                                   0",
"0             kkkkkkk                      k       k k k   g                           k                        k                                    0",
"0                      kk                  k             kkkk k kk                     k                       k                                     0",
"0                         k                k                      k                    k                      k                                      0",
"0                          kk              k                       kg  g  k            k                 kkkkkk                                      0",
"0                             k            k                        kkkkkk  k          k                 k                                           0",
"0                              kkk         k                                 k         k                kk                                           0",
"0                        ck       k        k                                     k     k              k kk        k  k                               0",
"0                       kkk         kk   T k                                  k   k    k            k k kT             k                             0",
"0        g    g g       kkk              t k                                      g cg k            k k kt       g  gggg                             0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};
void resetMap()
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (TileMap[i][j] == 'C')
				TileMap[i][j] = 'c';
			if (TileMap[i][j] == 'v')
				TileMap[i][j] = 't';
			if (TileMap[i][j] == 'V')
				TileMap[i][j] = 'T';

		}
	}

}
class PLAYER {

private:
	int HP;
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	int keyes;
public:
	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(65, 1240, 60, 64);
		dx = dy = 0.1;
		currentFrame = 0;
		keyes = 0;
		Texture key;
		HP = 3;
	}
	int getHP()
	{
		return HP;
	}
	float getDX()
	{
		return dx;
	}
	float getDY()
	{
		return dy;
	}
	FloatRect getrect()
	{
		return rect;
	}
	Sprite getSprite()
	{
		return sprite;
	}
	float getcurrentFrame()
	{
		return currentFrame;
	}
	bool getonGround()
	{
		return onGround;
	}
	void setRectLeft(int a)
	{
		rect.left = a;
	}
	void setonGround(bool x)
	{
		onGround = x;
	}
	void setRect(FloatRect rect1)
	{
		rect = rect1;
	}
	void setDX(float a)
	{
		dx = a;
	}
	void setDy(float a)
	{
		dy = a;
	}
	void setHP(int a)
	{
		HP = a;
	}
	void setSprite(Sprite sprite1)
	{
		sprite = sprite1;
	}
	void setCurrentframe(float a)
	{
		currentFrame = a;
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

		remove();
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
				if (TileMap[i][j] == 'g' && (rect.top + 76) > (i * 64 + 32) && (abs(rect.left - j * 64) < 40))
				{
					HP = HP - 1;
					if (dy == 0)
					{
						if (dx > 0) rect.left = j * 64 - rect.width;
						else rect.left = j * 64 + 64;
					}
					else
						rect.top = rect.top - 5;
					dy = -0.4;
				}
				
				if (TileMap[i][j] == 'c')
				{
					TileMap[i][j] = 'C';
					keyes++;

				}
				if ((TileMap[i][j] == 'T') && keyes != 0)
				{
					keyes = keyes - 1;
					TileMap[i][j] = 'V';
					TileMap[i + 1][j] = 'v';
				}
				if ((TileMap[i][j] == 't') && keyes != 0)
				{
					keyes = keyes - 1;
					TileMap[i - 1][j] = 'V';
					TileMap[i][j] = 'v';
				}
			}
	}
	int getkey()
	{
		return keyes;
	}
	void remove()
	{
		for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
			{
				if ((TileMap[i][j] == 'V') || (TileMap[i][j] == 'v'))
				{
					rect = FloatRect(44 * 64 * Zdvig + 1, 1240, 60, 64);
					Zdvig++;
					offsetY = 640;

				}
			}
	}
};

class ENEMY
{
protected:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;
public:
	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 64, 64);
		dx = 0.05;
		currentFrame = 0;
		life = true;
	}
	void set(Texture &image, int x, int y, float speed)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 64, 64);
		dx = speed;
		currentFrame = 0;
		life = true;
	}
	float getDX()
	{
		return dx;
	}
	float getDY()
	{
		return dy;
	}
	FloatRect getrect()
	{
		return rect;
	}
	Sprite getSprite()
	{
		return sprite;
	}
	float getcurrentFrame()
	{
		return currentFrame;
	}
	bool getLife()
	{
		return life;
	}
	void setDX(float a)
	{
		dx = a;
	}
	void setDy(float a)
	{
		dy = a;
	}
	void setRect(FloatRect rect1)
	{
		rect = rect1;
	}
	void setSprite(Sprite sprite1)
	{
		sprite = sprite1;
	}
	void setCurrentframe(float a)
	{
		currentFrame = a;
	}
	void setLife(bool a)
	{
		life = a;
	}
	void ATTACK(PLAYER &Hero)
	{
		if (Hero.getrect().intersects(rect))
		{
			if (life) {
				if (Hero.getDY() > 0) { dx = 0; Hero.setDy(-0.2); life = false; }
				else
				{
					Hero.setHP( Hero.getHP() - 1);
					Hero.setDy  (-0.4);
					if (dx > 0) { dx = -0.15; Hero.setRectLeft( Hero.getrect().left + 15); }
					else { dx = 0.15; Hero.setRectLeft( Hero.getrect().left - 15); }
				}
			}
		}
	}
};
class GOAST : public ENEMY
{
public:
	void update(float time)
	{
		rect.left += dx * time;
		Collision();
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
class BAT : public ENEMY
{
public:
	void update(float time)
	{
		rect.left += dx * time;
		Collision();
		sprite.setTextureRect(IntRect(71, 188, 70, 48));
		if (!life)
		{
			sprite.setTextureRect(IntRect(71, 188, 70, 48));
			rect.top =24*64 - 48;
		}
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
bool isGameStarted()
{
	RenderWindow window(VideoMode(1440, 960), "Project!");
	menu(window, isExit);
	Texture tileSet;
	tileSet.loadFromFile("platformPack_tilesheet.png");
	Texture hero;
	hero.loadFromFile("platformerPack_character.png");
	Texture enem;
	enem.loadFromFile("enemies.png");
	PLAYER Hero(hero);
	GOAST enemy;
	enemy.set(enem, 19 * 64, 24 * 64 - 72);
	BAT bbat;
	bbat.set(enem, 64 * 64, 23 * 64 - 48);
	Sprite tile(tileSet);
	Sprite Keyimage(tileSet);
	Keyimage.setTextureRect(IntRect(512, 256, 64, 64));
	Keyimage.setPosition(1376, 0);

	Sprite heart(tileSet);
	heart.setTextureRect(IntRect(704, 256, 64, 64));
	heart.setPosition(0, 0);

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
			Hero.setDX (-0.1);

		if (Keyboard::isKeyPressed(Keyboard::Right))
			Hero.setDX (0.1);

		if (Keyboard::isKeyPressed(Keyboard::Up))
			if (Hero.getonGround())
			{
				Hero.setDy(-0.43);
				Hero.setonGround( false);
				sound.play();
			}

		Hero.update(time);
		bbat.update(time);
		enemy.update(time);
		
		
		enemy.ATTACK(Hero);
		bbat.ATTACK(Hero);

		if (Hero.getrect().left > 500) offsetX = Hero.getrect().left - 500;
		if (Hero.getrect().top < 1240) offsetY = Hero.getrect().top - 600;

		window.clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')
					tile.setTextureRect(IntRect(192, 64, 64, 64)); //ïîë

				if (TileMap[i][j] == 'k')
					tile.setTextureRect(IntRect(192, 256, 64, 64)); // áëîêè ïî êîòðûì ïðûãàòü

				if (TileMap[i][j] == 'c')
					tile.setTextureRect(IntRect(512, 256, 64, 64)); // êëþ÷

				if (TileMap[i][j] == 'T')
					tile.setTextureRect(IntRect(448, 318, 64, 128)); // äâåðü

				if (TileMap[i][j] == 'V')
					tile.setTextureRect(IntRect(320, 320, 64, 128)); // äâåðü îòêðûòà

				if (TileMap[i][j] == 'g')
					tile.setTextureRect(IntRect(0, 320, 64, 64));// øèïû

				if (TileMap[i][j] == '0')
					tile.setTextureRect(IntRect(256, 256, 64, 64)); // êðàé êàðòû

				if (TileMap[i][j] == ' ' || TileMap[i][j] == 't' || TileMap[i][j] == 'v' || TileMap[i][j] == 'C')
					continue;

				tile.setPosition(j * 64 - offsetX, i * 64 - offsetY);
				window.draw(tile);
			}
		if (Hero.getkey() != 0)
			window.draw(Keyimage);
		for (int i = 0; i < Hero.getHP(); i++)
		{
			heart.setPosition(i*64, 0);
			window.draw(heart);
		}
		window.draw(enemy.getSprite());
		window.draw(bbat.getSprite());
		window.draw(Hero.getSprite());
		if (Keyboard::isKeyPressed(Keyboard::Tab) || Hero.getHP() == 0 || Zdvig == 4)
		{
			offsetX = 0;
			offsetY = 640;
			Zdvig = 1;
			resetMap();
			return true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			return false;
		window.display();
	}

}

void GameRunning()
{
	if (isGameStarted() && !isExit)
	{
		offsetX = 0;
		offsetY = 640;
		GameRunning();
		Zdvig = 1;
		resetMap();
	}
}

int main()
{
	GameRunning();
	return 0;
}