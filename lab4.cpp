#include <iostream>
#include <cstring>
#include <Windows.h>
#include <fstream>
using namespace std;

void BMASearch(char* s) {
    char ss[21];
    cout << "5.2) ������� ���������: ";
    cin >> ss;
    int lens = strlen(s);
    int lenss = strlen(ss);
    int* indents = new int[lenss];
    char* symbols = new char[lenss];
    for (int i = 0; i < lenss - 1; i++) {
        symbols[i] = ss[i];
        for (int j = 0; j < i; j++) {
            if (symbols[j] == ss[i]) indents[j] = lenss - i - 1;
        }
        indents[i] = lenss - i - 1;
    }
    symbols[lenss - 1] = ss[lenss - 1];
    indents[lenss - 1] = lenss;
    bool fl;
    bool found = false;
    bool inTable;
    for (int i = 0; i <= lens - lenss;) {
        fl = true;
        for (int j = lenss - 1; j >= 0; j--) {
            if (s[i + j] != ss[j]) {
                fl = false;
                inTable = false;
                for (int k = 0; k < lenss - 1; k++)
                    if (s[i + j] == symbols[k]) {
                        i += indents[k];
                        inTable = true;
                        break;
                    }
                if (!inTable) i += lenss;
                break;
            }

        }
        if (fl) {
            cout << "��������� ���������� � ������� " << i << " � ������������� �� ������� " << i + lenss - 1 << ".\n";
            found = true;
            i++;
        }
    }
    if (!found) cout << "����� ��������� �� ����������.\n";
}
void linearSearch(char* s) {
    char ss[21];
    cout << "5.1) ������� ���������: ";
    cin >> ss;
    int lens = strlen(s);
    int lenss = strlen(ss);
    bool fl;
    bool found = false;
    for (int i = 0; i <= lens - lenss; i++) {
        fl = true;
        for (int j = 0; j < lenss; j++) {
            if (s[i + j] != ss[j]) fl = false;
            if (!fl) break;
        }
        if (fl) {
            cout << "��������� ���������� � ������� " << i << " � ������������� �� ������� " << i + lenss - 1 << ".\n";
            found = true;
        }
    }
    if (!found) cout << "����� ��������� �� ����������.\n";
}
int isPrep(char s) {
    int x = int(s);
    if ((x >= 33 && x <= 47) || (x >= 58 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 126)) return 1;
    else return 0;
}
int isInUppercase(char s) {
    int x = int(s);
    if ((x >= -64 && x <= -33) || (x >= 65 && x <= 90)) return 1;
    else return 0;
}
int isInLowercase(char s) {
    int x = int(s);
    if ((x >= -32 && x <= -1) || (x >= 97 && x <= 122)) return 1;
    else return 0;
}
int isDigit(char s) {
    int x = int(s);
    if (x >= 48 && x <= 57) return 1;
    else return 0;
}
int drivercode4() {
    setlocale(LC_CTYPE, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "1) �������� ������ �����:\n1. � ����������\n2. � �����\n";
    int inputMethod;
    cin >> inputMethod;
    char str[1000];
    if (inputMethod == 1) {
        cout << "������� �����: ";
        cin.ignore();
        cin.getline(str, 1000);
    }
    else {
        ifstream File;
        File.open("type here.txt");

        if (!File.is_open()) {

            cout << "������� ���� �� �������! \n";

            return 0;
        }
        File.getline(str, 1000);
        File.close();
    }
    // cout << str << "\n";
    int k = 0;
    bool space = false;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' && !space) {
            space = true;
            str[k] = str[i];
            k++;
        }
        else if (str[i] != ' ' && space) {
            space = false;
            str[k] = str[i];
            k++;
        }
        else if (str[i] != ' ' && !space) {
            str[k] = str[i];
            k++;
        }
    }
    str[k] = '\0';
    // cout << str << "\n";

    k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isPrep(str[i]) && str[k - 1] == ' ') {
            str[k - 1] = str[i];
        }
        else {
            str[k] = str[i];
            k++;
        }
    }
    str[k] = '\0';
    // cout << str << "\n";
    k = 0;
    bool ellipsis = false;
    int percount = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '.' && !ellipsis) {
            percount++;
            if (percount == 3) {
                str[k] = '.';
                str[k + 1] = '.';
                str[k + 2] = '.';
                k += 3;
                percount = 0;
                ellipsis = true;
            }
        }
        else if (str[i] == '.' && ellipsis) {

        }
        else {
            if (percount == 1 || percount == 2) {
                str[k] = '.';
                k++;
            }
            str[k] = str[i];
            percount = 0;
            k++;
            ellipsis = false;
        }
    }
    str[k] = '.';
    k++;
    str[k] = '\0';
    // cout << str << "\n";
    k = 0;
    bool prevPrep = false;
    for (int i = 0; i < strlen(str); i++) {
        if (isPrep(str[i]) && !prevPrep) {
            if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '.') {
                str[k] = '.';
                str[k + 1] = '.';
                str[k + 2] = '.';
                k += 3;
                i += 2;
            }
            else {
                prevPrep = true;
                str[k] = str[i];
                k++;
            }
        }
        else if (!isPrep(str[i]) && prevPrep) {
            prevPrep = false;
            str[k] = str[i];
            k++;
            percount = 0;
        }
        else if (!isPrep(str[i]) && !prevPrep) {
            str[k] = str[i];
            k++;
        }
    }
    str[k] = '\0';
    // cout << str << "\n";
    k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isInUppercase(str[i]) || isInLowercase(str[i])) {
            if (isInUppercase(str[i + 1])) str[i + 1] = char(int(str[i + 1]) + 32);
        }
    }
    cout << "2) " << str << '\n';
    char curWord[20];
    memset(curWord, 0, sizeof(curWord));
    bool isCorrupted = false;
    k = 0;
    cout << "3) ";
    for (int i = 0; i < strlen(str); i++) {
        if (isInUppercase(str[i]) || isInLowercase(str[i])) {
            curWord[k] = str[i];
            k++;
        }
        else if (isDigit(str[i])) {
            isCorrupted = true;
        }
        else {
            if (!isCorrupted && curWord[0]) {
                cout << curWord << " ";
                memset(curWord, 0, sizeof(curWord));
                k = 0;
            }
            else {
                memset(curWord, 0, sizeof(curWord));
                k = 0;
            }
            isCorrupted = false;
        }
    }
    /*str[k] = '.';
    k++; */
    for (int i = 0; i < strlen(str); i++) {
        if (isInUppercase(str[i])) str[i] = char(int(str[i]) + 32);
    }
    cout << "\n4) " << str << '\n';
    linearSearch(str);
    BMASearch(str);
}


