#pragma once
#include "Array.h"

//Фиксированный размер
template <typename T>
class FixedArray : public Array<T> {
public:

    using Array<T>::Array;  // наследуем конструкторы базового класса        
    
    // Конструктор копирования
    FixedArray(const FixedArray<T>& other) : Array(other) {}

    // Конструктор перемещения
    FixedArray(FixedArray<T>&& other) noexcept : Array(std::move(other)) {}

    // Явно объявляем операторы присваивания
    FixedArray& operator=(const FixedArray& other) {
        Array<T>::operator=(other);
        return *this;
    }

    FixedArray& operator=(FixedArray&& other) noexcept {
        Array<T>::operator=(std::move(other));
        return *this;
    }

    //переопределяемые функции    
    void push_back(const T& item) override {
        if (this->free_space() == 0) {
            throw std::length_error("FixedArray: cannot add elements - fixed capacity");
        }
        this->data[this->size_++] = item;
    }

    void push_back(T&& item) override {
        if (this->free_space() == 0) { 
            throw std::length_error("FixedArray: cannot add elements - fixed capacity"); 
        }
        this->data[this->size_++] = std::move(item);
    }

    void push(const T& item, size_t idx) override {
        if (this->free_space() == 0) {
            throw std::length_error("FixedArray: cannot add elements - fixed capacity");
        }
        this->shift_down(idx);
        this->data[idx] = item;
    };

    void push(T&& item, size_t idx) override {
        if (this->free_space() == 0) {
            throw std::length_error("FixedArray: cannot add elements - fixed capacity");
        }
        this->shift_down(idx);
        this->data[idx] = std::move(item);
    };
};
