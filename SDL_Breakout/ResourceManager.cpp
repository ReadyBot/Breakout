#include "ResourceManager.h"

ResourceManager *ResourceManager::instance_;

ResourceManager::ResourceManager(){}


ResourceManager::~ResourceManager(){}

SDL_Texture *ResourceManager::GetTexture(std::string key){
	std::map<std::string, SDL_Texture*>::iterator i = textureMap_.find(key);
	if(i != textureMap_.end()){
		return i->second;
	} else{
		//TODO: Create failsafe if tmp = NULL
		SDL_Texture *tmp = CreateTexture(key);
		textureMap_[key] = tmp;
		return tmp;
	}
}

SDL_Texture *ResourceManager::CreateTexture(std::string imgName){
	std::string path = "res/sprites/" + imgName + ".png";
	auto surface = IMG_Load(path.c_str());
	if(!surface){
		std::cerr << "Failed to create surface " << path << std::endl;
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
	//TODO: Create failsafe for faild texture creation

	SDL_FreeSurface(surface);

	return texture;
}

bool ResourceManager::CreateRenderer(SDL_Window *window, SDL_Color bgColor){
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

void ResourceManager::RefreshRenderer(){
	SDL_RenderPresent(renderer_);
	SDL_RenderClear(renderer_);
}
