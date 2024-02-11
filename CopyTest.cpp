#include <iostream>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#pragma comment( lib, "winmm" )

using namespace std;

void Clipboard(string text, int length)
{
    const char* str = text.c_str();
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, length * sizeof(CHAR*));
    LPVOID gl = GlobalLock(h);

    memcpy(gl, str, length * sizeof(CHAR*));

    GlobalUnlock(gl);

    OpenClipboard(NULL); // hWnd is set to NULL
    EmptyClipboard(); // Sets clipboard ownership to someone don't know
    SetClipboardData(CF_TEXT, h);  // Successfully data to clipboard!
    CloseClipboard();
}

vector<string> ReadText()
{
    ifstream input_file("Codes.txt");
    vector<string> Codes;
    string line;

    if (input_file.is_open()) {
        while (getline(input_file, line))
            Codes.push_back(line);
        input_file.close();
        return Codes;
    }
    else
        cout << "Cant find file 'Codes.txt' \n";
}

int main() {
    static int i = 0;
    static bool cando = true;
    static bool CopyDo = true;
    vector<string> test = ReadText();
    string text[255];
    for (int id = 0; id < test.size(); id++)
        text[id] = test[id];

    if (test[0] == "") {
        CopyDo = false;
        system("pause");
    }

    while (CopyDo)
    {
        if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(0x56) & 0x8000 && cando == true) {
            i += 1;
            if (i >= size(text) || text[i] == "") {
                i = 0;
                PlaySound((LPCWSTR)"C:\\Windows\\Media\\Speech Off.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            cando = false;
        }

        if (!(GetKeyState(VK_CONTROL) & 0x8000) || !(GetKeyState(0x56) & 0x8000)) {
            cando = true;
            Clipboard(text[i], text[i].length());
        }

        Sleep(1);
    }
}