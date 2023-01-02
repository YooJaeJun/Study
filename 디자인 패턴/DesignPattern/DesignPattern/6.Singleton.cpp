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
		// �Ҵ��� ���� IO API ���
	}
	virtual void writeFile(char* path, char* contents)
	{
		// �Ҵ��� ���� IO API ���
	}
};

// ���ٵ� �� �� �ٸ� �÷����� ���
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

// ��Ÿ�ӿ� �ν��Ͻ� ������ Ȯ���Ѵٴ� �� ����



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

// Game Ŭ������ �˰� �ִ� �ڵ忡���� AudioPlayer�� Game Ŭ�����κ��� �޾Ƽ� ����
// Game Ŭ������ �𸣴� �ڵ忡���� �Ѱ��ֱ�(�Ű�������)�� ���� Ŭ�����κ��� ��⸦ ���� AudioPlayer�� ����

