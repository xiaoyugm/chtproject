@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by KJMONITOR.HPJ. >"hlp\KJMonitor.hm"
echo. >>"hlp\KJMonitor.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\KJMonitor.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\KJMonitor.hm"
echo. >>"hlp\KJMonitor.hm"
echo // Prompts (IDP_*) >>"hlp\KJMonitor.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\KJMonitor.hm"
echo. >>"hlp\KJMonitor.hm"
echo // Resources (IDR_*) >>"hlp\KJMonitor.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\KJMonitor.hm"
echo. >>"hlp\KJMonitor.hm"
echo // Dialogs (IDD_*) >>"hlp\KJMonitor.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\KJMonitor.hm"
echo. >>"hlp\KJMonitor.hm"
echo // Frame Controls (IDW_*) >>"hlp\KJMonitor.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\KJMonitor.hm"
REM -- Make help for Project KJMONITOR


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\KJMonitor.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\KJMonitor.hlp" goto :Error
if not exist "hlp\KJMonitor.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\KJMonitor.hlp" Debug
if exist Debug\nul copy "hlp\KJMonitor.cnt" Debug
if exist Release\nul copy "hlp\KJMonitor.hlp" Release
if exist Release\nul copy "hlp\KJMonitor.cnt" Release
echo.
goto :done

:Error
echo hlp\KJMonitor.hpj(1) : error: Problem encountered creating help file

:done
echo.
