#pragma once
#include "Array.h"

//Увеличение на 1 элемент
template <typename T>
class SingleArray : public Array<T> {
public:

    using Array<T>::Array;  // наследуем конструкторы базового класса
    using Array<T>::operator=;  // наследуем операторы для базовой части
    
    // Конструктор копирования
    SingleArray(const SingleArray<T>& other) : Array(other) {}

    // Конструктор перемещения
    SingleArray(SingleArray<T>&& other) noexcept : Array(std::move(other)) {}

    //переопределяемые функции    
    void push_back(const T& item) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + 1);  // +1
        }
        this->data[this->size_++] = item;
    }

    void push_back(T&& item) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + 1);  // +1
        }
        this->data[this->size_++] = std::move(item);
    }

    void push(const T& item, size_t idx) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + 1);  // +1
        }
        this->shift_down(idx);
        this->data[idx] = item;
    };

    void push(T&& item, size_t idx) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + 1);  // +1
        }
        this->shift_down(idx);
        this->data[idx] = std::move(item);
    };
};
