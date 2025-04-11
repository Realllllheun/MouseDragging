#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';             // ���ĺ� 'O'
    POINT mousePos;                // ���콺 ��ġ
    int isDragging = 0;            // �巡�� ����
    int letterX = 10, letterY = 5; // 'O'�� ��ġ

    HWND consoleWindow = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int fontWidth = 9;     // �ܼ� �۲� ���� ũ��
    const int fontHeight = 19;   // �ܼ� �۲� ���� ũ��

    while (1) {
        // ���콺 ��ġ ����
        GetCursorPos(&mousePos);
        ScreenToClient(consoleWindow, &mousePos);  // ȭ�� �� �ܼ� ��ǥ

        int mouseX = mousePos.x / fontWidth;
        int mouseY = mousePos.y / fontHeight;

        // �巡�� ����: Ŭ�� + 'O' ��
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !isDragging) {
            if (mouseX == letterX && mouseY == letterY) {
                isDragging = 1;
            }
        }

        // �巡�� ���̸� ��ġ ����
        if (isDragging) {
            letterX = mouseX;
            letterY = mouseY;

            // Ŭ�� ���� �� �巡�� ����
            if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                isDragging = 0;
            }
        }

        // �ܼ� �ʱ�ȭ �� ���
        system("cls");
        printf("���ĺ� '%c'�� ���콺�� Ŭ���ؼ� �̵��ϼ��� (Q Ű ����)\n", letter);
        printf("���� ���ĺ� ��ġ: (%d, %d)\n", letterX, letterY);
        printf("���콺 ��ġ: (%d, %d)\n", mouseX, mouseY);

        // ���콺 ��ġ�� "<" ���
        SetConsoleCursorPosition(hConsole, (COORD) { mouseX, mouseY });
        printf("<");

        // ���ĺ� 'O' ���
        SetConsoleCursorPosition(hConsole, (COORD) { letterX, letterY });
        printf("%c", letter);

        // Q Ű ������ ����
        if (GetAsyncKeyState('Q') & 0x8000) {
            printf("\n���α׷� ����\n");
            break;
        }

        Sleep(10); // CPU ������ ����
    }

    return 0;
}
