// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
    TDynamicMatrix<int> a(5), b(5), c(5);
    int i, j;
    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класс работы с матрицами" << endl;
    for (i = 0; i < 5; i++)
        for (j = i; j < 5; j++)
        {
            a[i][j] = i * 10 + j;
            b[i][j] = (i * 10 + j) * 100;
        }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;
    // Пример других операций
    cout << "Matrix a - b:" << endl << a - b << endl;
    cout << "Matrix a * b:" << endl << a * b << endl;
    // Пример работы с элементами матрицы через метод at
    try
    {
        cout << "Элемент a[2][3]: " << a.at(2, 3) << endl;
        a.at(2, 3) = 555;  // Изменяем значение элемента
        cout << "После изменения a[2][3]: " << a.at(2, 3) << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Ошибка доступа к элементу: " << e.what() << endl;
    }
}
//---------------------------------------------------------------------------
