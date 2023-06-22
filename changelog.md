# Changelog

## Version 1.0.2 (11/28/2022)
*	[aprip-1.0.2-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.2-windows-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.2-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.2-linux-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.2-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.2.zip)

Changes:

*   Cleaned up `cd-command-logger.sh`/`cd-command-logger.bat` and `ap-type-checker.sh`/`ap-type-checker.bat` scripts. The Windows `find` command is now executed via it's full filepath (in system32) to ensure the correct find command is being executed. It was possible in v1.0.1 that some non-standard `%PATH%` configuration could override the Windows default `find` command, breaking the `.bat` scripts.
*   Small performance increase (start searching at sector 19 instead of 0) for the bin-patcher mode has been applied.

## Version 1.0.1 (11/8/2022)
*	[aprip-1.0.1-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.1-windows-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.1-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.1-linux-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.1-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.1.zip)

Changes:

*	Limited file size max for bin patch mode to 750MB (sanity check, no actual PSX software is even close to this).

*	Added info on DuckStation 8 MB RAM setting (must be left unchecked). APrip also warns you if you try to give it an 8MB RAM dump now after the filesize mismatch error explaining what happened.

### Version 1.0 (11/4/2022)
*	[aprip-1.0-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0-windows-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0-linux-x86_64](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.zip)