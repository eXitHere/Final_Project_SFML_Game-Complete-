#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class soundPlayBack
{
public:
	soundPlayBack();
	void restartMusicBackground();
	void soundControl(int state);
	void setVolumeMusic(int val);
	void setVolumeEffect(int val);
	void playClick();
	void playHitItem();
	void playLvUp();
	void playJump();
	void playCat();
	void playPaint();
	void playDoor();

private:
	Music M_music;
	Sound clickSound;
	SoundBuffer clickBuffer;
	Sound itemHit[3],lvUp,jump,meaw,paint,door;
	SoundBuffer itemHitBuffer[3],lvUpBuffer,jumpBuffer, meawBuffer,paintBuffer,doorBuffer;
};

