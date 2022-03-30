
//��ġ�� �ϰ� �ͱ⵵�ϰ�, ���� �׸� ���������� �÷��� ���
enum YJJState {
	Hungry = 1 << 0, //ù��° ��Ʈ�� 1�� �������. 2^n
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