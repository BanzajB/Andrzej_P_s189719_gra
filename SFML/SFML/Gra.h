#pragma once
#include"gracz.h"



// Okno jako klasa / game engine
//tworzymy funkcje

using namespace sf;


class Gra
{
private:
									//Private functions
	//void initVariable();

	void initWindow(); 
	



	//Variables
							//Okno jako pointer
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

						//Gracz (wska�nik)
	gracz* player;
	void initPlayer();
	


public:
									//Konstruktor  / Destruktor
	Gra();
	virtual ~Gra();

	//Accessors / U�ywane do pobierane danych z privte
	//const bool running() const;


	//Funkcje

	
	void run();
	void pollEvents();
	void update();
	void render();
};

