#include <SDL2/SDL.h>
#include <stdio.h>

#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)

enum GameAppFuncState
{
	GA_KEYFUNC				= 7,	// bool*()	frame function		(default: NULL)
	GA_FRAMEFUNC			= 8,    // bool*()	frame function		(default: NULL) (you MUST set this)
	GA_RENDERFUNC			= 9,    // bool*()	render function		(default: NULL)
	GA_LOADFUNC				= 10,	// bool*()  run onse			(default: NULL)
	GA_FOCUSLOSTFUNC		= 11,   // bool*()	focus lost function	(default: NULL)
	GA_FOCUSGAINFUNC		= 12,   // bool*()	focus gain function	(default: NULL)
	GA_EXITFUNC				= 13,   // bool*()	exit function		(default: NULL)
};
enum GameAppIntState
{
	GA_SCREENWIDTH		= 17,   // int		screen width		(default: 800)
	GA_SCREENHEIGHT		= 18,   // int		screen height		(default: 600)
	GA_SCREENBPP		= 19,   // int		screen bitdepth		(default: 32) (desktop bpp in windowed mode)
	
	GA_FPS				= 24,	// int		fixed fps			(default: HGEFPS_UNLIMITED)
};

typedef bool (*GameAppCallback)();

class GameApp
{
public:
	SDL_Renderer *render;
private:
	int width;
	int height;

	SDL_Window *window;
	SDL_Event e;

	const Uint8 *keyboard;

	float time,delta;
	int fps;
	char *title;

	GameAppCallback frameFunction;
	GameAppCallback renderFunction;
	GameAppCallback keyFunction;
	GameAppCallback loadFunction;

public:
	GameApp()
	{
		title =new char[20];
		width=800;
		height=600;

		frameFunction=0;
		renderFunction=0;
		keyFunction=0;
		loadFunction=0;
	}
	~GameApp()
	{
		delete[] title;
	}

	void System_SetState(GameAppFuncState state,GameAppCallback value)
	{
		switch(state)
		{
			case GA_FRAMEFUNC:frameFunction=value;break;
			case GA_RENDERFUNC:renderFunction=value;break;
			case GA_KEYFUNC:keyFunction=value;break;
			case GA_LOADFUNC:loadFunction=value;break;
		}
	}
	void System_SetState(GameAppIntState state,int value)
	{
			switch(state)
		{
			case GA_SCREENWIDTH:width=value;break;
			case GA_SCREENHEIGHT:height=value;break;
			case GA_FPS:fps=1000/value;delta=(float)fps;break;
		}
	}
	int System_CreateScreen()
	{
		return SDL_CreateWindowAndRenderer(width,height,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN,&window,&render);
	}
	bool System_Initiate()
	{
		if(SDL_Init( SDL_INIT_EVERYTHING )==-1)
		{
			printf("%s\n",SDL_GetError());
			return false;
		}
		return true;
	}
	void System_Start()
	{
		if(loadFunction)loadFunction();
		Uint32 time=SDL_GetTicks(),oldtime=time;
		int deltat=0;
		char title[16]={0};
		for(;;)
		{
			oldtime=SDL_GetTicks();

			SDL_PollEvent(&e);
			keyboard=SDL_GetKeyboardState(0);

			if(frameFunction)if(!frameFunction())break;

			if(e.type==SDL_KEYDOWN)if(keyFunction)if(!keyFunction())break;
			if(e.type==SDL_QUIT)break;

			if(renderFunction)
			{
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

			this->time = time/1000.0f;
			this->delta = delta;
		}
	}
	void System_Shutdown()
	{
		if(render)SDL_DestroyRenderer(render);
		if(window)SDL_DestroyWindow(window);
	}
	float System_GetEllapsedTime()
	{
		return delta;
	}
	float System_GetTime()
	{
		return time;
	}
	float System_GetFPS()
	{
		return fps;
	}

	bool Input_KeyDown(Uint8 key)
	{
		return keyboard[key]>0;
	}
	bool Input_KeyUp(Uint8 key)
	{
		return !keyboard[key];
	}

	void Gfx_printf(int x,int y,Uint32 color,char* format,...)
	{
		char str[1000];
		va_list args;
		va_start(args, format);
		vsnprintf(str,1000,format,args);
		va_end(args);

		//print str
	}

};
