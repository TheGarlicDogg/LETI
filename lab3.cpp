#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h> 
#include <thread>
using namespace std;

void gotoxy(int x, int y);

void snakePrint(int N, int** matrix) {
    for (int i = 0; i < N * N; i++) {
        if ((i / N) % 2 == 1) {
            gotoxy(4 * (i / N), (N - (i % N)) - 1);
            cout << setw(4) << *(*(matrix + (N - (i % N) - 1)) + (i / N)); //*( *(arr+���) + ������� ) ) )
        }
        else {
            gotoxy(4 * (i / N), (i % N));
            cout << setw(4) << *(*(matrix + (i % N)) + (i / N));
        }

        this_thread::sleep_for(0.1s);
    }
    gotoxy(0, N);
}
void upperCorner(int N, int len, int** matrix) {
    int x = 0, y = 0;
    int margin = (N - len) / 2;
    for (int i = 0; i < len * 2 - 1; i++) {
        if (i <= len - 1) {
            gotoxy(4 * (i + margin), margin);
            cout << setw(4) << *(*(matrix + margin) + (i + margin));
        }
        else {
            gotoxy(4 * (len - 1 + margin), i - len + 1 + margin);
            cout << setw(4) << *(*(matrix + (i - len + 1 + margin)) + (len - 1 + margin));
        }
        this_thread::sleep_for(0.1s);
    }
}
void lowerCorner(int N, int len, int** matrix) {
    int x = 0, y = 0;
    int margin = (N - len) / 2;
    for (int i = len * 2 - 1; i >= 1; i--) {
        if (i >= len) {
            gotoxy(4 * ((i % len) + margin), len + margin);
            cout << setw(4) << *(*(matrix + (len + margin)) + (i % len) + margin);
        }
        else {
            gotoxy(4 * margin, i + margin);
            cout << setw(4) << *(*(matrix + (i + margin)) + margin);
        }
        this_thread::sleep_for(0.1s);
    }
}
void spiralPrint(int N, int** matrix) {
    for (int len = N; len > 0; len--) {
        if (len % 2 == 0) upperCorner(N, len, matrix);
        if (len % 2 == 1) lowerCorner(N, len, matrix);
    }
    gotoxy(0, N);
}
void increaseMatrix(int** matrix, int N, int k) {
    for (int** rows = matrix, **endrows = rows + N - 1; rows <= endrows; rows++)
        for (int* curcol = *rows, *endcol = curcol + N - 1; curcol <= endcol; curcol++)
            *curcol += k;
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }

    gotoxy(0, N + 2);
}
void decreaseMatrix(int** matrix, int N, int k) {
    for (int** rows = matrix, **endrows = rows + N - 1; rows <= endrows; rows++)
        for (int* curcol = *rows, *endcol = curcol + N - 1; curcol <= endcol; curcol++)
            *curcol -= k;
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }

    gotoxy(0, N + 2);
}
void multiplyMatrix(int** matrix, int N, int k) {
    for (int** rows = matrix, **endrows = rows + N - 1; rows <= endrows; rows++)
        for (int* curcol = *rows, *endcol = curcol + N - 1; curcol <= endcol; curcol++)
            *curcol *= k;
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }

    gotoxy(0, N + 2);
}
void divideMatrix(int** matrix, int N, int k) {
    for (int** rows = matrix, **endrows = rows + N - 1; rows <= endrows; rows++)
        for (int* curcol = *rows, *endcol = curcol + N - 1; curcol <= endcol; curcol++)
            *curcol /= k;
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }

    gotoxy(0, N + 2);
}
void replaceBlocks(int N, int** matrix) {
    int** NW = new int* [N / 2], ** NE = new int* [N / 2], ** SE = new int* [N / 2], ** SW = new int* [N / 2];
    int*** newMatrix = new int** [4] {NW, NE, SE, SW};
    for (int*** nM = newMatrix, ***nMend = nM + 3; nM <= nMend; nM++) {
        for (int** curBlock = *nM, **curBlockend = curBlock + N / 2; curBlock < curBlockend; curBlock++)
            *curBlock = new int[N / 2];
    }

    for (int** rows = matrix, **endrows = rows + N / 2, **newRow = NW; rows < endrows; rows++, newRow++) {
        for (int* col = *rows, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *newCol = *col;
        }
    }
    for (int** rows = matrix, **endrows = rows + N / 2, **newRow = NE; rows < endrows; rows++, newRow++) {
        for (int* col = *rows + N / 2, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *newCol = *col;
        }
    }
    for (int** rows = matrix + N / 2, **endrows = rows + N / 2, **newRow = SW; rows < endrows; rows++, newRow++) {
        for (int* col = *rows, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *newCol = *col;
        }
    }
    for (int** rows = matrix + N / 2, **endrows = rows + N / 2, **newRow = SE; rows < endrows; rows++, newRow++) {
        for (int* col = *rows + N / 2, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *newCol = *col;
        }
    }
    cout << "\n�������� ��� �������� ��������� ��������� �������:\n1. ����������� �������� �� ������� �������\n2. ����������� �������� �� ���������\n3. ����������� �������� �� ���������\n4. ����������� �������� �� �����������" << endl;
    int option;
    cin >> option;
    int** newNW, ** newNE, ** newSW, ** newSE;
    if (option == 1) {
        newNW = SW;
        newNE = NW;
        newSW = SE;
        newSE = NE;
    }
    else if (option == 2) {
        newNW = SE;
        newNE = SW;
        newSW = NE;
        newSE = NW;
    }
    else if (option == 3) {
        newNW = SW;
        newNE = SE;
        newSW = NW;
        newSE = NE;
    }
    else {
        newNW = NE;
        newNE = NW;
        newSW = SE;
        newSE = SW;
    }
    for (int** rows = matrix, **endrows = rows + N / 2, **newRow = newNW; rows < endrows; rows++, newRow++) {
        for (int* col = *rows, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *col = *newCol;
        }
    }
    for (int** rows = matrix, **endrows = rows + N / 2, **newRow = newNE; rows < endrows; rows++, newRow++) {
        for (int* col = *rows + N / 2, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *col = *newCol;
        }
    }
    for (int** rows = matrix + N / 2, **endrows = rows + N / 2, **newRow = newSW; rows < endrows; rows++, newRow++) {
        for (int* col = *rows, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *col = *newCol;
        }
    }
    for (int** rows = matrix + N / 2, **endrows = rows + N / 2, **newRow = newSE; rows < endrows; rows++, newRow++) {
        for (int* col = *rows + N / 2, *endcol = col + N / 2, *newCol = *newRow; col < endcol; col++, newCol++) {
            *col = *newCol;
        }
    }
    system("cls");
    cout << "������� ����� ���������: " << '\n';
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }
    gotoxy(0, N + 3);
}
void sortMatrix(int N, int** matrix) {
    int n = N * N;
    int* sortArr = new int[n];
    int* adr;
    adr = sortArr;
    for (int** rows = matrix, **endrows = rows + N - 1; rows <= endrows; rows++) {
        for (int* col = *rows, *endcol = col + N - 1; col <= endcol; col++, sortArr++) {
            *sortArr = *col;
        }
    }
    sortArr = adr;
    for (; n != 1; n--) {
        for (int* cur = sortArr, *endarr = cur + n - 2; cur <= endarr; cur++) {
            if (*cur > *(cur + 1)) {
                swap(*cur, *(cur + 1));
            }
        }
    }

    for (int** rows = matrix, **rowsend = rows + N; rows < rowsend; rows++) {
        for (int* col = *rows, *colend = col + N; col < colend; col++) {
            *col = *sortArr++;
        }
    }
    sortArr = adr;
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N) + 2);
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
    }

    gotoxy(0, N + 2);
}

int drivercode3() {
    srand(time(0));
    int N;
    cout << "�������� ����������� �������: 6, 8, 10:" << "\n";
    cin >> N;
    int** matrix = new int* [N];
    for (int** row = matrix, **endrow = row + N; row < endrow; row++) {
        *row = new int[N];
    }
    for (int** row = matrix, **endrow = row + N; row < endrow; row++) {
        for (int* col = *row, *endcol = col + N; col < endcol; col++) {
            *col = rand() % (N * N) + 1;
        }
    }
    int filling;
    cout << "�������� ��� ��������� �������:\n1. ��������\n2. \"�������\"" << endl;
    cin >> filling;
    if (filling == 1) {
        system("cls");
        spiralPrint(N, matrix);
    }
    else {
        system("cls");
        snakePrint(N, matrix);;
    }
    replaceBlocks(N, matrix);
    system("Pause");
    system("cls");
    cout << "��������������� �������:";
    sortMatrix(N, matrix);
    cout << '\n' << "�������� ����� �������� ��������� � ������ ��������� �������:\n1. ��������\n2. ���������\n3. ���������\n4. ������� (������)\n";
    int operation;
    cin >> operation;
    cout << "������� �����, � ������� �������� ��������: ";
    int k;
    cin >> k;
    system("cls");
    cout << "������� ����� ���������: " << '\n';
    switch (operation) {
    case 1:
        increaseMatrix(matrix, N, k);
        break;
    case 2:
        decreaseMatrix(matrix, N, k);
        break;
    case 3:
        multiplyMatrix(matrix, N, k);
        break;
    case 4:
        divideMatrix(matrix, N, k);
        break;
    default:
        break;
    }
    system("pause");
    return 0;
}
int drivercode3idz()
{
    srand(time(0));
    setlocale(0, "");
    system("cls");
    int N;
    cout << "�������� �� ���������� ��������.\n�������� ����������� �������: 6, 8, 10:" << "\n";
    cin >> N;
    int** matrix = new int* [N];
    for (int** row = matrix, **endrow = row + N; row < endrow; row++) {
        *row = new int[N];
    }
    for (int** row = matrix, **endrow = row + N; row < endrow; row++) {
        for (int* col = *row, *endcol = col + N; col < endcol; col++) {
            *col = rand() % (N * N) + 1;
        }
    }
    system("cls");
    for (int i = 0; i < N * N; i++) {
        gotoxy(4 * (i % N), (i / N));
        cout << setw(4) << *(*(matrix + (i / N)) + i % N);;
        this_thread::sleep_for(0.05s);
    }

    // ������
    int sum;
    int lsum = 0;
    int currow = 0;
    bool fl = true;
    for (int** rows = matrix, **endrows = rows + N; rows < endrows; rows++) {
        sum = 0;
        for (int* col = *rows, *endcol = col + N; col < endcol; col++) {
            sum += *col;
        }
        gotoxy(4 * (N + 1), currow);
        cout << sum;
        if (lsum != sum and lsum != 0) {
            fl = false;
        }
        else {
            lsum = sum;
        }
        currow++;
        this_thread::sleep_for(0.1s);
    }
    // �������
    ;
    for (int colnum = 0, **rows = matrix; colnum < N; colnum++) {
        sum = 0;
        for (int i = 0; i < N; i++) {
            sum += *(*(rows + i) + colnum);
        }
        gotoxy(4 * colnum + 1, N + 1);
        cout << sum;
        if (lsum != sum and lsum != 0) {
            fl = false;
        }
        else {
            lsum = sum;
        }
        this_thread::sleep_for(0.1s);
    }
    // ���������
    sum = 0;
    for (int i = 0; i < N; i++) {
        sum += *(*(matrix + i) + i);
    }
    gotoxy(4 * (N + 1), N + 1);
    cout << sum;
    if (lsum != sum and lsum != 0) {
        fl = false;
    }
    else {
        lsum = sum;
    }
    if (fl) cout << "\n��� ������� �������� ���������� ���������";
    else cout << "\n��� ������� �� �������� ���������� ���������";
    return 1;
}

