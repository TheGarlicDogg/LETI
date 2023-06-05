#include <iostream>
#include <ctime>
#include <chrono>
#include <conio.h>
using namespace std;
struct list_item {
    int inf;
    list_item* head;
    list_item* tail;
};
list_item *createList(int n) {
    list_item *cur = 0, *prevcur = 0;
    cur = new list_item;
    cur->tail = prevcur;
    prevcur = cur;
    for (int i = 1; i < n; i++) {
        cur = new list_item;
        cur->tail = prevcur;
        prevcur->head = cur;
        prevcur = cur;
    }
    cur->head = 0;
    return cur;
}
void getItemByIndex(list_item* list, int index) {
    auto start = chrono::high_resolution_clock::now();
    list_item* cur = list;
    for (int i = 0; i < index; i++){
        cur = cur->tail;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end-start;
    cout << "Элементом под индексом <" << index << "> является " << cur->inf << " Элемент найден за " << fixed << duration.count() << " сек." <<  endl << endl;
}
void getItemByInfo(list_item* list, int info, int n) {
    auto start = chrono::high_resolution_clock::now();
    list_item* cur = list;
    int i = 0;
    while (i<n){
        if (cur->inf == info) {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<float> duration = end - start;
            cout << "Элемент " << info << " находится под индексом <" << i << "> Элемент найден за " << fixed << duration.count() << " сек." << endl << endl;
            return;
        }
        cur = cur->tail;
        i++;
    }
    cout << "Такого элемента не существует\n\n";
}
void insItem(list_item*& list, int index, int info, int* n) {
    auto start = chrono::high_resolution_clock::now();
    list_item* cur = list;
    list_item* newitem = new list_item;
    newitem->inf = info;
    if (index == 0) {
        list->head = newitem;
        newitem->head = 0;
        newitem->tail = list;
        list = newitem;
    }
    if (index == *n) {
        for (int i = 1; i < *n; i++) {
            cur = cur->tail;
        }
        cur->tail = newitem;
        newitem->head = cur;
        newitem->tail = 0;
    }
    if (index > 0 && index < *n) {
        for (int i = 0; i < index; i++) {
            cur = cur->tail;
        }
        cur->head->tail = newitem;
        newitem->head = cur->head;
        newitem->tail = cur;
        cur->head = newitem;
    }
    (*n)++;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cur = list;
    cout << "Ваш отредактированный список: ";
    for (int i = 0; i < *n; i++) {
        cout << cur->inf << " ";
        cur = cur->tail;
    }
    cout << "Элемент вставлен за " << fixed << duration.count() << " сек." << endl << endl;
}
void delItemById(list_item* &list, int index, int *n) {
    auto start = chrono::high_resolution_clock::now();
    list_item* cur = list;
    if (index == 0 && *n == 1) {
        delete list;
        n--;
        cout << "Список пуст.\n\n";
        return;
    }
    if (index == 0) {
        cur = cur->tail;
        delete list; // []
        list = cur;
        cur->head = 0;
    }
    if (index == *n - 1) {
        for (int i = 1; i < *n; i++) {
            cur = cur->tail;
        }
        cur->head->tail = 0;
        delete cur;

    }
    if (index > 0 && index < *n - 1) {
        for (int i = 0; i < index; i++) {
            cur = cur->tail;
        }
        cur->head->tail = cur->tail;
        cur->tail->head = cur->head;
        delete cur;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cur = list;
    cout << "Ваш отредактированный список: ";
    for (int i = 1; i < *n; i++) {
        cout << cur->inf << " ";
        cur = cur->tail;
    }
    cout << "Элемент удален за " << fixed << duration.count() << " сек." << endl << endl;
}
void delItemByInfo(list_item* &list, int info, int* n) {
    auto start = chrono::high_resolution_clock::now();
    list_item* cur = list;
    int i = 0;
    bool fl = false;
    if (list->inf == info && *n == 1) {
        delete list;
        (*n)--;
        cout << "Список пуст.\n\n";
        return;
    }
    while (i < *n) {
        if (cur->inf == info) {
            if (i == 0) {
                cur = cur->tail;
                delete list;
                cur->head = 0;
                list = cur;
                fl = true;
                break;
            }
            if (i == *n - 1) {
                cur->head->tail = 0;
                delete cur;
                fl = true;
                break;
            }
            if (i > 0 && i < *n - 1) {
                cur->head->tail = cur->tail;
                cur->tail->head = cur->head;
                delete cur;
                fl = true;
                break;
            }
        }
        cur = cur->tail;
        i++;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cur = list;
    if (fl) {
        (*n)--;
        cout << "Ваш отредактированный список: ";
        for (int i = 0; i < *n; i++) {
            cout << cur->inf << " ";
            cur = cur->tail;
        }
        cout << "Элемент удален за " << fixed << duration.count() << " сек." << endl << endl;
    }
    else {
        cout << "Такого элемента не существует. Текущий список: \n";
        for (int i = 0; i < *n; i++) {
            cout << cur->inf << " ";
            cur = cur->tail;
        }
        cout << endl << endl;
    }
}
void swapItems(list_item*& list, int index1, int index2, int n) {
    auto start = chrono::high_resolution_clock::now();
    list_item* first = list;
    list_item* second = list;
    if (index2 < index1) {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }
    for (int i = 0; i < index1; i++) {
        first = first->tail;
    }
    for (int i = 0; i < index2; i++) {
        second = second->tail;
    }
    if (index1 + 1 != index2) {
        list_item* temp = new list_item;
        temp->head = first->head;
        temp->tail = first->tail;
        if (index1 != 0) first->head->tail = second;// проверить что если первый - последний
        first->tail->head = second;
        first->head = second->head;
        first->tail = second->tail;
        second->head->tail = first;
        if (index2 != n - 1) second->tail->head = first;
        second->head = temp->head;
        second->tail = temp->tail;
        if (index1 == 0) list = second;
        delete temp;
    }
    else {
        if (index1 != 0) first->head->tail = second;
        if (index2 != n-1) second->tail->head = first;
        first->tail = second->tail;
        second->head = first->head;
        first->head = second;
        second->tail = first;
        if (index1 == 0) list = second;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    first = list;
    for (int i = 0; i < n; i++) {
        cout << first->inf << " ";
        first = first->tail;
    }

    cout << "Элементы обменяны за " << fixed << duration.count() << " сек." << endl << endl;
}
void silentSwapItems(list_item*& list, int index1, int index2, int n) {
    list_item* first = list;
    list_item* second = list;
    if (index2 < index1) {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }
    for (int i = 0; i < index1; i++) {
        first = first->tail;
    }
    for (int i = 0; i < index2; i++) {
        second = second->tail;
    }
    if (index1 + 1 != index2) {
        list_item* temp = new list_item;
        temp->head = first->head;
        temp->tail = first->tail;
        if (index1 != 0) first->head->tail = second;// проверить что если первый - последний
        first->tail->head = second;
        first->head = second->head;
        first->tail = second->tail;
        second->head->tail = first;
        if (index2 != n - 1) second->tail->head = first;
        second->head = temp->head;
        second->tail = temp->tail;
        if (index1 == 0) list = second;
        delete temp;
    }
    else {
        if (index1 != 0) first->head->tail = second;
        if (index2 != n - 1) second->tail->head = first;
        first->tail = second->tail;
        second->head = first->head;
        first->head = second;
        second->tail = first;
        if (index1 == 0) list = second;
    }
}
int* addarritem(int* arr, int n) {
    int* dest = new int[n+1];
    for (int i = 0; i < n; i++) {
        dest[i] = arr[i];
    }
    delete[] arr;
    return dest;
}
void bubbleSortList(list_item*& list, int n) {
    int fixn = n;
    list_item* cur = list;
    for (; n != 1; n--) {
        for (int i = 0; i < n - 1; i++) {
            if (cur->inf > cur->tail->inf) {
                silentSwapItems(list, i, i + 1, fixn);
            }
            else {
                cur = cur->tail;
            }
        }
        cur = list;
    }
    cur = list;
    for (int i = 0; i < fixn; i++) {
        cout << cur->inf << " ";
        cur = cur->tail;
    }
    cout << endl << endl;
}
void shakerSortList(list_item*& list, int n) {
    auto start1 = chrono::high_resolution_clock::now();
    list_item* cur = list;
    bool swapped = true;
    int start = 0;
    int fixedn = n;
    while (swapped) {
        swapped = false;
        for (int i = start; i < n - 1; ++i) {
            if (cur->inf > cur->tail->inf) {
                silentSwapItems(list, i, i+1, fixedn);
                swapped = true;
            }
            else {
                cur = cur->tail;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --n;
        cur = cur->head;
        for (int i = n - 2; i >= start; --i) {
            if (cur->inf < cur->head->inf) {
                silentSwapItems(list, i, i + 1, fixedn);
                swapped = true;
            }
            else {
                cur = cur->head;
            }
        }
        ++start;
        cur = cur->tail;
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end1 - start1;
    cur = list;
    for (int i = 0; i < fixedn; i++) {
        cout << cur->inf << " ";
        cur = cur->tail;
    }
    cout << endl << "Список отсортирован за " << fixed << duration.count() << " сек." << endl << endl;
}
void shakerSortArr(int* arr, int n) {
    auto start1 = chrono::high_resolution_clock::now();
    bool swapped = true;
    int start = 0;
    int fixn = n;
    while (swapped) {
        swapped = false;
        for (int i = start; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --n;
        for (int i = n - 2; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
    auto end1= chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end1 - start1;
    for (int i = 0; i < fixn; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << "Массив отсортирован за " << fixed << duration.count() << " сек." << endl << endl;
}
int main(){
    setlocale(0, "");
    srand(time(0));
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto start1 = chrono::high_resolution_clock::now();
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<float> duration;
    chrono::duration<float> duration1;
    int n = 0, action;
    int* pn = &n;
    int m = 1;
    char ch;
    int* manarr = new int [m];
    list_item* list = 0;
    list_item* cur = list;
    int* shakeArr = new int[n];
    while (true) {
        cout << "Введите номер нужной команды:\n1. Создать двусвязный список\n2. Вставить новый элемент в список\n3. Удалить элемент из списка\n4. Получить элемент списка\n5. Обменять элементы списка\n>> Команда №";
        cin >> action;
        cout << endl;
        switch (action) {
        case(1):
            while (true) {
                cout << "Создать список:\n1. Автоматически заполнить список размера N случайными числами;\n2. Вручную\n>> Команда №";
                cin >> action;
                cout << endl;
                if (action == 1) {
                    cout << "Введите количество элементов: ";
                    cin >> n;
                    auto start = chrono::high_resolution_clock::now();
                    list = createList(n);
                    list_item* cur = list;
                    while (cur) {
                        cur->inf = rand() % 100;
                        cur = cur->tail;
                    }
                    cur = list;
                    auto end = chrono::high_resolution_clock::now();
                    cout << "Ваш созданный список: ";
                    while (cur) {
                        cout << cur->inf << " ";
                        cur = cur->tail;
                    }
                    
                    duration = end - start;
                    cout << "\nСписок создан за " << fixed << duration.count() << " сек." << endl << endl;
                    break;
                }
                if (action == 2) { //подробнее вход
                    int i = 0;
                    char ch;
                    start1 = chrono::high_resolution_clock::now();
                    end1 = chrono::high_resolution_clock::now();
                    duration1 = end1 - start1;
                    cout << "Введите элементы через пробел, чтобы закончить ввод - нажмите Enter:\n";
                    while (cin >> manarr[i]) {
                        start1 = chrono::high_resolution_clock::now();
                        if (i + 1 == m) {
                            manarr = addarritem(manarr, m);
                            m++;
                        }
                        i++;
                        ch = getchar();
                        end1 = chrono::high_resolution_clock::now();
                        duration1 += end1 - start1;
                        if (ch == '\n') break;
                    }
                    n = m-1;
                    start = chrono::high_resolution_clock::now();
                    list = createList(i);
                    list_item* cur = list;
                    i = 0;
                    while (cur) {
                        cur->inf = manarr[i];
                        cur = cur->tail;
                        i++;
                    }
                    
                    cur = list;
                    end = chrono::high_resolution_clock::now();
                    duration = end - start + duration1;
                    cout << "\nСписок создан за " << fixed << duration.count() << " сек." << endl;
                    break;
                }
                cin.clear();
                cout << "Неверно введен номер команды. Попробуйте еще раз.\n";
            }
            break;
        case(2):
            if (n == 0) {
                cout << "В списке нет элементов\n";
                break;
            }
            cout << "Введите индекс нового элемента (текущий индекс последнего элемента - " << n-1 << "): ";
            int index, info;
            cin >> index;
            if (index > n || index < 0) {
                cout << "Невозможно добавить элемент по такому индексу\n\n";
                cin.clear();
            }
            if (index >= 0 && index <= n) {
                cout << "Введите значение: ";
                cin >> info;
                if (info == 2147483647) {
                    cin.clear();
                    cout << "Невозможно добавить такой элемент\n\n";
                    break;
                }
                insItem(list, index, info, pn);
            }
            break;
        case(3):
            if (n == 0) {
                cout << "В списке нет элементов\n";
                break;
            }
            while (true) {
                cout << "Удалить элемент:\n1. По индексу\n2. По значению (из нескольких одинаковых удаляет первый)\n>> Команда №";
                cin >> action;
                if (action == 1) {
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    if (index >= n) {
                        cout << "Невозможно удалить несуществующий элемент\n\n";
                        break;
                    }
                    cout << endl;
                    if (index >= 0 && index < n) {
                        delItemById(list, index, pn);
                        n--;
                    }
                    else {
                        cin.clear();    
                        cout << "Такого индекса не существует\n\n";
                    }
                    break;
                }
                if (action == 2) {
                    cout << "Введите значение: ";
                    int info;
                    cin >> info;
                    cout << endl;
                    delItemByInfo(list, info, pn);
                    cin.clear();
                    break;
                }
                cin.clear();
                cout << "Неверно введен номер команды. Попробуйте еще раз.\n";
            }
            break;
            /*cout << "Введите индекс: ";
            int index;
            cin >> index;
            if (index >= n) {
                cout << "Невозможно удалить несуществующий элемент\n\n";
                break;
            }
            delItemById(list, index, n);
            n--;
            break;
            */
        case(4):
            if (n == 0) {
                cout << "В списке нет элементов\n";
                break;
            }
            while (true) {
                cout << "Найти элемент:\n1. По индексу\n2. По значению\n>> Команда №";
                cin >> action;
                if (action == 1) {
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    cout << endl;
                    if (index >= 0 && index < n) {
                        getItemByIndex(list, index);
                    }
                    else {
                        cin.clear();
                        cout << "Такого индекса не существует\n\n";
                    }
                    break;
                }
                if (action == 2) {
                    cout << "Введите значение: ";
                    int info;
                    cin >> info;
                    cout << endl;
                    getItemByInfo(list, info, n);
                    cin.clear();
                    break;
                }
                cin.clear();
                cout << "Неверно введен номер команды. Попробуйте еще раз.\n";
            }
            break;
        case(5):
            if (n == 0) {
                cout << "В списке нет элементов\n";
                break;
            }
            cout << "Введите индекс первого элемента: ";
            int index1, index2;
            cin >> index1;
            if (index1 >= n || index1 < 0) {
                cout << "Невозможно обменять элемент по такому индексу\n\n";
                cin.clear();
            } else{
                cout << "Введите индекс второго элемента: ";
                cin >> index2;
                if (index2 == index1) {
                    cout << "Невозможно обменять один и тот же элемент\n\n";
                    break;
                }
                if (index2 >= n || index2 < 0) {
                    cout << "Невозможно обменять элемент по такому индексу\n\n";
                    cin.clear();
                }
                else {
                    swapItems(list, index1, index2, n);
                }
                cin.clear();
            }
            break;
        case(6):
            bubbleSortList(list, n);
            break;
        case(7):
            cur = list;
            for (int i = 0; i < n; i++) {
                shakeArr[i] = cur->inf;
                cur = cur->tail;
            }
            shakerSortList(list, n);
            
            shakerSortArr(shakeArr, n);
           
            break;
        default:
            cin.clear();
            cout << "Неверно введен номер команды. Попробуйте еще раз.\n\n";
            break;
        }
    }
    return 0;
}
