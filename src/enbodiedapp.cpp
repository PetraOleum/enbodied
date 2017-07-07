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

	std::pair<double, double> of = force(ISS, Earth);

	of.first /= ISS.mass;
	of.second /= ISS.mass;
	ISS.tayX.setDerivative(3, of.first - ISS.tayX.getDerivative(2));
	ISS.tayX.setDerivative(2, of.first);
	ISS.velX += of.first;
	ISS.tayX.setDerivative(1, ISS.velX);
	ISS.posX += ISS.velX;
	ISS.tayX.setDerivative(0, ISS.posX);
	ISS.tayY.setDerivative(3, of.second - ISS.tayY.getDerivative(2));
	ISS.tayY.setDerivative(2, of.second);
	ISS.velY += of.second;
	ISS.tayY.setDerivative(1, ISS.velY);
	ISS.posY += ISS.velY;
	ISS.tayY.setDerivative(0, ISS.posY);

}

void EnbodiedApp::OnRender() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_GetWindowSize(window, &winX, &winY);

	int minwin = (winX < winY) ? winX : winY;

	double scale = minwin/7000000.0;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderDrawPoint(renderer, (int)(ISS.posX * scale), (int)(ISS.posY * scale));

	printf("%d, %d\t%f,%f\n",(int)(ISS.posX * scale), (int)(ISS.posY * scale), ISS.velX, ISS.velY);

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

}
