#ifndef MAIN
#define MAIN


// make sure to add $(SFML_SDK)\lib to the project properties under
// Linker/additional library directories





#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-main-d.lib")
#pragma comment(lib,"sfml-network-d.lib") 
#define NO_RANDOM
#else 
#pragma comment(lib,"sfml-main.lib")
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-network.lib") 

#endif //_DEBUG 


#endif // MAIN