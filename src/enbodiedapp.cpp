#include "enbodiedapp.h"

EnbodiedApp::EnbodiedApp() {

}

EnbodiedApp::~EnbodiedApp() {

}

int EnbodiedApp::OnExecute() {
	if (!OnInit())
		return -1;

	SDL_Event event;

	while (running) {
		Uint32 lstart = SDL_GetTicks();
		while (SDL_PollEvent(&event))
			OnEvent(&event);
		OnLoop();
		OnRender();
		Uint32 lend = SDL_GetTicks();
		if ((lend - lstart) < LOOP_TIME)
			SDL_Delay(LOOP_TIME - (lend - lstart));
	}

	OnCleanup();
	return 0;

}

bool EnbodiedApp::OnInit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL. SDL error: %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Enbodied",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			INIT_SCREEN_WIDTH,
			INIT_SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		fprintf(stderr, "Window could not be created. SDL error: %s\n", SDL_GetError());
		return false;
	}
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		fprintf(stderr, "Could not create renderer. SDL error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	running = true;
	return true;

}

void EnbodiedApp::OnLoop() {
	currentTime += simulationTimestep;

	auto moonpos = mp.calculate(currentTime);
	Moon.posX = moonpos.first;
	Moon.posY = moonpos.second;

	std::pair<double, double> ef = force(ISS, Earth);
	std::pair<double, double> mf = force(ISS, Moon);
	std::pair<double, double> of = { 
		ef.first + mf.first,
		ef.second + mf.second
	};

	of.first /= ISS.mass;
	of.second /= ISS.mass;
	ISS.tayX.setDerivative(3, ( of.first - ISS.tayX.getDerivative(2) ) / simulationTimestep);
	ISS.tayX.setDerivative(2, of.first);
	ISS.tayX.setDerivative(1, ISS.velX + of.first);
	ISS.velX += of.first * simulationTimestep;
	ISS.tayX.setDerivative(0, ISS.posX + ISS.velX);
	ISS.posX += ISS.velX * simulationTimestep;

	ISS.tayY.setDerivative(3, (of.second - ISS.tayY.getDerivative(2)) / simulationTimestep);
	ISS.tayY.setDerivative(2, of.second);
	ISS.tayY.setDerivative(1, ISS.velY + of.second);
	ISS.velY += of.second * simulationTimestep;
	ISS.tayY.setDerivative(0, ISS.posY + ISS.velY);
	ISS.posY += ISS.velY * simulationTimestep;

}

void EnbodiedApp::OnRender() {

	if (centreOnISS) {
		centreX = ISS.posX;
		centreY = ISS.posY;
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_GetWindowSize(window, &winX, &winY);

	int minwin = (winX < winY) ? winX : winY;

	filledCircleRGBA(renderer, 
			(Sint16)((Earth.posX - centreX) * scale + winX / 2),
			(Sint16)((Earth.posY - centreY) * scale + winY / 2),
			(Sint16)(Earth.radius * scale),
			0x60, 0x60, 0xFF, 0xFF);

	filledCircleRGBA(renderer, 
			(Sint16)((Moon.posX - centreX) * scale + winX / 2),
			(Sint16)((Moon.posY - centreY) * scale + winY / 2),
			(Sint16)(Moon.radius * scale),
			0x60, 0x60, 0x60, 0xFF);

	SDL_Point points[201];

	for (int i = -0; i < 201; i++) {
		points[i] = {
			(int)((ISS.tayX.Calculate((i - 100) * taylorTimestep, 1) - centreX) * scale + winX / 2),
			(int)((ISS.tayY.Calculate((i - 100) * taylorTimestep, 1) - centreY) * scale + winY / 2)
		};
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0xAF, 0x00, 0xFF);

	SDL_RenderDrawLines(renderer, points, 201);

	for (int i = 0; i < 201; i++) {
		points[i] = {
			(int)((ISS.tayX.Calculate((i - 100) * taylorTimestep, 2) - centreX) * scale + winX / 2),
			(int)((ISS.tayY.Calculate((i - 100) * taylorTimestep, 2) - centreY) * scale + winY / 2)
		};
	}

	SDL_SetRenderDrawColor(renderer, 0xAF, 0x00, 0x00, 0xFF);

	SDL_RenderDrawLines(renderer, points, 201);

	for (int i = -0; i < 201; i++) {
		points[i] = {
			(int)((ISS.tayX.Calculate((i - 100) * taylorTimestep, 3) - centreX) * scale + winX / 2),
			(int)((ISS.tayY.Calculate((i - 100) * taylorTimestep, 3) - centreY) * scale + winY / 2)
		};
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xAF, 0xFF);

	SDL_RenderDrawLines(renderer, points, 201);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderDrawPoint(renderer, (int)((ISS.posX - centreX) * scale + winX / 2), (int)((ISS.posY - centreY) * scale + winY / 2));

//	printf("%d, %d\t%f,%f\n",(int)(ISS.posX * scale), (int)(ISS.posY * scale), ISS.velX, ISS.velY);

	SDL_RenderPresent(renderer);
}

void EnbodiedApp::OnEvent(SDL_Event * event) {
	switch (event->type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			onKeyDown(&event->key);
			break;
		default:
			break;
	}
}

void EnbodiedApp::OnCleanup() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();

}

void EnbodiedApp::onKeyDown(SDL_KeyboardEvent * keyEvent) {
	switch(keyEvent->keysym.sym) {
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			scale = (scale <= 0) ? 1.0e-4 : scale / 1.1;
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			scale = (scale <= 0) ? 1.0e-4 : scale * 1.1;
			break;
		case SDLK_LEFT:
			centreX -= 50 / scale;
			break;
		case SDLK_RIGHT:
			centreX += 50 / scale;
			break;
		case SDLK_UP:
			centreY -= 50 / scale;
			break;
		case SDLK_DOWN:
			centreY += 50 / scale;
			break;
		case SDLK_c:
			centreOnISS = !centreOnISS;
			break;
		case SDLK_PAGEUP:
			taylorTimestep = (taylorTimestep <= 0) ? 10 : taylorTimestep * 1.1;
			break;
		case SDLK_PAGEDOWN:
			taylorTimestep = (taylorTimestep <= 0) ? 10 : taylorTimestep / 1.1;
			break;
		case SDLK_PERIOD:
			simulationTimestep = (simulationTimestep <= 0) ? 1 : simulationTimestep * 1.1;
			break;
		case SDLK_COMMA:
			simulationTimestep = (simulationTimestep <= 0) ? 1 : simulationTimestep / 1.1;
			break;
		default:
			break;
	}

}
