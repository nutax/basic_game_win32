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
#define MAIN_LOOP_DURATION 32
char const *WINDOW_CLASS_NAME = "MyWindowClass";
char const *WINDOW_TITLE = "Basic Game";

// ----------------------
// VARIABLES
// ----------------------
WNDCLASS window_class = {0};
HWND window_handler = NULL;
MSG msg = {0};
DWORD start_tick;
BOOL loop_should_continue = TRUE;

// ----------------------
// PROCEDURE DECLARATIONS
// ----------------------
void main();

void main_init();
void main_loop();
void main_exit();

void init_window();
void init_other();

void loop_capture_start_tick();
void loop_manage_window_messages();
void loop_wait_remaining_time();

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
    while (loop_should_continue)
    {
        loop_capture_start_tick();
        loop_manage_window_messages();
        loop_wait_remaining_time();
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

void loop_capture_start_tick()
{
    start_tick = GetTickCount();
}

void loop_manage_window_messages()
{
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            loop_should_continue = FALSE;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void loop_wait_remaining_time()
{
    while ((GetTickCount() - start_tick) < MAIN_LOOP_DURATION)
        ;
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
        0,                   // Optional window styles.
        WINDOW_CLASS_NAME,   // Window class
        WINDOW_TITLE,        // Window text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,

        NULL,                  // Parent window
        NULL,                  // Menu
        GetModuleHandle(NULL), // Instance handle
        NULL                   // Additional application data
    );

    if (window_handler == NULL)
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