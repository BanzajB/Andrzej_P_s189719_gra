#include "Przeciwnik.h"



void Przeciwnik::initVariables()
{
	this->licznikPunkt�w = rand() % 8 + 3;           //rand() % 8 warto�ci od 0-7;           warto�ci mi�dzy 3 a 10
	this-> type          = 0; 
	this->speed          = static_cast<float>(this->licznikPunkt�w/2);        //rzutoawanie;   speed jest float wi�c musimy wrto�� z licznika punkt�w zrzutowa� na float
	this-> hpMax         = static_cast<int>(this->licznikPunkt�w);
	this-> hp            = this->hpMax;                                   //aktualne hp przeciwnika
	this-> damage        = this->licznikPunkt�w;
	this-> points        = this->licznikPunkt�w /3;                  //liczba punkt�w co si� dotaje po zniszeczniu przeciwnika
}

void Przeciwnik::initKsztalt()
{
	this->ksztalt.setRadius(this->licznikPunkt�w *3);                           //wielko�� przeciwnik�w
	this->ksztalt.setPointCount(this->licznikPunkt�w);                          // kszta�t w zale�no��i od ilo�ci k�t�w
	this->ksztalt.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));                  // random color
}

Przeciwnik::Przeciwnik(float poz_x, float poz_y)
{
	
	this->initVariables();
	this->initKsztalt();
	this->ksztalt.setPosition(poz_x, poz_y);
	
}

Przeciwnik::~Przeciwnik()
{
}

//Accessor
const sf::FloatRect Przeciwnik::getObrys() const
{
	return this->ksztalt.getGlobalBounds();
}

const int& Przeciwnik::getPunkty() const
{
	return this->points;
}

const int& Przeciwnik::getDamage() const
{
	return this->damage;
}


//F
void Przeciwnik::update()
{
	this->ksztalt.move(0.f, this->speed);
}

void Przeciwnik::render(sf::RenderTarget* target)
{
	target->draw(this->ksztalt);
}
