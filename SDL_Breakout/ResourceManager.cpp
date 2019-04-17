#include "ResourceManager.h"

breaker::ResourceManager *breaker::ResourceManager::instance_;

breaker::ResourceManager::ResourceManager(){}


breaker::ResourceManager::~ResourceManager(){}

SDL_Texture *breaker::ResourceManager::GetTexture(std::string key){
	std::map<std::string, SDL_Texture*>::iterator i = textureMap_.find(key);
	if(i != textureMap_.end()){
		return i->second;
	} else{
		//TODO: Create failsafe if tmp = NULL
		SDL_Texture *tmp = CreateTexture(key);
		if(!tmp){
			std::cout << "Failed to apply texture " << key << std::endl;
			return nullptr;
		}
		textureMap_[key] = tmp;
		return tmp;
	}
}

SDL_Texture *breaker::ResourceManager::CreateTexture(std::string imgName){
	std::string path = "res/sprites/" + imgName + ".png";
	auto surface = IMG_Load(path.c_str());
	if(!surface){
		std::cerr << "Failed to create surface " << path << std::endl;
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
	//TODO: Create failsafe for faild texture creation

	if(!texture){
		std::cout << "Failed to create texture " << SDL_Error << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

bool breaker::ResourceManager::CreateRenderer(SDL_Window *window, SDL_Color bgColor){
	renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer_ == nullptr){
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	SDL_SetRenderDrawColor(renderer_, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderClear(renderer_);
	return true;
}

void breaker::ResourceManager::RefreshRenderer(){
	SDL_RenderPresent(renderer_);
	SDL_RenderClear(renderer_);
}
