# Microsoft Developer Studio Project File - Name="T3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=T3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "T3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "T3D.mak" CFG="T3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "T3D - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "T3D - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "T3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "T3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "c:/DEV/3D/glut" /I "c:/DEV/3D/glut/T3D" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "T3D - Win32 Release"
# Name "T3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\T3DBox.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DCalcul.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DColor.cpp
# End Source File
# Begin Source File

SOURCE=.\T3dFontRaster.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DLoadBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DLoadGif.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DLoadImg.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DPrimitiv.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DTransf.cpp
# End Source File
# Begin Source File

SOURCE=.\T3DVect3D.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\T3DBox.h
# End Source File
# Begin Source File

SOURCE=.\T3DCalcul.h
# End Source File
# Begin Source File

SOURCE=.\T3DColor.h
# End Source File
# Begin Source File

SOURCE=.\T3DFont.h
# End Source File
# Begin Source File

SOURCE=.\T3dFontRaster.h
# End Source File
# Begin Source File

SOURCE=.\T3DLoadImg.h
# End Source File
# Begin Source File

SOURCE=.\T3DPrimitiv.h
# End Source File
# Begin Source File

SOURCE=.\T3dTab.h
# End Source File
# Begin Source File

SOURCE=.\T3DTexture.h
# End Source File
# Begin Source File

SOURCE=.\T3DTransf.h
# End Source File
# Begin Source File

SOURCE=.\T3DType.h
# End Source File
# Begin Source File

SOURCE=.\T3DVect3D.h
# End Source File
# Begin Source File

SOURCE=.\TVectType.h
# End Source File
# End Group
# End Target
# End Project
