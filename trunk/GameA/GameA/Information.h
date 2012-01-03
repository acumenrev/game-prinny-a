#include <windows.h>
#include <stdlib.h>
//Define Window Size:
#pragma once
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define APPNAME "Prinny"
#define KEYDOWN(name, key) (name[key] & 0x80? 1 : 0)
#define KEYUP(name, key) (name[key] & 0x80? 0 : 1)
#define BUTTONDOWN(name, key)(name.rgbButtons[key]&0x80)
#define SizeTile 32
#define NumberOfMap 2
enum GameState
{
	GamePlay=0,
	GameMenu=1,
	GameContinue=2,
	GameAbout = 3,
	GameExit=4,
	MenuIn=5,
	GameDeath
};
//////////////////////////////////////////////////////////////////////////
RECT Rectangle(float fX, float fY, int width, int height)
{
	RECT r;
	r.top = fY;
	r.left = fX;
	r.bottom = fY + height;
	r.right = fX + width;
	return r;
}