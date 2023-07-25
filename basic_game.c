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
RECT const FULL_WINDOW_RECT = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

// ----------------------
// VARIABLES
// ----------------------
WNDCLASS window_class = {0};
HWND window_handler = NULL;
MSG msg = {0};
DWORD start_tick;
BOOL loop_should_continue = TRUE;
DEVMODE display_settings;
HDC main_graphic_handler = NULL;
HDC secondary_graphic_handler = NULL;
HBITMAP secondary_bitmap = NULL;
HBITMAP old_bitmap = NULL;
HPEN red_pen = NULL;
HPEN green_pen = NULL;
HPEN blue_pen = NULL;
HPEN white_pen = NULL;
HPEN black_pen = NULL;
HBRUSH black_brush = NULL;
HBRUSH white_brush = NULL;

// ----------------------
// PROCEDURE DECLARATIONS
// ----------------------
void main();

void main_init();
void main_loop();
void main_exit();

void init_window();
void init_display_settings();
void init_graphic_handlers();
void init_colors();

void loop_capture_start_tick();
void loop_manage_window_messages();
void loop_clear_back_buffer();
void loop_update_entities();
void loop_render_entities();
void loop_swap_buffers();
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
    init_display_settings();
    init_graphic_handlers();
    init_colors();
}

void main_loop()
{
    while (loop_should_continue)
    {
        loop_capture_start_tick();
        loop_manage_window_messages();
        loop_clear_back_buffer();
        loop_update_entities();
        loop_render_entities();
        loop_swap_buffers();
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

void init_display_settings()
{
    ZeroMemory(&display_settings, sizeof(display_settings));
    display_settings.dmSize = sizeof(display_settings);
    display_settings.dmPelsWidth = WINDOW_WIDTH;
    display_settings.dmPelsHeight = WINDOW_HEIGHT;
    display_settings.dmBitsPerPel = 16;
    display_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&display_settings, CDS_FULLSCREEN);
}

void init_graphic_handlers()
{
    main_graphic_handler = GetDC(window_handler);
    secondary_graphic_handler = CreateCompatibleDC(main_graphic_handler);
    secondary_bitmap = CreateCompatibleBitmap(main_graphic_handler, WINDOW_WIDTH, WINDOW_HEIGHT);
    old_bitmap = SelectObject(secondary_graphic_handler, secondary_bitmap);
}

void init_colors()
{
    red_pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    green_pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    blue_pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    white_pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    black_pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    black_brush = CreateSolidBrush(RGB(0, 0, 0));
    white_brush = CreateSolidBrush(RGB(255, 255, 255));
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

void loop_clear_back_buffer()
{
    FillRect(secondary_graphic_handler, &FULL_WINDOW_RECT, black_brush);
}

void loop_update_entities()
{
    // TODO
}

void loop_render_entities()
{
    // TODO
}

void loop_swap_buffers()
{
    BitBlt(main_graphic_handler, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, secondary_graphic_handler, 0, 0, SRCCOPY);
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