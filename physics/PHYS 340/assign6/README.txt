copy glut32.lib and glut.lib to directory: C:\Program Files\PellesC\Lib\Win

copy glut.h to directory C:\Program Files\PellesC\Include\Win\gl

copy glut32.dll to directory C:\Windows\SysWOW64

When creating project, use the Win32 console program template

Under project options, do the following:

1) under the compiler tab, check "Enable Microsoft extensions"
2) under the linker tab, add the following to "library and object files:" glut32.lib glut.lib