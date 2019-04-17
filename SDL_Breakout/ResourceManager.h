#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

namespace breaker{
	class ResourceManager{
	public:

		static ResourceManager* Instance(){
			if(instance_ == nullptr)
				instance_ = new ResourceManager();
			return instance_;
		}

		ResourceManager();
		~ResourceManager();

		struct Texture{
			SDL_Texture* texture;
			SDL_Rect rect;
		};

		SDL_Texture *GetTexture(std::string key);
		SDL_Renderer *GetRenderer(){ return renderer_; };

		bool CreateRenderer(SDL_Window *window, SDL_Color backgroundColor);
		void RefreshRenderer();

	private:

		SDL_Texture *CreateTexture(std::string imgName);
		Texture newTexture_;

		static ResourceManager *instance_;

		SDL_Renderer *renderer_;

		std::map<std::string, SDL_Texture*> textureMap_;


	};
}

#endif