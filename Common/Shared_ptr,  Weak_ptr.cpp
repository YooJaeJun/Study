//shared_ptr	순환참조 때 소멸자 호출 안 하는 문제
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
		// 이 user는 이 스코프 안에서 소멸되지만,
		// 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
		shared_ptr<User> user(new User);

		// 아래 과정에서 순환 참조가 발생한다.
		party->AddMember(user);
		user->SetParty(party);
	}

	// 여기에서 party.reset을 수행해 보지만,
	// 5명의 파티원이 party 객체를 물고 있어 아직 refCount = 5 의 상태
	// 따라서, party가 소멸되지 못하고, party의 vector에 저장된 user 객체들 역시 소멸되지 못한다.
	party.reset();

	return 0;
}





//weak_ptr	개선안
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
		// 이 user는 이 스코프 안에서 소멸되지만,
		// 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
		shared_ptr<User> user(new User);

		// 아래 과정에서 순환 참조가 발생한다.
		party->AddMember(user);
		user->SetParty(party);
	}

	// 여기에서 party.reset을 수행해 보지만,
	// 5명의 파티원이 party 객체를 물고 있어 아직 refCount = 5 의 상태
	// 따라서, party가 소멸되지 못하고, party의 vector에 저장된 user 객체들 역시 소멸되지 못한다.
	party.reset();

	return 0;
}