#include "Audio.h"

void Audio::InitialiseAudio() {
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

//===================================================================================//
void Audio::LoadSoundLoading() {
	result = system->createSound("../Audio/Talking.wav", FMOD_DEFAULT, 0, &sound5);
	result = sound5->setMode(FMOD_LOOP_NORMAL);
}

void Audio::LoadSoundMenu() {
	result = system->createSound("../Audio/BGM.wav", FMOD_DEFAULT, 0, &sound1);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	result = sound1->setLoopCount(-1);

	result = system->createSound("../Audio/Click.wav", FMOD_DEFAULT, 0, &sound2);
	result = sound2->setMode(FMOD_LOOP_OFF);
}

void Audio::LoadSoundLv1() {
	result = system->createSound("../Audio/BGM.wav", FMOD_DEFAULT, 0, &sound1);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	result = sound1->setLoopCount(-1);

	result = system->createSound("../Audio/Jump.wav", FMOD_DEFAULT, 0, &sound3);
	result = sound2->setMode(FMOD_LOOP_OFF);
}

void Audio::LoadSoundLv2() {
	result = system->createSound("../Audio/BGM.wav", FMOD_DEFAULT, 0, &sound1);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	result = sound1->setLoopCount(-1);

	result = system->createSound("../Audio/Jump.wav", FMOD_DEFAULT, 0, &sound3);
	result = sound2->setMode(FMOD_LOOP_OFF);

	result = system->createSound("../Audio/Wind.wav", FMOD_DEFAULT, 0, &sound4);
	result = sound3->setMode(FMOD_LOOP_OFF);
}

void Audio::LoadSoundLv3() {
	result = system->createSound("../Audio/Crash.wav", FMOD_DEFAULT, 0, &sound7);
	result = sound7->setMode(FMOD_LOOP_OFF);
}

void Audio::LoadSoundWin() {
	result = system->createSound("../Audio/Win.wav", FMOD_DEFAULT, 0, &sound6);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	result = sound1->setLoopCount(-1);
}

//===================================================================================//

void Audio::PlayBGM(float bgmVolume) {
	result = system->playSound(sound1, 0, false, &channel1);
	channel1->setVolume(bgmVolume);
	channel1->setFrequency(48000);
	channel1->setPaused(false);
}

void Audio::PlayingBGM() {
	result = channel1->isPlaying(&bgmIsPlaying);
	if (result == FMOD_OK) {
		bgmIsPlaying = true;
	}
	else bgmIsPlaying = false;
}

//===================================================================================//

void Audio::playClickSound() {
	result = system->playSound(sound2, 0, true, &channel2);
	channel2->setVolume(5.0f);
	channel2->setFrequency(48000);
	channel2->setPaused(false);
}

void Audio::Clicking() {
	result = channel2->isPlaying(&mouseClickIsPlaying);
	if (result == FMOD_OK) {
		mouseClickIsPlaying = true;
	}
	else mouseClickIsPlaying = false;
}

//===================================================================================//

void Audio::playJumpSound() {
	result = system->playSound(sound3, 0, true, &channel3);
	channel3->setVolume(5.0f);
	channel3->setFrequency(48000);
	channel3->setPaused(false);
}

//===================================================================================//

void Audio::PlayWindSound(float windDirection) {
	result = system->playSound(sound4, 0, false, &channel4);
	channel4->setVolume(3.0f);
	channel4->setPan(windDirection);
	channel4->setFrequency(44100);
	channel4->setPaused(false);
}

void Audio::Blowing() {
	result = channel4->isPlaying(&windIsPlaying);
	if (result == FMOD_OK) {
		windIsPlaying = true;
	}
	else windIsPlaying = false;
}

void Audio::WindDirectionUpdate() {
	if (windCounter % 1000 == 0) {
		channel4->stop();
		windCounter = 0;
		windDirection *= -1;
	}
}

//===================================================================================//

void Audio::PlayTalkSound() {
	result = system->playSound(sound5, 0, true, &channel5);
	channel5->setVolume(1.0f);
	channel5->setFrequency(44100);
	channel5->setPaused(false);
}

//===================================================================================//
void Audio::PlayWin(float bgmVolume) {
	result = system->playSound(sound6, 0, false, &channel6);
	channel1->setVolume(bgmVolume);
	channel1->setFrequency(48000);
	channel1->setPaused(false);
}

//===================================================================================//

void Audio::PlayCrashSound() {
	result = system->playSound(sound7, 0, true, &channel7);
	channel7->setVolume(5.0f);
	channel7->setFrequency(48000);
	channel7->setPaused(false);
}

void Audio::PlayingCrash() {
	result = channel7->isPlaying(&crashIsPlaying);
	if (result == FMOD_OK) {
		bgmIsPlaying = true;
	}
	else bgmIsPlaying = false;
}

//===================================================================================//

void Audio::UpdateSound() {
	system->update();
}

void Audio::ClearSound(){
	sound1->release();
	sound1 = nullptr;
	sound2->release();
	sound2 = nullptr;
	sound3->release();
	sound3 = nullptr;
	sound4->release();
	sound4 = nullptr;
	sound5->release();
	sound5 = nullptr;
    sound6->release();
    sound6 = nullptr;
    sound7->release();
    sound7 = nullptr;

}

//===================================================================================//

Audio::Audio()
{
}

Audio::~Audio()
{
}
