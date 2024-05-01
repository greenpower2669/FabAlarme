#include <windows.h>
#include <string>

//#define IDI_MYICON 901
#define ID_BUTTON_CLOSE 101
#define ID_BUTTON_SETTINGS 102
#define ID_BUTTON_ALERTE 103
#define ID_EDIT_STOP 104
#define ID_EDIT_HOUR 201
#define ID_EDIT_MINUTE 202
#define ID_EDIT_CHOIX 203
#define ID_EDIT_HOURS 301
#define ID_EDIT_MINUTES 302
#define ID_EDIT_HOURS_MINUTES_SEND 303
#define ID_EDIT_SAISIE 304
// Convertit un nombre en chaîne de caractères wide string
std::wstring to_wstring(int number) {
    return std::to_wstring(number);
}

SYSTEMTIME chosenTime; // Variable globale pour stocker l'heure choisie
COLORREF chosenColor; // Variable globale pour stocker la couleur choisie

bool saisie_State = false;
int Savebox_w, Savebox_h, Savebox_x, Savebox_y, New_w, New_h, New_x, New_y;
// ici alerte AlerteActive(); permet de desactiver l'alerte et de vider les champs heure et minute
// si l'alerte est activée alors il fautra appuyer sur le bouton point pour la desactiver.
// si l'alerte est active alors la couleure de fond de passe par toutes les couleur de façon cyclique.
bool isAlerteActive = false;

HWND hwndMain;

enum { COLOR_BLUE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_PURPLE, COLOR_ORANGE };
COLORREF colors[] = { RGB(0, 0, 255), RGB(255, 0, 0), RGB(0, 255, 0), RGB(255, 255, 0), RGB(128, 0, 128), RGB(255, 165, 0) };

DWORD WINAPI BackgroundThreadFunc(LPVOID lpParam);
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void ShowSettingsDialog(HWND hwndParent);
void InitializeGlobals();
void SimulateTimeSelection();
void SimulateColorSelection();
void SetSaveNewvalue(HWND hwnd);
//inventaire index
//void  AlerteActive() {};
//void ChangeBackgroundColor(HWND hwnd, COLORREF color) {}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    InitializeGlobals();

    MSG messages;
    WNDCLASS wc = { 0 };


    wc.hInstance = hInstance;
    wc.lpszClassName = L"MainClass";
    wc.lpfnWndProc = WindowProcedure;
    wc.style = CS_DBLCLKS;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClass(&wc)) return 0;

    hwndMain = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST, L"MainClass", L"FabAlarme", WS_POPUP | WS_VISIBLE | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 85, 70, HWND_DESKTOP, NULL, hInstance, NULL);
    SetLayeredWindowAttributes(hwndMain, 0, (255 * 75) / 100, LWA_ALPHA);

    CreateWindow(L"BUTTON", L"X", WS_VISIBLE | WS_CHILD, 45, 10, 20, 20, hwndMain, (HMENU)ID_BUTTON_CLOSE, hInstance, NULL);
    CreateWindow(L"BUTTON", L"O", WS_VISIBLE | WS_CHILD, 5, 10, 20, 20, hwndMain, (HMENU)ID_BUTTON_SETTINGS, hInstance, NULL);
    CreateWindow(L"BUTTON", L".", WS_VISIBLE | WS_CHILD, 25, 20, 20, 20, hwndMain, (HMENU)ID_BUTTON_ALERTE, hInstance, NULL);
    // Création des champs de saisie pour l'heure et les minutes
    HWND hwndHourEdit = CreateWindow(L"EDIT", L"23", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 15, 50, 40, 20, hwndMain, (HMENU)ID_EDIT_HOUR, NULL, NULL);
    HWND hwndMinuteEdit = CreateWindow(L"EDIT", L"59", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 70, 50, 40, 20, hwndMain, (HMENU)ID_EDIT_MINUTE, NULL, NULL);
    HWND hwndsStopEdit = CreateWindow(L"EDIT", L"<--- Stoper l'alarme!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 140, 20, 140, 20, hwndMain, (HMENU)ID_EDIT_STOP, NULL, NULL);
    HWND hwndsChoixEdit = CreateWindow(L"EDIT", L"<--- Alarme choisie.", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 140, 50, 140, 20, hwndMain, (HMENU)ID_EDIT_CHOIX, NULL, NULL);
    HWND hwndsSaisieEdit = CreateWindow(L"EDIT", L"<--- Zone de saisie.", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 140, 90, 140, 20, hwndMain, (HMENU)ID_EDIT_SAISIE, NULL, NULL);
    // Passer des champs en lecture seule
    SendMessage(hwndHourEdit, EM_SETREADONLY, (WPARAM)TRUE, 0);
    SendMessage(hwndMinuteEdit, EM_SETREADONLY, (WPARAM)TRUE, 0);
    SendMessage(hwndsStopEdit, EM_SETREADONLY, (WPARAM)TRUE, 0);
    SendMessage(hwndsChoixEdit, EM_SETREADONLY, (WPARAM)TRUE, 0);
    SendMessage(hwndsSaisieEdit, EM_SETREADONLY, (WPARAM)TRUE, 0);
    //Formulaire
    CreateWindow(L"EDIT", L"HH ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 15, 90, 40, 20, hwndMain, (HMENU)ID_EDIT_HOURS, NULL, NULL);
    CreateWindow(L"EDIT", L"MM", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 70, 90, 40, 20, hwndMain, (HMENU)ID_EDIT_MINUTES, NULL, NULL);
    CreateWindow(L"BUTTON", L"Enregistrer!", WS_VISIBLE | WS_CHILD, 15, 115, 95, 20, hwndMain, (HMENU)ID_EDIT_HOURS_MINUTES_SEND, hInstance, NULL);
    ShowWindow(hwndMain, nCmdShow);

    //
  
    HICON hIcon = LoadIcon(NULL, IDI_APPLICATION);
    if (hIcon) {
        SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwndMain, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
    //

    CreateThread(NULL, 0, BackgroundThreadFunc, NULL, 0, NULL);

    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

void InitializeGlobals() {
    GetSystemTime(&chosenTime);
    chosenColor = colors[COLOR_BLUE];
}
// Fonction pour changer la couleur de fond
void ChangeBackgroundColor(HWND hwnd, COLORREF color) {
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);
    HBRUSH hBrush = CreateSolidBrush(color);
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);
    ReleaseDC(hwnd, hdc);
    RedrawWindow(hwndMain, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN);
}
DWORD WINAPI BackgroundThreadFunc(LPVOID lpParam) {

    SYSTEMTIME currentTime;
    COLORREF rainbowColors[] = { RGB(255, 0, 0), RGB(255, 127, 0), RGB(255, 255, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(75, 0, 130), RGB(143, 0, 255) };
    int colorIndex = 0;
    WCHAR hourStr[3] = { 0 };
    WCHAR minuteStr[3] = { 0 };
    while (true) {
        GetLocalTime(&currentTime);
        // Convertir l'heure actuelle et l'heure choisie en minutes pour faciliter la comparaison
        int currentMinutes = currentTime.wHour * 60 + currentTime.wMinute;
        int chosenMinutes = chosenTime.wHour * 60 + chosenTime.wMinute;
        // Obtenez les valeurs des champs de saisie
        GetWindowText(GetDlgItem(hwndMain, ID_EDIT_HOUR), hourStr, 3);
        GetWindowText(GetDlgItem(hwndMain, ID_EDIT_MINUTE), minuteStr, 3);

        // Convertissez en int
        int hour = _wtoi(hourStr);
        int minute = _wtoi(minuteStr);
        //chosenTime.wHour;
        //chosenTime.wMinute;
        // Vérifiez si les valeurs sont correctes (ajustez cette logique selon vos besoins)
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
            // Mise à jour de chosenMinutes (exemple simple, ajustez selon le besoin)
            chosenMinutes = hour * 60 + minute;
        }
        // Pour le débogage: afficher l'heure actuelle et l'heure choisie en minutes
        //std::wstring debugMessage = L"Current Time in Minutes: " + to_wstring(currentMinutes) +
        //    L", Chosen Time in Minutes: " + to_wstring(chosenMinutes);
        //OutputDebugString(debugMessage.c_str());

        // Vérifier si l'heure actuelle dépasse l'heure de l'alerte moins 1 minute
        if (!isAlerteActive && (currentMinutes >= (chosenMinutes - 5))) {
            // Activer l'alerte ici
            //SendMessage(hwndMain, WM_COMMAND, ID_BUTTON_ALERTE, 0);
            isAlerteActive = true;
        }
        if (isAlerteActive) {
            // Change la couleur de fond avec la couleur actuelle de l'arc-en-ciel
            ChangeBackgroundColor(hwndMain, rainbowColors[colorIndex]);
            colorIndex = (colorIndex + 1) % (sizeof(rainbowColors) / sizeof(COLORREF));



        }
        Sleep(100); // Attendre 1 seconde avant la prochaine itération
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_NCHITTEST: {
        LRESULT hit = DefWindowProc(hwnd, message, wParam, lParam);
        if (hit == HTCLIENT) hit = HTCAPTION;
        return hit;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON_CLOSE) {
            PostQuitMessage(0);
        }
        else if (LOWORD(wParam) == ID_BUTTON_SETTINGS) {
            SetSaveNewvalue(hwnd);
        }
        // Ajout pour gérer les clics sur le bouton ID_BUTTON_ALERTE
        else if (LOWORD(wParam) == ID_BUTTON_ALERTE) {
            // Inverser l'état de isAlerteActive

            isAlerteActive = !isAlerteActive;
            if (!isAlerteActive) {
                // Définir les valeurs initiales des champs de saisie à 23 pour l'heure et 59 pour les minutes
                SetWindowText(GetDlgItem(hwndMain, ID_EDIT_HOUR), L"23");
                SetWindowText(GetDlgItem(hwndMain, ID_EDIT_MINUTE), L"59");
                ChangeBackgroundColor(hwndMain, GetSysColor(COLOR_APPWORKSPACE));


            }
            // Ici, vous pouvez appeler une fonction pour réagir à ce changement d'état
            // Par exemple, démarrer ou arrêter une animation de clignotement
        }
        else if (LOWORD(wParam) == ID_EDIT_HOURS_MINUTES_SEND) {
            WCHAR hourStrs[3] = { 0 };
            WCHAR minuteStrs[3] = { 0 };
            GetWindowText(GetDlgItem(hwndMain, ID_EDIT_HOURS), hourStrs, 3);
            GetWindowText(GetDlgItem(hwndMain, ID_EDIT_MINUTES), minuteStrs, 3);
            SetWindowText(GetDlgItem(hwndMain, ID_EDIT_HOUR), hourStrs);
            SetWindowText(GetDlgItem(hwndMain, ID_EDIT_MINUTE), minuteStrs);
        }

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}


void ShowSettingsDialog(HWND hwndParent) {
    SimulateTimeSelection();
    SimulateColorSelection();
    wchar_t msg[256];
    wsprintf(msg, L"Heure choisie: %02d:%02d\nCouleur choisie: #%02X%02X%02X",
        chosenTime.wHour, chosenTime.wMinute,
        GetRValue(chosenColor), GetGValue(chosenColor), GetBValue(chosenColor));
    MessageBox(hwndParent, msg, L"Paramètres Sélectionnés", MB_OK);
}

void SimulateTimeSelection() {
    // Ici, vous pouvez simuler la sélection de l'heure par l'utilisateur
    GetSystemTime(&chosenTime); // Simuler en prenant l'heure actuelle
}

void SimulateColorSelection() {
    // Ici, vous pouvez simuler la sélection de la couleur par l'utilisateur
    chosenColor = colors[COLOR_GREEN]; // Simuler en choisissant une couleur
}

void SetSaveNewvalue(HWND hwnd) {
    if (!saisie_State) {
        RECT rect;
        GetWindowRect(hwnd, &rect);
        Savebox_w = rect.right - rect.left;
        Savebox_h = rect.bottom - rect.top;
        Savebox_x = rect.left;
        Savebox_y = rect.top;

        New_w = GetSystemMetrics(SM_CXSCREEN) / 2;
        New_h = GetSystemMetrics(SM_CYSCREEN) / 2;
        New_x = New_w / 2;
        New_y = New_h / 2;

        SetWindowPos(hwnd, HWND_TOP, New_x, New_y, New_w, New_h, SWP_NOZORDER);
        saisie_State = true;
    }
    else {
        SetWindowPos(hwnd, HWND_TOP, Savebox_x, Savebox_y, Savebox_w, Savebox_h, SWP_NOZORDER);
        saisie_State = false;
    }
}
void AlerteActive(bool activate) {
    isAlerteActive = activate;
    if (!activate) {
        // Désactiver l'alerte et réinitialiser les champs d'heure et de minute
        chosenTime.wHour = 0;
        chosenTime.wMinute = 0;
        SetWindowText(GetDlgItem(hwndMain, ID_EDIT_HOUR), L"");
        SetWindowText(GetDlgItem(hwndMain, ID_EDIT_MINUTE), L"");
    }
    // Ici, ajoutez d'autres actions nécessaires pour gérer l'activation/désactivation de l'alerte
}

