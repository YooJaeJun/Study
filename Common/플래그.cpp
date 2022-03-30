
//겹치게 하고 싶기도하고, 양이 그리 많지않을때 플래그 사용
enum YJJState {
	Hungry = 1 << 0, //첫번째 비트에 1을 집어넣음. 2^n
	Happy = 1 << 1,
	Angry = 1 << 2,
	Sad = 1 << 3,
	Alone = 1 << 4,
	Together = 1 << 5,
};
struct YJJStateStruct {
	void AddState(YJJState NewState) {
	}
	bool IsHungry() const { return HasState(Hungry); }
	bool IsHappy() const { return HasState(Happy); }
	bool IsAngry() const { return HasState(Angry); }

private:
	bool HasState(YJJState CheckState) const {
		return (value & (int)CheckState) != 0;
	}

private:
	unsigned int value = 0;
};
//[1][0][0][0] [0][0][0][0] &&
//[1][0][1][0] [0][0][0][0]


int main() {
	const int fStates = Hungry | Angry;
	const bool IsHungry = (fStates & Hungry) != 0;

	return 0;
}