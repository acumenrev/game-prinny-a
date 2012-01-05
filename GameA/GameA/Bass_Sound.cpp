#include "Bass_Sound.h"

namespace WaZ_Game_App {
	Bass_Sound::Bass_Sound() {
		// Nothing here
	}

	Bass_Sound::Bass_Sound (HWND hwnd){
		this->m_hWnd	= hwnd;
		m_szFile		= NULL;
		m_Device		= -1;
		m_flags			= 0;
		m_freg			= 44100;
		m_streams		= NULL;
		m_nStreamCount	= 0;
	}

	int Bass_Sound::Init (int nDevice, DWORD freg, DWORD flags){
		m_Device	= nDevice;
		m_freg		= freg;
		m_flags		= flags;

		if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
			MessageBox(m_hWnd,"An incorrect version of BASS.DLL was loaded", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!BASS_Init(m_Device, m_freg, m_flags, m_hWnd, NULL)) {
			MessageBox(m_hWnd, "Can't initialize device", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	int Bass_Sound::AddFile (STREAM_TYPE type, const char* sID, const char* szFile, DWORD flags){
		for (int nL = 0; nL < m_nStreamCount; nL++){
			if (strcmp(sID, m_streams[nL].sID) == 0){
				MessageBox(m_hWnd, "This id current exist !\nChoose another, please.", "Error", MB_OK | MB_ICONERROR);
				return false;
			}
		}
		DWORD hSound;
		if (type == STR_MP123_OGG_WAV_AIFF){
			/// Creates a sample stream from an MP3, MP2, MP1, OGG, WAV, AIFF formats
			if (hSound = BASS_StreamCreateFile(FALSE, szFile, 0, 0, flags)) {
				m_nStreamCount++;
				m_streams = (PSTREAM_NODE)realloc((void*)m_streams, m_nStreamCount*sizeof(STREAM_NODE));

				m_streams[m_nStreamCount - 1].hStream	= hSound;
				m_streams[m_nStreamCount - 1].idType	= type;
				m_streams[m_nStreamCount - 1].sID = (char*)malloc(sizeof(char) * strlen(sID));
				strcpy(m_streams[m_nStreamCount - 1].sID, sID);
			} else {
				MessageBox(m_hWnd, "Can't load file !", "Error", MB_OK | MB_ICONERROR);
				return false;
			}
		} else if (type == STR_MOD) {
			/// Loads a MOD music file; MO3 / IT / XM / S3M / MTM / MOD / UMX formats.
			if (hSound = BASS_MusicLoad(FALSE, szFile, 0, 0, flags, 0)) {
				m_nStreamCount++;
				m_streams = (PSTREAM_NODE)realloc((void*)m_streams, m_nStreamCount*sizeof(STREAM_NODE));

				m_streams[m_nStreamCount - 1].hStream	= hSound;
				m_streams[m_nStreamCount - 1].idType	= type;
				m_streams[m_nStreamCount - 1].sID = (char*)malloc(sizeof(char) * strlen(sID));
				strcpy(m_streams[m_nStreamCount - 1].sID, sID);
			} else {
				MessageBox(m_hWnd, "Can't load music !", "Error", MB_OK | MB_ICONASTERISK);
				return false;
			}
		} else {
			MessageBox(m_hWnd, "You pass invalid type !", "Information", MB_OK | MB_ICONINFORMATION);
			return false;
		}

		return true;
	}

	void Bass_Sound::RemoveFile (char* id){
		int nPos;
		int nFound = 0;
		for (nPos = 0; nPos < m_nStreamCount; nPos++){
			if (strcmp(m_streams[nPos].sID, id) == 0){
				nFound = 1;
				break;
			}
		}
		if (nFound == 0){
			return;
		}
		if (m_streams[nPos].idType == STR_MP123_OGG_WAV_AIFF){
			BASS_StreamFree(m_streams[nPos].hStream);
			m_nStreamCount--;
			memcpy(m_streams + nPos, m_streams + nPos + 1, (m_nStreamCount - nPos)*sizeof(STREAM_NODE));
		} else if (m_streams[nPos].idType == STR_MOD){
			BASS_MusicFree(m_streams[nPos].hStream);
			m_nStreamCount--;
			memcpy(m_streams + nPos, m_streams + nPos + 1, (m_nStreamCount - nPos)*sizeof(STREAM_NODE));
		}
	}

	int	Bass_Sound::Play (char* id, bool bRestart){
		int nPos;
		int nFound = 0;
		for (nPos = 0; nPos < m_nStreamCount; nPos++){
			if (strcmp(m_streams[nPos].sID, id) == 0){
				nFound = 1;
				break;
			}
		}
		if (0 == nFound){
			return false;
		}
		if (!BASS_ChannelPlay(m_streams[nPos].hStream, bRestart)){
			MessageBox(m_hWnd, "Can't play file !", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void Bass_Sound::Pause (char* id){
		int nPos;
		int nFound = 0;
		for (nPos = 0; nPos < m_nStreamCount; nPos++){
			if (strcmp(m_streams[nPos].sID, id) == 0){
				nFound = 1;
				break;
			}
		}
		if (nFound == 0){
			return;
		}
		BASS_ChannelPause(m_streams[nPos].hStream);
	}

	void Bass_Sound::Stop (char* id){
		int nPos, nFound = 0;
		for (nPos = 0; nPos < m_nStreamCount; nPos++){
			if (strcmp(m_streams[nPos].sID, id) == 0){
				nFound = 1;
				break;
			}
		}
		if (nFound == 0){
			return;
		}
		BASS_ChannelStop(m_streams[nPos].hStream);
	}

	void Bass_Sound::PauseAll (){
		BASS_Pause();
	}

	void Bass_Sound::StopAll (){
		BASS_Stop();
	}

	void Bass_Sound::ResumeAll (){
		BASS_Start();
	}

	void Bass_Sound::SetGlobalVolume (int nVol){
		BASS_SetVolume((float)nVol/100.0f);
	}

	void Bass_Sound::SetItemVolume (char* id, int nVal){
		int nPos, nFound = 0;
		for (nPos = 0; nPos < m_nStreamCount; nPos++){
			if (0 == strcmp(m_streams[nPos].sID, id)){
				nFound = 1;
				break;
			}
		}
		if (nFound == 0){
			return;
		}
		BASS_ChannelSetAttribute(m_streams[nPos].hStream, BASS_ATTRIB_VOL,  (float)nVal/100);
	}
}