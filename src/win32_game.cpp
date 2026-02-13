#include <Windows.h>

#define global static
#define local_persist static
#define internal static


global bool Running;


internal void Win32UpdateWindow(HWND Window, int X, int Y, int Width, int Height)
{
  
}
internal void ResizeDIBSection(int Width, int Height) // Device Independent Bitmap
{

} 



LRESULT Win32MainWindowCallback(
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
      RECT ClientRect;
      GetClientRect(Window, &ClientRect);
      int Width = ClientRect.right - ClientRect.left;
      int Height = ClientRect.bottom - ClientRect.top;
      ResizeDIBSection(Width, Height);
      OutputDebugStringA("WM_SIZE\n");
    } break;

    case WM_DESTROY:
    {
      Running = false;
    } break;

    case WM_CLOSE:
    {
      Running = false;
    } break;

    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    case WM_PAINT:
    { 
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Width = Paint.rcPaint.right - Paint.rcPaint.left;
      int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      Win32UpdateWindow(Window, X, Y, Width, Height);
      EndPaint(Window, &Paint); 
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
  WindowClass.lpfnWndProc = Win32MainWindowCallback;
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
      while(Running)
      {
        Running = true;
        MSG Message;
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




