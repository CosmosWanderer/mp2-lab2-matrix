// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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
    TDynamicVector(size_t size = 1)
    {
        if (size > MAX_VECTOR_SIZE || size < 0) throw out_of_range("Vector size is incorrect");
        sz = size;
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    
    TDynamicVector(T* arr, size_t s)
    {
        if (s > MAX_VECTOR_SIZE || s < 0) throw out_of_range("Vector size is incorrect");
        sz = s;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = arr[i];
        }
    }

    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }

    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = std::move(v.pMem);
        v.pMem = nullptr;
        sz = v.sz;
        v.sz = 0;

    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            delete[] pMem; 
            sz = v.sz;
            pMem = new T[sz];
            for (int i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }
        }

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            pMem = std::move(v.pMem);
            v.pMem = nullptr;
            sz = v.sz;
            v.sz = 0;
        }
        return *this;
    }

    size_t size() const noexcept 
    { 
        return sz; 
    }

    // индексация
    T& operator[](size_t ind)
    {
        return this->pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        return this->pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind > sz - 1) throw out_of_range("Index is incorrect");
        return this->pMem[ind]; 
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind > sz - 1) throw out_of_range("Index is incorrect");
        return this->pMem[ind];
    }

  // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (this == &v) return 1;
        if (sz != v.sz) return 0;
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return 0;
        }
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

  // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
  TDynamicVector operator*(double val)
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw logic_error("Vectors have different sizes");
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw logic_error("Vectors have different sizes");;
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }

    T operator*(const TDynamicVector& v) //noexcept(noexcept(T())) Это что и зачем? Оно тесты руинит
    {
        if (sz != v.sz) throw logic_error("Vectors have different sizes");
        T res = 0;
        for (int i = 0; i < sz; i++) {
            res += pMem[i] * v.pMem[i];
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
        if (s > MAX_MATRIX_SIZE || s < 0) throw out_of_range("Size is incorrect");
        for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (this == &m) return 1;
        if (sz != m.sz) return 0;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) {
                return 0;
            }
        }
        return 1;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m)
    }

    // получение размера
    size_t size() const noexcept
    {
        return sz;
    }
    
    // индексация с контролем
    T& at(int ind1, int ind2)
    {
        if (ind1 < 0 || ind1 > sz - 1 || ind2 < 0 || ind2 > sz - 1) throw out_of_range("Index is incorrect");
        return pMem[ind1][ind2];
    }     
    const T& at(int ind1, int ind2) const
    {
        if (ind1 < 0 || ind1 > sz - 1 || ind2 < 0 || ind2 > sz - 1) throw out_of_range("Index is incorrect");
        return pMem[ind1][ind2];
    }
    
    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> res(sz);
        res.pMem = pMem * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw logic_error("Vectors have different sizes");

        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = pMem[i] * v;
        }

        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.size()) throw logic_error("Matrices have different sizes");
        
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + m.pMem[i];
        }
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        
        if (sz != m.size()) throw logic_error("Matrices have different sizes");
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + m.pMem[i];
        }
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.size()) throw logic_error("Matrices have different sizes");
        
        TDynamicMatrix<T> res(sz);
        
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                res.pMem[i][j] = 0;
            }
        }

        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                for (int j = 0; j < sz; j++) {
                    res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }

        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (int i = 0; i < m.sz; i++) cin >> m.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (int i = 0; i < m.sz; i++) cout << m.pMem[i] << endl;
        return ostr;
    }
};

#endif
