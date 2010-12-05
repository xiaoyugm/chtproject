# Microsoft Developer Studio Project File - Name="KJMonitor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KJMonitor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KJMonitor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KJMonitor.mak" CFG="KJMonitor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KJMonitor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KJMonitor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KJMonitor - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /i "../include" /i "Nport.lib" /d "DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../lib/KJMonitor.exe"

!ELSEIF  "$(CFG)" == "KJMonitor - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KJMonitor - Win32 Release"
# Name "KJMonitor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddrPointScanStatusDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AnologInput.cpp
# End Source File
# Begin Source File

SOURCE=.\AnologOutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BackupSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BitCmdCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CommParaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CommStatusFM.cpp
# End Source File
# Begin Source File

SOURCE=.\CommStatusPointDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlCmdDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgModify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewR.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit12ModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditWatchPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\FMMonitorPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\IcoControl.cpp
# End Source File
# Begin Source File

SOURCE=.\KJMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\KJMonitor.hpj

!IF  "$(CFG)" == "KJMonitor - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__KJMON="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=KJMonitor
InputPath=.\hlp\KJMonitor.hpj
InputName=KJMonitor

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "KJMonitor - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__KJMON="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=KJMonitor
InputPath=.\hlp\KJMonitor.hpj
InputName=KJMonitor

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KJMonitor.rc
# End Source File
# Begin Source File

SOURCE=.\KJMonitorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\KJMonitorView.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MonitorPointThread.cpp
# End Source File
# Begin Source File

SOURCE=.\MQClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MQServer.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PointEditAnologIn.cpp
# End Source File
# Begin Source File

SOURCE=.\PointEditSwitchIn.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPortVsTrunkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SyncDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TabView.cpp
# End Source File
# Begin Source File

SOURCE=.\TrunkAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\UserPasswdDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewDeleteAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\warncauseeditdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WarningWin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddrPointScanStatusDlg.h
# End Source File
# Begin Source File

SOURCE=.\AnologInput.h
# End Source File
# Begin Source File

SOURCE=.\AnologOutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BackupSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\BitCmdCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\CommParaDlg.h
# End Source File
# Begin Source File

SOURCE=.\CommStatusFM.h
# End Source File
# Begin Source File

SOURCE=.\CommStatusPointDlg.h
# End Source File
# Begin Source File

SOURCE=.\CtrlCmdDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgModify.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewR.h
# End Source File
# Begin Source File

SOURCE=.\Edit12ModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditWatchPoint.h
# End Source File
# Begin Source File

SOURCE=.\FMMonitorPoint.h
# End Source File
# Begin Source File

SOURCE=.\IcoControl.h
# End Source File
# Begin Source File

SOURCE=.\KJMonitor.h
# End Source File
# Begin Source File

SOURCE=.\KJMonitorDoc.h
# End Source File
# Begin Source File

SOURCE=.\KJMonitorView.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MonitorPointThread.h
# End Source File
# Begin Source File

SOURCE=.\MQClient.h
# End Source File
# Begin Source File

SOURCE=.\MQCommandType.h
# End Source File
# Begin Source File

SOURCE=.\MQServer.h
# End Source File
# Begin Source File

SOURCE=.\OutputBar.h
# End Source File
# Begin Source File

SOURCE=.\PointEditAnologIn.h
# End Source File
# Begin Source File

SOURCE=.\PointEditSwitchIn.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "KJMonitor - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=KJMonitor
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "KJMonitor - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=KJMonitor
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetPortVsTrunkDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SyncDlg.h
# End Source File
# Begin Source File

SOURCE=.\TabDoc.h
# End Source File
# Begin Source File

SOURCE=.\TabView.h
# End Source File
# Begin Source File

SOURCE=.\TrunkAdd.h
# End Source File
# Begin Source File

SOURCE=.\UserPasswdDlg.h
# End Source File
# Begin Source File

SOURCE=.\ViewDeleteAddr.h
# End Source File
# Begin Source File

SOURCE=.\warncauseeditdlg.h
# End Source File
# Begin Source File

SOURCE=.\WarningWin.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\ADD.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\ADD1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\ADDdeselect.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ADDdeselect1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ADDSingle.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ADDSingle1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\anologvaluein.ico
# End Source File
# Begin Source File

SOURCE=.\RES\anologvalueout.ico
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Cancel0132x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Cancel32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\RES\CLOSE1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\CommSet.ico
# End Source File
# Begin Source File

SOURCE=.\RES\comserialctrledit.ico
# End Source File
# Begin Source File

SOURCE=.\RES\comserialmonitor.ico
# End Source File
# Begin Source File

SOURCE=.\RES\comstarttimeedit.ico
# End Source File
# Begin Source File

SOURCE=.\RES\CUSTOM.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\CUSTOM1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\CUSTOM2.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\database1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\DATETIME.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\Display.ico
# End Source File
# Begin Source File

SOURCE=.\RES\DisplayClear.ico
# End Source File
# Begin Source File

SOURCE=.\RES\excel.ico
# End Source File
# Begin Source File

SOURCE=.\RES\EXIT.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\gasmonitor.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Halloween1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Halloween2.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Help.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ICON_TAB.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\iconhall.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Imgstatus.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\ImgTab.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\ImgView.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Item1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Item2.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Item5.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ItemLoadFile.ico
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Keymanager.ico
# End Source File
# Begin Source File

SOURCE=.\res\KJMonitor.ico
# End Source File
# Begin Source File

SOURCE=.\res\KJMonitor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\KJMonitorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\LedOff.ico
# End Source File
# Begin Source File

SOURCE=.\RES\LedOn.ico
# End Source File
# Begin Source File

SOURCE=.\RES\LEDON1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\Left32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Login.ico
# End Source File
# Begin Source File

SOURCE=.\RES\LOGININ.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\microphone.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Network.ico
# End Source File
# Begin Source File

SOURCE=.\RES\NEW.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NNNN.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\OK.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\OK.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\OPEN1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\owner1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\PRINTER.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\RecycleGreen.ico
# End Source File
# Begin Source File

SOURCE=.\RES\RecycleRed.ico
# End Source File
# Begin Source File

SOURCE=.\RES\reginctrledit.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Right32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Robustech.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\savecustom.ico
# End Source File
# Begin Source File

SOURCE=.\RES\SaveIco.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Search.ico
# End Source File
# Begin Source File

SOURCE=.\RES\SORT.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\sound1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\soundbox.ico
# End Source File
# Begin Source File

SOURCE=.\RES\soundplay.gif
# End Source File
# Begin Source File

SOURCE=.\RES\START.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\STOP.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\STOP1.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\SwitchValueInEdit.ico
# End Source File
# Begin Source File

SOURCE=.\RES\SwitchValueOutEdit.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem10.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem2.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem3.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem4.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem5.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem6.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem8.ico
# End Source File
# Begin Source File

SOURCE=.\RES\tableitem9.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\userpassword.ico
# End Source File
# Begin Source File

SOURCE=.\RES\WarnEdit.ico
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxDb.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleSv.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\KJMonitor.cnt

!IF  "$(CFG)" == "KJMonitor - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\KJMonitor.cnt
InputName=KJMonitor

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "KJMonitor - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\KJMonitor.cnt
InputName=KJMonitor

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Group "SQL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SQL\SQLColumn.cpp
# End Source File
# Begin Source File

SOURCE=.\SQL\SQLColumn.h
# End Source File
# Begin Source File

SOURCE=.\SQL\SQLDirect.cpp
# End Source File
# Begin Source File

SOURCE=.\SQL\SQLDirect.h
# End Source File
# Begin Source File

SOURCE=.\SQL\String2DataType.cpp
# End Source File
# Begin Source File

SOURCE=.\SQL\String2DataType.h
# End Source File
# End Group
# Begin Group "Com"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Com\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\Com\SerialPort.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Controls\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\Controls\Drawgdix.h
# End Source File
# Begin Source File

SOURCE=.\Controls\editex.cxx
# End Source File
# Begin Source File

SOURCE=.\Controls\MABString.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\MABString.h
# End Source File
# Begin Source File

SOURCE=.\Controls\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\Controls\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\Controls\ProgressCtrlX.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\ProgressCtrlX.h
# End Source File
# Begin Source File

SOURCE=.\Controls\ThemeHelperST.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\ThemeHelperST.h
# End Source File
# Begin Source File

SOURCE=.\Controls\WatchBarList.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\WatchBarList.h
# End Source File
# Begin Source File

SOURCE=.\Controls\XPStyleButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls\XPStyleButtonST.h
# End Source File
# End Group
# Begin Group "FlatTab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FlatTab\ColorListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTab\ColorListBox.h
# End Source File
# Begin Source File

SOURCE=.\FlatTab\EditCtrlForFlatTab.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTab\EditCtrlForFlatTab.h
# End Source File
# Begin Source File

SOURCE=.\FlatTab\ListCtrlForFlatTab.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTab\ListCtrlForFlatTab.h
# End Source File
# Begin Source File

SOURCE=.\FlatTab\OutputBarEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTab\OutputBarEdit.h
# End Source File
# Begin Source File

SOURCE=.\FlatTab\TreeCtrlForFlatTab.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTab\TreeCtrlForFlatTab.h
# End Source File
# End Group
# Begin Group "NDK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NDK\NDKClient.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKClient.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKDataBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKDataBuffer.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKDefines.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKMessage.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKMessageData.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKMessageData.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKServer.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKServer.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKUser.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKUser.h
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKUserManager.cpp
# End Source File
# Begin Source File

SOURCE=.\NDK\NDKUserManager.h
# End Source File
# End Group
# Begin Group "NPORT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NPORT\Nport.h
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Others\errorprint.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\errorprint.h
# End Source File
# Begin Source File

SOURCE=.\Others\excel9.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\excel9.h
# End Source File
# Begin Source File

SOURCE=.\Others\iniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\iniFile.h
# End Source File
# Begin Source File

SOURCE=.\Others\SoundBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\SoundBase.h
# End Source File
# Begin Source File

SOURCE=.\Others\soundBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\soundBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Others\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\Others\Splash.h
# End Source File
# End Group
# Begin Group "Sequence"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Sequence\DialogFeg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\DialogFeg.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogR.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogR.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogspumonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogspumonitor.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogtime.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\dialogtime.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\Sequence.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\shixuDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\shixuDlg.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\spu_temp.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\Spudetailed_me.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\Spudetailed_me.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\SpuEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\SpuEdit.h
# End Source File
# Begin Source File

SOURCE=.\Sequence\SpuInform.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence\SpuInform.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\KJMonitor.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
