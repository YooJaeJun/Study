#include <bits/stdc++.h>
using namespace std;


class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:
	// �� ��� ����
	virtual void playSound(int soundID)
	{}
	virtual void stopSound(int soundID)
	{}
	virtual void stopAllSounds()
	{}
};

class NullAudio : public Audio
{
public:
	// �Լ� ��ü���� �ƹ��͵� ���� �ʴ´�.
	virtual void playSound(int soundID) {}
	virtual void stopSound(int soundID) {}
	virtual void stopAllSounds() {}
};

class LoggedAudio : public Audio
{
public:
	LoggedAudio(Audio& wrapped) : wrapped_(wrapped) {}
	
	void enableAudioLogging()
	{
		// ���� ���񽺸� ��Ŀ����Ʈ�Ѵ�.
		Audio* service = new LoggedAudio(Locator::getAudio());
		// �� ������ �ٲ�ġ���Ѵ�.
		Locator::provide(service);
	}

	virtual void playSound(int soundID)
	{
		log("���� ���");
		wrapped_.playSound(soundID);
	}
	virtual void stopSound(int soundID)
	{
		log("���� ����");
		wrapped_.stopSound(soundID);
	}
	virtual void stopAllSounds()
	{
		log("��� ���� ����");
		wrapped_.stopAllSounds();
	}

private:
	// �α� ����� �ڵ�
	void log(const char* message)
	{}
	Audio& wrapped_;
};

// �߰���
class Locator
{
public:
	static void initialize()
	{
		service_ = &nullService_;
	}
	static Audio& getAudio() 
	{ 
		Audio* service = nullptr;
		// ���񽺸� ã�� �ڵ�..
		assert(service != nullptr);
		return *service_; 
	}
	static void provide(Audio* service) 
	{ 
		if (service == nullptr)
		{
			service_ = &nullService_;
		}
		else
		{
			service_ = service;
		}
	}

private:
	// �������� �� ���ε�
#if DEBUG
	static DebugAudio service_;
#else
	static ReleaseAudio service_;
#endif

	static Audio* service_;
	static NullAudio nullService_;
};

int main()
{
	// ���
	Audio* audio = Locator::getAudio();
	audio->playSound(VERY_LOUD_BANG);

	// ���ø����̼� ���� ��
	ConsoleAudio* audio = new ConsoleAudio();
	Locator::provide(audio);
}


class Base
{
	// ���񽺸� ã�� service_�� ����ϴ� �ڵ�...

protected:
	// ���񽺸� �����ϴ� ���� �޼���� ���� Ŭ���������� ������ �� �ִ�.
	Audio& getAudio() { return *service_; }

private:
	static Audio* service_;
};

