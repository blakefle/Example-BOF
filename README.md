To compile this with Visual Studio:
cl.exe /c /GS- minidump.c /Fominidump.o

To compile this with x86 MinGW:
i686-w64-mingw32-gcc -c minidump.c -o minidump.o

To compile this with x64 MinGW:
x86_64-w64-mingw32-gcc -c minidump.c -o minidump.o

The commands above produce a minidump.o file. Use inline-execute in Beacon to run the BOF.

beacon> inline-execute /path/to/minidump.o args
