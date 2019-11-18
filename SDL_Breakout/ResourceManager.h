#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/*
	The resourcemanager works by loading textures to memory by saving them in a std::map.
	This way we reduce the time it takes to get a texture multiple times, becuase we have
	created a cache to quickly get access to the textures.
	The texture name is the key for the std::map and the texture itself is the value.
	The path to the textures is hard coded for now, and all images has to be .png for it to work.
*/

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

		SDL_Texture *GetTexture(std::string key);
		SDL_Renderer *GetRenderer(){ return renderer_; };

		bool CreateRenderer(SDL_Window *window, SDL_Color backgroundColor);
		void RefreshRenderer();

	private:

		SDL_Texture *CreateTexture(std::string imgName);

		static ResourceManager *instance_;

		SDL_Renderer *renderer_;

		std::map<std::string, SDL_Texture*> textureMap_;


	};
}

#endif