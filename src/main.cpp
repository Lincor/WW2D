#include <SDL2/SDL_image.h>
#include <gameapp.hpp>
#include <wrestler.hpp>

#define WIDHT 640
#define HEIGHT 480

SDL_Renderer *GameApp::render;
GameAppCallback GameApp::frameFunction;
GameAppCallback GameApp::renderFunction;
GameAppCallback GameApp::keyFunction;
GameAppCallback GameApp::loadFunction;

SDL_Texture *wrestler_texture;

Ring *ring;
Wrestler *wrestler;

int camerax,cameray;

bool KeyFunk() {
	if(GameApp::Input_KeyDown(SDL_SCANCODE_ESCAPE)) return false;

	if(GameApp::Input_KeyDown(SDL_SCANCODE_W))wrestler->MoveUp();
	if(GameApp::Input_KeyDown(SDL_SCANCODE_S))wrestler->MoveDown();
	if(GameApp::Input_KeyDown(SDL_SCANCODE_A))wrestler->MoveLeft();
	if(GameApp::Input_KeyDown(SDL_SCANCODE_D))wrestler->MoveRight();

	if(GameApp::Input_KeyDown(SDL_SCANCODE_Z))wrestler->Attack();
	if(GameApp::Input_KeyDown(SDL_SCANCODE_X))wrestler->Jump();
	//if(GameApp::Input_KeyDown(SDL_SCANCODE_C))wrestler->SitDown();

	return true;
}

bool FrameFunk() {
	wrestler->Update(1/GameApp::System_GetFPS());
	return true;
}

bool RenderFunk() {
	//ring plate
	SDL_SetRenderDrawColor(GameApp::render, 100, 100, 100, 255);
	SDL_Rect ringsource = ring->GetRect(camerax,HEIGHT);
	SDL_RenderFillRect(GameApp::render,&ringsource);

	//ring cannats
	SDL_SetRenderDrawColor(GameApp::render, 70, 70, 70, 255);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y-40);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-41,ringsource.x+ringsource.w-1,ringsource.y-41);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-25,ringsource.x+ringsource.w-1,ringsource.y-25);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-26,ringsource.x+ringsource.w-1,ringsource.y-26);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-10,ringsource.x+ringsource.w-1,ringsource.y-10);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-11,ringsource.x+ringsource.w-1,ringsource.y-11);

	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-40,ringsource.x,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(GameApp::render,ringsource.x+1,ringsource.y-40,ringsource.x,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(GameApp::render,ringsource.x+ringsource.w-1,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(GameApp::render,ringsource.x+ringsource.w-1,ringsource.y-40,ringsource.x+ringsource.w-2,ringsource.y+ringsource.h);

	//ring fundament
	ringsource.y+=ringsource.h;
	ringsource.h=30;
	SDL_SetRenderDrawColor(GameApp::render, 70, 70, 70, 255);
	SDL_RenderFillRect(GameApp::render,&ringsource);

	//player
	SDL_Rect rect = wrestler->GetRect(camerax,HEIGHT,2);
	SDL_Rect source = wrestler->GetSource(GameApp::System_GetTime());
	SDL_Point anchor= wrestler->GetAnchor();
	SDL_RenderCopyEx(GameApp::render,wrestler_texture,&source,&rect,0,&anchor,wrestler->orientation?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL);

	//ring cannats
	SDL_SetRenderDrawColor(GameApp::render, 70, 70, 70, 255);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y-40);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-41,ringsource.x+ringsource.w-1,ringsource.y-41);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-25,ringsource.x+ringsource.w-1,ringsource.y-25);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-26,ringsource.x+ringsource.w-1,ringsource.y-26);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-10,ringsource.x+ringsource.w-1,ringsource.y-10);
	SDL_RenderDrawLine(GameApp::render,ringsource.x,ringsource.y-11,ringsource.x+ringsource.w-1,ringsource.y-11);

	SDL_SetRenderDrawColor(GameApp::render, 0, 0, 0, 255);
	return true;
}

bool LoadFunk() {
	wrestler_texture = IMG_LoadTexture(GameApp::render, "res/wrestler.png");
	return true;
}

int main(int argc, char **argv) {
	camerax = (WIDHT-600)/2;
	ring = new Ring();
	wrestler = new Wrestler(ring);

	GameApp::System_Initiate();

	GameApp::System_SetState(GA_FPS,60);
	GameApp::System_SetState(GA_SCREENWIDTH,WIDHT);
	GameApp::System_SetState(GA_SCREENHEIGHT,HEIGHT);

	GameApp::System_SetState(GA_FRAMEFUNC,FrameFunk);
	GameApp::System_SetState(GA_RENDERFUNC,RenderFunk);
	GameApp::System_SetState(GA_KEYFUNC,KeyFunk);
	GameApp::System_SetState(GA_LOADFUNC,LoadFunk);

	GameApp::System_CreateScreen(800, 600);
	GameApp::System_Start();

	SDL_DestroyTexture(wrestler_texture);
	GameApp::System_Shutdown();

	return 0;
}
