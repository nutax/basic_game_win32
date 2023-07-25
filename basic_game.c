// ----------------------
// COMPILATION COMMAND
// ----------------------
// gcc -o basic_game basic_game.c -mwindows -O3 -march=native -ffast-math



// ----------------------
// INCLUDES
// ----------------------
#include <Windows.h>



// ----------------------
// CONSTANTS
// ----------------------
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
char const * WINDOW_CLASS_NAME = "MyWindowClass";
char const * WINDOW_TITLE = "Basic Game";



// ----------------------
// VARIABLES
// ----------------------
WNDCLASS window_class = {0};
HWND window_handler = NULL;



// ----------------------
// PROCEDURE DECLARATIONS
// ----------------------
void main();

void main_init();
void main_loop();
void main_exit();

void init_window();
void init_other();

void window_register_class();
void window_create_handler();
void window_show();

LRESULT CALLBACK class_window_procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// ----------------------
// PROCEDURE DEFINITIONS
// ----------------------

void main()
{
    main_init();
    main_loop();
    main_exit();
}

void main_init()
{
    init_window();
    init_other();
}

void main_loop()
{
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void main_exit()
{
    exit(EXIT_SUCCESS);
}

void init_window()
{
    window_register_class();
    window_create_handler();
    window_show();
}

void init_other()
{

}

void window_register_class()
{
    window_class.lpfnWndProc = class_window_procedure;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&window_class);
}

void window_create_handler()
{
    window_handler = CreateWindowEx(
        0,                          // Optional window styles.
        WINDOW_CLASS_NAME,           // Window class
        WINDOW_TITLE,                // Window text
        WS_OVERLAPPEDWINDOW,        // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,

        NULL,       // Parent window
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
    );

    if(window_handler == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

void window_show()
{
    ShowWindow(window_handler, SW_SHOWNORMAL);
}

LRESULT CALLBACK class_window_procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}