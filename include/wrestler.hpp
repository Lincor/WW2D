#ifndef WRESTLER_H
#define WRESTLER_H

enum WrestlerStates {
	W_IDLE,
	W_RUN,
	W_JUMP,
	W_ATTACK,
	W_SIT
};

class Ring {
public:
	int sizex;
	int sizey;

	Ring() {
		sizex=600;
		sizey=600;
	}
	SDL_Rect GetRect(int camerax,int height) {
		SDL_Rect rect = {camerax,height-64-sizey/3,sizex,sizey/3};
		return rect;
	}
};

class Wrestler {
public:
	double posx;
	double posy;
	double height;

	double vertical_accselerate;
	double horizontal_speed;
	double depth_speed;

	int state;
	enum { LEFT, RIGHT } orientation;

	double timetoidle;

	Ring* ring;

	Wrestler(Ring* ring) {
		posx=300;
		posy=300;
		height=0;

		horizontal_speed=0;
		vertical_accselerate=0;
		depth_speed=0;

		state=W_IDLE;
		orientation=RIGHT;

		timetoidle=0;

		this->ring=ring;
	}

	SDL_Rect GetSource(float time);
	SDL_Rect GetRect(int camerax,int height,int scale);
	SDL_Point GetAnchor();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void SitDown();
	void Jump();
	void Attack();
	void Update(float ellapsedtime);
};

#endif
