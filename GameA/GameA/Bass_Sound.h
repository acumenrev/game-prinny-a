#ifndef _BASS_SOUND_H_
#define _BASS_SOUND_H_
#include "bass.h"
#include <stdlib.h>

//#pragma comment(lib, "../source/Bass.lib")
/*
 Sử dụng như sau:
  using namespace WaZ_Game_App;
  Bass_Sound* mSound = new Bass_Sound(hWnd /*Handle của cửa sổ ứng dụng cần gán âm thanh*///);
 // if (!mSound){
  //	exit(0); // Thoát nếu không cấp phát bộ nhớ được
  //}
  //mSound->Init(-1, 44100, 0); // Gọi với tham số giống hàm BASS_Init(...). Ở đây gọi với device mặc định
  /// Thêm file nhạc. Có hai kiểu định dạng được hỗ trợ: STR_MP123_OGG_WAV_AIFF & STR_MOD
  //m_Sound->AddFile(STR_MOD, "tenamthanh", "fileamthanh.mod", BASS_MUSIC_RAMPS | BASS_MUSIC_LOOP); // Thêm file âm thanh "fileamthanh.mod" và đặt tên nó trong bộ nhớ là "tenamthanh", cho phép file này phát lặp lại khi phát hết (BASS_MUSIC_LOOP)
  /// Có thể add nhiều file, mỗi file đặt một tên khác nhau trong bộ nhớ 
  //mSound->AddFile(STR_MP123_OGG_WAV_AIFF, "filemp3", "Am thanh.mp3", BASS_MUSIC_RAMPS ); // Thêm file mp3. Không phát lặp lại

  /// Phát âm thanh đã add. Chúi ý: do tên file add vào có phân biệt chữ hoa và chữ thường nên phải gõ đúng tên.
  //mSound->Play("tenamthanh");
  //mSound->Play("filemp3");

  /// Đặt volume cho một file
  //mSound->SetItemVolume("filemp3", 80); // Đặt volume với giá trị từ 0-100
  /// Đặt âm lượng tổng thể. Có tác dụng toàn cục lên hệ thống âm lượng
  //mSound->SetGlobalVolume(50); // Giá trị từ 0 -100

  // Các hàm khác sài tương tự :D (Tự tìm hiểu đêeee);
//*/

namespace WaZ_Game_App {

	enum STREAM_TYPE {
		STR_MP123_OGG_WAV_AIFF,
		STR_MOD
	};

	typedef struct tagStreamNode {
		STREAM_TYPE	idType ;
		char*		sID;
		DWORD		hStream;
	} STREAM_NODE, * PSTREAM_NODE;

	class Bass_Sound {
	private:
		char*		m_szFile;
		HWND		m_hWnd;
		int			m_Device;
		DWORD		m_freg;
		DWORD		m_flags;

		PSTREAM_NODE	m_streams;
		int			m_nStreamCount;

	public:
		/// Constructors
		Bass_Sound();
		Bass_Sound(HWND hwnd);
		/// Destructor(s)
		~Bass_Sound();

		/// Init
		int		Init(int nDevice, DWORD freg, DWORD flags);

		/// Add file to list
		int		AddFile(STREAM_TYPE type, const char* sID, const char* szFile, DWORD flags);
		/// Remove file from list
		void	RemoveFile(char* id);

		/// Play
		int		Play(char* id, bool bRestart);
		/// Pause
		void	Pause(char* id);
		/// Stop
		void	Stop(char* id);
		/// Pause all
		void	PauseAll();
		/// Stop all playing stream
		void	StopAll();
		/// Resume all 
		void	ResumeAll();
		/// Set global volume
		/// 0 - 100
		void	SetGlobalVolume(int nVol);
		/// Se volume for a channel
		// 0 - 100
		void	SetItemVolume(char* id, int nVal);
	};
}

#endif