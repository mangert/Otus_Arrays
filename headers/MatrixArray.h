#pragma once
#include "Array.h"

template <typename T>
class MatrixArray {    

public:
    //минимальный конструктор
    MatrixArray(size_t row_length) : row_len(row_length) {
        data = new Array<T>*[1];  // начинаем с одной строки
        data[0] = new Array<T>(row_len);  // каждая строка - указатель на Array<T>
        capacity_ = row_len;
        size_ = 0;       
    }

    // Конструктор размера (заполненный default значениями)    
    MatrixArray(size_t size, size_t row_length)
        : row_len(row_length), size_(size) {
        if (size_ == 0) {
            // Пустой массив
            data = new Array<T>[1];
            data[0] = Array<T>(row_len);
            capacity_ = row_len;
        }
        else {
            // Непустой массив
            size_t row_count = (size_ + row_len - 1) / row_len;
            capacity_ = row_count * row_len;
            data = new Array<T>[row_count];

            for (size_t row = 0; row < row_count; ++row) {
                data[row] = Array<T>(row_len, T{});
            }
        }
    }

    //конструктор предоставленных данных     
    using InitList = std::initializer_list<T>;  // псевдоним
    MatrixArray(InitList init, size_t row_length = 10)
        : row_len(row_length), size_(init.size()) {
        
        if (size_ == 0) {
            // Пустой массив
            data = new Array<T>*[1];
            data[0] = new Array<T>(row_len);
            capacity_ = row_len;
        }        
        else {            
            size_t row_count = (size_ - 1) / row_len + 1;
            capacity_ = row_count * row_len;          
           
            data = new Array<T>*[row_count];            
            for (size_t i = 0; i != row_count; ++i) {
                data[i] = new Array<T>(row_len);                
            }
            
            //переносим данные
            auto it = init.begin();
            for (size_t i = 0; i < size_; ++i, ++it) {
                size_t row = i / row_len;
                size_t col = i % row_len;
                data[row]->place_at(col, *it);
                
            }
        }
    }
    
    //конструктор копирования
    MatrixArray(const MatrixArray& other)
        : row_len(other.row_len), size_(other.size_), capacity_(other.capacity_)
    {
        if (size_ == 0) {
            data = new Array<T>*[1];
            data[0] = new Array<T>(row_len);
        }
        else {
            size_t row_count = capacity_ / row_len;
            data = new Array<T>*[row_count];

            // Создаем и копируем строки
            for (size_t row = 0; row < row_count; ++row) {
                data[row] = new Array<T>(*other.data[row]);
            }            
        }
    }
    //конструктор перемещения
    MatrixArray(MatrixArray&& other) noexcept
        : data(other.data), row_len(other.row_len),
        size_(other.size_), capacity_(other.capacity_) {
        other.data = nullptr;
        other.row_len = 0;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    ~MatrixArray() {
        if (data) {
            size_t row_count = capacity_ / row_len;
            for (size_t i = 0; i < row_count; ++i) {
                delete data[i];  // удаляем каждую строку
            }
            delete[] data;  // удаляем массив указателей
        }
    }
    
    // Оператор копирующего присваивания
    MatrixArray& operator=(const MatrixArray& other) {
        if (this == &other) return *this;

        delete[] data;  // освобождаем старые данные

        // Копируем параметры
        size_ = other.size_;
        capacity_ = other.capacity_;
        row_len = other.row_len;

        if (size_ == 0) {
            // Пустой массив
            data = new Array<T>*[1];
            data[0] = new Array<T>(row_len);
        }
        else {
            size_t row_count = capacity_ / row_len;
            data = new Array<T>*[row_count];

            // Создаем и копируем строки
            for (size_t row = 0; row < row_count; ++row) {
                data[row] = new Array<T>(*other.data[row]);
            }
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    MatrixArray& operator=(MatrixArray&& other) noexcept {
        if (this == &other) return *this;
        
        delete[] data;
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        row_len = other.row_len;
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.row_len = 0;
        return *this;
    }
    

    // доступ к элементам
    T& operator[] (size_t idx) {
        if (idx >= size_) throw std::invalid_argument("Index out of range");
        size_t row = idx / row_len;
        size_t col = idx % row_len;
        return (*data[row])[col];
    }

    const T& operator[] (size_t idx) const {
        if (idx >= size_) throw std::invalid_argument("Index out of range");
        size_t row = idx / row_len;
        size_t col = idx % row_len;
        return (*data[row])[col];
    }    
    
    // Методы для работы с размером
    size_t size() const noexcept { return size_; };
    size_t capacity() const noexcept { return capacity_; };
    bool is_empty() const noexcept { return 0 == size_; }
    
    //медоды для добавления / удаления элементов
    
    void push_back(const T& item) {        
        if (size_ == capacity_) {
            add_row();  // добавляем строку когда место кончилось
        }

        size_t row = size_ / row_len;
        size_t col = size_ % row_len;
        data[row]->place_at(col, item);
        ++size_;
    }

    void push_back(T&& item) {
        if (size_ == capacity_) {
            add_row();  // добавляем строку когда место кончилось
        }

        size_t row = size_ / row_len;
        size_t col = size_ % row_len;
        data[row]->place_at(col,std::move(item));
        ++size_;
    }

    virtual void push(const T& item, size_t idx) {
        if (this->free_space() == 0) this->add_row();
        this->shift_down(idx);
        size_t row = idx / row_len;
        size_t col = idx % row_len;
        (*data[row])[col] = item;
    }

    virtual void push(T&& item, size_t idx) {
        if (this->free_space() == 0) this->add_row();
        this->shift_down(idx);
        size_t row = idx / row_len;
        size_t col = idx % row_len;
        (*data[row])[col] = std::move(item);
    }

    virtual T del(size_t idx) {
        if (idx >= size_) throw std::invalid_argument("Index out of range");
        
        size_t row = idx / row_len;
        size_t col = idx % row_len;
        T item = (*data[row])[col];
        shift_up(idx + 1);
        return item;
    }    
    //внутренние данные и методы класса
protected:
    
    size_t free_space() const {
        return capacity_ - size_;
    }
    //служебные функции для сдвига элементов    
    void shift_down(size_t idx) {
        if (free_space() == 0 || idx >= size_)
            throw std::invalid_argument("Index out of range");

        for (size_t i = size_; i > idx; --i) {
            // Прямой расчет индексов
            size_t row_curr = i / row_len;
            size_t col_curr = i % row_len;
            size_t row_prev = (i - 1) / row_len;
            size_t col_prev = (i - 1) % row_len;
            
            (*data[row_curr])[col_curr] = std::move((*data[row_prev])[col_prev]);
        }
        ++size_;
    }

    void shift_up(size_t idx) {
        
        if (idx > size_) throw std::invalid_argument("Index out of range");        
        for (size_t i = idx; i != size_; ++i) {
            // Прямой расчет индексов
            size_t row_curr = (i - 1) / row_len;
            size_t col_curr = (i - 1) % row_len;
            size_t row_next = i / row_len;
            size_t col_next = i % row_len;

            (*data[row_curr])[col_curr] = std::move((*data[row_next])[col_next]);
        }
        --size_;
    }    
    
    //служебная фукнция изменения размера    
    void add_row() {
        size_t old_row_count = capacity_ / row_len;
        size_t new_row_count = old_row_count + 1;

        // Создаем новый массив строк
        Array<T>** new_data = new Array<T>*[new_row_count];

        // Копируем старые строки
        for (size_t i = 0; i < old_row_count; ++i) {
            new_data[i] = data[i];
        }

        // Добавляем новую строку
        new_data[old_row_count] = new Array<T>(row_len);

        // Заменяем данные
        delete[] data;
        data = new_data;
        capacity_ += row_len;
    }

protected:    
    Array<T>** data;
    size_t row_len;   
    size_t size_;
    size_t capacity_;

//итератор для работы с нашим массивом
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator() : matrix(nullptr), flat_index(0) {}
        Iterator(MatrixArray* mat, size_t idx = 0) : matrix(mat), flat_index(idx) {}
        Iterator(const Iterator& other) : matrix(other.matrix), flat_index(other.flat_index) {}
        ~Iterator() = default;

        // Оператор доступа к членам
        T* operator->() {
            return &(operator*());
        }
        
        const T* operator->() const {
            return &(operator*());
        }

        // Обмен
        void swap(Iterator& other) {
            std::swap(matrix, other.matrix);
            std::swap(flat_index, other.flat_index);
        }

        // Присваивание
        Iterator& operator=(const Iterator& other) {
            matrix = other.matrix;
            flat_index = other.flat_index;
            return *this;
        }

        // Разыменование
        T& operator*() {
            return (*matrix)[flat_index];  // используем готовый operator[]
        }        
        const T& operator*() const {
            return (*matrix)[flat_index];
        }
        
        // Инкремент
        Iterator& operator++() {
            ++flat_index;
            return *this;
        }        

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++flat_index;
            return tmp;
        }

        // Декремент
        Iterator& operator--() {
            --flat_index;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --flat_index;
            return tmp;
        }

        // Сравнение
        bool operator==(const Iterator& other) const { 
            return (flat_index == other.flat_index) && (matrix == other.matrix); 
        }
        bool operator!=(const Iterator& other) const { 
            return (flat_index != other.flat_index) || (matrix != other.matrix); }

    private:
        MatrixArray* matrix;
        size_t flat_index;
    };
    // Итераторы
    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, size_); }
};


