#pragma once

namespace Gungeon
{
	class Command;

	class InputHandler
	{
	public:
		Command* HandleInput();

	private:
		Command* buttonMouseL;
		Command* buttonMouseR;
		Command* buttonW;
		Command* buttonA;
		Command* buttonS;
		Command* buttonD;
	};
}
