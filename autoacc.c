#include <windows.h>

bool TestAPI(int* mouseAccArray, LASTINPUTINFO* lastInput, CURSORINFO* cursorInfo) {
    bool success = true;

    for (int i = 0; i < 2; i++) {
        cursorInfo->cbSize = sizeof(CURSORINFO);
        success &= GetCursorInfo(cursorInfo);

        lastInput->cbSize = sizeof(LASTINPUTINFO);
        success &= GetLastInputInfo(lastInput);

        success &= SystemParametersInfo(SPI_GETMOUSE, 0, mouseAccArray, 0);

        int mouseAccArrayBeforeSet[3];
        for (int j = 0; j < 3; ++j) {
            mouseAccArrayBeforeSet[j] = mouseAccArray[j];
        }

        success &= SystemParametersInfo(SPI_SETMOUSE, 0, mouseAccArray, 0);

        for (int j = 0; j < 3; ++j) {
            success &= (mouseAccArray[j] == mouseAccArrayBeforeSet[j]);
        }
    }

    return success;
}

void Main(void) {
    CURSORINFO cursorInfo;
    LASTINPUTINFO lastInput;
    int mouseAccArray[3];

    if (!TestAPI(mouseAccArray, &lastInput, &cursorInfo)) {
        ExitProcess(1);
    }

    const int mouseAccEnabledSetting[] = {6, 10, 1};
    const int mouseAccDisabledSetting[] = {0, 0, 0};

    DWORD lastInputTick = 0;

    while (true) {
        lastInput.cbSize = sizeof(LASTINPUTINFO);
        GetLastInputInfo(&lastInput);

        if (lastInput.dwTime != lastInputTick) {
            lastInputTick = lastInput.dwTime;

            cursorInfo.cbSize = sizeof(CURSORINFO);
            GetCursorInfo(&cursorInfo);

            SystemParametersInfo(SPI_GETMOUSE, 0, &mouseAccArray, 0);

            const bool cursorHidden = (cursorInfo.flags == 0);
            const bool accEnabled   = (mouseAccArray[2] == mouseAccEnabledSetting[2]);

            if (!cursorHidden && !accEnabled) {
                SystemParametersInfo(SPI_SETMOUSE, 0, (int*)mouseAccEnabledSetting, 0);
            }
            else if (cursorHidden && accEnabled) {
                SystemParametersInfo(SPI_SETMOUSE, 0, (int*)mouseAccDisabledSetting, 0);
            }
        }

        Sleep(200);
    }
}