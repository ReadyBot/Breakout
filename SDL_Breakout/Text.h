#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <string>
#include "Vector2.h"

namespace breaker{
	class Text{
	public:

		static Text* Instance(){
			if(instance_ == nullptr)
				instance_ = new Text();
			return instance_;
		}

		Text();
		~Text();

		void DrawString(std::string string, Vector2 pos, int size);
		TTF_Font GetFont(std::string, int size);

	private:

		static Text *instance_;


	};
}

#endif