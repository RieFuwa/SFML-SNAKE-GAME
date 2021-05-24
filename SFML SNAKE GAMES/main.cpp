#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
													

using namespace sf;
using namespace std;


int oyun = 1, dongu = 0, hiz = 200, randomx = 0, randomy = 0, score = 0, durdur = 0, tasiyici, yon=0;
bool dogru = true;	// my control mechanism
bool oyunuDurdur = true;
struct Point {
	int x = 0;
	int y = 0;
}p[625];

int main() {
	int size = 3;
	RenderWindow appWindow(VideoMode(625, 625), "----BEDIRHAN KABATAS----YILAN OYUNUM----"); //WİNDOW.
	Event nesnem;

	//MY MATERIALS !!!!
	Texture yilan, yilanSol, yilanAsagi, yilanYukari, karpuz, cimen, tekrar, pause, bir, iki, uc, arka;	
	bir.loadFromFile("bir.png");
	iki.loadFromFile("iki.png");
	uc.loadFromFile("uc.png");
	yilan.loadFromFile("yilan.png");
	pause.loadFromFile("pause.png");
	yilanAsagi.loadFromFile("yilanAsagi.png");
	yilanYukari.loadFromFile("yilanYukari.png");
	yilanSol.loadFromFile("yilanSol.png");
	arka.loadFromFile("arka.png");
	karpuz.loadFromFile("karpuz.png");
	cimen.loadFromFile("cimen.png");				
	tekrar.loadFromFile("tekrar.png");
	//skor.loadFromFile("skor.png");

	//color!!!
	Sprite yilansag(yilan), refresh(tekrar), transparent(karpuz), fondo(cimen), black(pause), sprite1(bir), sprite2(iki), sprite3(uc);  //renklerim
	Sprite yilansol(yilanSol), yilanasagi(yilanAsagi), yilanyukari(yilanYukari), arkayil(arka);
	yilansag.setPosition(0,0);
	yilansag.setColor(Color(255, 100, 120));
	yilansol.setColor(Color(255, 100, 120));
	yilanasagi.setColor(Color(255, 100, 120));
	yilanyukari.setColor(Color(255, 100, 120));
	arkayil.setColor(Color(255, 130, 120));
	transparent.setPosition(1000, 0);
	transparent.setColor(Color(255, 100, 50));

	//sound !!!!!!
	SoundBuffer saga, sola, yukari, asagi, yeme, carpma, baslama, pausebir;
	pausebir.loadFromFile("pausebir.wav");
	baslama.loadFromFile("baslama.wav");
	saga.loadFromFile("saga.wav");
	sola.loadFromFile("sola.wav");
	yukari.loadFromFile("yukari.wav");
	asagi.loadFromFile("asagi.wav");
	yeme.loadFromFile("yeme.wav");
	carpma.loadFromFile("carpma.wav");
	Sound ses;

	srand(time(NULL)); // I throw the watermelon in random places.
	randomx = 1 + rand() % (600);
	randomy = 1 + rand() % (600);
	for (int i = 0; i < 25; i++) {
		if (randomx <= (i + 1) * 25 && randomx > i * 25) randomx = (i + 1) * 25;
		if (randomy <= (i + 1) * 25 && randomy > i * 25) randomy = (i + 1) * 25;
	}

	//printing score	
	Font arial;
	arial.loadFromFile("arial.ttf");

	ostringstream ssScore;
	ssScore << "SKOR : " << score;

	Text skor;
	skor.setCharacterSize(30);
	skor.setFillColor(Color::Black);
	skor.setPosition({ 10,0 });
	skor.setFont(arial);
	skor.setString(ssScore.str());
	//skor.setColor(Color(28, 26, 16));
	while (appWindow.isOpen())
	{
		Vector2i pos = Mouse::getPosition(appWindow); //vector2i .	
		while (appWindow.pollEvent(nesnem)) //
		{
			if (nesnem.type == Event::Closed) {
				appWindow.close();
			}
			if (nesnem.type == Event::MouseButtonReleased) {		//.
				if (nesnem.key.code == Mouse::Left) {
					if (refresh.getGlobalBounds().contains(pos.x, pos.y)) { //sınır
						if (oyun == 2) { //Yandıktan sonra tekrara binen oyun.
							ses.setBuffer(baslama);
							ses.play();
							oyun = 1;
							refresh.setPosition(1000, 0);
							size = 3;
							p[0].x = 0;
							p[0].y = 0;
							dongu = 0;
							hiz = 200;
							score = 0;
							dogru = true;

							while (dogru) {					//My watermelon doesn't always come out in the same place.
								randomx = 1 + rand() % (600);
								randomy = 1 + rand() & (600);

								for (int i = 0; i < 24; i++) {
									if (randomx <= (i + 1) * 25 && randomx > i * 25) randomx = (i + 1) * 25; //my watermelon 25x25px.
									if (randomy <= (i + 1) * 25 && randomy > i * 25) randomy = (i + 1) * 25;
								}
								for (int i = 0; i < size; i++) {			//My watermelon snake won't come out of my body.
									if (randomx == p[i].x && randomy == p[i].y) {
										break;
									}
									if ((randomx != p[i].x || randomy != p[i].x) && i == size - 1) {
										dogru = false;
									}
								}
							}
						}
					}
				}
			}
			if (nesnem.type == Event::KeyPressed) { //controller
				if (oyun == 1) {
					if (nesnem.key.code == Keyboard::D && dongu != 1)
					{		
						ses.setBuffer(saga);
						ses.play();
						Sleep(1);
						dongu = 0;
						
					}
					if (nesnem.key.code == Keyboard::A && dongu != 0)
					{
						ses.setBuffer(sola);
						ses.play();
						Sleep(1);
						dongu = 1;
					}
					if (nesnem.key.code == Keyboard::S && dongu != 3)
					{
						ses.setBuffer(asagi);
						ses.play();
						Sleep(1);
						dongu = 2;
					}
					if (nesnem.key.code == Keyboard::W && dongu != 2)
					{
						ses.setBuffer(yukari);
						ses.play();
						Sleep(1);
						dongu = 3;
					}					
					//pause 
					if((nesnem.key.code == Keyboard::P) && durdur!=1)
					{		
						ses.setBuffer(pausebir);
						ses.play();												
						//tasiyici = hiz; VELOCITY
						//hiz = 2000;
						durdur = 1;							
					}				
					if ((nesnem.key.code == Keyboard::Enter))
					{
						ses.setBuffer(baslama);
						ses.play();	
						durdur = 0;						
						//Sleep(1000);
					}				
				}			
			}
		}
		//appWindow.clear(Color(26, 28, 36));
		if (durdur != 1) //Pause için
		{
			if (oyun == 1) {
				refresh.setPosition(1000, 0);
				//appWindow.draw(fondo); //			
				//appWindow.draw(orange);
				for (int i = size; i > 0; i--) {
					p[i].x = p[i - 1].x;
					p[i].y = p[i - 1].y;
				}
				if (dongu == 0) p[0].x += 25; //move
				if (dongu == 1) p[0].x -= 25;
				if (dongu == 2) p[0].y += 25;
				if (dongu == 3) p[0].y -= 25;
				
				//Game ending situations !!!!!!!!!!!!

				if (p[0].x == 625 || p[0].x == -25 || p[0].y == 625 || p[0].y == -25) { //hit the wall
					ses.setBuffer(carpma);
					ses.play();
					oyun = 2;
				}
				for (int i = 1; i < size; i++) {
					if (p[0].x == p[i].x && p[0].y == p[i].y) {			//hit yourself
						ses.setBuffer(carpma);
						ses.play();
						oyun = 2;
					}
				}
				if (p[0].x == transparent.getPosition().x && p[0].y == transparent.getPosition().y) // The snake is increasing in size
				{
					ses.setBuffer(yeme);
					ses.play();
					size += 1;
					score += 10;

					if (hiz != 70)hiz -= 4;							//  The snake is speeding up
					dogru = true;
					while (dogru) {					//Controll
						randomx = 1 + rand() % (600);
						randomy = 1 + rand() & (600);

						for (int i = 0; i < 24; i++) {
							if (randomx <= (i + 1) * 25 && randomx > i * 25) randomx = (i + 1) * 25; //watermelon 25x25px.
							if (randomy <= (i + 1) * 25 && randomy > i * 25) randomy = (i + 1) * 25;
						}
						for (int i = 0; i < size; i++) {			//My watermelon will not be able to come out of my snake body..
							if (randomx == p[i].x && randomy == p[i].y) {
								break;
							}
							if ((randomx != p[i].x || randomy != p[i].x) && i == size - 1) {
								dogru = false;
							}
						}
					}
				}
				transparent.setPosition(randomx, randomy); //watermelon coordinates.
			}
		}
		//score printing area!!!!
		ssScore.str("");
		ssScore << "SKOR : " << score;
		skor.setString(ssScore.str());
		appWindow.draw(fondo);
		appWindow.draw(transparent);
			
		for (int i = 1; i < size; i++) {   			
			if (i == 1)					
			{
				if (dongu == 0)				//snake animations!!
				{
					yilansag.setPosition(p[i].x, p[i].y);
					appWindow.draw(yilansag);
				}
				else if (dongu == 1)
				{
					yilansol.setPosition(p[i].x, p[i].y);
					appWindow.draw(yilansol);
				}
				else if (dongu == 2)
				{
					yilanasagi.setPosition(p[i].x, p[i].y);
					appWindow.draw(yilanasagi);
				}
				else if (dongu == 3)
				{
					yilanyukari.setPosition(p[i].x, p[i].y);
					appWindow.draw(yilanyukari);
				}
			}
			else
			arkayil.setPosition(p[i].x, p[i].y); //snake's current body coordinate.
			appWindow.draw(arkayil);
		}
		if (durdur==1) //pause 
		{
			black.setPosition(90, 200);
			appWindow.draw(black);
		}
		if (oyun == 2) {
			appWindow.draw(refresh); //play again
			refresh.setPosition(200, 200);
			//cout << appWindow.draw(orange); << score << endl;
		}
		appWindow.draw(skor);		 //score printing
		appWindow.display();		 //GO GO GO
		Sleep(hiz);					//snake velocity
	}
	return 0;
}