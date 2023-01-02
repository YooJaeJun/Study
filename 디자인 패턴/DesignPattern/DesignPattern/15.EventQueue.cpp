#include <bits/stdc++.h>
using namespace std;

struct PlayMessage
{
	SoundId id;
	int volume;
};

class Audio
{
public:
	static void init()
	{
		head_ = 0;
		tail_ = 0;
	}

	static void playSound(SoundId id, int volume)
	{
		// ���� ���� ��û�� �� ���캻��.
		for (int i = head_; i != tail_; i = (i + 1) % MAX_PENDING)
		{
			if (pending_[i].id == id)
			{
				// �� �߿� �Ҹ��� ū ������ �����.
				pending_[i].volume = max(volume, pending_[i].volume);
				// �� ��û�� ť�� ���� �ʴ´�.
				return;
			}
		}

		assert(tail_ < MAX_PENDING);

		// �迭 �� �ڿ� �߰��Ѵ�.
		pending_[tail_].id = id;
		pending_[tail_].volume = volume;
		tail_ = (tail_ + 1) % MAX_PENDING;
	}

	static void update()
	{
		for (int i = 0; i < numPending_; i++)
		{
			// ������ ��û�� ���ٸ� �ƹ��͵� ���� �ʴ´�.
			if (head_ == tail_) return;
			ResourceId resource = loadSound(pending_[head_].id);
			int channel = findOpenChannel();
			if (channel == -1) return;
			startSound(resource, channel, pending_[head_].volume);
			head_ = (head_ + 1) % MAX_PENDING;
		}
		numPending_ = 0;
	}

private:
	static const int MAX_PENDING = 16;
	static PlayMessage pending_[MAX_PENDING];
	static int numPending_;
	static int head_;
	static int tail_;
};

class Menu
{
public:
	void onSelect(int index)
	{
		Audio::playSound(SOUND_BLOOP, VOL_MAX);
	}
};
