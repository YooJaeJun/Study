#pragma once

// Command ∆–≈œ
namespace Gungeon
{
	class Character;

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Character* character) = 0;
		virtual void undo() = 0;
	};
}
