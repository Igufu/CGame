#include <Windows.h>




LRESULT MainWindowCallback(
  HWND Window,
  UINT Message,
  WPARAM WParam,
  LPARAM LParam
)
{ LRESULT Result = 0;

  switch(Message)
  {
    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    } break;

    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY\n");
    } break;

    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE\n");
    } break;

    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    default:
    {
      OutputDebugStringA("default\n");
      Result = DefWindowProc(Window, Message, WParam, LParam);
    } break;
  }

  return(Result);
}


int CALLBACK
WinMain(HINSTANCE Instance,  
        HINSTANCE PrevInstance,
        LPSTR     CommandLine,
        int       ShowCommand) 
{
  WNDCLASS WindowClass = {};

  WindowClass.style = CS_HREDRAW|CS_OWNDC|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = Instance;
  // WindowClass.hIcon;
  WindowClass.lpszClassName = "WindowName";
  if (RegisterClass(&WindowClass))
  {
    HWND WindowHandle = 
      CreateWindowExA(
        0,
        WindowClass.lpszClassName,
        "Placeholder name",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        Instance,
        0);
    if (WindowHandle != NULL) 
    {
      MSG Message;
      for(;;) // equiv to while(1)
      {
        BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
        if(MessageResult > 0) 
        {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        }
        else
        {
          break;
        }
      }
     
    }
    else 
    {  
      // TODO: logging errors
    }
  }
  else 
  {
    // TODO: logging errors
  }



  return(0);
}




