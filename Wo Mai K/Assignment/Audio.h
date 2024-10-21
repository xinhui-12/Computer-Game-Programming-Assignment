#pragma once
#include "fmod.hpp"

class Audio
{
public:
	FMOD::System* system;
	FMOD::Sound* sound1, * sound2, * sound3, * sound4, * sound5, * sound6, *sound7;
	FMOD::Channel* channel1, * channel2, * channel3, * channel4, * channel5, * channel6, * channel7 = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;

	float bgmVolume = 0.5;
	int windCounter;
	float windDirection = 2.0f;
	bool bgmIsPlaying;
	bool windIsPlaying;
	bool mouseClickIsPlaying = false;
	bool crashIsPlaying;

	void InitialiseAudio();
	void LoadSoundLoading();
	void LoadSoundMenu();
	void LoadSoundLv1();
	void LoadSoundLv2();
	void LoadSoundLv3();
	void LoadSoundWin();

	void PlayBGM(float bgmVolume);
	void PlayingBGM();

	void playClickSound();
	void Clicking();

	void playJumpSound();


	void PlayWindSound(float windDirection);
	void Blowing();
	void WindDirectionUpdate();

	void PlayTalkSound();

	void PlayWin(float bgmVolume);

	void PlayCrashSound();
	void PlayingCrash();

	void ClearSound();
	void UpdateSound();

	Audio();
	~Audio();

};

