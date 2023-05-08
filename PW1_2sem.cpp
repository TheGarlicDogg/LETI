#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>
#include <string>
#include <iomanip>
using namespace std;
// динамический массив, понять как записывать до конца, удалить массив, обновлять файлик
struct Student {
    string name;
    bool isMale;
    int group;
    int id;
    int marks[8];
};
Student* addStudent(Student* studArr, int num) {
    int t;
    Student newStud;
    Student* dest = new Student[num];
    for (int i = 0; i < num; i++) {
        dest[i] = studArr[i];
    }
    studArr = new Student[num + 1];
    for (int i = 0; i < num; i++) {
        studArr[i] = dest[i];
    }
    cout << "Введите ФИО студента: ";
    cin.ignore();
    getline(cin, newStud.name);
    cout << "Выберите пол студента:\n1. Мужской\n2. Женский\n";
    cin >> t;
    (t == 1) ? newStud.isMale = true : newStud.isMale = false;
    cout << "Введите номер группы студента: ";
    cin >> newStud.group;
    cout << "Введите номер студента в группе: ";
    cin >> newStud.id;
    cout << "Введите оценки студента через пробел: ";
    for (int i = 0; i < 8; i++) {
        cin >> newStud.marks[i];
    }
    studArr[num] = newStud;
    ofstream File;
    File.open("students_data.txt", ios::app);
    if (!File.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    File << "\n" << newStud.name << " " << newStud.isMale << " " << newStud.group << " " << newStud.id;
    for (int i = 0; i < 8; i++) File << " " << newStud.marks[i];
    File.close();
    
    cout << "\nНовая запись была добавлена.\n";
    system("Pause");
    system("cls");
    return studArr;
}
void editData(Student* studArr, int num) {
    cout << "\nВведите номер записи, которую нужно изменить: ";
    int k, t;
    cin >> k;
    Student* p = studArr + k - 1; //??
    cout << "Введите ФИО студента: ";
    cin.ignore();
    getline(cin, p->name);
    cout << "Выберите пол студента:\n1. Мужской\n2. Женский\n";
    cin >> t;
    (t == 1) ? p->isMale = true : p->isMale = false;
    cout << "Введите номер группы студента: ";
    cin >> p->group;
    cout << "Введите номер студента в группе: ";
    cin >> p->id;
    cout << "Введите оценки студента через пробел: ";
    for (int i = 0; i < 8; i++) {
            cin >> p->marks[i];
    }
    ofstream File;
    File.open("students_data.txt");
    if (!File.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return;
    }
    for (int i = 0; i < num; i++) {
        File << studArr[i].name << " " << studArr[i].isMale << " " << studArr[i].group << " " << studArr[i].id;
        for (int j = 0; j < 8; j++) File << " " << studArr[i].marks[j];
        if (i < num - 1) File << "\n";
    }
    
    File.close();
    cout << "\nДанные изменены.\n";
}
void showStudents(Student* studArr, int num){
    cout << "№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
    int i = 1;
    for (Student* p = studArr; p < studArr + num; p++, i++) {
        cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
        (p->isMale) ? cout << "М" : cout << "Ж";
        cout << " | " << p->group << " | " << setw(2) << p->id << " |";
        for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
        cout << endl;
    }
}
void showGroup(Student* studArr, int num) {
    cout << "Введите номер группы: ";
    int k;
    cin >> k;
    cout << "№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
    int i = 1;
    for (Student* p = studArr; p < studArr + num; p++) {
        if (p->group == k) {
            cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
            (p->isMale) ? cout << "М" : cout << "Ж";
            cout << " | " << p->group << " | " << setw(2) << p->id << " |";
            for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
            cout << endl;
            i++;
        }
    }
}
void showStudentTop(Student* studArr, int num) {
    double* marksArr = new double[num];
    int* indexArr = new int[num];
    int sum = 0, i = 0;
    for (Student* p = studArr; p < studArr + num; p++) {
        sum = 0;
        for (int j = 0; j < 8; j++) {
            sum += p->marks[j];
        }
        marksArr[i] = sum / double(8);
        indexArr[i] = i;
        i++;
    }
    for (; num != 1; num--)
        for (int i = 0; i < num - 1; i++) {
            if (marksArr[i] < marksArr[i + 1]) {
                swap(marksArr[i], marksArr[i + 1]);
                swap(indexArr[i], indexArr[i + 1]);
            }
        }
    cout << "№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i+1 << " | " << setw(32) << left << studArr[indexArr[i]].name << " | ";
        (studArr[indexArr[i]].isMale) ? cout << "М" : cout << "Ж";
        cout << " | " << studArr[indexArr[i]].group << " | " << setw(2) << studArr[indexArr[i]].id << " |";
        for (int j = 0; j < 8; j++) cout << " " << studArr[indexArr[i]].marks[j];
        cout << endl;
    }
    delete[] marksArr;
    delete[] indexArr;
}
void countGender(Student* studArr, int num) {
    int mc = 0, wc = 0;
    for (Student* p = studArr; p < studArr + num; p++) {
        if (p->isMale) mc++;
        else wc++;
    }
    cout << "Количество студентов мужского пола: " << mc << "\nКоличество студентов женского пола: " << wc << endl;
}
void showStudentsMarks(Student* studArr, int num) {
    cout << "1. Вывести список студентов, не получающих стипендию.\n2. Вывести список студентов, учащихся на «4» и «5».\n3. Вывести список студентов, учащихся на «5».\n";
    int k;
    bool fl = true;
    int i = 1;
    cin >> k;
    system("cls");
    switch (k){
    case 1:
        cout << "Список студентов, не получающих стипендию:\n№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
        for (Student* p = studArr; p < studArr + num; p++) {
            for (int j = 0; j < 8; j++) {
                if (p->marks[j] == 3 || p->marks[j] == 2) {
                    cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
                    (p->isMale) ? cout << "М" : cout << "Ж";
                    cout << " | " << p->group << " | " << setw(2) << p->id << " |";
                    for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
                    cout << endl;
                    i++;
                    break;
                }
            }
        }
        break;
    case 2:
        cout << "Список студентов, учащихся на «4» и «5»:\n№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
        for (Student* p = studArr; p < studArr + num; p++) {
            fl = true;
            for (int j = 0; j < 8; j++) {
                if (p->marks[j] == 3 || p->marks[j] == 2) {
                    fl = false;
                    break;
                }
            }
            if (fl) {
                cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
                (p->isMale) ? cout << "М" : cout << "Ж";
                cout << " | " << p->group << " | " << setw(2) << p->id << " |";
                for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
                cout << endl;
                i++;
            }
        }
        break;
    case 3:
        cout << "Список студентов, учащихся на «5»:\n№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
        for (Student* p = studArr; p < studArr + num; p++) {
            fl = true;
            for (int j = 0; j < 8; j++) {
                if (p->marks[j] == 3 || p->marks[j] == 4 || p->marks[j] == 2) {
                    fl = false;
                    break;
                }
            }
            if (fl) {
                cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
                (p->isMale) ? cout << "М" : cout << "Ж";
                cout << " | " << p->group << " | " << setw(2) << p->id << " |";
                for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
                cout << endl;
                i++;
            }
        }
        break;
    default:
        break;
    }
}
void showId(Student* studArr, int num) {
    cout << "Введите номер: ";
    int k;
    cin >> k;
    cout << "№  | " << setw(32) << left << "ФИО" << " |Пол| № гр.| №  | Оценки за сессию" << endl;
    int i = 1;
    for (Student* p = studArr; p < studArr + num; p++) {
        if (p->id == k) {
            cout << setw(2) << i << " | " << setw(32) << left << p->name << " | ";
            (p->isMale) ? cout << "М" : cout << "Ж";
            cout << " | " << p->group << " | " << setw(2) << p->id << " |";
            for (int i = 0; i < 8; i++) cout << " " << p->marks[i];
            cout << endl;
            i++;
        }
    }
}
int main(){
    setlocale(LC_CTYPE, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string nametemp1,nametemp2;
    ifstream File;
    File.open("students_data.txt");
    if (!File.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    int num = 0;
    while (!File.eof()) {
        getline(File, nametemp1);
        num++;
    }
    File.close();
    Student* studArr = new Student[num];
    
    File.open("students_data.txt");
    if (!File.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    for (int i = 0; i < num; i++) {
        File >> studArr[i].name >> nametemp1 >> nametemp2 >> studArr[i].isMale >> studArr[i].group >> studArr[i].id;
        studArr[i].name = studArr[i].name + " " + nametemp1 + " " + nametemp2;
        for (int j = 0; j < 8; j++) File >> studArr[i].marks[j];
    }
    File.close();
    short int input;
    while (true) {
        cout << "1. Cоздать новую запись о студенте\n2. Внести изменения в уже имеющуюся запись\n3. Вывести все данные о студентах\n4. Вывод информации обо всех студентах конкретной группы\n5. Вывести топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию\n6. Вывести количество студентов мужского и женского пола\n7. Вывести данные о студентах, которые не получают стипендию; учатся только на «4» и «5»; учатся только на «5»\n8. Вывод данных о студентах, имеющих конкретный номер в списке\n\nВведите номер команды: ";
        cin >> input;
        while (input < 1 || input > 8) {
            cout << "Неверно введен номер команды. Попробуйте еще раз: ";
            cin >> input;
        }
        switch (input) {
        case 1:
            studArr = addStudent(studArr, num);
            num++;
            break;
        case 2:
            system("cls");
            showStudents(studArr, num);
            editData(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 3:
            system("cls");
            showStudents(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 4:
            system("cls");
            showGroup(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 5:
            system("cls");
            showStudentTop(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 6:
            system("cls");
            countGender(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 7:
            system("cls");
            showStudentsMarks(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 8:
            system("cls");
            showId(studArr, num);
            system("Pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    system("Pause");
}
