#include <windows.h>
#include <stdlib.h>
//Define Window Size:
#pragma once
#define SizeTile 56
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define APPNAME "Prinny"
#define NumberOfMap 2
#define KEYDOWN(name, key) (name[key] & 0x80? 1 : 0)
#define KEYUP(name, key) (name[key] & 0x80? 0 : 1)
#define BUTTONDOWN(name, key)(name.rgbButtons[key]&0x80)
//#define SizeTile 32
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
/************************************************************************/
/*                     Define units in game                             */
/************************************************************************/
#define UNIT_BLANK '0' // units that do not contain anything
#define UNIT_STATIC '1' // units that do not move or active
#define UNIT_SAVE '2' // unit that used to save game
#define UNIT_BEGIN '3' // unit that used to begin the game
#define UNIT_DESTRUCTION '4' // Can be destroyed
#define UNIT_END '5' // unit that used to end a map
#define UNIT_LEFTRIGHT '6' // unit that can move left or right in game
#define UNIT_TOPBOTTOM '7' // unit that can move up or down
// Grasses
#define UNIT_GRASS1 'Q' // Grass type 1
#define UNIT_GRASS2 'W' // Grass type 2
// Grounds
#define UNIT_GROUND1 'E' // Ground type 1
#define UNIT_GROUND2 'R' // Ground type 2
// Backgrounds
#define UNIT_BACKGROUND1 'T' // Background type 1
#define UNIT_BACKGROUND2 'Y' // Background type 2
//Rock
#define UNIT_ROCK1 'Z' // rock type 1
// Monster
#define UNIT_MONSTER1 'M' // Monster type 1
#define UNIT_MONSTER2 'N' // Monster type 2
#define UNIT_MONSTER3 'L' // Monster type 3
// Fire
#define UNIT_FIRE1 'B' // Fire type 1
// Cloud
#define UNIT_CLOUD 'C'
