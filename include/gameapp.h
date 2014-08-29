#ifndef GAMEAPP_H
#define GAMEAPP_H

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
		void System_SetState(GameAppFuncState state,GameAppCallback value);
		void System_SetState(GameAppIntState state,int value);
		int System_CreateScreen();
		bool System_Initiate();
		void System_Start();
		void System_Shutdown();
		float System_GetEllapsedTime();
		float System_GetTime();
		float System_GetFPS();
		bool Input_KeyDown(Uint8 key);
		bool Input_KeyUp(Uint8 key);
		void Gfx_printf(int x,int y,Uint32 color,char* format,...);
};

#endif
