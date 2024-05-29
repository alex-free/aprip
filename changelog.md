# [Aprip](readme.md) -> Changelog

## Version 1.0.8 (5/28/2024)

Changes:

*   Implemented [sector user data compare function](#comparing-cd-images). This allows you to display only differences in user data (and not ECC/EDC) between i.e. an unmodified disc image vs a patched one.

*    Implemented [Aprip-style patch creation/applicator functions](#creating-aprip-style-patches). An APrip-style patch searches all sector user data for a pattern of bytes and then patches specific bytes in the pattern (pre-defined in the patch) without using known offsets. It can be used to 'port' patch methods.

----------------------------------------------------

*	[aprip-v1.0.8-windows-i686-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-windows-i686-static.zip) _Portable Release For Windows 95 OSR 2.5 and above, Pentium CPU minimum (32 bit)_

*	[aprip-v1.0.8-windows-x86\_64-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-windows-x86_64-static.zip) _Portable Release For x86_64 Windows (64 bit)_

*	[aprip-v1.0.8-linux-i386-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-linux-i386-static.zip) _Portable Release For Linux 3.2.0 and above, 386 CPU minimum (32 bit)_

*	[aprip-v1.0.8-linux-i386-static.deb](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-linux-i386-static.deb) _Deb package file For Linux 3.2.0 and above, 386 CPU minimum (32 bit)_

*	[aprip-v1.0.8-linux-x86\_64-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-linux-x86_64-static.zip) _Portable Release For x86\_64 Linux 3.2.0 and above (64 bit)_

*	[aprip-v1.0.8-linux-x86\_64-static.deb](https://github.com/alex-free/aprip/releases/download/v1.0.8/aprip-v1.0.8-linux-x86_64-static.deb) _Deb package file for x86_64 Linux 3.2.0 and above (64 bit)_

---------------------------------------

## Version 1.0.7 (4/2/2024)

Changes:

*   Implemented Append No Swap Bypass (By  mdmdj) for disc image patcher mode. This only currently supports the [Append Discs](https://remywiki.com/APPEND_DISC) [Beat Mania Append GottaMix](http://redump.org/disc/3550/) and [Beat Mania Append 3rdMix](http://redump.org/disc/2306/), allowing them to work without a [Key Disc](https://remywiki.com/KEY_DISC).

*   Implemented my new [EzRe](https://github.com/alex-free/ezre) build system.

----------------------------------------------------

*	[aprip-v1.0.7-windows-i686-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-windows-i686-static.zip) _Portable Release For Windows 95 OSR 2.5 and above, Pentium CPU minimum (32 bit)_

*	[aprip-v1.0.7-windows-x86\_64-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-windows-x86_64-static.zip) _Portable Release For x86_64 Windows (64 bit)_

*	[aprip-v1.0.7-linux-i386-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-linux-i386-static.zip) _Portable Release For Linux 3.2.0 and above, 386 CPU minimum (32 bit)_

*	[aprip-v1.0.7-linux-i386-static.deb](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-linux-i386-static.deb) _Deb package file For Linux 3.2.0 and above, 386 CPU minimum (32 bit)_

*	[aprip-v1.0.7-linux-x86\_64-static.zip](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-linux-x86_64-static.zip) _Portable Release For x86\_64 Linux 3.2.0 and above (64 bit)_

*	[aprip-v1.0.7-linux-x86\_64-static.deb](https://github.com/alex-free/aprip/releases/download/v1.0.7/aprip-v1.0.7-linux-x86_64-static.deb) _Deb package file for x86_64 Linux 3.2.0 and above (64 bit)_

---------------------------------------

## Version 1.0.6 (11/6/2023)

*	[aprip-v1.0.6-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.6/aprip-v1.0.6-windows-x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-v1.0.6-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.6/aprip-v1.0.6-windows-x86_64.zip) _For 64-bit Windows_
*	[aprip-v1.0.6-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.6/aprip-v1.0.6-linux-x86_static.zip) _For x86 Linux Distros_
*	[aprip-v1.0.6-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.6/aprip-v1.0.6-linux-x86_64_static.zip) _For x86\_64 Linux Distros_
*	[aprip-1.0.6-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.6.zip)

Changes:

*	Added support for my Zero APv1 bypass for GameShark code generation and CD image BIN file patching.

*   Added support for the Fake PAL APv2 bypass for GameShark code generation and CD image BIN file patching.

*	Added support for B.A.D's LibCrypt v2 bypass for GameShark code generation and CD image BIN file patching.

## Version 1.0.5 (6/26/2023)

*	[aprip-1.0.5-windows\_x86](https://github.com/alex-free/aprip/releases/download/v1.0.5/aprip-1.0.5-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.5-windows\_x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.5/aprip-1.0.5-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.5-linux\_x86](https://github.com/alex-free/aprip/releases/download/v1.0.5/aprip-1.0.5-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.5-linux\_x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.5/aprip-1.0.5-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.5-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.5.zip)

Changes:

*	Removed broken non-stealth mod-chip APv1/APv2 patching.

*   Improved and cleaned up code, enabling build on Pop!OS.

*   Added info on [EDC](#edc) Protected games.

## Version 1.0.4

*	[aprip-1.0.4-windows\_x86](https://github.com/alex-free/aprip/releases/download/v1.0.4/aprip-1.0.4-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.4-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.4/aprip-1.0.4-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.4-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.4/aprip-1.0.4-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.4-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.4/aprip-1.0.4-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.4-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.4.zip)

Changes:

*	Added support for LibCrypt v1 CD image patching (all the PAL regional releases of MediEvil now work)!

## Version 1.0.3 (6/22/2023)

*	[aprip-1.0.3-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.3/aprip-1.0.3-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.3-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.3/aprip-1.0.3-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.3-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.3/aprip-1.0.3-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.3-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.3/aprip-1.0.3-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.3-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.3.zip)

Changes:

*	Added support for LibCrypt 2 CD image patching.

*   Substantial documentation rewrite.

## Version 1.0.2 (11/28/2022)
*	[aprip-1.0.2-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.2-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.2-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.2-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.2/aprip-1.0.2-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.2-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.2.zip)

Changes:

*   Cleaned up `cd-command-logger.sh`/`cd-command-logger.bat` and `ap-type-checker.sh`/`ap-type-checker.bat` scripts. The Windows `find` command is now executed via it's full filepath (in system32) to ensure the correct find command is being executed. It was possible in v1.0.1 that some non-standard `%PATH%` configuration could override the Windows default `find` command, breaking the `.bat` scripts.
*   Small performance increase (start searching at sector 19 instead of 0) for the bin-patcher mode has been applied.

## Version 1.0.1 (11/8/2022)
*	[aprip-1.0.1-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0.1-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0.1-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0.1-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0.1/aprip-1.0.1-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0.1-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.1.zip)

Changes:

*	Limited file size max for bin patch mode to 750MB (sanity check, no actual PSX software is even close to this).

*	Added info on DuckStation 8 MB RAM setting (must be left unchecked). APrip also warns you if you try to give it an 8MB RAM dump now after the filesize mismatch error explaining what happened.

### Version 1.0 (11/4/2022)
*	[aprip-1.0-windows-x86](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-windows_x86.zip) _For Windows 95 OSR 2.5 Or Newer (32-bit Windows)_
*	[aprip-1.0-windows-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-windows_x86_64.zip) _For 64-bit Windows_
*	[aprip-1.0-linux-x86](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-linux_x86_static.zip) _For x86 Linux Distros_
*	[aprip-1.0-linux-x86\_64](https://github.com/alex-free/aprip/releases/download/v1.0/aprip-1.0-linux_x86_64_static.zip) _For x86_64 Linux Distros_
*	[aprip-1.0-source](https://github.com/alex-free/aprip/archive/refs/tags/v1.0.zip)