@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DRAW.HPJ. >"hlp\Draw.hm"
echo. >>"hlp\Draw.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Draw.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Draw.hm"
echo. >>"hlp\Draw.hm"
echo // Prompts (IDP_*) >>"hlp\Draw.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Draw.hm"
echo. >>"hlp\Draw.hm"
echo // Resources (IDR_*) >>"hlp\Draw.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Draw.hm"
echo. >>"hlp\Draw.hm"
echo // Dialogs (IDD_*) >>"hlp\Draw.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Draw.hm"
echo. >>"hlp\Draw.hm"
echo // Frame Controls (IDW_*) >>"hlp\Draw.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Draw.hm"
REM -- Make help for Project DRAW


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Draw.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Draw.hlp" goto :Error
if not exist "hlp\Draw.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Draw.hlp" Debug
if exist Debug\nul copy "hlp\Draw.cnt" Debug
if exist Release\nul copy "hlp\Draw.hlp" Release
if exist Release\nul copy "hlp\Draw.cnt" Release
echo.
goto :done

:Error
echo hlp\Draw.hpj(1) : error: Problem encountered creating help file

:done
echo.
