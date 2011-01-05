# Microsoft Developer Studio Project File - Name="GUI_VisualStudio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GUI_VisualStudio - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GUI_VisualStudio_vc60.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GUI_VisualStudio_vc60.mak" CFG="GUI_VisualStudio - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GUI_VisualStudio - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GUI_VisualStudio - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "GUI_VisualStudio - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "GUI_VisualStudio - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release/vc60"
# PROP BASE Intermediate_Dir "Release/vc60"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/vc60"
# PROP Intermediate_Dir "Release/vc60"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /Zm200 /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "AboutDlg" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "AboutDlg" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"bin/vc60/RSDRAW-YRun.EXE"

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug/vc60"
# PROP BASE Intermediate_Dir "Debug/vc60"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/vc60"
# PROP Intermediate_Dir "Debug/vc60"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "AboutDlg" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_MBCS" /FR /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "AboutDlg" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"bin/vc60/RSDRAW-YRunD.EXE" /pdbtype:sept

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GUI_VisualStudio___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "GUI_VisualStudio___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release/vc60"
# PROP Intermediate_Dir "Unicode_Release/vc60"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../../Source" /I "../../AboutDlg" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /Zm200 /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../Source" /I "../../AboutDlg" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /i "../../../Source" /i "../../AboutDlg" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "../../../Source" /i "../../AboutDlg" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"../../../bin/vc60/GUI_VisualStudio.exe" /libpath:"../../../lib/vc60"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"../../../bin/vc60/GUI_VisualStudioU.exe" /libpath:"../../../lib/vc60"

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GUI_VisualStudio___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "GUI_VisualStudio___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug/vc60"
# PROP Intermediate_Dir "Unicode_Debug/vc60"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../Source" /I "../../AboutDlg" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../Source" /I "../../AboutDlg" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /i "../../../Source" /i "../../AboutDlg" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "AboutDlg" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../../../bin/vc60/GUI_VisualStudioD.exe" /pdbtype:sept /libpath:"../../../lib/vc60"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"../../../bin/vc60/GUI_VisualStudioUD.exe" /pdbtype:sept /libpath:"../../../lib/vc60"

!ENDIF 

# Begin Target

# Name "GUI_VisualStudio - Win32 Release"
# Name "GUI_VisualStudio - Win32 Debug"
# Name "GUI_VisualStudio - Win32 Unicode Release"
# Name "GUI_VisualStudio - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdjustDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTime.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassViewPane.cpp
# End Source File
# Begin Source File

SOURCE=.\DASafeMehod.cpp
# End Source File
# Begin Source File

SOURCE=.\DCH5m.cpp
# End Source File
# Begin Source File

SOURCE=.\DListEXT.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicHelpView.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\FormDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI_OutlookView.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudio.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudio.rc
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudioDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudioView.cpp
# End Source File
# Begin Source File

SOURCE=.\LangPreviewView.cpp
# End Source File
# Begin Source File

SOURCE=.\MadeCertView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MFClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MSClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MSServer.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputPane.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesPane.cpp
# End Source File
# Begin Source File

SOURCE=.\RTDataManage.cpp
# End Source File
# Begin Source File

SOURCE=.\SafeMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\SolutionExplorerPane.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TimerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\XProgressWnd.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdjustDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ClassTime.h
# End Source File
# Begin Source File

SOURCE=.\ClassViewPane.h
# End Source File
# Begin Source File

SOURCE=.\DASafeMehod.h
# End Source File
# Begin Source File

SOURCE=.\DCH5m.h
# End Source File
# Begin Source File

SOURCE=.\DListEXT.h
# End Source File
# Begin Source File

SOURCE=.\DynamicHelpView.h
# End Source File
# Begin Source File

SOURCE=.\DynamicMenu.h
# End Source File
# Begin Source File

SOURCE=.\FormDraw.h
# End Source File
# Begin Source File

SOURCE=.\GUI_OutlookView.h
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudio.h
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudioDoc.h
# End Source File
# Begin Source File

SOURCE=.\GUI_VisualStudioView.h
# End Source File
# Begin Source File

SOURCE=.\LangPreviewView.h
# End Source File
# Begin Source File

SOURCE=.\MadeCertView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MFClient.h
# End Source File
# Begin Source File

SOURCE=.\MSClient.h
# End Source File
# Begin Source File

SOURCE=.\MSServer.h
# End Source File
# Begin Source File

SOURCE=.\OutputPane.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesPane.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RTDataManage.h
# End Source File
# Begin Source File

SOURCE=.\SafeMethod.h
# End Source File
# Begin Source File

SOURCE=.\SolutionExplorerPane.h
# End Source File
# Begin Source File

SOURCE=.\SplashWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TimerThread.h
# End Source File
# Begin Source File

SOURCE=.\XProgressWnd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CjSample.ico
# End Source File
# Begin Source File

SOURCE=.\res\clear.gif
# End Source File
# Begin Source File

SOURCE=.\res\col_0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\col_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\col_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctxhelp_hide.gif
# End Source File
# Begin Source File

SOURCE=.\res\ctxhelp_show.gif
# End Source File
# Begin Source File

SOURCE=.\res\ctxsample_hide.gif
# End Source File
# Begin Source File

SOURCE=.\res\ctxsample_show.gif
# End Source File
# Begin Source File

SOURCE=.\res\dynamic_help.htm
# End Source File
# Begin Source File

SOURCE=.\res\FullScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\grip_closed.cur
# End Source File
# Begin Source File

SOURCE=.\res\grip_open.cur
# End Source File
# Begin Source File

SOURCE=.\res\GUI_VisualStudio.ico
# End Source File
# Begin Source File

SOURCE=.\res\GUI_VisualStudio.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GUI_VisualStudioDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\iconMA.ico
# End Source File
# Begin Source File

SOURCE=.\res\img_classtree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\img_filetree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\img_restree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\loupe.cur
# End Source File
# Begin Source File

SOURCE=.\res\loupe_minus.CUR
# End Source File
# Begin Source File

SOURCE=.\res\loupe_plus.CUR
# End Source File
# Begin Source File

SOURCE=.\res\MenuBar.png
# End Source File
# Begin Source File

SOURCE=.\res\msword_draft.ico
# End Source File
# Begin Source File

SOURCE=.\res\msword_fullscreen.ico
# End Source File
# Begin Source File

SOURCE=.\res\msword_outline.ico
# End Source File
# Begin Source File

SOURCE=.\res\msword_print.ico
# End Source File
# Begin Source File

SOURCE=.\res\msword_web.ico
# End Source File
# Begin Source File

SOURCE=.\res\PaneProperties.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\res\SolutionExplorerPane.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\ThemeBar.png
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.png
# End Source File
# Begin Source File

SOURCE=.\res\toolbary.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Web.png
# End Source File
# End Group
# Begin Group "EditConfig"

# PROP Default_Filter ""
# Begin Group "Schemas"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Config\Schemas\_cpp.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_cpp.schclass

"$(TargetDir)\EditConfig\Schemas\_cpp.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_cpp.schclass

"$(TargetDir)\EditConfig\Schemas\_cpp.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_cpp.schclass

"$(TargetDir)\EditConfig\Schemas\_cpp.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_cpp.schclass

"$(TargetDir)\EditConfig\Schemas\_cpp.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_HTML_ASP.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_HTML_ASP.schclass

"$(TargetDir)\EditConfig\Schemas\_HTML_ASP.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_HTML_ASP.schclass

"$(TargetDir)\EditConfig\Schemas\_HTML_ASP.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_HTML_ASP.schclass

"$(TargetDir)\EditConfig\Schemas\_HTML_ASP.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_HTML_ASP.schclass

"$(TargetDir)\EditConfig\Schemas\_HTML_ASP.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_ini.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_ini.schclass

"$(TargetDir)\EditConfig\Schemas\_ini.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_ini.schclass

"$(TargetDir)\EditConfig\Schemas\_ini.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_ini.schclass

"$(TargetDir)\EditConfig\Schemas\_ini.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_ini.schclass

"$(TargetDir)\EditConfig\Schemas\_ini.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_nsi.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_nsi.schclass

"$(TargetDir)\EditConfig\Schemas\_nsi.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_nsi.schclass

"$(TargetDir)\EditConfig\Schemas\_nsi.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_nsi.schclass

"$(TargetDir)\EditConfig\Schemas\_nsi.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_nsi.schclass

"$(TargetDir)\EditConfig\Schemas\_nsi.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_pascal.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_pascal.schclass

"$(TargetDir)\EditConfig\Schemas\_pascal.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_pascal.schclass

"$(TargetDir)\EditConfig\Schemas\_pascal.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_pascal.schclass

"$(TargetDir)\EditConfig\Schemas\_pascal.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_pascal.schclass

"$(TargetDir)\EditConfig\Schemas\_pascal.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_schclass.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_schclass.schclass

"$(TargetDir)\EditConfig\Schemas\_schclass.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_schclass.schclass

"$(TargetDir)\EditConfig\Schemas\_schclass.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_schclass.schclass

"$(TargetDir)\EditConfig\Schemas\_schclass.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_schclass.schclass

"$(TargetDir)\EditConfig\Schemas\_schclass.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Schemas\_sql.schclass

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_sql.schclass

"$(TargetDir)\EditConfig\Schemas\_sql.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Schemas\_sql.schclass

"$(TargetDir)\EditConfig\Schemas\_sql.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_sql.schclass

"$(TargetDir)\EditConfig\Schemas\_sql.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Schemas\_sql.schclass

"$(TargetDir)\EditConfig\Schemas\_sql.schclass" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Schemas"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Themes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Config\Themes\colorSchema0.ini

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Themes\colorSchema0.ini

"$(TargetDir)\EditConfig\Themes\colorSchema0.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Themes\colorSchema0.ini

"$(TargetDir)\EditConfig\Themes\colorSchema0.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Themes\colorSchema0.ini

"$(TargetDir)\EditConfig\Themes\colorSchema0.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Themes\colorSchema0.ini

"$(TargetDir)\EditConfig\Themes\colorSchema0.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Config\Themes\colorSchema1.ini

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Themes\colorSchema1.ini

"$(TargetDir)\EditConfig\Themes\colorSchema1.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\Themes\colorSchema1.ini

"$(TargetDir)\EditConfig\Themes\colorSchema1.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Themes\colorSchema1.ini

"$(TargetDir)\EditConfig\Themes\colorSchema1.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\Themes\colorSchema1.ini

"$(TargetDir)\EditConfig\Themes\colorSchema1.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig\Themes"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Config\SyntaxEdit.ini

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\SyntaxEdit.ini

"$(TargetDir)\EditConfig\SyntaxEdit.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# Begin Custom Build
TargetDir=.\bin\vc60
InputPath=.\Config\SyntaxEdit.ini

"$(TargetDir)\EditConfig\SyntaxEdit.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\SyntaxEdit.ini

"$(TargetDir)\EditConfig\SyntaxEdit.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig"

# End Custom Build

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

# Begin Custom Build
TargetDir=\bin\vc60
InputPath=.\Config\SyntaxEdit.ini

"$(TargetDir)\EditConfig\SyntaxEdit.ini" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(InputPath)" "$(TargetDir)\EditConfig"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "DrawClient"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DrawButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawButton.h
# End Source File
# Begin Source File

SOURCE=.\DrawCar.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawCar.h
# End Source File
# Begin Source File

SOURCE=.\DrawChart.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawChart.h
# End Source File
# Begin Source File

SOURCE=.\DrawConduit.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawConduit.h
# End Source File
# Begin Source File

SOURCE=.\DrawDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawDoc.h
# End Source File
# Begin Source File

SOURCE=.\DrawObj.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawObj.h
# End Source File
# Begin Source File

SOURCE=.\DrawPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawPoly.h
# End Source File
# Begin Source File

SOURCE=.\DrawRect.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawRect.h
# End Source File
# Begin Source File

SOURCE=.\DrawRotary.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawRotary.h
# End Source File
# Begin Source File

SOURCE=.\drawtool.cpp
# End Source File
# Begin Source File

SOURCE=.\drawtool.h
# End Source File
# Begin Source File

SOURCE=.\DrawView.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawView.h
# End Source File
# Begin Source File

SOURCE=.\DrawWarn.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawWarn.h
# End Source File
# Begin Source File

SOURCE=.\FlatTabPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTabPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\FlatTabViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTabViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\FlatTabViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatTabViewView.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\MQClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MQClient.h
# End Source File
# Begin Source File

SOURCE=.\MQServer.cpp
# End Source File
# Begin Source File

SOURCE=.\MQServer.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\TabbedViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\TabbedViewView.h
# End Source File
# Begin Source File

SOURCE=.\ZoomView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomView.h
# End Source File
# End Group
# Begin Group "RealTime"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RealTime\ClassArr.h
# End Source File
# Begin Source File

SOURCE=.\RealTime\Graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTime\Graphics.h
# End Source File
# Begin Source File

SOURCE=.\RealTime\random.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTime\Random.h
# End Source File
# Begin Source File

SOURCE=.\RealTime\RealTime.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTime\RealTime.h
# End Source File
# Begin Source File

SOURCE=.\RealTime\RTSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTime\RTSlider.h
# End Source File
# Begin Source File

SOURCE=.\RealTime\Str.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTime\Str.h
# End Source File
# End Group
# Begin Group "DbAx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dbAx\AccountSetEvents.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxAccountSet.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxColorset.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxConnction.cpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxContactCmd.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxContactSet.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxControl.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxDispoint.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxException.cpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxFeedE.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxLib.h
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxLogin.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxMAlocationSet.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxPointDescription.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\AxSControl.hpp
# End Source File
# Begin Source File

SOURCE=.\BasicExcel.cpp

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BasicExcel.hpp
# End Source File
# Begin Source File

SOURCE=.\dbAx\CardFileEvents.hpp
# End Source File
# Begin Source File

SOURCE=.\ControlXml.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlXml.h
# End Source File
# Begin Source File

SOURCE=.\dbAx\CppSQLite3.cpp

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dbAx\CppSQLite3.h
# End Source File
# Begin Source File

SOURCE=.\excel2003.cpp
# End Source File
# Begin Source File

SOURCE=.\excel2003.h
# End Source File
# Begin Source File

SOURCE=.\ExcelFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcelFormat.h
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp

!IF  "$(CFG)" == "GUI_VisualStudio - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "GUI_VisualStudio - Win32 Unicode Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# End Group
# Begin Group "CGridListCtrlEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnManager.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnManagerProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnManagerProfile.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTrait.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitCombo.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitDateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitDateTime.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitEdit.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitImage.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitImage.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitText.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitText.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridColumnTraitVisitor.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridListCtrlGroups.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridListCtrlGroups.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTrait.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTraitText.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTraitText.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTraitVisitor.h
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTraitXP.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridListCtrlEx\CGridRowTraitXP.h
# End Source File
# End Group
# Begin Group "Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AddSQLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddSQLDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResourceViewPane.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceViewPane.h
# End Source File
# Begin Source File

SOURCE=.\SampleFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFormView.h
# End Source File
# Begin Source File

SOURCE=.\SetTimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetTimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingHostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingHostDlg.h
# End Source File
# End Group
# Begin Group "Zoom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\QBufferDC.cpp
# End Source File
# Begin Source File

SOURCE=.\QBufferDC.h
# End Source File
# Begin Source File

SOURCE=.\QSelectTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\QSelectTracker.h
# End Source File
# Begin Source File

SOURCE=.\QTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\QTracker.h
# End Source File
# Begin Source File

SOURCE=.\QZoomView.cpp
# End Source File
# Begin Source File

SOURCE=.\QZoomView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\download.avi
# End Source File
# Begin Source File

SOURCE=.\res\find.avi
# End Source File
# Begin Source File

SOURCE=.\res\heartbeat.avi
# End Source File
# Begin Source File

SOURCE=.\res\sync.avi
# End Source File
# Begin Source File

SOURCE=.\res\update.avi
# End Source File
# Begin Source File

SOURCE=.\res\write.avi
# End Source File
# End Target
# End Project
