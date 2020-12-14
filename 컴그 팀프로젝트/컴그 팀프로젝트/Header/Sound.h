#pragma once
#include "header.h"


class Sound {

public:
	FMOD_SYSTEM* soundSystem;   //사운드 시스템
	FMOD_SOUND* bgmSound[2];	//배경브금갯수
	FMOD_SOUND* effectSound[6];	//이펙트브금갯수
	FMOD_CHANNEL* Channel[2];	//배경+이펙트 해서 채널

	//사운드 초기화 함수
	void Init_Sound();


};



