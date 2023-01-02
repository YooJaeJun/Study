#include <bits/stdc++.h>
using namespace std;

class Framebuffer
{
public:
	Framebuffer() { clear(); }
	void clear()
	{
		for (int i = 0; i < WIDTH * HEIGHT; i++)
		{
			pixels_[i] = WHITE;
		}
	}
	void draw(int x, int y)
	{
		pixels_[(WIDTH * y) + x] = BLACK;
	}
	const char* getPixels() { return pixels_; }

private:
	static const int WIDTH = 160;
	static const int HEIGHT = 120;

	char pixels_[WIDTH * HEIGHT];
};

class Scene
{
public:
	Scene() : current_(&buffers_[0]), next_(&buffers_[1]) {}
	void draw()
	{
		next_->clear();
		next_->draw(1, 1);		next_->draw(4, 1);
		next_->draw(1, 3);		next_->draw(2, 4);
		next_->draw(3, 4);		next_->draw(4, 3);
		swap();
	}
	Framebuffer& getBuffer() { return *current_; }

private:
	void swap()
	{
		Framebuffer* temp = current_;
		current_ = next_;
		next_ = temp;
	}
	Framebuffer buffers_[2];
	Framebuffer* current_;
	Framebuffer* next_;

};



// 슬랩스틱 코미디 기반 게임 행동 시스템
/*
class Actor
{
public:
	Actor() : currentSlapped_(false) {}
	virtual ~Actor() {}
	virtual void update() = 0;

	void swap()
	{
		// 버퍼 교체
		currentSlapped_ = nextSlapped_;
		// 다음 버퍼 초기화
		nextSlapped_ = false;
	}

	// void reset() { slapped_ = false; }
	void slap() { nextSlapped_ = true; }
	bool wasSlapped() { return currentSlapped_; }

private:
	bool currentSlapped_;
	bool nextSlapped_;
};
*/
class Actor
{
public:
	static void init() { current_ = 0; }
	static void swap() { current_ = next(); }

	void slap() { slapped_[next()] = true; }
	bool wasSlapped() { return slapped_[current_]; }

private:
	static int current_;
	static int next() { return 1 - current_; }

	bool slapped_[2];
};

class Stage
{
public:
	void add(Actor* actor, int index)
	{
		actors_[index] = actor;
	}
	void update()
	{
		for (int i = 0; i < NUM_ACTORS; i++)
		{
			actors_[i]->update();
		}
		for (int i = 0; i < NUM_ACTORS; i++)
		{
			actors_[i]->swap();
		}
	}

private:
	static const int NUM_ACTORS = 3;
	Actor* actors_[NUM_ACTORS];
};

class Comedian : public Actor
{
public:
	void face(Actor* actor) { facing_ = actor; }
	virtual void update()
	{
		if (wasSlapped())
		{
			facing_->slap();
		}
	}
	
private:
	Actor* facing_;
};


int main()
{
	Comedian* harry = new Comedian();
	Comedian* baldy = new Comedian();
	Comedian* chump = new Comedian();

	harry->face(baldy);
	baldy->face(chump);
	chump->face(harry);

	Stage stage;
	stage.add(harry, 0);
	stage.add(baldy, 1);
	stage.add(chump, 2);

	harry->slap();
	stage.update();
}

