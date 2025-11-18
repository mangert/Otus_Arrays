#pragma once

template <typename T>
class Array {
public:
    // Конструкторы
    Array() : data(nullptr), size_(0), capacity_(0) {}

    Array(size_t capacity) : data(new T[capacity]{}), size_(capacity), capacity_(capacity) {}

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
        delete[] data;
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
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    // Итераторы
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }

public:
    class Iterator {
    public:
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

protected:
    T* data;
    size_t size_;
    size_t capacity_;
};