#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

#define ASSERT_VALID() {\
    if (!isValid()) {\
        dump(__PRETTY_FUNCTION__, std::cout);\
        assert(!"Stack is good");\
        throw std::exception();\
    }\
}

/*!
 * @brief Класс, реализующий работу стека
 */
template <class T>
class Stack {
public:
    /*!
     * @brief	Конструкор, создающий пустой стек
     */
    Stack () :
        m_arr     (nullptr),
        m_cur     (0),
        m_maxSize (0)
        {}

    /*!
     * @brief	Копирущий конструтор класса стек
     */
    Stack (const Stack& st);

    /*!
     * @brief	Копирующее равно
     */
    const Stack& operator = (const Stack& st);

    /*!
     * @brief	Деструктор класса стек
     */
    ~Stack() {
        delete[] m_arr;
    }

    /*!
     * @brief	Функция, возвращающая последний элемент в стеке
     * @throws std::out_of_range в случае если стек был пустой
     */
    const T& top() const throw (std::out_of_range);

    /*!
     * @brief	Проверка на пустоту стека
     */
    bool empty() const {
        ASSERT_VALID();
        return (m_cur == 0);
    }

    /*!
     * @brief	Возвращает рамер стека, используемый элементами
     */
    size_t size() const;

    /*!
     * @brief	Добавляет новое значение в конец стека
     * @param value Значение, которое надо добавить
     * @throw std::bad_alloc Если не получилось выделить память под новый элемент
     */
    void push( const T& value ) throw (std::bad_alloc);

    /*!
     * @brief  Удаляет последний элемент стека
     */
    void pop();

    /*!
     * @brief  Проверяет стек на валидность
     */
    bool isValid() const;

    /*!
     * @brief  Выводит полную информацию о стеке
     */
    void dump(const char* function_name, std::ostream& os) const;

private:
    const static size_t QUOTA = 10;
    T* m_arr;
    size_t m_cur;
    size_t m_maxSize;

};

#endif // STACK_H

template<class T>
Stack<T>::Stack(const Stack &st) :
    m_arr(new T[st.m_maxSize]),
    m_cur(st.m_cur),
    m_maxSize(st.m_maxSize)
{
    ASSERT_VALID();
    for(size_t i = 0; i < st.m_cur; ++i)
        m_arr[i] = st.m_arr[i];
    ASSERT_VALID();
}

template<class T>
const Stack<T> &Stack<T>::operator =(const Stack &st){
    ASSERT_VALID();
	if (&st != this) {
		Stack::~Stack();
	    new (this) Stack (st);
	}

    return *this;
}

template<class T>
const T &Stack<T>::top() const throw (std::out_of_range) {
    ASSERT_VALID();
    if(m_cur <= 0)
        throw std::out_of_range("The stack is empty!\n");
    ASSERT_VALID();
    return m_arr[m_cur-1];
}

template<class T>
size_t Stack<T>::size() const {
    ASSERT_VALID();
    return m_cur;
}

template<class T>
void Stack<T>::push(const T &value) throw (std::bad_alloc) {
    ASSERT_VALID();
    if(m_cur+1 >= m_maxSize) {
        m_maxSize += QUOTA;
        try{
            T* tmp = new T[m_maxSize];
            for(size_t i = 0; i < m_cur; ++i)
                tmp[i] = m_arr[i];
            delete m_arr;
            m_arr = tmp;
        } catch (const std::bad_alloc& e){
            throw e;
        }

    }
    m_arr[m_cur++] = value;
    ASSERT_VALID();
}

template<class T>
void Stack<T>::pop() {
    ASSERT_VALID();
    if(m_cur <= 0)
        return;
    --m_cur;
    if(m_cur < (m_maxSize-QUOTA)){
        m_maxSize -= QUOTA;
        try{
            T* tmp = new T[m_maxSize];
            for(size_t i = 0; i < m_cur; ++i)
                tmp[i] = m_arr[i];
            delete m_arr;
            m_arr = tmp;
        } catch(const std::out_of_range&){

        }
    }
    ASSERT_VALID();
}

template<class T>
bool Stack<T>::isValid() const {
    return m_cur <= m_maxSize ? true : false;
}

template<class T>
void Stack<T>::dump(const char *function_name, std::ostream &os) const {
    os << function_name << std::endl;
    os << "    Stack max size: " << m_maxSize << std::endl;
    os << "    Stack current size: " << m_cur << std::endl  ;
    os << "    Stack elements: \n";
    for(size_t i = 0; i < m_cur; ++i)
        os << "        " << i << ".  " << m_arr[i] << std::endl;
    os << std::endl;
}
