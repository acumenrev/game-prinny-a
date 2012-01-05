//**************************************************************************************************
//
// SoundPlayer.h: interface for the CSoundPlayer class.
//
// Description: Uses DirectSound to play back sounds
// Note: Makes use of the DirectX framework files dsutil.cpp and dsutil.h
// These define classes CSoundManager and CSound used by this program
//
// Created by: Keith Ditchburn 30/01/2004
//
//**************************************************************************************************

#if !defined(AFX_SOUND1_H__9E6A20A2_156A_47D8_9063_4CEC8193874E__INCLUDED_)
#define AFX_SOUND1_H__9E6A20A2_156A_47D8_9063_4CEC8193874E__INCLUDED_

#pragma once

#include <vector>
#include <Windows.h>
#include <d3d9.h>
#include "dsutil.h"

class CSoundManager;
class CSound;

class CSoundPlayer  
{
private:
	static CSoundPlayer* m_instance;
	CSoundManager* m_soundManager;
	std::vector <CSound*> m_soundVector;
	HRESULT Initialise(HWND hWnd);
	CSoundPlayer();
public:
	void StopSound(int id);
	bool PlaySound(int id,bool loop);
	bool AddWav(char* filename,int *id);
	static CSoundPlayer* GetInstance(HWND hWnd);
	static CSoundPlayer* GetInstance();
	virtual ~CSoundPlayer();
};

#endif // !defined(AFX_SOUND1_H__9E6A20A2_156A_47D8_9063_4CEC8193874E__INCLUDED_)
