//shared_ptr	��ȯ���� �� �Ҹ��� ȣ�� �� �ϴ� ����
#include <iostream>
#include <memory>    // for shared_ptr
#include <vector>
#include <string>
using namespace std;

class User;

class Party
{
public:
	Party() {
		std::cout << "Party ctor\n";
	}
	~Party() {
		std::cout << "Party ctor\n";
		m_MemberList.clear();
	}

public:
	void AddMember(const shared_ptr<User>& member)
	{
		m_MemberList.push_back(member);
		int d = 0;
	}

	const string& GetPartyName() const { return PartyName; }
private:
	typedef vector<shared_ptr<User>> MemberList;
	MemberList m_MemberList;
	string PartyName;
};

class User
{
public:
	User() {
		std::cout << "User ctor\n";
	}
	~User() {
		std::cout << "User dtor\n";
	}

	void SetParty(const shared_ptr<Party>& party)
	{
		m_Party = party;
	}

	string GetPartyName() const {
		if (m_Party)
		{
			return m_Party->GetPartyName();
		}
		return "";
	}

private:
	shared_ptr<Party> m_Party;
};


int main()
{
	shared_ptr<Party> party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// �� user�� �� ������ �ȿ��� �Ҹ������,
		// �Ʒ� party->AddMember�� ���� �� �������� ����Ǿ user�� refCount = 1
		shared_ptr<User> user(new User);

		// �Ʒ� �������� ��ȯ ������ �߻��Ѵ�.
		party->AddMember(user);
		user->SetParty(party);
	}

	// ���⿡�� party.reset�� ������ ������,
	// 5���� ��Ƽ���� party ��ü�� ���� �־� ���� refCount = 5 �� ����
	// ����, party�� �Ҹ���� ���ϰ�, party�� vector�� ����� user ��ü�� ���� �Ҹ���� ���Ѵ�.
	party.reset();

	return 0;
}





//weak_ptr	������
#include <iostream>
#include <memory>    // for shared_ptr
#include <vector>
#include <string>
using namespace std;

class User;

class Party
{
public:
	Party() {
		std::cout << "Party ctor\n";
	}
	~Party() {
		std::cout << "Party ctor\n";
		m_MemberList.clear();
	}

public:
	void AddMember(const shared_ptr<User>& member)
	{
		m_MemberList.push_back(member);
		int d = 0;
	}

	const string& GetPartyName() const { return PartyName; }
private:
	typedef vector<shared_ptr<User>> MemberList;
	MemberList m_MemberList;
	string PartyName;
};

class User
{
public:
	User() {
		std::cout << "User ctor\n";
	}
	~User() {
		std::cout << "User dtor\n";
	}

	void SetParty(const shared_ptr<Party>& party)
	{
		m_Party = party;
	}

	string GetPartyName() const {
		if (auto LockParty = m_Party.lock())
		{
			return LockParty->GetPartyName();
		}
		return "";
	}

private:
	weak_ptr<Party> m_Party;
};


int main()
{
	shared_ptr<Party> party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// �� user�� �� ������ �ȿ��� �Ҹ������,
		// �Ʒ� party->AddMember�� ���� �� �������� ����Ǿ user�� refCount = 1
		shared_ptr<User> user(new User);

		// �Ʒ� �������� ��ȯ ������ �߻��Ѵ�.
		party->AddMember(user);
		user->SetParty(party);
	}

	// ���⿡�� party.reset�� ������ ������,
	// 5���� ��Ƽ���� party ��ü�� ���� �־� ���� refCount = 5 �� ����
	// ����, party�� �Ҹ���� ���ϰ�, party�� vector�� ����� user ��ü�� ���� �Ҹ���� ���Ѵ�.
	party.reset();

	return 0;
}