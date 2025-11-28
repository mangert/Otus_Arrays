#pragma once
#include "Array.h"

//Увеличение с умножением на коэффициент (задается в параметре шаблона)
template <typename T, size_t F>
class FactorArray : public Array<T> {
public:

    using Array<T>::Array;  // наследуем конструкторы базового класса
    using Array<T>::operator=;  // наследуем операторы для базовой части

    // Конструктор копирования
    FactorArray(const FactorArray<T, F>& other) : Array(other) {}

    // Конструктор перемещения
    FactorArray(FactorArray<T, F>&& other) noexcept : Array(std::move(other)) {}

    //переопределяемые функции    
    void push_back(const T& item) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ * factor);  //*F
        }
        this->data[this->size_++] = item;
    }

    void push_back(T&& item) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ * factor);  //*F
        }
        this->data[this->size_++] = std::move(item);
    }

    void push(const T& item, size_t idx) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ * factor);  //*F
        }
        this->shift_down(idx);
        this->data[idx] = item;
    }

    void push(T&& item, size_t idx) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ * factor);  //*F
        }
        this->shift_down(idx);
        this->data[idx] = std::move(item);
    };

private:
    static constexpr size_t factor = F;
};