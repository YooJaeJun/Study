#include "InputHandler.h"

namespace Gungeon
{
	Command* Gungeon::InputHandler::HandleInput()
	{
		if (INPUT->KeyDown(VK_LBUTTON)) return buttonMouseL;
		if (INPUT->KeyDown(VK_RBUTTON)) return buttonMouseR;
		return nullptr;
	}
}