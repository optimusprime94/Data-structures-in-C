Biblioteken kompilerade f�r VS2015 med statisk C runtime.

F�r ditt projekt som skall anv�nda MazeLib2015.lib (det besv�rligaste
biblioteket) eller om du f�r l�nkfel om LIBCMD och/eller fel om
/SAFESEH fr�n l�nkaren:

* S�tt projekt->C++/C->Code Generation->Runtime Library till "Multi-threaded Debug"

* S�tt projekt->Linker->Advanced->Image Has Safe Exception Handlers till "No (/SAFESEH:NO)"

