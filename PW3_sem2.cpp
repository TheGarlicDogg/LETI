#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Stack {
    string item;
    Stack* tail;
};
bool isOperator(char sym) {
    if (sym == '(' || sym == ')' || sym == '+' || sym == '-' || sym == '*' || sym == '/') return true;
    else return false;
}
int weight(char sym) {
    switch (sym) {
    case '(': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    default: return -1;
    }
}
string* reverseArr(string* arr, int n) {
    int i, j;
    string temp;
    j = n - 1;
    for (int i = 0; i < j; i++, j--) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}
void displayCurrentState(string *output, string* operst, int k1, int k2) {
    cout << "Состояние вывода: ";
    for (int i = 0; i < k1; i++) {
        cout << output[i] << " ";
    }
    cout << "\nСостояние стека: ";
    for (int i = 0; i < k2; i++) {
        cout << operst[i] << " ";
    }
    cout << endl;
}
string* transformToPostfix(string* src, int n, bool isDisplayed) {
    Stack* st = 0;
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    string* output = new string [n];
    string operst[100];
    int k1 = 0, k2 = 0;
    for (int i = 0; i < n; i++) {
        if (!isOperator(arr[i][0])) {
            output[k1] = arr[i];
            k1++;
        }
        else { //если оператор
            if (arr[i][0] == ')') {
                while (st->item[0] != '(') {
                    output[k1] = st->item;
                    k1++;
                    Stack* cur = st;
                    st = st->tail;
                    k2--;
                    if (isDisplayed) displayCurrentState(output, operst, k1, k2);
                }
                Stack* cur = st;
                st = st->tail;
                k2--;
                continue;
            }
            while (arr[i][0] != '(' && st && (weight(st->item[0]) >= weight(arr[i][0]))) {
                output[k1] = st->item;
                k1++;
                Stack* cur = st;
                st = st->tail;
                k2--;
                if (isDisplayed) displayCurrentState(output, operst, k1, k2);
            }
            Stack* cur = new Stack;
            cur->tail = st;
            st = cur;
            st->item = arr[i];
            operst[k2] = arr[i][0];
            k2++;
        }
        if (isDisplayed) displayCurrentState(output, operst, k1, k2);
    }

    while (st) {
        output[k1] = st->item;
        k1++;
        Stack* cur = st;
        st = st->tail;
        k2--;
        if (isDisplayed) displayCurrentState(output, operst, k1, k2);
    }
    if (isDisplayed) {
        cout << "\nВыражение в обратной польской нотации: ";
        for (int i = 0; i < k1; i++) {
            cout << output[i] << " ";
        }
        cout << endl << endl;
    }

    return output;
}
string* transformToPrefix(string* src, int n, int countbr, bool isDisplayed) {
    Stack* st = 0;
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    string output[100];
    string operst[100];
    arr = reverseArr(arr, n);
    cout << "Развернем выражение: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int k1 = 0, k2 = 0;
    for (int i = 0; i < n; i++) {
        if (!isOperator(arr[i][0])) {
            output[k1] = arr[i];
            k1++;
        }
        else { //если оператор
            if (arr[i][0] == '(') {
                while (st->item[0] != ')') {
                    output[k1] = st->item;
                    k1++;
                    Stack* cur = st;
                    st = st->tail;
                    k2--;
                    if (isDisplayed) displayCurrentState(output, operst, k1, k2);
                }
                Stack* cur = st;
                st = st->tail;
                k2--;
                continue;
            }
            while (arr[i][0] != ')' && st && (weight(st->item[0]) > weight(arr[i][0]))) {
                output[k1] = st->item;
                k1++;
                Stack* cur = st;
                st = st->tail;
                k2--;
                if (isDisplayed) displayCurrentState(output, operst, k1, k2);
            }
            Stack* cur = new Stack;
            cur->tail = st;
            st = cur;
            st->item = arr[i];
            operst[k2] = arr[i][0];
            k2++;
        }
        if (isDisplayed) displayCurrentState(output, operst, k1, k2);
    }

    while (st) {
        output[k1] = st->item;
        k1++;
        Stack* cur = st;
        st = st->tail;
        k2--;
        if (isDisplayed) displayCurrentState(output, operst, k1, k2);
    }
    reverseArr(output, n-countbr);
    if (isDisplayed) {
        cout << "\nРазвернем и получим выражение в прямой польской нотации: ";
        for (int i = 0; i < k1; i++) {
            cout << output[i] << " ";
        }
        cout << endl << endl;
    }
    return output;
}
int checkInfix(string* src, int n, int count, int countbr, bool isDisplayed) {
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    int curn = 0;
    bool isOperand = 0; // prev
    if (countbr%2!= 0 || count + 1 != n - count - countbr) {
        cout << "Выражение введено неверно." << endl << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i][0] == '(' || arr[i][0] == ')') {
            if (arr[i][0] == '(') {
                if (isOperand) {
                    cout << "Выражение введено неверно." << endl << endl;
                    return 0;
                }
            }
            if (arr[i][0] == ')') {
                if (!isOperand) {
                    cout << "Выражение введено неверно." << endl << endl;
                    return 0;
                }
            }
            continue;
        }
        if (isOperator(arr[i][0])) {
            if (!isOperand) {
                cout << "Выражение введено неверно." << endl << endl;
                return 0;
            }
            isOperand = 0;
        }
        else {
            if (isOperand) {
                cout << "Выражение введено неверно." << endl << endl;
                return 0;
            }
            isOperand = 1;
        }
    }
    if (isDisplayed) cout << "Выражение введено верно." << endl << endl;
    return 1;
}
int checkPostfix(string* src, int n, int count, int countbr, bool isDisplayed) {
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    int curn = 0;
    if (countbr != 0 || count+1 != n-count) {
        cout << "Выражение введено неверно." << endl << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (isOperator(arr[i][0])) curn--;
        else curn++;
        if (!curn) {
            cout << "Выражение введено неверно." << endl << endl;
            return 0;
        }
    }
    if (isDisplayed) cout << "Выражение введено верно." << endl << endl;
    return 1;
}
int checkPrefix(string* src, int n, int count, int countbr, bool isDisplayed) {
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    arr = reverseArr(arr, n);
    int curn = 0;
    if (countbr != 0 || count + 1 != n - count) {
        cout << "Выражение введено неверно." << endl << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (isOperator(arr[i][0])) curn--;
        else curn++;
        if (!curn) {
            cout << "Выражение введено неверно." << endl << endl;
            return 0;
        }
    }
    if (isDisplayed) cout << "Выражение введено верно." << endl << endl;
    return 1;
}
void calcPostfix(string* src, int n) {
    string var;
    string ststate[100];
    Stack* st = 0;
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (isOperator(arr[i][0])) {
            if (arr[i][0] == '+'){
                cout << noshowpoint << "> Вычислим: " << stod(st->tail->item) << " + " << stod(st->item) << " = " << stod(st->tail->item) + stod(st->item) << endl;
                    st->tail->item = to_string(stod(st->tail->item) + stod(st->item));
            }
            if (arr[i][0] == '-') {
                cout << noshowpoint << "> Вычислим: " << stod(st->tail->item) << " - " << stod(st->item) << " = " << stod(st->tail->item) - stod(st->item) << endl;
                st->tail->item = to_string(stod(st->tail->item) - stod(st->item));
            }
            if (arr[i][0] == '*') {
                cout << noshowpoint << "> Вычислим: " << stod(st->tail->item) << " * " << stod(st->item) << " = " << stod(st->tail->item) * stod(st->item) << endl;
                st->tail->item = to_string(stod(st->tail->item) * stod(st->item));

            }
            if (arr[i][0] == '/') {
                cout << noshowpoint << "> Вычислим: " << stod(st->tail->item) << " / " << stod(st->item) << " = " << stod(st->tail->item) / stod(st->item) << endl;
                st->tail->item = to_string((stod(st->tail->item)) / stod(st->item));
            }
            st = st->tail;
            k--;
            ststate[k-1] = st->item;
        }
        else {
            if (!isdigit(arr[i][0])) {
                cout << "Введите значение переменной " << arr[i] << ": ";
                cin >> var;
                arr[i] = var;
            }
            Stack* cur = new Stack;
            cur->tail = st;
            st = cur;
            st->item = arr[i];
            ststate[k] = arr[i];
            k++;
        }
        cout << "Состояние стека: ";
        for (int j = 0; j < k; j++) {
            if (ststate[j].find('.') != string::npos) {
                ststate[j].erase(ststate[j].find_last_not_of('0') + 1, string::npos);
                if (ststate[j][ststate[j].length()-1] == '.') ststate[j].pop_back();
            }
            cout << ststate[j] << " ";
        }
        cout << endl;
    }
    cout << "Ответ: " << ststate[0] << endl << endl;
}
void calcPrefix(string* src, int n) {
    string var;
    string ststate[100];
    Stack* st = 0;
    string* arr = new string[n];
    memcpy(arr, src, n * sizeof(string));
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    arr = reverseArr(arr, n);
    cout << "Развернем выражение: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (isOperator(arr[i][0])) {
            if (arr[i][0] == '+') {
                cout << noshowpoint << "> Вычислим: " << stod(st->item) << " + " << stod(st->tail->item) << " = " << stod(st->item) + stod(st->tail->item) << endl;
                st->tail->item = to_string(stod(st->item) + stod(st->tail->item));
            }
            if (arr[i][0] == '-') {
                cout << noshowpoint << "> Вычислим: " << stod(st->item) << " - " << stod(st->tail->item) << " = " << stod(st->item) - stod(st->tail->item) << endl;
                st->tail->item = to_string(stod(st->item) - stod(st->tail->item));
            }
            if (arr[i][0] == '*') {
                cout << noshowpoint << "> Вычислим: " << stod(st->item) << " * " << stod(st->tail->item) << " = " << stod(st->item) * stod(st->tail->item) << endl;
                st->tail->item = to_string(stod(st->item) * stod(st->tail->item));

            }
            if (arr[i][0] == '/') {
                cout << noshowpoint << "> Вычислим: " << stod(st->item) << " / " << stod(st->tail->item) << " = " << stod(st->item) / stod(st->tail->item) << endl;
                st->tail->item = to_string((stod(st->item) / stod(st->tail->item)));
            }
            st = st->tail;
            k--;
            ststate[k - 1] = st->item;
        }
        else {
            if (!isdigit(arr[i][0])) {
                cout << "Введите значение переменной " << arr[i] << ": ";
                cin >> var;
                arr[i] = var;
            }
            Stack* cur = new Stack;
            cur->tail = st;
            st = cur;
            st->item = arr[i];
            ststate[k] = arr[i];
            k++;
        }
        cout << "Состояние стека: ";
        for (int j = 0; j < k; j++) {
            if (ststate[j].find('.') != string::npos) {
                ststate[j].erase(ststate[j].find_last_not_of('0') + 1, string::npos);
                if (ststate[j][ststate[j].length() - 1] == '.') ststate[j].pop_back();
            }
            cout << ststate[j] << " ";
        }
        cout << endl;
    }
    cout << "Ответ: " << ststate[0] << endl << endl;
}
int main() {
    setlocale(LC_CTYPE, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input;
    ifstream File;
    File.open("input_expression.txt");
    if (!File.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    getline(File, input);
    File.close();
    int count = 0;
    int countbr = 0;
    for (int i = 0; i < input.length(); i++) {
        if (isOperator(input[i]) && input[i] != '(' && input[i] != ')') count++;
        if (input[i] == '(') countbr += 2;
    }
    string* iarr = new string[200];
    int k = 0;
    for (int i = 0; i < input.length(); i++) {
        if ((input[i]) == ' ') {
            continue;
        }
        else if (isOperator(input[i])) {
            iarr[k] = input[i];
            k++;
        }
        else { // символ
            if (i != 0 && k !=0) {
                if (input[i-1]!=' ' && !isOperator(input[i - 1])){
                    iarr[k - 1] += input[i];
                }
                else {
                    iarr[k] = input[i];
                    k++;
                }
            }
            else {
                iarr[k] = input[i];
                k++;
            }
        }
    }
    int n = k;
    string* arr = new string[n];
    for (int i = 0; i < n; i++) {
        arr[i] = iarr[i];
    }
    delete[] iarr;
    while (true) {
        cout << "1. Преобразовать выражение.\n2. Проверить корректность выражения.\n3. Вычислить выражение.\nКоманда №";
        unsigned choice;
        cin >> choice;
        switch (choice){
        case 1:
            if (checkInfix(arr, n, count, countbr, 0)) {
                cout << "1. Преобразовать в обратную польскую нотацию.\n2. Преобразовать в прямую польскую нотацию.\nКоманда №";
                cin >> choice;
                switch (choice) {
                case 1:
                    transformToPostfix(arr, n, 1);
                    break;
                case 2:
                    transformToPrefix(arr, n, countbr, 1);
                    break;
                default:
                    cout << "Команда введена неверно. Попробуйте еще раз.\n";
                    
                }
                break;
            }
            break;
        case 2:
            cout << "Как записано ваше выражение?\n1. Обратная польская нотания.\n2. Прямая польская нотация.\n3. Простое выражение.\nКоманда №";
            cin >> choice;
            switch (choice) {
            case 1:
                checkPostfix(arr, n, count, countbr, 1);
                break;
            case 2:
                checkPrefix(arr, n, count, countbr, 1);
                break;
            case 3:
                checkInfix(arr, n, count, countbr, 1);
                break;
            default:
                cout << "Команда введена неверно. Попробуйте еще раз.\n";
                break;
            }
            break;
        case 3:
            cout << "Как записано ваше выражение?\n1. Обратная польская нотания.\n2. Прямая польская нотация.\n3. Простое выражение.\nКоманда №";
            cin >> choice;
            switch (choice) {
            case 1:
                if(checkPostfix(arr, n, count, countbr, 0)) calcPostfix(arr, n);
                break;
            case 2:
                if (checkPrefix(arr, n, count, countbr, 0)) calcPrefix(arr, n);
                break;
            case 3:
                if (checkInfix(arr, n, count, countbr, 0)) calcPostfix(transformToPostfix(arr, n, 1), n-countbr);
                break;
            default:
                cout << "Команда введена неверно. Попробуйте еще раз.\n";
                break;
            }
            break;
        default:
            cout << "Команда введена неверно. Попробуйте еще раз.\n";
            break;
        }
    }
}
/*
    for (int i = 0; i < input.length(); i++) {
        if (int(input[i]) > 57 || int(input[i]) < 48) {
            int var;
            cout << "Введите значение переменной " << input[i] << ": ";
            cin >> var;
            cout <<
        }
    }
    */