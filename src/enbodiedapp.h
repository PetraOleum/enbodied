#ifndef ENBODIEDAPP_H
#define ENBODIEDAPP_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "orbitals.h"

#define INIT_SCREEN_WIDTH 500
#define INIT_SCREEN_HEIGHT 500

#define LOOP_TIME (1000/100)

class EnbodiedApp {
	private:

		double currentTime = 0;

		void onKeyDown(SDL_KeyboardEvent * keyEvent);

		int winX = INIT_SCREEN_WIDTH;

		int winY = INIT_SCREEN_HEIGHT;

		double centreX = 0;
		double centreY = 0;

		bool centreOnISS = false;

		double scale = 7.0e-5;

		double taylorTimestep = 10;

		double simulationTimestep = 1;

		bool running = false;

		SDL_Window * window = NULL;

		SDL_Renderer * renderer;

		Body Earth = {
			0,
			0,
			6371000,
			5.972e+24,
			0,
			0,
			true,
			Taylor(),
			Taylor()
		};

//		Body ISS = {
//			0,
//			400000 + 6371000,
//			1,
//			419600,
//			7667,
//			0,
//			false,
//			Taylor(3),
//			Taylor(3)
//		};

		Body ISS = {
			410000000,
			0,
			1,
			419600,
			0,
			-2000,
			false,
			Taylor(3),
			Taylor(3)
		};

		Body Moon = {
			384399000,
			0,
			1737100,
			7.342e+22,
			0,
			-1022,
			true,
			Taylor(),
			Taylor()
		};

		KeplerParameters mp = {
			0,
			384399000,
			0.0549,
			27.321661 * 24 * 60 * 60,
			M_PI
		};

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
