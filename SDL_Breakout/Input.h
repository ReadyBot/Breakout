#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>

namespace breaker{
	class Input{
	public:
		static Input* Instance(){
			if(instance_ == nullptr)
				instance_ = new Input();
			return instance_;
		}

		Input();
		~Input();

		// KeyDown -> True the frame the key was pressed down
		// Key     -> True if key is down on this or last frame
		// KeyUp   -> True the frame the key was released
		bool GetKeyDown(int keyIndex) const{ return (CurKeyDown(keyIndex)) && (!OldKeyDown(keyIndex)); };
		bool GetKey(int keyIndex) const{ return CurKeyDown(keyIndex) || OldKeyDown(keyIndex); };
		bool GetKeyUp(int keyIndex) const{ return !CurKeyDown(keyIndex) && OldKeyDown(keyIndex); };

		// Mouse.
		bool MouseDown(int button) const{ return CurMouseKeyDown(button) && !OldMouseKeyDown(button); };
		bool MouseStillDown(int button);
		bool MouseUp(int button);
		bool MouseStillUp(int button);

		void Update();


	protected:
		// A pointer to SDL's internal key state array.
		// (Memory handled by SDL.)
		const Uint8* keys = nullptr;
		// Our own copy of last update's array.
		// NB! Memory handled dynamically by us!
		std::unique_ptr<Uint8> oldKeys;
		// Number of keys in the arrays above, for this
		// app. (Can vary depending on setup/hardware.)
		int keyCount;
		// Mouse pos x and y.
		int mouseX;
		int mouseY;
		// Mouse buttons pressed.
		Uint8 mButtons;
		// Mouse buttons pressed last update.
		Uint8 mOldButtons;


	private:

		static Input* instance_;

		bool CurKeyDown(int keyIndex) const{ return keys[keyIndex] != 0; };
		bool OldKeyDown(int keyIndex) const{ return oldKeys.get()[keyIndex] != 0; };

		bool CurMouseKeyDown(int button) const{ return false; };
		bool OldMouseKeyDown(int button) const{ return false; };

	};
}

#endif