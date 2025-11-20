#pragma once
#include "Array.h"

//”величение на фиксированное количество элементов (задаетс€ в параметре шаблона)
template <typename T, size_t S>
class VectorArray : public Array<T> {
public:

    using Array<T>::Array;  // наследуем конструкторы базового класса
    using Array<T>::operator=;  // наследуем операторы дл€ базовой части

    //  онструктор копировани€
    VectorArray(const VectorArray<T, S>& other) : Array(other) {}

    //  онструктор перемещени€
    VectorArray(VectorArray<T, S>&& other) noexcept : Array(std::move(other)) {}

    //переопредел€емые функции    
    void push_back(T item) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + step);  // + S
        }
        this->data[this->size_++] = item;
    }

    void push(T item, size_t idx) override {
        if (this->free_space() == 0) {
            this->resize(this->capacity_ + step);  // + S
        }
        this->shift_down(idx);
        this->data[idx] = item;
    };

private:
    static constexpr size_t step = S;
};