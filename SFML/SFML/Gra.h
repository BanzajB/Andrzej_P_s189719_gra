#pragma once

#include<time.h>
#include<map>
#include"gracz.h"
#include"Pocisk.h"
#include"Przeciwnik.h"


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

	//Resources
	std::map<std::string, Texture*> textures;    //alokacja pami�ci, mapuje dwie cechy razem (dla ka�dego stringa daje tekstur�)
	std::vector<Pocisk*> pocisk;

	//GUI
	Font czcionka;
	Text Punkt_txt;


						//Gracz (wska�nik)
	gracz* player;

	//Przeciwnicy

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Przeciwnik*> przeciwnicy;    //wektor by mie� kilku przeciwnik�w

	
	

	void initPlayer();
	void initTextures();
	void initGUI();
	void initPrzeciwnicy();


public:
									//Konstruktor  / Destruktor
	Gra();
	virtual ~Gra();

	//Accessors / U�ywane do pobierane danych z privte
	//const bool running() const;


	//Funkcje

	
	void run();

	void pollEvents();
	//void cooldown(int seconds);
	void updateEvents();
	void updateInput();
	void updateGUI();
	void updatePociski();
	void updatePrzeciwnicy();
	void update();

	void renderGUI();
	void render();
};

