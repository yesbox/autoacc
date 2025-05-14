@echo off
setlocal

set "MSYS2_PATH=C:\msys64"
set "UCRT64_BIN=%MSYS2_PATH%\ucrt64\bin"
set "PATH=%UCRT64_BIN%;%PATH%"

gcc autoacc.c -o autoacc.exe ^
  -std=c23 -Werror -Wall -Wextra -Wpedantic ^
  -nostdlib -Wl,--entry=Main ^
  -Os -s -flto -Wl,--gc-sections -Wl,--strip-all ^
  -mwindows -lkernel32 -luser32