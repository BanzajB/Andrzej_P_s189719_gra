#include "Gra.h"


using namespace sf;
//Tutaj deklarujemy funkcje


// Prywatne Funkcje
/*void Gra::initVariable()
{
	this->window = nullptr;
}
*/

void Gra::initWindow()
{
	//zamiast na twardo wymiary w RenderWidndow to mamy w zmiennych
	this->videoMode.height = 800;
	this->videoMode.width = 1400;

	this ->window = new RenderWindow(this->videoMode, "Space shootage");

	//ograniczmy ilo�� klatek
	this->window->setFramerateLimit(144);

	//wy��czamy vsync(synchr. pionow�)
	this->window->setVerticalSyncEnabled(false);

}



void Gra::initPlayer()
{
	this->player = new gracz();

}

void Gra::initTextures()
{
	this->textures["POCISK"] = new Texture();
	this->textures["POCISK"]->loadFromFile("textures/laser.png");
}

void Gra::initGUI()
{
	//Czcionka
	if(!this->czcionka.loadFromFile("textures/PixelFlag.ttf"));
	std::cout << "ERROR nie uda�o si� zaladowa� czcionki! " << std::endl;

	// Init tekstu do punkt�w
	this->Punkt_txt.setFont(this->czcionka);
	this->Punkt_txt.setCharacterSize(30);
	this->Punkt_txt.setFillColor(sf::Color::Yellow);
	this->Punkt_txt.setString("AMOGUS");                        //dajemy stringa na nasza czcionk� 
}

void Gra::initPrzeciwnicy()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = spawnTimerMax;
}

// Konstruktor 
Gra::Gra()
{
	//this->initVariable();
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initPlayer();
	this->initPrzeciwnicy();
}

// Destruktor / Niszczy obiekty klass stworzone przez konstruktor
Gra::~Gra()
{
	delete this->window;
	delete this->player;

	//Kasowanie tekstur

	for (auto  &i : this->textures)  //r�wnocze�nie z deklaracj� nast�puje inicjalizacja zmiennej warto�ci� (auto - samo decyduje o typie zmienniej)
	{                                          // for dla kolejnych tekstur przypisuje kolejne warto�ci i po tym iteruje
		delete i.second;                        // w mapie mapowan� warto�� kasuje, a nie klucz
	}

	for (auto* i : this->pocisk)  // kasowanie pocisk�w
	{
		delete i;
	}

	for (auto* i : this->przeciwnicy)
	{
		delete i;
	}

}

//Accessors / Mo�emy odpali� onko kt�re mamy w private

/*const bool Gra::running() const
{
	return this->window->isOpen();
}
*/



//Functions


void Gra::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Gra::pollEvents()
{
	//u�ywamy thiss bo window to wzka�nik
	while (this ->window ->pollEvent(this ->ev)) 
	{
		if (this ->ev.type == Event::Closed)
			this ->window->close();

		switch (this ->ev.type)
		{
		case Event::KeyPressed:
			if (this ->ev.key.code == Keyboard::J)
				this->window->close();
			break;
		}
	}
}

/*void Gra::cooldown(int seconds)
{
	clock_t start = clock();
	clock_t period = seconds * CLOCKS_PER_SEC;
	clock_t elapsed;                             //czas kt�ry up�yn�

	do {
		elapsed = clock() - start;
	} while (elapsed < period);
}
*/

void Gra::updateEvents()
{
	
}

void Gra::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		this->player->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->player->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->player->move(0.f, 1.f);

	if (Keyboard::isKeyPressed(Keyboard::Space) && this->player->resetReload())    //resetReload zwraca true
	{
		this->pocisk.push_back(new Pocisk(this->textures["POCISK"], this->player->getPozycja().x + 25.f, this->player->getPozycja().y - 15.f, 0.f, -1.f, 4.f));  // push_back dodaje elementy rzosze�aj�c vektor "pocisk"
	}

}

void Gra::updateGUI()
{
}

void Gra::updatePociski()
{
	unsigned licznik = 0;

	for (auto* naboj : this->pocisk)                               // nab�j to pojedy�czy pocisk; "pocisk" odnosi sie do ka�dego pocisku (wektora pocisk�w)
	{
		naboj->update();


		if (naboj->getObrysPck().top + naboj->getObrysPck().height < 0.f)  //kasowanie pocisk�w gdy wyjd� poza ekaran
		{

			delete this->pocisk.at(licznik);	                   //delete do kasowania rzeczy tworzonych przez new  // licznik to klucz w mapowaniu  
			this->pocisk.erase(this->pocisk.begin() + licznik);    //kasowanie z wektora, kasujemy ten pociski co jako piwrwszy wylecaia�
			--licznik;

			//std::cout << this->pocisk.size() +1 << "\n";          //zliczanie naboji na ekranie
		}
		++licznik;
	}
}

void Gra::updatePrzeciwnicy()
{
	this->spawnTimer += 0.5f;                                        //przeciwnicy ci�gle si� pojawiaj� 
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->przeciwnicy.push_back(new Przeciwnik(rand()% this->window->getSize().x -20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	/* if (1 > 0)
	{
		cooldown(3);
		this->przeciwnicy.push_back(new Przeciwnik(rand() % (this->videoMode.width) - 30, rand() % (this->videoMode.height) - 30));
	}
	*/

	


	for (int i = 0; i < this->przeciwnicy.size(); ++i)							// i - numeracja przeciwnik�w
	{
		bool  przeciwnik_erased = false;

		this->przeciwnicy[i]->update();										//przciwnicy pojawiaj� si� ci�gle

		for (size_t k = 0; k < this->pocisk.size() && !przeciwnik_erased; k++)                 //kolizja           // size_t - typ ca�kowity bez znaku (unsigned int), mie�ci rozmiar dowolnego obiektu
		{
		

			if (this->pocisk[k]->getObrysPck().intersects(this->przeciwnicy[i]->getObrys()))
			{
				delete this->pocisk[k];
				this->pocisk.erase(this->pocisk.begin() + k);

				delete this->przeciwnicy[i];
				this->przeciwnicy.erase(this->przeciwnicy.begin() + i);
				przeciwnik_erased = true;
			}
		}
		
		
		if (!przeciwnik_erased)                                           //true musi by� by if si� wykona�
		{
			if (this->przeciwnicy[i]->getObrys().top > this->window->getSize().y)  //usuwanie przeciwnik�w z do�u okienka
			{
				delete this->przeciwnicy[i];
				this->przeciwnicy.erase(this->przeciwnicy.begin() + i);
				std::cout << this->przeciwnicy.size() << std::endl;            //zliczanie przzeciwnik�w
				przeciwnik_erased = true;
			}
		}
	}
}


void Gra::update()
{
	this->pollEvents();

	this->updateInput();

	this->player->update();

	this->updatePociski();

	this->updatePrzeciwnicy();

	this->updateGUI();
}

void Gra::renderGUI()
{
	this->window->draw(this->Punkt_txt);
}

void Gra::render()
{
	this->window->clear(Color::Blue);

	//tu b�dziemy rysowa� gr�
	this->player->render(*this->window);

	for (auto* naboj : this->pocisk)   // naboj to 1 pocisk
	{
		naboj->render(this->window);
	}

	for (auto* a : this->przeciwnicy)  // a to 1 przeciwnik
	{
		a->render(this->window);
	}

	this->renderGUI();

	this->window->display();
}