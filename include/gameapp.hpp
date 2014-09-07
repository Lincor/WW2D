#ifndef GAMEAPP_H
#define GAMEAPP_H

#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)

enum GameAppFuncState {
	GA_KEYFUNC				= 7,	// bool*()	frame function		(default: NULL)
	GA_FRAMEFUNC			= 8,    // bool*()	frame function		(default: NULL) (you MUST set this)
	GA_RENDERFUNC			= 9,    // bool*()	render function		(default: NULL)
	GA_LOADFUNC				= 10,	// bool*()  run onse			(default: NULL)
	GA_FOCUSLOSTFUNC		= 11,   // bool*()	focus lost function	(default: NULL)
	GA_FOCUSGAINFUNC		= 12,   // bool*()	focus gain function	(default: NULL)
	GA_EXITFUNC				= 13,   // bool*()	exit function		(default: NULL)
};
enum GameAppIntState {
	GA_SCREENWIDTH		= 17,   // int		screen width		(default: 800)
	GA_SCREENHEIGHT		= 18,   // int		screen height		(default: 600)
	GA_SCREENBPP		= 19,   // int		screen bitdepth		(default: 32) (desktop bpp in windowed mode)

	GA_FPS				= 24,	// int		fixed fps			(default: HGEFPS_UNLIMITED)
};

typedef bool (*GameAppCallback)();

class GameApp {
public:
	static SDL_Renderer *render;
private:
	static int width;
	static int height;

	static SDL_Window *window;
	static SDL_Event e;

	static const Uint8 *keyboard;

	static float time,delta;
	static int fps;
	static char *title;

	static GameAppCallback frameFunction;
	static GameAppCallback renderFunction;
	static GameAppCallback keyFunction;
	static GameAppCallback loadFunction;

public:
	static void System_SetState(GameAppFuncState state,GameAppCallback value);
	static void System_SetState(GameAppIntState state,int value);
	static int System_CreateScreen(int, int);
	static bool System_Initiate();
	static void System_Start();
	static void System_Shutdown();
	static double System_GetEllapsedTime();
	static double System_GetTime();
	static double System_GetFPS();
	static bool Input_KeyDown(Uint8 key);
	static bool Input_KeyUp(Uint8 key);
	static void Gfx_printf(int x,int y,Uint32 color,char* format,...);
};

#endif
