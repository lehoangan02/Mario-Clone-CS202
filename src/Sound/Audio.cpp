#include "Audio.h"

std::vector<Sound> SoundManager::soundSet;

SoundManager::SoundManager() {
    soundSet.push_back(LoadSound("assets/audio/coin_sound.wav"));
    soundSet.push_back(LoadSound("assets/audio/jump_small.wav"));
    soundSet.push_back(LoadSound("assets/audio/block_hitted.wav"));
	soundSet.push_back(LoadSound("assets/audio/kill.wav"));
	soundSet.push_back(LoadSound("assets/audio/powerup.wav"));
	soundSet.push_back(LoadSound("assets/audio/powerdown.wav"));
	soundSet.push_back(LoadSound("assets/audio/die.wav"));
	soundSet.push_back(LoadSound("assets/audio/itemPopUp.wav"));
	soundSet.push_back(LoadSound("assets/audio/flag_down.wav"));

}

SoundManager::~SoundManager() {
    /*for (auto& sound : soundSet) {
        UnloadSound(sound);
    }*/
}

void SoundManager::PlaySoundEffect(SoundTrack sound) {
    switch (sound) {
    case COIN_SOUND:
        PlaySound(soundSet[0]);
        break;
    case JUMP_SOUND:
        PlaySound(soundSet[1]);
        break;
    case HITBLOCK_SOUND:
        PlaySound(soundSet[2]);
        break;
	case KILL_SOUND:
		PlaySound(soundSet[3]);
		break;
	case POWERUP_SOUND:
		PlaySound(soundSet[4]);
		break;
	case POWERDOWN_SOUND:
		PlaySound(soundSet[5]);
		break;
	case DIE_SOUND:
		PlaySound(soundSet[6]);
		break;
	case ITEMPOPUP_SOUND:
		PlaySound(soundSet[7]);
		break;
	case FLAGDOWN_SOUND:
		PlaySound(soundSet[8]);
		break;

    }
}


std::vector<Music> MusicManager::musicSet;

MusicManager::MusicManager() {
	currentTrack = -1;
	musicSet.push_back(LoadMusicStream("assets/audio/background_open.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_underground.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_castle.wav"));
}

MusicManager::~MusicManager() {
    for (auto& music : musicSet) {
        UnloadMusicStream(music);
    }
}

void MusicManager::PlayMusic(MusicTrack music) {
	if (currentTrack != -1) {
		StopMusic();
	}
	switch (music) {
	case OverWorld:
		PlayMusicStream(musicSet[OverWorld]);
		currentTrack = 0;
		break;
	case UnderGround:
		PlayMusicStream(musicSet[UnderGround]);
		currentTrack = 1;
		break;
    case Invincible:
		PlayMusicStream(musicSet[Invincible]);
		currentTrack = 2;
		break;
	}
}

void MusicManager::UpdateMusic() {
   /* for (auto& music : musicSet) {
        UpdateMusicStream(music);
    }*/
    if (currentTrack == -1) return;
	UpdateMusicStream(musicSet[currentTrack]);
}

void MusicManager::StopMusic() {
    for (auto& music : musicSet) {
        StopMusicStream(music);
    }
    currentTrack = -1;
}