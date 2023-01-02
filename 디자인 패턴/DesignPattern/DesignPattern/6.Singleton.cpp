#include <bits/stdc++.h>
using namespace std;

/*
class FileSystem
{
public:
	static FileSystem& instance();

	virtual ~FileSystem() {}
	virtual char* readFile(char* path) = 0;
	virtual void writeFile(char* path, char* contents) = 0;

protected:
	FileSystem() {}
};


static FileSystem& instance()
{
#if PLATFORM == PLAYSTATION3
	static FileSystem* instance = new PS3FileSystem();
#elif PLATFORM == WII
	static FileSystem* instance = new WiiFileSystem();
#endif
	return *instance;
}

class PS3FileSystem : public FileSystem
{
public:
	virtual char* readFile(char* path)
	{
		// 소니의 파일 IO API 사용
	}
	virtual void writeFile(char* path, char* contents)
	{
		// 소니의 파일 IO API 사용
	}
};

// 닌텐도 위 등 다른 플랫폼도 상속
*/

/*
class FileSystem
{
public:
	static FileSystem& instance() { return instance_; }

private:
	FileSystem() {}

	static FileSystem instance_;
};
*/

class FileSystem
{
public:
	FileSystem()
	{
		assert(!instantiated_);
		instantiated_ = true;
	}
	~FileSystem()
	{
		instantiated_ = false;
	}

private:
	static bool instantiated_;
};

bool FileSystem::instantiated_ = false;

// 런타임에 인스턴스 개수를 확인한다는 게 단점



class GameObject
{
protected:
	Log& getLog() { return log_; }

private:
	static Log& log_;
};

class Enemy : public GameObject
{
	void doSomething()
	{
		getLog().write("I can log!");
	}
};



class Game
{
public:
	static Game& instance() { return instance_; }

	Log& getLog() { return *log_; }
	FileSystem& getFileSystem() { return *fileSystem_; }
	AudioPlayer& getAudioPlayer() { return *audioPlayer_; }

private:
	static Game instance_;
	Log* log_;
	FileSystem* fileSystem_;
	AudioPlayer* audioPlayer_;
};

int main()
{
	Game::instance().getAudioPlayer().play(VERY_LOUD_BANG);
}

// Game 클래스를 알고 있는 코드에서는 AudioPlayer를 Game 클래스로부터 받아서 쓰기
// Game 클래스를 모르는 코드에서는 넘겨주기(매개변수로)나 상위 클래스로부터 얻기를 통해 AudioPlayer에 접근

