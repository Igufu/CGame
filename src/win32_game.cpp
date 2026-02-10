#include <Windows.h>


int CALLBACK WinMain(HINSTANCE hInstance,  
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nShowCmd)
{
  MessageBoxExA(0, "THA BOX", "cool title", 
    MB_OK|MB_ICONINFORMATION, 0);
  return 0;
}

