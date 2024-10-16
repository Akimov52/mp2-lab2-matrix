// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Requested vector size exceeds maximum allowable size");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(0), pMem(nullptr)
    {
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        TDynamicVector temp(v);
        swap(*this, temp);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
            swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of bounds");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of bounds");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of bounds");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of bounds");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        for (size_t i = 0; i < sz; ++i)
            if (pMem[i] != v.pMem[i])
                return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] + val;
        return result;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] - val;
        return result;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] * val;
        return result;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw length_error("Vectors must be of the same size");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] + v.pMem[i];
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw length_error("Vectors must be of the same size");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] - v.pMem[i];
        return result;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw length_error("Vectors must be of the same size");
        T result = T();
        for (size_t i = 0; i < sz; ++i)
            result += pMem[i] * v.pMem[i];
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        swap(lhs.sz, rhs.sz);
        swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size exceeds maximum allowed size");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    T& at(size_t row, size_t col)
    {
        if (row >= sz || col >= sz)
            throw out_of_range("Index is out of range");
        return pMem[row].at(col);
    }

    const T& at(size_t row, size_t col) const
    {
        if (row >= sz || col >= sz)
            throw out_of_range("Index is out of range");
        return pMem[row].at(col);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;
        for (size_t i = 0; i < sz; ++i)
            if (pMem[i] != m.pMem[i])
                return false;
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] * val;
        return result;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw length_error("Matrix and vector dimensions do not match");
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i)
            result[i] = pMem[i] * v;
        return result;

    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw length_error("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] + m.pMem[i];
        return result;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw length_error("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
            result.pMem[i] = pMem[i] - m.pMem[i];
        return result;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw length_error("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
            {
                result[i][j] = T();
                for (size_t k = 0; k < sz; ++k)
                    result[i][j] += pMem[i][k] * m.pMem[k][j];
            }
        return result;
    }
    
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << endl;
        return ostr;
    }
};

#endif