#include <stdio.h>
#include "Turboc.h"

void main()
{
	int x, y;
	int ch;
	char munja = '#';
	x = 40;
	y = 10;
	clrscr();

	for (;;)
	{
		gotoxy(x, y);
		_putch(munja);
		ch = _getch();
		if (ch == 0xE0 || ch == 0)
		{
			ch = _getch();
			switch (ch)
			{
			case 75:
				if (x > 0) x = x - 1;
				else x = 79;
				break;
			case 77:
				if (x < 79) x = x + 1;
				else x = 0;
				break;
			case 72:
				if (y > 0) y = y - 1;
				else y = 24;
				break;
			case 80:
				if (y < 24) y = y + 1;
				else y = 0;
				break;
			default:
				_putch('\a');
				break;
			}
		}
		else
		{
			switch (ch)
			{
			case ' ':
				clrscr();
				break;
			case 'q':
			case 'Q':
				exit(0);
			case '1':
				munja = '$';
				break;
			case '2':
				munja = '@';
				break;
			case '3':
				munja = '#';
				break;
			case '4':
				munja = ' ';
				break;
			}
		}
	}
}