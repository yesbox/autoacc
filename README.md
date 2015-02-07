# autoacc
Automatically manages the Windows mouse acceleration (also known as enhanced pointer precision).

## Why?
If you perfer to keep Windows mouse acceleration enabled on the desktop but not in legacy Windows games that doesn't use raw input to bypass the Windows mouse filters.

## How?
The program runs in the background and detects if the native Windows cursor becomes hidden. If hidden, the mouse acceleration will become disabled. When visible, it will become enabled.

## What else?
Compiled with Visual Studio and tested on Windows 7 and Windows 8.1.
To set the mouse acceleration manually, open the mouse properties from the control panel and navigate to the pointer options. There is setting for enhanced pointer precision. When enabled (this is the default) mouse acceleration turned on.

## Where do I get it?
https://github.com/yesbox/autoacc/releases
