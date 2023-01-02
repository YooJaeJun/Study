#include <bits/stdc++.h>
using namespace std;

class ParticleSystem
{
};

class SoundId
{
};

/*
class Superpower
{
public:
	virtual ~Superpower() {}

protected:
	virtual void activate() = 0;
	void move(double x, double y, double z) {}
	void playSound(SoundId sound, double volume) {}
	void stopSound(SoundId sound) {}
	void setVolume(SoundId sound) {}
	void spawnParticles(ParticleType type, int count) {}

	double getHeroX() {}
	double getHeroY() {}
	double getHeroZ() {}
};

class SkyLaunch : public Superpower
{
protected:
	virtual void activate()
	{
		if (getHeroZ() == 0)
		{
			playSound(SOUND_SPROING, 1.0f);
			spawnParticles(PARTICLE_DUST, 10);
			move(0, 0, 20);
		}
		else if (getHeroZ() < 10.0f)
		{
			playSound(SOUND_SWOOP, 1.0f);
			move(0, 0, getHeroZ() - 20);
		}
		else
		{
			playSound(SOUND_DIVE, 0.7f);
			spawnParticles(PARTICLE_SPARKLES, 1);
			move(0, 0, -getHeroZ());
		}
	}
};
*/

class SoundPlayer
{
	void playSound(SoundId sound, double volume) {}
	void stopSound(SoundId sound) {}
	void setVolume(SoundId sound) {}
};

class Superpower
{
public:
	static void init(ParticleSystem* particles)
	{
		particles_ = particles;
	}

protected:
	SoundPlayer& getSoundPlayer()
	{
		return soundPlayer_;
	}
	void spawnParticles(ParticleType type, int count)
	{
		ParticleSystem& particles = Locator::getParticles();
		particles.spawn(type, count);
	}

private:
	SoundPlayer soundPlayer_;
	static ParticleSystem* particles_;
};

class SkyLaunch : public Superpower
{
public:
	Superpower* createSkyLaunch(ParticleSystem* particles)
	{
		Superpower* power = new SkyLaunch();
		power->init(particles);
		return power;
	}
};

int main()
{
	ParticleSystem* particles;
	Superpower* power = new SkyLaunch();
	power->init(particles);
}