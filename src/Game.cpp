#include "Game.h"
#include "Utils/Utils.h"
#include "GameComponents/Environment.h"
#include "GameComponents/Peashooter.h"
#include "GameComponents/Bullet.h"
#include "GameComponents/SimpleZombie.h"
#include "GameComponents/SunFlower.h"
#include "GameComponents/Sun.h"
#include <vector>
#include <ctime>

//TODO:
//Arena Cinematic
//Sun Collection
//Main Menu
//Game Over
//Carts At End

enum plantType
{
	SUN,
	PEA,
	POTATO,
	NONE
};

Game::Game(int width, int height)
    : mWidth(width), mHeight(height)
{
}

void Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return;
    }

    SDL_Window* mWindow = SDL_CreateWindow("PvZ Clone",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mWidth, mHeight,
        0);

    if (!mWindow)
    {
        std::cout << "Failed to create window\n";
        return;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);


    if (!mRenderer)
    {
        std::cout << "Failed to get the surface from the window\n";
        return;
    }

	IMG_Init(IMG_INIT_PNG);
}

void Game::Run()
{
	srand(time(0));

    bool running = true;
    
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	Environment background(mRenderer, "graphics/Environment.png", 2, 2, 447, 192);
	Environment grass(mRenderer, "graphics/Environment.png", 248, 242, 246, 169, true, 0x49, 0x6F, 0xA0);
	Environment marker(mRenderer, "graphics/marker.png", 0, 0, 64, 64);

	Environment peaPick(mRenderer, "graphics/PeaShooter.png", 113, 35, 26, 26, true, 0x75, 0x65, 0xFF);
	Environment sunflowerPick(mRenderer, "graphics/SunPlant.png", 32, 37, 27, 25, true, 0x75, 0x65, 0xFF);
	Environment shovel(mRenderer, "graphics/marker.png", 0, 0, 64, 64);

	peaPick.setDestRect(3, 57, 26 * 2, 26 * 2);
	sunflowerPick.setDestRect(3, 57 + 26 * 2, 26 * 2, 26 * 2);
	shovel.setDestRect(3, 57 + 26 * 2 + 26 * 2, 26 * 2, 26 * 2);

	std::vector<std::vector<Environment>> markers(9,std::vector<Environment>(5));
	std::vector<std::vector<bool>> isPlantThere(9, std::vector<bool>(5));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			isPlantThere[i][j] = false;
		}
	}

	int initialX = 171;
	int initialY = 62;


	std::vector<SDL_Rect> sunflowerIdleCoordinates;
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 2,3,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 31,3,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 60,5,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 89,5,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 119,4,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 147,3,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 176,3,30,34 });
	sunflowerIdleCoordinates.push_back(SDL_Rect{ 206,3,30,34 });

	std::vector<SDL_Rect> sunflowerProduceCoordinates;
	sunflowerProduceCoordinates.push_back(SDL_Rect{ 2,37,30,29 });


	std::vector<SDL_Rect> peasCoordinates;
	peasCoordinates.push_back(SDL_Rect{ 0,0,27,33 });
	peasCoordinates.push_back(SDL_Rect{ 27,0,26,33 });
	peasCoordinates.push_back(SDL_Rect{ 53,0,28,33 });
	peasCoordinates.push_back(SDL_Rect{ 80,1,28,32 });
	peasCoordinates.push_back(SDL_Rect{ 107,1,28,32 });
	peasCoordinates.push_back(SDL_Rect{ 134,0,27,33 });
	peasCoordinates.push_back(SDL_Rect{ 162,0,27,33 });
	peasCoordinates.push_back(SDL_Rect{ 188,0,26,33 });

	std::vector<SDL_Rect> peasAttackCoordinates;
	peasAttackCoordinates.push_back(SDL_Rect{ 0,33,27,31 });
	peasAttackCoordinates.push_back(SDL_Rect{ 26,33,24,31 });
	peasAttackCoordinates.push_back(SDL_Rect{ 50,33,28,31 });

	Peashooter pea(peasCoordinates, peasAttackCoordinates);
	pea.LoadImages(mRenderer, "graphics/PeaShooter.png", peasCoordinates, 8, true, 0x75, 0x65, 0xFF);



	std::vector<SDL_Rect> simpleZombieIdle;
	simpleZombieIdle.push_back(SDL_Rect{ 1,4,28,42 });
	simpleZombieIdle.push_back(SDL_Rect{ 27,4,28,42 });
	simpleZombieIdle.push_back(SDL_Rect{ 56,5,28,42 });
	simpleZombieIdle.push_back(SDL_Rect{ 84,4,28,42 });

	std::vector<SDL_Rect> simpleZombieWalkHand;
	simpleZombieWalkHand.push_back(SDL_Rect{ 114,1,28,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 141,1,28,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 165,1,28,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 190,1,28,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 218,1,28,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 240,1,30,47 });
	simpleZombieWalkHand.push_back(SDL_Rect{ 270,1,30,47 });

	std::vector<SDL_Rect> simpleZombieAttackHand;
	simpleZombieAttackHand.push_back(SDL_Rect{ 301,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 332,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 364,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 394,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 426,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 456,4,31,44 });
	simpleZombieAttackHand.push_back(SDL_Rect{ 486,4,31,44 });

	std::vector<SDL_Rect> simpleZombieWalkNoHand;
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 114,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 141,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 163,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 185,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 213,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 235,49,28,47 });
	simpleZombieWalkNoHand.push_back(SDL_Rect{ 265,49,28,47 });

	std::vector<SDL_Rect> simpleZombieAttackNoHand;
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 296,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 327,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 358,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 389,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 420,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 450,52,31,44 });
	simpleZombieAttackNoHand.push_back(SDL_Rect{ 479,52,31,44 });

	SimpleZombie zombie(simpleZombieIdle, simpleZombieAttackHand, simpleZombieWalkHand, simpleZombieWalkNoHand, simpleZombieAttackNoHand);
	zombie.LoadImages(mRenderer, "graphics/SimpleZombie.png", simpleZombieIdle, 8, true, 0x68, 0xA4, 0xFF);
	zombie.setDestRect(700,62,35,40);
	zombie.setXVelocity(-0.1);
	zombie.changeState(1);
	zombie.setLane(0);

	std::vector<SDL_Rect> peaBulletCoordinates;
	peaBulletCoordinates.push_back(SDL_Rect{ 77,41,12,14 });
	peaBulletCoordinates.push_back(SDL_Rect{ 88,41,12,14 });
	peaBulletCoordinates.push_back(SDL_Rect{ 99,38,15,19 });
	Bullet bullet;
	bullet.LoadImages(mRenderer, "graphics/PeaShooter.png", peaBulletCoordinates, 3, true, 0x75, 0x65, 0xFF);
	bullet.setDestRect(0, 0, 64, 64);

	std::vector<Bullet> bullets;

	std::vector<SimpleZombie> zombies;
	zombies.push_back(zombie);

	std::vector<Peashooter> peaShooters;
	peaShooters.reserve(45);

	std::vector<SunFlower> sunFlowers;
	sunFlowers.reserve(45);

	std::vector<SDL_Rect> sunCoordinates;
	sunCoordinates.push_back(SDL_Rect{ 0,0,26,26 });
	sunCoordinates.push_back(SDL_Rect{ 26,0,26,26 });

	std::vector<Sun> suns;

	//std::vector<Plant> plants;
	//plants.push_back(pea);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			markers[i][j].Init(mRenderer, "graphics/marker.png", 0, 0, 64, 64);
			markers[i][j].setDestRect(initialX + (i * 51), initialY + (j * 62), 35, 43);
		}
	}

	grass.setDestRect(152,39,487,333);
	marker.setDestRect(171, 62, 35, 40);
	bool showMousePos = false;
	bool showMarker = false;
	int xMouse, yMouse;

	bool plantSelected = false;
	bool removePlant = false;
	plantType currentType = plantType::NONE;

	Uint32 lastUpdate = 0;
	int state = 0;

	float zombieCollisionTimer = 0.5f;
	float zombierCurrentTimer = 0.0f;

	float zombieGenerateTimer = 3.0f;
	float zombieGenerateTimeCounter = 0.0f;
	int totalZombies = 3;
	int currentZombieCount = 1;

	while (running) 
	{
		frameStart = SDL_GetTicks();

		Uint32 currentTime = SDL_GetTicks();
		float dT = (currentTime - lastUpdate) / 1000.0f;

		SDL_Event e;

		SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
		SDL_RenderClear(mRenderer);

		// Event loop
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) 
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEMOTION:
				if (showMousePos)
				{
					SDL_GetMouseState(&xMouse, &yMouse);
					std::cout << "X : " << xMouse << " Y : " << yMouse << std::endl;
				}
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_S:
					showMousePos = !showMousePos;
					break;
				case SDL_SCANCODE_A:
					showMarker = !showMarker;
					break;
				case SDL_SCANCODE_E:
					/*state = pea.currentState;
					pea.changeState(1);
					pea.Fire(bullets, mRenderer);
					if (state == 1)
					{
					}*/
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					int x;
					int y;
					SDL_GetMouseState(&x, &y);
					std::cout << "Clicked X : " << x << " Clicked Y : " << y << std::endl;

					if (currentType != plantType::NONE)
					{
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 5; j++)
							{
								SDL_Rect tempRect = markers[i][j].getDestRect();
								if (isCollidedPointAndRect(x, y, tempRect) && isPlantThere[i][j] == false)
								{
									std::cout << "MARKER CLICKED " << i << ", " << j << std::endl;

									//pea.setDestRect(tempRect.x, tempRect.y, tempRect.w, tempRect.h);
									switch (currentType)
									{
									case plantType::PEA:
									{
										Peashooter Pea(peasCoordinates, peasAttackCoordinates);
										Pea.LoadImages(mRenderer, "graphics/PeaShooter.png", peasCoordinates, 8, true, 0x75, 0x65, 0xFF);
										Pea.setDestRect(tempRect.x, tempRect.y, tempRect.w, tempRect.h);
										Pea.setLane(j);
										//peaShooters.push_back(Pea);
										peaShooters.insert(peaShooters.begin(), Pea);

										isPlantThere[i][j] = true;

										currentType = plantType::NONE;
									}
									break;
									case plantType::SUN:
									{
										SunFlower Sun(sunflowerIdleCoordinates, sunflowerProduceCoordinates);
										Sun.LoadImages(mRenderer, "graphics/SunPlant.png", sunflowerIdleCoordinates, 8, true, 0x75, 0x65, 0xFF);
										Sun.setDestRect(tempRect.x, tempRect.y, tempRect.w, tempRect.h);
										Sun.setLane(j);
										sunFlowers.insert(sunFlowers.begin(), Sun);

										isPlantThere[i][j] = true;

										currentType = plantType::NONE;
									}
									break;
									}
								}
							}
						}
					}
					else if (removePlant)
					{
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 5; j++)
							{
								SDL_Rect tempRect = markers[i][j].getDestRect();
								if (isCollidedPointAndRect(x, y, tempRect) && isPlantThere[i][j] == true)
								{
									for (int i = 0; i < peaShooters.size(); i++)
									{
										if (peaShooters[i].getDestRect().x == tempRect.x && peaShooters[i].getDestRect().y == tempRect.y)
										{
											peaShooters.erase(peaShooters.begin() + i);
										}
									}
									for (int i = 0; i < sunFlowers.size(); i++)
									{
										if (sunFlowers[i].getDestRect().x == tempRect.x && sunFlowers[i].getDestRect().y == tempRect.y)
										{
											sunFlowers.erase(sunFlowers.begin() + i);
										}
									}

									isPlantThere[i][j] = false;
									removePlant = false;
								}
							}
						}
					}
					
					if (suns.size() != 0)
					{
						for (int i = 0; i < suns.size(); i++)
						{
							if (isCollidedPointAndRect(x, y, suns[i].getDestRect()))
							{
								suns.erase(suns.begin() + i);
							}
						}
					}

					if (isCollidedPointAndRect(x, y, peaPick.getDestRect()))
					{
						currentType = plantType::PEA;
					}
					if (isCollidedPointAndRect(x, y, sunflowerPick.getDestRect()))
					{
						currentType = plantType::SUN;
					}
					if (isCollidedPointAndRect(x, y, shovel.getDestRect()))
					{
						removePlant = true;
						std::cout << "REMOVE PLANT ACTIVE!!" << std::endl;
					}

					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_S:
					break;
				case SDL_SCANCODE_A:
					break;
				case SDL_SCANCODE_E:
					break;
				}
			}
		}
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		zombieGenerateTimeCounter += dT;
		if (zombieGenerateTimeCounter > zombieGenerateTimer && currentZombieCount <= totalZombies)
		{
			zombieGenerateTimeCounter = 0.0f;
			zombieGenerateTimer = rand() % 10;
			int lane = 0 + (rand() % 5);

			SimpleZombie zom(simpleZombieIdle, simpleZombieAttackHand, simpleZombieWalkHand, simpleZombieWalkNoHand, simpleZombieAttackNoHand);
			zom.LoadImages(mRenderer, "graphics/SimpleZombie.png", simpleZombieIdle, 8, true, 0x68, 0xA4, 0xFF);
			zom.setXVelocity(-0.1);
			zom.changeState(1);
			zom.setLane(lane);
			zom.setDestRect(700, 62 + lane * 62, 35, 40);
			zombies.push_back(zom);

			currentZombieCount++;
		}




		zombierCurrentTimer += dT;
		if (zombierCurrentTimer > zombieCollisionTimer)
		{
			/*for (int i = 0; i < peaShooters.size(); i++)
			{
				if (peaShooters[i].getLane() == zombie.getLane())
				{
					zombie.checkCollision(peaShooters[i].getDestRect());
				}
			}*/

			/*for (auto& i : peaShooters)
			{
				if (i.getLane() == zombie.getLane())
				{
					zombie.checkCollision(i.getDestRect());
				}
			}*/

			for (auto& i : zombies)
			{
				for (auto& j : peaShooters)
				{
					if (i.getLane() == j.getLane())
					{
						if (i.checkCollision(j.getDestRect()) && j.getIsAlive())
						{
							if (j.getHealth() - 15 <= 0)
							{
								j.takeDamage(15);
								i.restoreAttackToWalk();
							}
							else
							{
								j.takeDamage(15);
							}
						}
					}
				}
			}

			for (auto& i : zombies)
			{
				for (auto& j : sunFlowers)
				{
					if (i.getLane() == j.getLane())
					{
						if (i.checkCollision(j.getDestRect()) && j.getIsAlive())
						{
							if (j.getHealth() - 15 <= 0)
							{
								j.takeDamage(15);
								i.restoreAttackToWalk();
							}
							else
							{
								j.takeDamage(15);
							}
						}
					}
				}
			}

			zombierCurrentTimer = 0.0f;
		}
		
		
		for (int i = 0; i < bullets.size(); i++)
		{
			for (int j = 0; j < zombies.size(); j++)
			{
				if (bullets[i].checkCollision(zombies[j].getDestRect()))
				{
					bullets.erase(bullets.begin() + i);
					zombies[i].takeDamage(15);
				}
			}
		}

		for (int i = 0; i < zombies.size(); i++)
		{
			if (!zombies[i].getIsAlive())
			{
				zombies.erase(zombies.begin() + i);
			}
		}

		/*if (pea.canFire == true)
		{
			pea.Fire(bullets, mRenderer);
		}*/

		for (int i = 0; i < peaShooters.size(); i++)
		{
			//peaShooters[i].setInRange(true);
			for (int j = 0; j < zombies.size(); j++)
			{
				if (peaShooters[i].getLane()==zombies[i].getLane())
				{
					if (calculateDistance(peaShooters[i].getDestRect().x, peaShooters[i].getDestRect().y, zombies[j].getDestRect().x, zombies[j].getDestRect().y) < 400.0f)
					{
						peaShooters[i].setInRange(true);
					}
					else
					{
						peaShooters[i].setInRange(false);
					}
				}
				else if(peaShooters[i].getLane() != zombies[i].getLane())
				{
					continue;
				}
			}
		}

		/*for (int i = 0; i < peaShooters.size(); i++)
		{
			if (calculateDistance(peaShooters[i].getDestRect().x, peaShooters[i].getDestRect().y, zombie.getDestRect().x, zombie.getDestRect().y) < 200.0f)
			{
				peaShooters[i].setInRange(true);
			}
			else
			{
				peaShooters[i].setInRange(false);
			}
		}*/

		for (int i = 0; i < peaShooters.size(); i++)
		{
			if (peaShooters[i].canFire == true && peaShooters[i].getInRange())
			{
				peaShooters[i].Fire(bullets, mRenderer);
			}
		}

		for (int i = 0; i < peaShooters.size(); i++)
		{
			if (!peaShooters[i].getIsAlive())
			{
				//std::cout << "Collided" << std::endl;
				peaShooters.erase(peaShooters.begin() + i);
			}
		}

		for (int i = 0; i < sunFlowers.size(); i++)
		{
			if (!sunFlowers[i].getIsAlive())
			{
				//std::cout << "Collided" << std::endl;
				sunFlowers.erase(sunFlowers.begin() + i);
			}
		}

		for (auto& i : sunFlowers)
		{
			if (i.getCanProduce())
			{
				Sun tempSun(sunCoordinates);
				tempSun.LoadImages(mRenderer, "graphics/Sun.png", sunCoordinates, 2, true, 0x00, 0x7F, 0x0E);
				tempSun.setDestRect(i.getDestRect().x + 5, i.getDestRect().y + 5, i.getDestRect().w / 2 + 10, i.getDestRect().h / 2 + 10);
				tempSun.setTotalFrames(2);
				i.setCanProduce(false);
				suns.push_back(tempSun);
				std::cout << "Sun Produced" << std::endl;
			}
		}

		for (int i = 0; i < peaShooters.size(); i++)
		{
			peaShooters[i].Update(dT);
		}

		for (int i = 0; i < sunFlowers.size(); i++)
		{
			sunFlowers[i].Update(dT);
		}

		//pea.Update(dT);
		//bullet.Update(dT);
		for (auto& i : zombies)
		{
			i.Update(dT);
		}
		//zombie.Update(dT);

		for (auto& i : suns)
		{
			i.Update(dT);
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(dT);
		}

		// Display window
		background.SimpleDraw(mRenderer);
		grass.Draw(mRenderer);
		//marker.Draw(mRenderer);

		for (int i = 0; i < peaShooters.size(); i++)
		{
			peaShooters[i].Draw(mRenderer);
		}

		for (int i = 0; i < sunFlowers.size(); i++)
		{
			sunFlowers[i].Draw(mRenderer);
		}

		//pea.Draw(mRenderer);
		//bullet.Draw(mRenderer);
		//zombie.Draw(mRenderer);
		for (auto& i : zombies)
		{
			i.Draw(mRenderer);
		}

		peaPick.Draw(mRenderer);
		sunflowerPick.Draw(mRenderer);
		shovel.Draw(mRenderer);

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw(mRenderer);
		}

		for (int i = 0; i < suns.size(); i++)
		{
			suns[i].Draw(mRenderer);
		}

		if (showMarker)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					markers[i][j].Draw(mRenderer);
				}
			}
		}

		SDL_RenderPresent(mRenderer);
		
		lastUpdate = currentTime;
	}

}
