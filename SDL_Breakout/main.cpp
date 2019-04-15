#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Input.h"
#include "Player.h"

#include "Window.h"
#include "ResourceManager.h"

#define Window_Width 550
#define Window_Height 400


int main(int argc, char* argv[]){
	/*
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK); // | SDL_INIT_JOYSTICK
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Texture* texture = nullptr;
	std::vector<SDL_Texture*> stickTextures;
	// For alle mulige konfigurasjonsalternativer, se: http://goo.gl/8vDJN
	window = SDL_CreateWindow(
		"Et awesome SDL2-vindu!", // window title
		SDL_WINDOWPOS_UNDEFINED, // initial x position
		SDL_WINDOWPOS_UNDEFINED, // initial y position
		550, // width, in pixels
		400, // height, in pixels
		SDL_WINDOW_SHOWN //| SDL_WINDOW_OPENGL // flags
	);

	if(window == nullptr){
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit(); // Rydd opp!
		return EXIT_FAILURE;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_Rect coords;

	//Initialize PNG loading
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	} else{
		//Get window surface
		auto surface1 = IMG_Load("res/images/stickman_1.png");
		auto surface2 = IMG_Load("res/images/stickman_2.png");

		if(!surface1){ std::cerr << "Failed to create surface 1." << std::endl; }
		if(!surface2){ std::cerr << "Failed to create surface 2." << std::endl; }

		stickTextures.push_back(SDL_CreateTextureFromSurface(renderer, surface1));
		stickTextures.push_back(SDL_CreateTextureFromSurface(renderer, surface2));

		if(!stickTextures.at(0)){ std::cerr << "Failed to create texture 1." << std::endl; }
		if(!stickTextures.at(1)){ std::cerr << "Failed to create texture 2." << std::endl; }

		coords.h = surface1->h; // Samme bredde og høyde som surface
		coords.w = surface1->w;
		coords.x = 0; // Endre disse for å "flytte" bildet i vinduet/renderer
		coords.y = 0;
		SDL_FreeSurface(surface1);
		SDL_FreeSurface(surface2);
	}*/
	
	
	SDL_Window *window = Window::Instance("SDL_Game", Window_Width, Window_Height)->GetWindow();
	ResourceManager *resManag = ResourceManager::Instance();
	SDL_Color bgColor = {
		0, 0, 0, 255
	};

	if(!resManag->CreateRenderer(window, bgColor)){
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	std::vector<Object*> gameObjects;
	SDL_Rect coords = { 0, 0, 0, 0 };
	coords.w = Window_Width / 6;
	coords.x = Window_Width / 2 - coords.w / 2;
	coords.h = 10;
	coords.y = Window_Height - (coords.h * 8);
	Object *obj = new Player(coords, resManag->GetTexture("brick_0"));
	gameObjects.push_back(obj);
	

	Input *input = Input::Instance();

	//Calculate delta time and fps
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0, fps = 0, fpsTimer = 0;


	while(true){

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		deltaTime *= 0.001; //Convert from milli to seconds

		fpsTimer += deltaTime;
		if(deltaTime > 0.040)
			std::cout << "long frame: " << deltaTime << std::endl;
		fps++;
		if(fpsTimer >= 1){
			//std::cout << "fps: " << fps << std::endl;
			fps = 0;
			fpsTimer = 0;
		}


		input->Update();
		if(input->GetKeyDown(SDL_SCANCODE_ESCAPE)){
			break;
		}


		

		//Loop all objects
		//player->Update(deltaTime);
		//player->Draw(renderer);
		//SDL_RenderCopy(renderer, activeStickTexture, nullptr, &coords);

		//foreach(Object* obj in gameObjects)
		gameObjects.at(0)->Update(deltaTime);
		gameObjects.at(0)->Draw();

		
		//Do once at the end of gameloop
		//SDL_RenderPresent(renderer);
		//SDL_RenderClear(renderer);
		resManag->RefreshRenderer();

	}

	delete(input);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
