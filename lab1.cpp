#include <iostream>
using namespace std;
int task1();
int task2();
int task3();
int task4();
int drivercode1();

int drivercode1() {
	task1();
	task2();
	task3();
	task4();
	return 1;
}
int task1() {
    cout << "int: " << sizeof(int) << endl << "short int: " << sizeof(short int) << endl << "long int: " << sizeof(long int) << endl << "float: " <<
        sizeof(float) << endl << "double: " << sizeof(double) << endl << "long double: " << sizeof(long double) << endl << "char: " << sizeof(char) << endl << "bool: " <<
        sizeof(bool) << endl << endl;
    return 0;

}

int task2() {
    int x;
    cout << "Введите целое число для представления в двоичной системе счисления: ";
    cin >> x;
    int m = 1;
    m <<= 31;
    for (int i = 0; i < 32; i++) {
        cout << ((x & m) ? 1 : 0);
        x <<= 1;
        if (i == 0) {
            cout << " ";
        }
    }
    cout << endl << endl;
    return 0;
}
int task3() {
    union {
        float xf;
        int xi;
    };

    cout << "Введите число типа float для представления в двоичной системе счисления: ";
    cin >> xf;
    int m = 1;
    m <<= 31;
    for (int i = 0; i < 32; i++) {
        cout << ((xi & m) ? 1 : 0);
        xi <<= 1;
        if (i == 0) {
            cout << " ";
        }
        if (i == 8) {
            cout << " ";
        }
    }
    cout << endl << endl;
    return 0;
}
int task4() {
    union {
        int xarr[2];
        double xd;
    };
    cout << "Введите число типа double для представления в двоичной системе счисления: ";
    cin >> xd;
    int m = 1;
    m <<= 31;
    for (int i = 0; i < 32; i++) {
        cout << ((xarr[1] & m) ? 1 : 0);
        xarr[1] <<= 1;
        if (i == 0) {
            cout << " ";
        }
        if (i == 11) {
            cout << " ";
        }
    }
    for (int i = 0; i < 32; i++) {
        cout << ((xarr[0] & m) ? 1 : 0);
        xarr[0] <<= 1;
    }
    cout << endl << endl;
    return 0;
}
int taskint();
int taskfloat();
int taskdouble();
int drivercode1idz();

int drivercode1idz()

//Основная идея - инверсия числа с помощью исключающего ИЛИ ( ^ )

{
		cout << "Выберите тип данных:\n" << "1.int\n" << "2.float\n" << "3.double\n";
		int answer;
		cin >> answer;
		switch (answer) {
		case 1:
			taskint();
			break;
		case 2:
			taskfloat();
			break;
		case 3:
			taskdouble();
			break;
		}
		return 0;
}
int taskint() {
	int x;
	int b; //Буфер для нашего числа
	unsigned int y = 0;
	y -= 1; //Получается число 11111111111111111111111111111111
	cout << "Введите число, которое хотите инвертировать в двоичной системе счисления: ";
	cin >> x;
	b = x; //Сохраняем наше число 
	int m = 1;
	m <<= 31;
	for (int i = 0; i < 32; i++) { // Выводим число на экран
		cout << ((x & m) ? 1 : 0);
		x <<= 1;
	}
	cout << endl << endl;
	x = b;
	x = x ^ y;
	cout << "Ваше число было инвертировано:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << ((x & m) ? 1 : 0);
		x <<= 1;
	}
	cout << endl << endl;
	return 0;
}
int taskfloat() {
	union {
		int xi;
		float xf;
	};
	int b;
	unsigned int y = 0;
	y -= 1;
	cout << "Введите число, которое хотите инвертировать в двоичной системе счисления: ";
	cin >> xf;
	b = xi;
	int m = 1;
	m <<= 31;
	for (int i = 0; i < 32; i++) {
		cout << ((xi & m) ? 1 : 0);
		xi <<= 1;
	}
	cout << endl << endl;
	xi = b;
	xi = xi ^ y;
	cout << "Ваше число было инвертировано:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << ((xi & m) ? 1 : 0);
		xi <<= 1;
	}
	cout << endl << endl;
	return 0;
}
int taskdouble() {
	union {
		int xarr[2];
		double xd;
	};
	int b[2];
	unsigned int invert = 0;
	invert -= 1; // invert стал 4294967295 (11111...11111)
	cout << "Введите число, которое хотите инвертировать в двоичной системе счисления: ";
	cin >> xd;
	b[0] = xarr[0];
	b[1] = xarr[1];
	int m = 1;
	m <<= 31;
	for (int i = 0; i < 32; i++) {
		cout << ((xarr[1] & m) ? 1 : 0);
		xarr[1] <<= 1;
	}
	for (int i = 0; i < 32; i++) {
		cout << ((xarr[1] & m) ? 1 : 0);
		xarr[0] <<= 1;
	}
	cout << endl;
	xarr[0] = b[0];
	xarr[1] = b[1];
	xarr[0] = xarr[0] ^ invert;
	xarr[1] = xarr[1] ^ invert;
	cout << "Ваше число было инвертировано:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << ((xarr[1] & m) ? 1 : 0);
		xarr[1] <<= 1;
	}
	for (int i = 0; i < 32; i++) {
		cout << ((xarr[0] & m) ? 1 : 0);
		xarr[0] <<= 1;
	}
	cout << endl << endl;

	return 0;
}
