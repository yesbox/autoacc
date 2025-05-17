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

void EnableEfficiencyMode(void) {
    THREAD_POWER_THROTTLING_STATE power = {};

    power.Version     = THREAD_POWER_THROTTLING_CURRENT_VERSION;
    power.ControlMask = THREAD_POWER_THROTTLING_EXECUTION_SPEED;
    power.StateMask   = THREAD_POWER_THROTTLING_EXECUTION_SPEED;

    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
    SetProcessInformation(GetCurrentProcess(), ProcessPowerThrottling, &power, sizeof(power));
}

void Main(void) {
    CURSORINFO cursorInfo;
    LASTINPUTINFO lastInput;
    int mouseAccArray[3];

    if (!TestAPI(mouseAccArray, &lastInput, &cursorInfo)) {
        ExitProcess(1);
    }

    EnableEfficiencyMode();
    SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);

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