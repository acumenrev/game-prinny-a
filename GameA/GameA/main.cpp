#include "Game.h"

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	CGame* game = new CGame(hInstance);
	if(game->GameInit() == true)
	{
		game->Run();
	}
	return 0;
}