#ifndef ENBODIEDAPP_H
#define ENBODIEDAPP_H

#include <SDL.h>

#define INIT_SCREEN_WIDTH 500
#define INIT_SCREEN_HEIGHT 500

#define LOOP_TIME (1000/100)

class EnbodiedApp {
	private:

		void onKeyDown(SDL_KeyboardEvent * keyEvent);

		int winX = INIT_SCREEN_WIDTH;

		int winY = INIT_SCREEN_HEIGHT;

		bool running = false;

		SDL_Window * window = NULL;

		SDL_Renderer * renderer;

	public:

		EnbodiedApp();

		~EnbodiedApp();

		int OnExecute();

		bool OnInit();

		void OnEvent(SDL_Event * event);

		void OnLoop();

		void OnRender();

		void OnCleanup();
};

#endif
