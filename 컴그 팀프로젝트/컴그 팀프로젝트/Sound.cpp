#include "Header/Sound.h"


void Sound::Init_Sound()
{
	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 10, FMOD_INIT_NORMAL, NULL);

	//브금 반복재생
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/bgm.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	//피카츄
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Pikachu.wav", FMOD_DEFAULT, 0, &effectSound[0]);
	//콘팡
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Venonat.wav", FMOD_DEFAULT, 0, &effectSound[1]);
	//찌리리공
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Voltorb.wav", FMOD_DEFAULT, 0, &effectSound[2]);
	//코일
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Magnemite.wav", FMOD_DEFAULT, 0, &effectSound[3]);
	//발챙이
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Poliwag.wav", FMOD_DEFAULT, 0, &effectSound[4]);
}
