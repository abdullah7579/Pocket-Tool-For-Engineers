#include <windows.h>

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowMainMenu(HWND hwnd);
void ShowSubMenu(HWND hwnd, int menuType);
void ClearControls(HWND hwnd);

// Button IDs for main menu
#define ID_MENU_NUMSYS 1
#define ID_MENU_DW_CONV 2
#define ID_MENU_NT_EQUIV 3
#define ID_MENU_ERR_CODES 4
#define ID_MENU_RES_VERIFY 5
#define ID_EXIT_APP 6

// Button IDs for submenus
#define ID_CONV_BINARY_DEC 11
#define ID_CONV_DEC_BINARY 12
#define ID_DELTA_TO_WYE 13
#define ID_WYE_TO_DELTA 14
#define ID_NORTON_EQUIV 15
#define ID_THEVENIN_EQUIV 16
#define ID_HAMMING_GEN 17
#define ID_HAMMING_CHECK 18
#define ID_CRC_GEN 19
#define ID_CRC_CHECK 20
#define ID_BACK 99

int currentMenu = 0; // 0: Main Menu, 1-5: Submenus

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // Define window class
    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MultiMenuApp";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class!", "Error", MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(
        "MultiMenuApp", "Engineering Tool", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Failed to create window!", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            ShowMainMenu(hwnd);
            break;

        case WM_COMMAND:
            if (currentMenu == 0) {
                // Main menu options
                switch (LOWORD(wParam)) {
                    case ID_MENU_NUMSYS:
                        ShowSubMenu(hwnd, 1);
                        break;
                    case ID_MENU_DW_CONV:
                        ShowSubMenu(hwnd, 2);
                        break;
                    case ID_MENU_NT_EQUIV:
                        ShowSubMenu(hwnd, 3);
                        break;
                    case ID_MENU_ERR_CODES:
                        ShowSubMenu(hwnd, 4);
                        break;
                    case ID_MENU_RES_VERIFY:
                        MessageBox(hwnd, "Resistor Value Verification selected!", "Resistor Verification", MB_OK);
                        break;
                    case ID_EXIT_APP:
                        PostQuitMessage(0);
                        break;
                }
            } else {
                // Submenu options
                switch (LOWORD(wParam)) {
                    case ID_CONV_BINARY_DEC:
                        MessageBox(hwnd, "Binary to Decimal selected!", "Conversion", MB_OK);
                        break;
                    case ID_CONV_DEC_BINARY:
                        MessageBox(hwnd, "Decimal to Binary selected!", "Conversion", MB_OK);
                        break;
                    case ID_DELTA_TO_WYE:
                        MessageBox(hwnd, "Delta to Wye selected!", "Delta-Wye", MB_OK);
                        break;
                    case ID_WYE_TO_DELTA:
                        MessageBox(hwnd, "Wye to Delta selected!", "Delta-Wye", MB_OK);
                        break;
                    case ID_NORTON_EQUIV:
                        MessageBox(hwnd, "Norton Equivalent selected!", "Norton-Thevenin", MB_OK);
                        break;
                    case ID_THEVENIN_EQUIV:
                        MessageBox(hwnd, "Thevenin Equivalent selected!", "Norton-Thevenin", MB_OK);
                        break;
                    case ID_HAMMING_GEN:
                        MessageBox(hwnd, "Hamming Code Generation selected!", "Error Correction", MB_OK);
                        break;
                    case ID_HAMMING_CHECK:
                        MessageBox(hwnd, "Check Hamming Code selected!", "Error Correction", MB_OK);
                        break;
                    case ID_CRC_GEN:
                        MessageBox(hwnd, "CRC Code Generation selected!", "Error Correction", MB_OK);
                        break;
                    case ID_CRC_CHECK:
                        MessageBox(hwnd, "Check CRC Code selected!", "Error Correction", MB_OK);
                        break;
                    case ID_BACK:
                        ShowMainMenu(hwnd);
                        break;
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void ClearControls(HWND hwnd) {
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while (hChild) {
        DestroyWindow(hChild);
        hChild = GetWindow(hwnd, GW_CHILD);
    }
}

void ShowMainMenu(HWND hwnd) {
    currentMenu = 0;

    ClearControls(hwnd); // Clear all controls

    // Main menu buttons
    CreateWindow("BUTTON", "Number Systems Conversion", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hwnd, (HMENU)ID_MENU_NUMSYS, NULL, NULL);
    CreateWindow("BUTTON", "Delta and Wye Conversion", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hwnd, (HMENU)ID_MENU_DW_CONV, NULL, NULL);
    CreateWindow("BUTTON", "Norton and Thevenin Equivalent", WS_VISIBLE | WS_CHILD, 50, 150, 200, 30, hwnd, (HMENU)ID_MENU_NT_EQUIV, NULL, NULL);
    CreateWindow("BUTTON", "Error Correction Codes", WS_VISIBLE | WS_CHILD, 50, 200, 200, 30, hwnd, (HMENU)ID_MENU_ERR_CODES, NULL, NULL);
    CreateWindow("BUTTON", "Resistor Value Verification", WS_VISIBLE | WS_CHILD, 50, 250, 200, 30, hwnd, (HMENU)ID_MENU_RES_VERIFY, NULL, NULL);
    CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD, 50, 300, 200, 30, hwnd, (HMENU)ID_EXIT_APP, NULL, NULL);
}

void ShowSubMenu(HWND hwnd, int menuType) {
    currentMenu = menuType;

    ClearControls(hwnd); // Clear all controls

    switch (menuType) {
        case 1: // Number System Conversion
            CreateWindow("BUTTON", "Binary to Decimal", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hwnd, (HMENU)ID_CONV_BINARY_DEC, NULL, NULL);
            CreateWindow("BUTTON", "Decimal to Binary", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hwnd, (HMENU)ID_CONV_DEC_BINARY, NULL, NULL);
            break;

        case 2: // Delta and Wye
            CreateWindow("BUTTON", "Delta to Wye", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hwnd, (HMENU)ID_DELTA_TO_WYE, NULL, NULL);
            CreateWindow("BUTTON", "Wye to Delta", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hwnd, (HMENU)ID_WYE_TO_DELTA, NULL, NULL);
            break;

        case 3: // Norton and Thevenin
            CreateWindow("BUTTON", "Norton Equivalent", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hwnd, (HMENU)ID_NORTON_EQUIV, NULL, NULL);
            CreateWindow("BUTTON", "Thevenin Equivalent", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hwnd, (HMENU)ID_THEVENIN_EQUIV, NULL, NULL);
            break;

        case 4: // Error Correction Codes
            CreateWindow("BUTTON", "Hamming Code Gen", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hwnd, (HMENU)ID_HAMMING_GEN, NULL, NULL);
            CreateWindow("BUTTON", "Check Hamming Code", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hwnd, (HMENU)ID_HAMMING_CHECK, NULL, NULL);
            CreateWindow("BUTTON", "CRC Code Gen", WS_VISIBLE | WS_CHILD, 50, 150, 200, 30, hwnd, (HMENU)ID_CRC_GEN, NULL, NULL);
            CreateWindow("BUTTON", "Check CRC Code", WS_VISIBLE | WS_CHILD, 50, 200, 200, 30, hwnd, (HMENU)ID_CRC_CHECK, NULL, NULL);
            break;
    }

    // Back button
    CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 200, 30, hwnd, (HMENU)ID_BACK, NULL, NULL);
}
