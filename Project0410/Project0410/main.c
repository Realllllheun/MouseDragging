#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';             // 알파벳 'O'
    POINT mousePos;                // 마우스 위치
    int isDragging = 0;            // 드래그 상태
    int letterX = 10, letterY = 5; // 'O'의 위치

    HWND consoleWindow = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int fontWidth = 9;     // 콘솔 글꼴 가로 크기
    const int fontHeight = 19;   // 콘솔 글꼴 세로 크기

    while (1) {
        // 마우스 위치 갱신
        GetCursorPos(&mousePos);
        ScreenToClient(consoleWindow, &mousePos);  // 화면 → 콘솔 좌표

        int mouseX = mousePos.x / fontWidth;
        int mouseY = mousePos.y / fontHeight;

        // 드래그 시작: 클릭 + 'O' 위
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !isDragging) {
            if (mouseX == letterX && mouseY == letterY) {
                isDragging = 1;
            }
        }

        // 드래그 중이면 위치 갱신
        if (isDragging) {
            letterX = mouseX;
            letterY = mouseY;

            // 클릭 해제 → 드래그 종료
            if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                isDragging = 0;
            }
        }

        // 콘솔 초기화 및 출력
        system("cls");
        printf("알파벳 '%c'을 마우스로 클릭해서 이동하세요 (Q 키 종료)\n", letter);
        printf("현재 알파벳 위치: (%d, %d)\n", letterX, letterY);
        printf("마우스 위치: (%d, %d)\n", mouseX, mouseY);

        // 마우스 위치에 "<" 출력
        SetConsoleCursorPosition(hConsole, (COORD) { mouseX, mouseY });
        printf("<");

        // 알파벳 'O' 출력
        SetConsoleCursorPosition(hConsole, (COORD) { letterX, letterY });
        printf("%c", letter);

        // Q 키 누르면 종료
        if (GetAsyncKeyState('Q') & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        Sleep(10); // CPU 과부하 방지
    }

    return 0;
}
