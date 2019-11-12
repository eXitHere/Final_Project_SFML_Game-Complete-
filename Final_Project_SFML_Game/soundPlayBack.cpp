#include"soundPlayBack.h"

soundPlayBack::soundPlayBack()
{
	this->M_music.openFromFile("music/menu/bg_menu.ogg");
	this->M_music.setLoop(true);
	//this->M_music.play();

	this->clickBuffer.loadFromFile("music/effect/click.wav");
	this->clickSound.setBuffer(this->clickBuffer);
	this->clickSound.setPitch(0.8);
	
	this->itemHitBuffer[0].loadFromFile("music/effect/item1.wav");
	this->itemHitBuffer[1].loadFromFile("music/effect/item2.wav");
	this->itemHitBuffer[2].loadFromFile("music/effect/item3.wav");
	for(int i=0;i<3;i++) this->itemHit[i].setBuffer(this->itemHitBuffer[i]);

	this->lvUpBuffer.loadFromFile("music/effect/lvUp.wav");
	this->lvUp.setBuffer(this->lvUpBuffer);

	this->jumpBuffer.loadFromFile("music/effect/jump.wav");
	this->jump.setBuffer(this->jumpBuffer);
	this->jump.setMinDistance(0.5);

	this->meawBuffer.loadFromFile("music/effect/meaw.wav");
	this->meaw.setBuffer(this->meawBuffer);

	this->paintBuffer.loadFromFile("music/effect/paint.wav");
	this->paint.setBuffer(this->paintBuffer);

	this->doorBuffer.loadFromFile("music/effect/door.wav");
	this->door.setBuffer(this->doorBuffer);
}

void soundPlayBack::restartMusicBackground()
{
	this->M_music.play();
}

void soundPlayBack::soundControl(int state)
{
	switch (state)
	{
	default:
		break;
	}
}

void soundPlayBack::setVolumeMusic(int val)
{
	this->M_music.setVolume(val);
}

void soundPlayBack::setVolumeEffect(int val)
{
	this->clickSound.setVolume(val);
	for (int i = 0; i < 3; i++) this->itemHit[i].setVolume(val);
	this->lvUp.setVolume(val * 0.5);
	this->jump.setVolume(val * 0.3);
	this->meaw.setVolume(val * 0.3);
	this->paint.setVolume(val * 0.3);
	this->door.setVolume(val * 0.3);
	//cout << val * 0.3 << endl;
}

void soundPlayBack::playClick()
{
	this->clickSound.play();
}

void soundPlayBack::playHitItem()
{
	//cout << "Cal " << endl
	this->itemHit[1].play();
}

void soundPlayBack::playLvUp()
{
	this->lvUp.play();
}

void soundPlayBack::playJump()
{
	this->jump.play();
}

void soundPlayBack::playCat()
{
	this->meaw.play();
}

void soundPlayBack::playPaint()
{
	this->paint.play();
}

void soundPlayBack::playDoor()
{
	this->door.play();
}
