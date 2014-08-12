#include "gameapp.cpp"
#include "wrestler.cpp"

#include <SDL2\SDL_image.h>

#define WIDHT 640
#define HEIGHT 480

GameApp *game;
SDL_Texture *wrestler_texture;

Ring *ring;
Wrestler *wrestler;

int camerax,cameray;

bool KeyFunk()
{
	if(game->Input_KeyDown(SDL_SCANCODE_ESCAPE))return false;

	if(game->Input_KeyDown(SDL_SCANCODE_W))wrestler->MoveUp();
	if(game->Input_KeyDown(SDL_SCANCODE_S))wrestler->MoveDown();
	if(game->Input_KeyDown(SDL_SCANCODE_A))wrestler->MoveLeft();
	if(game->Input_KeyDown(SDL_SCANCODE_D))wrestler->MoveRight();

	if(game->Input_KeyDown(SDL_SCANCODE_Z))wrestler->Attack();
	if(game->Input_KeyDown(SDL_SCANCODE_X))wrestler->Jump();
	//if(game->Input_KeyDown(SDL_SCANCODE_C))wrestler->SitDown();

	return true;
}

bool FrameFunk()
{
	wrestler->Update(1/game->System_GetFPS());
	return true;
}

bool RenderFunk()
{
	//ring plate
	SDL_SetRenderDrawColor(game->render, 100, 100, 100, 255);
	SDL_Rect ringsource = ring->GetRect(camerax,HEIGHT);
	SDL_RenderFillRect(game->render,&ringsource);

	//ring cannats
	SDL_SetRenderDrawColor(game->render, 70, 70, 70, 255);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y-40);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-41,ringsource.x+ringsource.w-1,ringsource.y-41);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-25,ringsource.x+ringsource.w-1,ringsource.y-25);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-26,ringsource.x+ringsource.w-1,ringsource.y-26);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-10,ringsource.x+ringsource.w-1,ringsource.y-10);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-11,ringsource.x+ringsource.w-1,ringsource.y-11);

	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-40,ringsource.x,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(game->render,ringsource.x+1,ringsource.y-40,ringsource.x,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(game->render,ringsource.x+ringsource.w-1,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y+ringsource.h);
	SDL_RenderDrawLine(game->render,ringsource.x+ringsource.w-1,ringsource.y-40,ringsource.x+ringsource.w-2,ringsource.y+ringsource.h);

	//ring fundament
	ringsource.y+=ringsource.h;
	ringsource.h=30;
	SDL_SetRenderDrawColor(game->render, 70, 70, 70, 255);
	SDL_RenderFillRect(game->render,&ringsource);

	//player
	SDL_Rect rect = wrestler->GetRect(camerax,HEIGHT,2);
	SDL_Rect source = wrestler->GetSource(game->System_GetTime());
	SDL_Point anchor= wrestler->GetAnchor();
	SDL_RenderCopyEx(game->render,wrestler_texture,&source,&rect,0,&anchor,wrestler->orientation?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL);

	//ring cannats
	SDL_SetRenderDrawColor(game->render, 70, 70, 70, 255);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-40,ringsource.x+ringsource.w-1,ringsource.y-40);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-41,ringsource.x+ringsource.w-1,ringsource.y-41);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-25,ringsource.x+ringsource.w-1,ringsource.y-25);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-26,ringsource.x+ringsource.w-1,ringsource.y-26);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-10,ringsource.x+ringsource.w-1,ringsource.y-10);
	SDL_RenderDrawLine(game->render,ringsource.x,ringsource.y-11,ringsource.x+ringsource.w-1,ringsource.y-11);

	SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
	return true;
}

bool LoadFunk()
{
	wrestler_texture = IMG_LoadTexture(game->render, "wrestler.png");
	return true;
}

int main(int argc, char **argv)
{
	camerax = (WIDHT-600)/2;
	ring = new Ring();
	wrestler = new Wrestler(ring);
	game = new GameApp();

	game->System_Initiate();

	game->System_SetState(GA_FPS,60);
	game->System_SetState(GA_SCREENWIDTH,WIDHT);
	game->System_SetState(GA_SCREENHEIGHT,HEIGHT);

	game->System_SetState(GA_FRAMEFUNC,FrameFunk);
	game->System_SetState(GA_RENDERFUNC,RenderFunk);
	game->System_SetState(GA_KEYFUNC,KeyFunk);
	game->System_SetState(GA_LOADFUNC,LoadFunk);

	game->System_CreateScreen();
	game->System_Start();

	SDL_DestroyTexture(wrestler_texture);
	game->System_Shutdown();

	return 0;
}
