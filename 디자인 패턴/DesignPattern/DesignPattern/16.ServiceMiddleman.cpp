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
	// 각 기능 생략
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
	// 함수 몸체에서 아무것도 하지 않는다.
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
		// 기존 서비스를 데커레이트한다.
		Audio* service = new LoggedAudio(Locator::getAudio());
		// 이 값으로 바꿔치기한다.
		Locator::provide(service);
	}

	virtual void playSound(int soundID)
	{
		log("사운드 출력");
		wrapped_.playSound(soundID);
	}
	virtual void stopSound(int soundID)
	{
		log("사운드 중지");
		wrapped_.stopSound(soundID);
	}
	virtual void stopAllSounds()
	{
		log("모든 사운드 중지");
		wrapped_.stopAllSounds();
	}

private:
	// 로그 남기는 코드
	void log(const char* message)
	{}
	Audio& wrapped_;
};

// 중개자
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
		// 서비스를 찾는 코드..
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
	// 컴파일할 때 바인딩
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
	// 사용
	Audio* audio = Locator::getAudio();
	audio->playSound(VERY_LOUD_BANG);

	// 어플리케이션 시작 시
	ConsoleAudio* audio = new ConsoleAudio();
	Locator::provide(audio);
}


class Base
{
	// 서비스를 찾아 service_에 등록하는 코드...

protected:
	// 서비스를 제공하는 정적 메서드는 하위 클래스에서만 접근할 수 있다.
	Audio& getAudio() { return *service_; }

private:
	static Audio* service_;
};

