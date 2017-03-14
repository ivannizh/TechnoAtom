#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <vector>
#include <exception>

template <class T>
class MyIter;

template <class T>
class MyVector {

private:
    static const int QUOTA = 10;
    int cnt;
    int cur;
    T* arr;

public:
    /*!
     * \brief Пустой конструктор класса MyVector
     */
    MyVector();

    /*!
     * \brief копируюший конструктор MyVector
     * \param a
     */
    MyVector(const MyVector &a);

    /*!
     * \brief перемещающий конструктор MyVector
     * \param a
     */
    MyVector(MyVector &&a);

    /*!
     * \brief Копирующий оператор равно
     */
    MyVector& operator= (const MyVector &a);

    /*!
     * \brief Перемещающее равно
     */
    MyVector& operator= (MyVector &&a);

    /*!
     * \brief Деструктор класса MyVector
     */
    ~MyVector() { delete[] arr; }

    /*!
     * \brief Оператор индексирования lvalue
     * \param Индекс элемента
     * \return Элемент, который лежит по заданому индексу
     * \throw std::out_of_range если задан некоректный индекс
     */
    T& operator[] (int index) throw (std::out_of_range);

    /*!
     * \brief Оператор индексирования rvalue
     * \param Индекс элемента
     * \return Элемент, который лежит по заданому индексу
     * \throw std::out_of_range если задан некоректный индекс
     */
    const T& operator[](int index) const throw (std::out_of_range);

    /*!
     * \brief Возвращает текущий размер массива
     */
    size_t size() const { return cur; }

    friend class MyIter<T>;
    typedef MyIter<T> iterator;

    /*!
     * \brief Возвращает итератор, указывающий на первый элемент
     */
    iterator begin() const { return iterator(arr); }

    /*!
     * \brief Возвращает итератор, указывающий на последний элемент
     */
    iterator end() const { return iterator(arr + cur); }

    /*!
     * \brief Очищает массив
     */
    void clear();

    /*!
     * \brief Закидывает в конец новый элемент
     * \param Элемент для закидывания
     */
    void push_back(const T& t);

    /*!
     * \brief Возвращает последний элемент в массиве
     */
    T back() { return *(iterator(arr + cur - 1)); }

    /*!
     * \brief Удаляет элемент массива
     * \param Итератор, указывающий на элемнт для удаления
     */
    MyVector& erase(const iterator &it);

};

template <class T>
class MyIter{
private:
    T* cur;
public:

    /*!
     * \brief Пустой конструктор MyIter
     */
    MyIter();

    /*!
     * \brief Конструктор MyIter
     * \param it Принимает укзатель на элемнт массива
     */
    MyIter(T *it);

    /*!
     * \brief Уменьшает итератор
     * \param index на сколько надо его уменьшить
     * \return
     */
    MyIter operator- (int index) { return MyIter(cur - index); }

    /*!
     * \brief Увеличивает итератор
     * \param index на сколько надо его увеличить
     * \return
     */
    MyIter operator+ (int index) { return MyIter(cur + index); }

    /*!
     * \brief Оператор разыменования и обращения
     * \return
     */
    T* operator->() const { return cur; }

    /*!
     * \brief Оператор разыменования
     * \throw std::runtime_error если разыменование прошло некоректно
     */
    T& operator* () const throw (std::runtime_error);

    /*!
     * \brief Оператор "не равен"
     * \param it итератор, с которым происходит сравнение
     * \return true(1), false(0)
     */
    int operator !=(const MyIter& it) const { return cur != it.cur; }

    /*!
     * \brief Оператор сравнения с указателем
     * \param it итератор, с которым происходит сравнение
     * \return true(1), false(0)
     */
    int operator == (const T* t) const { return t == cur; }

    /*!
     * \brief Оператор сравнения с итератором
     * \param it итератор, с которым происходит сравнение
     * \return true(1), false(0)
     */
    int operator ==(const MyIter& it) const { return cur == it.cur; }

    /*!
     * \brief Префиксный инкремент
     */
    MyIter& operator++();

    /*!
     * \brief Постфиксный инкремент
     */
    MyIter operator++(int);

    /*!
     * \brief Префиксный декремент
     */
    MyIter & operator--();

    /*!
     * \brief Постфиксный декремент
     */
    MyIter operator--(int);
};

#endif // MYVECTOR_H

template<class T>
MyVector<T>::MyVector() :
    cnt(0),
    cur(0),
    arr(nullptr) {}

template<class T>
MyVector<T>::MyVector(const MyVector<T> &a) :
    cnt(a.cnt),
    cur(a.cur),
    arr(new T[a.cnt]) { for (int i = 0; i < cur; ++i) arr[i] = a.arr[i]; }

template<class T>
MyVector<T>::MyVector(MyVector<T> &&a) :
    cnt(a.cnt),
    cur(a.cur),
    arr(a.arr) { a.arr = nullptr; }

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &a) {
    if (this != &a) {
        MyVector<T>::~MyVector();
        new (this) MyVector(a);
    }
    return *this;
}

template<class T>
MyVector<T>& MyVector<T>::operator =(MyVector<T> &&a) {
    if (this != &a){
        cur = a.cur;
        cnt = a.cnt;
        delete arr;
        arr = a.arr;
        a.arr = nullptr;
    }
    return *this;
}

template<class T>
T &MyVector<T>::operator[](int index) throw (std::out_of_range){
    if(index < 0 || index >= cur)
        throw std::out_of_range("");
    return arr[index];
}

template<class T>
const T &MyVector<T>::operator[](int index) const throw (std::out_of_range) {
    if(index < 0 || index >= cur)
        throw std::out_of_range("");
    return arr[index];
}

template<class T>
void MyVector<T>::clear() {
    cur = 0;
    cnt = 0;
    delete[] arr;
    arr = nullptr;
}

template<class T>
void MyVector<T>::push_back(const T &t){
    if(cur + 1 >= cnt){
        T* tmp = new T[cnt + QUOTA];
        for(int i = 0; i < cur; ++i)
            tmp[i] = arr[i];
        cnt += QUOTA;
        delete[] arr;
        arr = tmp;
    }
    arr[cur] = t;
    ++cur;
}

template<class T>
MyVector<T>& MyVector<T>::erase(const MyVector<T>::iterator &it){
    for(int i = 0; i < cur; i++){
        if(it == &arr[i]){
            T tmp;
            for(int j = i; j < cur -1; j++){
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            --cur;
            break;
        }
    }
    return *this;
}

template<class T>
MyIter<T>::MyIter()      : cur (nullptr) {}

template<class T>
MyIter<T>::MyIter(T *it) : cur (it)      {}

template<class T>
T &MyIter<T>::operator*() const throw (std::runtime_error) {
    if(cur)
        return *cur;
    throw std::runtime_error("illegal value for MyVector Iterator");
}

template<class T>
MyIter<T> &MyIter<T>::operator++() {
    ++cur;
    return *this;
}

template<class T>
MyIter<T> MyIter<T>::operator++(int) {
    MyIter res;
    res.cur = cur;
    ++cur;
    return res;
}

template<class T>
MyIter<T> &MyIter<T>::operator--() {
    ++cur;
    return *this;
}

template<class T>
MyIter<T> MyIter<T>::operator--(int) {
    MyIter res;
    res.cur = cur;
    ++cur;
    return res;
}
