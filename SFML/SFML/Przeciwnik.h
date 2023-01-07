#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>

#include <iostream>

class Przeciwnik
{
private:
	sf::CircleShape ksztalt;

	unsigned licznikPunkt�w;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;


	void initVariables();
	void initKsztalt();

public:
	Przeciwnik(float poz_x, float poz_y);
	virtual ~Przeciwnik();

	// Accessor
	const sf::FloatRect getObrys() const;   // const przed deklaracj�: funkcja nie modyfikuje obiektu ; const po: wrto�ci zwracane przez funkcje nie mog� by� modyfikowane
	const int& getPunkty() const;
	const int& getDamage() const;

	//F
	void update();
	void render(sf::RenderTarget* target);
};

