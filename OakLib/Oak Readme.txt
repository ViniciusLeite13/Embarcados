===================================================================================
Oak Library
Copyright (c) 2007-2011 Toradex AG, Horw, Switzerland
Version 1.3 2011-03-01
===================================================================================

Configuration
================
The library was tested in the following configuration
- Windows XP, Windows Vista and Window 7, (library compiled for 32-bit platform, but works on both 32 and 64 bit variants of Windows).
- Microsoft Visual Studio 2008
- C/C++ programming language

Quick Guide
================
Three simple steps to add the Oak library to your C/C++ project

1) Compiler
------------------
- add the file "oak.h" to your project
- add the statement
    #include "oak.h"
  in your source code


2) Linker
------------------
- if your project is set to use unicode character set,
  	 add "oakw.lib" to the list of linked libraries
- if your project is set to use ASCII character set,
  	 add "oaka.lib" to the list of linked libraries

  (make sure the path is set that the linker can find the file)

3) Runtime
------------------
- if your project is set to use unicode character set,
  	 copy "oakw.dll" into the same location as your executable (*.exe) file
- if your project is set to use ASCII character set,
  	 copy "oaka.dll" into the same location as your executable (*.exe) file



-----------------------------------------------------------------------------
Revision information:
-----------------------------------------------------------------------------

Changes from Version 1.2.5 to 1.3
=================================
2011-03-01
- Removed padding instruction for data structures ( was causing issues when using the DLL from .NET applications ).
- C String parameters are now const.
- Added a new Oak_Cleanup() function.
- Because of the changes above, this OakLib 1.3 is not binary compatible with 1.2.5.


Changes from Version 1.2.4 to 1.2.5
===================================
2010-10-27
- Fix for timeout parameter for Oak_GetInReport() & Oak_SendOutReport() that was not working


Changes from Version 1.2.3 to 1.2.4
===================================
2010-05-26
- Fix for windows handles not being closed in Oak_GetInReport() and Oak_SendOutReport()


Changes from Version 1.2.2 to 1.2.3
===================================
2009-11-26
- Bug fixed: application linked against OakLib and using the library's hotplug
  feature could crash if a non Oak HID device was plugged or unplugged


Changes from Version 1.2.1 to 1.2.2
===================================
2008-05-14
- MFC Library statically included.


Changes from Version 1.2 to 1.2.1
=================================
2008-04-14
- Bug fixed: Crash when unplug other HID device while plugged Oak device
- Bug fixed: Crash when map/unmap network drives


Changes from Version 1.1 to 1.2
===============================
2008-02-15
- Add function for sending out reports for the new Oak devices


Changes from Version 1.0 to 1.1
===============================
2007-10-12
Bugs fixed
- Channel Name was reported empty (first character was substituted with #0)
- Channel Names ended with a space character (#0x20)


Initial Release Version 1.0
===========================
2007-30-06



Toradex AG, October 2010