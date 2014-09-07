#include <SDL2/SDL.h>
#include <gameapp.hpp>
#include <wrestler.hpp>

SDL_Rect Wrestler::GetSource(float time) {
	int discretetime = (int)(time*6);

	SDL_Rect rect= {0,0,36,46};

	switch(state) {
	case W_IDLE:
	case W_RUN:
		rect.x=discretetime%8*36;
		break;
	case W_JUMP:
		rect.x=36*8;
		break;
	case W_ATTACK:
		rect.x=36*9+(discretetime)%2*36;
		break;
	}

	return rect;
}

SDL_Rect Wrestler::GetRect(int camerax,int height,int scale) {
	SDL_Rect rect = {camerax,height-64,36*scale,46*scale};
	rect.x+=posx;
	rect.y-=posy/3;
	rect.y-=this->height;

	rect.x-=(orientation?10:(36-10))*scale;
	rect.y-=46*scale;

	return rect;
}

SDL_Point Wrestler::GetAnchor() {
	SDL_Point anchor = {orientation?10:(36-10),46};
	return anchor;
}

void Wrestler::MoveRight() {
	horizontal_speed+=100;
	orientation=RIGHT;
	state = W_RUN;
	timetoidle=0.4;
}

void Wrestler::MoveLeft() {
	horizontal_speed-=100;
	orientation=LEFT;
	state = W_RUN;
	timetoidle=0.4;
}

void Wrestler::MoveUp() {
	depth_speed+=100;
	state = W_RUN;
	timetoidle=0.4;
}

void Wrestler::MoveDown() {
	depth_speed-=100;
	state = W_RUN;
	timetoidle=0.4;
}

void Wrestler::SitDown() {
	state=W_SIT;
}

void Wrestler::Jump() {
	if(state!=W_JUMP) {
		state=W_JUMP;
		vertical_accselerate=17;
	}
}

void Wrestler::Attack() {
	state=W_ATTACK;
	timetoidle=0.5;
}

void Wrestler::Update(float ellapsedtime) {
	posx+=horizontal_speed*ellapsedtime;
	posy+=depth_speed*ellapsedtime;

	horizontal_speed=0;
	depth_speed=0;

	vertical_accselerate-=1.98;
	bool infly = height>0;
	height+=vertical_accselerate;

	if(height<0) {
		height=0;
		vertical_accselerate=0;
		if(infly)
			state=W_IDLE;
	}
	if(posx<0)posx=0;
	if(posy<0)posy=0;
	if(posx>ring->sizex)posx=ring->sizex;
	if(posy>ring->sizey)posy=ring->sizey;

	if(timetoidle>0) {
		timetoidle-=ellapsedtime;

		if(timetoidle<=0) {
			timetoidle=0;
			state=W_IDLE;
		}
	}
}
