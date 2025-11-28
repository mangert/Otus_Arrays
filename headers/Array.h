#pragma once
#include <stdexcept>  // для std::runtime_error
#include <new>        // для std::bad_alloc

//базовый класс массива (емкость не изменяется)
template <typename T>
class Array {
public:
    // Конструкторы
    Array() : data(nullptr), size_(0), capacity_(0) {}

    // Конструктор емкости (пустой массив)
    Array(size_t capacity) : data(new T[capacity]), size_(0), capacity_(capacity) {}

    // Конструктор размера (заполненный заданными значениями)
    Array(size_t size, const T& value)
        : data(new T[size]), size_(size), capacity_(size)
    {
        for (size_t i = 0; i < size_; ++i) {
            data[i] = value;
        }
    }

    //конструктор предоставленных данных
    Array(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()) {
        if (size_) {
            data = new T[size_];
            std::copy(init.begin(), init.end(), data);
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор копирования
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data = new T[capacity_];
        for (size_t idx = 0; idx != size_; ++idx) {
            data[idx] = other.data[idx];
        }
    }

    // Конструктор перемещения
    Array(Array&& other) noexcept
        : data(other.data), size_(other.size_), capacity_(other.capacity_) {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    virtual ~Array() {        
        if (data) { delete[] data; };        
    }

    // Оператор копирующего присваивания
    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        delete[] data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data = new T[capacity_];
        for (size_t idx = 0; idx != size_; ++idx) {
            data[idx] = other.data[idx];
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    Array& operator=(Array&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    // доступ к элементам
    T& operator[] (size_t idx) {
        if (idx >= size_) throw std::invalid_argument("Index out of range");
        return data[idx];
    }

    const T& operator[] (size_t idx) const {
        if (idx >= size_) throw std::invalid_argument("Index out of range");
        return data[idx];
    }

    // Методы для работы с размером
    size_t size() const noexcept { return size_; };
    size_t capacity() const noexcept { return capacity_; };
    bool is_empty() const noexcept { return 0==size_; }

    //медоды для добавления / удаления элементов            
    virtual void push_back(const T& item) {};
    virtual void push_back(T&& item) {};

    virtual void push(const T& item, size_t idx) {};
    virtual void push(T&& item, size_t idx) {};

    virtual T del(size_t idx) {        
        if (idx >= size_) throw std::invalid_argument("Index out of range");        
        T item = data[idx];
        shift_up(idx + 1);
        return item;
    }    

    // Служебные функции добавляют один элемент к size в пределах емкости
    void place_at(size_t idx, const T& value) {
        if (idx >= capacity_) throw std::out_of_range("Capacity exceeded");
        if (idx >= size_) size_ = idx + 1;  // автоматически увеличиваем size
        data[idx] = value;
    }

    void place_at(size_t idx, T&& value) {
        if (idx >= capacity_) throw std::out_of_range("Capacity exceeded");
        if (idx >= size_) size_ = idx + 1;
        data[idx] = std::move(value);
    }
//внутренние данные и методы класса
protected:    
    size_t free_space() {
        return (capacity_ - size_);
    }
    //служебные функции для сдвига элементов    
    virtual void shift_down(size_t idx) { //сдвигаем все элементы к концу на 1 начиная с idx)
        if(!free_space() || idx >= size_) throw std::invalid_argument("Index out of range");
        
        for(size_t i = size_; i > idx; --i) {
            data[i] = data[i - 1];
        };
        ++size_;
    }    

    virtual void shift_up(size_t idx) { //сдвигаем все элементы к началу на 1 начиная с idx)        
        
        if (idx == 0 || idx > size_) throw std::invalid_argument("Index out of range");

        for(size_t i = idx; i != size_; ++i) {
            data[i - 1] = data[i];
        };
        --size_;
    }
    //служебная фукнция изменения размера
    virtual void resize(size_t new_capacity) {      

        try {
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data[i]);
            }

            delete[] data;
            data = new_data;
            capacity_ = new_capacity;

        }
        catch (const std::bad_alloc& e) {
            throw std::runtime_error("Failed to allocate memory for resize");
        }
    }
    
protected:
    T* data;
    size_t size_;
    size_t capacity_;

//итератор для работы с нашим массивом
public:
    class Iterator {
    public:
        //для совместимости с STL
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator() : ptr(nullptr) {}
        Iterator(T* item) : ptr(item) {}
        Iterator(const Iterator& other) : ptr(other.ptr) {}
        ~Iterator() = default;

        // Оператор доступа к членам
        T* operator->() const { return ptr; }

        // Обмен
        void swap(Iterator& other) {
            std::swap(ptr, other.ptr);
        }

        // Присваивание
        Iterator& operator=(const Iterator& other) {
            ptr = other.ptr;
            return *this;
        }

        // Разыменование
        T& operator*() { return *ptr; }
        const T& operator*() const { return *ptr; }

        // Инкремент
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        // Декремент
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --ptr;
            return tmp;
        }

        // Сравнение
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

    private:
        T* ptr;
    };
    // Итераторы
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }
};