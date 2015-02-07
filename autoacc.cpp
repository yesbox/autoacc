#include "stdafx.h"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	CURSORINFO cursorInfo;
	int mouseAccArray[3];

	int mouseAccEnabledSetting[] = {6, 10, 1};
	int mouseAccDisabledSetting[] = {0, 0, 0};

	while (1)
	{
		SystemParametersInfo(SPI_GETMOUSE, 0, &mouseAccArray, 0);

		cursorInfo.cbSize = sizeof(CURSORINFO);
		GetCursorInfo(&cursorInfo);

		if (cursorInfo.flags && !mouseAccArray[2])
			SystemParametersInfo(SPI_SETMOUSE, 0, &mouseAccEnabledSetting, 0);

		else if (!cursorInfo.flags && mouseAccArray[2])
			SystemParametersInfo(SPI_SETMOUSE, 0, &mouseAccDisabledSetting, 0);

		Sleep(200);
	}
}
