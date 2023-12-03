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
        if (size > MAX_VECTOR_SIZE) throw length_error("Vector size is too large!");
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (s > MAX_VECTOR_SIZE) throw length_error("Vector size is too large!");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];

        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (pMem != v.pMem) {

            if (sz != v.sz) {
                delete[] pMem;
                sz = v.sz;
                pMem = new T[v.sz];
            }

            for (size_t i = 0; i < v.sz; i++) {
                pMem[i] = v.pMem[i];
            }
        }

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        std::swap(sz, v.sz);
        std::swap(pMem, v.pMem);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz) throw std::out_of_range("Out of range!");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz) throw std::out_of_range("Out of range!");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;

        for (size_t i = 0; i < sz; i++) {

            if (pMem[i] != v[i]) {
                return false;
            }

        }

        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return true;

        for (size_t i = 0; i < sz; i++) {

            if (pMem[i] != v[i]) {
                return true;
            }

        }

        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + val;
        }

        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - val;
        }

        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }

        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw std::length_error("The sizes are not equal!");
        }

        TDynamicVector res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + v[i];
        }

        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw std::length_error("The sizes are not equal!");
        }

        TDynamicVector res(sz);

        for (size_t i = 0; i < v.sz; i++) {
            res[i] = pMem[i] - v[i];
        }

        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) {
            throw std::length_error("The sizes are not equal!");
        }

        T res = 0;

        for (size_t i = 0; i < v.sz; i++) {
            res += pMem[i] * v[i];
        }

        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
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
        if (s > MAX_MATRIX_SIZE) {
            throw std::length_error("Too large matrix size!");
        }

        sz = s;
        pMem = new TDynamicVector<T>[sz];

        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    size_t size() const noexcept { return sz; }

    TDynamicMatrix& operator=(const TDynamicMatrix& v) {

        if (pMem != v.pMem) {

            if (sz != v.sz) {
                delete[] pMem;
                sz = v.sz;
                pMem = new TDynamicVector<T>[sz];
            }

            for (size_t i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }

        }

        return *this;
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) {
            return false;
        }

        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {

        if (sz != m.sz) {
            return true;
        }

        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m[i]) {
                return true;
            }
        }

        return false;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }

        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) {
            throw std::length_error("Vector and matrix dimensions must be equal!");
        }

        TDynamicVector<T> res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i] += pMem[i][j] * v[j];
            }
        }

        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("Vector and matrix dimensions must be equal!");
        }

        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + m[i];
        }

        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("Vector and matrix dimensions must be equal!");
        }

        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - m[i];
        }

        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("Vector and matrix dimensions must be equal!");
        }

        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] = 0;
                for (size_t k = 0; k < sz; k++) {
                    res[i][j] += pMem[i][k] * m[k][j];
                }
            }

        }

        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v[i]; // требуется оператор>> для типа T
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v[i] << endl; // требуется оператор>> для типа T
        }
        return ostr;
    }
};

#endif
