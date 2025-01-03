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
	soundSet.push_back(LoadSound("assets/audio/fireball_popped.wav"));
	soundSet.push_back(LoadSound("assets/audio/fireworks.wav"));
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
		MusicManager::getInstance().StopMusic();
		PlaySound(soundSet[6]);
		break;
	case ITEMPOPUP_SOUND:
		PlaySound(soundSet[7]);
		break;
	case FLAGDOWN_SOUND:
		PlaySound(soundSet[8]);
		break;
	case FIREBALL_SOUND:
		PlaySound(soundSet[9]);
		break;
	case BOOM_SOUND:
		PlaySound(soundSet[10]);
		break;
    }
}
void SoundManager::StopSoundEffect(SoundTrack sound) {
	switch (sound) {
	case COIN_SOUND:
		StopSound(soundSet[0]);
		break;
	case JUMP_SOUND:
		StopSound(soundSet[1]);
		break;
	case HITBLOCK_SOUND:
		StopSound(soundSet[2]);
		break;
	case KILL_SOUND:
		StopSound(soundSet[3]);
		break;
	case POWERUP_SOUND:
		StopSound(soundSet[4]);
		break;
	case POWERDOWN_SOUND:
		StopSound(soundSet[5]);
		break;
	case DIE_SOUND:
		StopSound(soundSet[6]);
		break;
	case ITEMPOPUP_SOUND:
		StopSound(soundSet[7]);
		break;
	case FLAGDOWN_SOUND:
		StopSound(soundSet[8]);
		break;
	}
}


std::vector<Music> MusicManager::musicSet;

MusicManager::MusicManager() {
	currentTrack = -1;
	prevTrack = -1;
	musicSet.push_back(LoadMusicStream("assets/audio/background_Overworld.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_Underworld.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_Invincible.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_SuperBellHill.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_FlowerGarden.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_Athletic.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_UnderGround.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/background_SMB.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/level_finished.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/flag_down.wav"));
	musicSet.push_back(LoadMusicStream("assets/audio/OIIAOIIA_CATxAFTER_DARK.wav"));
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
	prevTrack = currentTrack;
	switch (music) {
	case OverWorld:
		PlayMusicStream(musicSet[OverWorld]);
		currentTrack = 0;
		break;
	case Origin_UnderWorld:
		PlayMusicStream(musicSet[Origin_UnderWorld]);
		currentTrack = 1;
		break;
    case Invincible:
		PlayMusicStream(musicSet[Invincible]);
		currentTrack = 2;
		SetMusicVolume(0.6f);
		break;
	case SuperBellHill:
		PlayMusicStream(musicSet[SuperBellHill]);
		currentTrack = 3;
		SetMusicVolume(0.3f);
		break;
	case FlowerGarden:
		PlayMusicStream(musicSet[FlowerGarden]);
		currentTrack = 4;
		SetMusicVolume(0.3f);
		break;
	case Athletic:
		PlayMusicStream(musicSet[Athletic]);
		currentTrack = 5;
		SetMusicVolume(0.3f);
		break;
	case UnderGround:
		PlayMusicStream(musicSet[UnderGround]);
		currentTrack = 6;
		break;
	case SMB:
		PlayMusicStream(musicSet[SMB]);
		currentTrack = 7;
		break;
	case LevelFinished:
		PlayMusicStream(musicSet[LevelFinished]);
		currentTrack = 8;
		break;
	case FlagDown:
		PlayMusicStream(musicSet[FlagDown]);
		currentTrack = 9;
		break;
	case UIA:
		PlayMusicStream(musicSet[UIA]);
		currentTrack = 10;
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
	if (currentTrack == -1) return;
	StopMusicStream(musicSet[currentTrack]);
}

bool MusicManager::IsMusicPlaying() {
	if (currentTrack == -1) return false;
	return IsMusicStreamPlaying(musicSet[currentTrack]);
}

void MusicManager::PlayPreviousTrack() {
	if (prevTrack == -1) return;
	PlayMusicStream(musicSet[prevTrack]);
	//std::cout << "prevTrack: " << prevTrack << std::endl;	
	currentTrack = prevTrack;
}

void MusicManager::PlayCurrentTrack() {
	if (currentTrack == -1) return;
	PlayMusicStream(musicSet[currentTrack]);
}

void MusicManager::SetMusicVolume(float volume) {
	if (currentTrack == -1) {
		return; 
	}
	if (volume < 0.0f) volume = 0.0f; 
	if (volume > 1.0f) volume = 1.0f;
	::SetMusicVolume(musicSet[currentTrack], volume); 
}