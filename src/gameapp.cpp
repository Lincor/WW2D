#include <SDL2/SDL.h>
#include <stdio.h>
#include <gameapp.hpp>

int GameApp::width;
int GameApp::height;

SDL_Window *GameApp::window;
SDL_Event GameApp::e;

const Uint8 *GameApp::keyboard;

float GameApp::time,GameApp::delta;
int GameApp::fps;
char *GameApp::title;

void GameApp::System_SetState(GameAppFuncState state,GameAppCallback value) {
	switch(state) {
	case GA_FRAMEFUNC:
		frameFunction=value;
		break;
	case GA_RENDERFUNC:
		renderFunction=value;
		break;
	case GA_KEYFUNC:
		keyFunction=value;
		break;
	case GA_LOADFUNC:
		loadFunction=value;
		break;
	}
}

void GameApp::System_SetState(GameAppIntState state,int value) {
	switch(state) {
	case GA_SCREENWIDTH:
		width=value;
		break;
	case GA_SCREENHEIGHT:
		height=value;
		break;
	case GA_FPS:
		fps=1000/value;
		delta=(double)fps;
		break;
	}
}

int GameApp::System_CreateScreen(int width, int height) {
	return SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &window, &render);
}

bool GameApp::System_Initiate() {
	if(SDL_Init( SDL_INIT_EVERYTHING )==-1) {
		printf("%s\n",SDL_GetError());
		return false;
	}
	return true;
}

void GameApp::System_Start() {
	if(loadFunction)loadFunction();
	Uint32 time=SDL_GetTicks(),oldtime=time;
	int deltat=0;
	char title[16]= {0};
	for(;;) {
		oldtime=SDL_GetTicks();
		SDL_PollEvent(&e);

		keyboard=SDL_GetKeyboardState(0);

		if(frameFunction)if(!frameFunction())break;

		if(e.type==SDL_KEYDOWN)if(keyFunction)if(!keyFunction())break;
		if(e.type==SDL_QUIT)break;

		if(renderFunction) {
			SDL_RenderClear(render);
			if(!renderFunction())break;
			SDL_RenderPresent(render);
		}

		time=SDL_GetTicks();
		deltat=time-oldtime;
		if(!deltat)deltat=1;

		if(fps>0)
			if(deltat<fps)
				SDL_Delay(fps-deltat);

		time=SDL_GetTicks();
		delta=(time-oldtime)/1000.0f;

		sprintf(title,"FPS=%4.0f\\%4.0f",1.0f/delta,1000.0f/deltat);
		SDL_SetWindowTitle(window,title);

		GameApp::time = time/1000.0f;
		GameApp::delta = delta;
	}
}

void GameApp::System_Shutdown() {
	if(render)SDL_DestroyRenderer(render);
	if(window)SDL_DestroyWindow(window);
}

double GameApp::System_GetEllapsedTime() {
	return delta;
}

double GameApp::System_GetTime() {
	return time;
}

double GameApp::System_GetFPS() {
	return fps;
}

bool GameApp::Input_KeyDown(Uint8 key) {
	return keyboard[key]>0;
}

bool GameApp::Input_KeyUp(Uint8 key) {
	return !keyboard[key];
}

void GameApp::Gfx_printf(int x,int y,Uint32 color,char* format,...) {
	char str[1000];
	va_list args;
	va_start(args, format);
	vsnprintf(str,1000,format,args);
	va_end(args);
}
