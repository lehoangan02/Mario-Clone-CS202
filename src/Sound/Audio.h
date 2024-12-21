#include "raylib.h"
#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include <string>
#include <iostream>

#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>

enum SoundTrack {
    COIN_SOUND,
    JUMP_SOUND,
    HITBLOCK_SOUND,
	KILL_SOUND,
	POWERUP_SOUND,
	POWERDOWN_SOUND,
	DIE_SOUND,
	ITEMPOPUP_SOUND,
	FLAGDOWN_SOUND
};

class SoundManager {
public:
    static SoundManager& getInstance() {
        static SoundManager instance;
        return instance;
    }

    void PlaySoundEffect(SoundTrack sound);

private:
    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static std::vector<Sound> soundSet;
};

enum MusicTrack {
    OverWorld,
	Origin_UnderWorld,
	Invincible,
	SuperBellHill,
	FlowerGarden,
	Athletic,
	UnderGround,
	SMB,
	LevelFinished,
    FlagDown
};

class MusicManager {
public:
    static MusicManager& getInstance() {
        static MusicManager instance;
        return instance;
    }

    void PlayMusic(MusicTrack music);
    void UpdateMusic();
    void StopMusic();
	bool IsMusicPlaying();
	void SetVolume(float volume);
    void PlayPreviousTrack();
private:
    int currentTrack;
    int prevTrack;
    MusicManager();
    ~MusicManager();
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    static std::vector<Music> musicSet;
};