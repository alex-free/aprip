@echo off

echo DuckStation AP Type Checker v1.0 For Windows
echo By Alex Free
set argC=0
for %%x in (%*) do Set /A argC+=1
IF NOT "%argC%" == "2" (
	echo Error: Incorrect number of arguments given to %0%.
	echo Usage:
	echo %0% ^<duckstation .exe file^> ^<game cue file^>
	echo.
	cmd /k
)

IF NOT EXIST "%~f1" (
	echo Error: Can't open the DuckStation executable file: "%~f1"
	echo.
	pause
cmd /k
) ELSE (
	echo Got DuckStation executable: "%~f1"
)

IF NOT EXIST "%~f2" (
	echo Error: Can't open the PSX game cue file: "%~f2"
	echo.
	pause
cmd /k
) ELSE (
	echo Got PSX game cue file: "%~f2"
)

FOR /F "tokens=3 delims= " %%G IN ('REG QUERY "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Personal"') DO (SET docsdir=%%G)
set log="%docsdir%\DuckStation\duckstation.log"
del %log% 2> nul
"%~f1" "%~f2"
echo.
echo Number Of 0x19 Test Commands Sent:
find /C "CDROM executing command 0x19" %log%
echo.
find "CDROM executing command 0x19" %log%
echo.
echo Number Of 0x1E ReadTOC Commands Sent:
find /C "CDROM executing command 0x1E" %log%
echo.
find "CDROM executing command 0x1E" %log%
echo Number Of 0x13 GetTN Commands Sent:
find /C "CDROM executing command 0x13" %log%
echo.
find "CDROM executing command 0x13" %log%
echo.
echo Number Of 0x14 GetTD Commands Sent:
find /C "CDROM executing command 0x14" %log%
echo.
find "CDROM executing command 0x14" %log%