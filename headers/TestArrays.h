#pragma once
#include <chrono>

template<template<typename> class ContainerT, typename T>
class TestArrays {
private:
    ContainerT<T> container;
    size_t initial_size;
    size_t step;
    size_t max_count;

public:
    // Конструктор для обычных массивов/списков
    TestArrays(size_t init_size, size_t step_size, size_t max_elements)
        : container(create_initial_container(init_size)),
        initial_size(init_size), step(step_size), max_count(max_elements)
    {
        // Инициализируем начальными данными если нужно
        for (size_t i = 0; i < init_size; ++i) {
            container.push_back(T{});
        }
    }

    // Перегруженный конструктор для MatrixArray (с параметром строки)
    /*template<size_t RowLen>
    TestArrays(size_t init_size, size_t step_size, size_t max_elements,
        std::enable_if_t<std::is_same_v<ContainerT<T>, MatrixArray<T>>, int> = 0)
        : container(create_initial_matrix_container<RowLen>(init_size)),
        initial_size(init_size), step(step_size), max_count(max_elements)
    {
        for (size_t i = 0; i < init_size; ++i) {
            container.push_back(T{});
        }
    }*/

    void test_push_back() {
        for (size_t n = initial_size; n <= max_count; n *= step) {
            auto start = std::chrono::high_resolution_clock::now();

            // Добавляем элементы
            for (size_t i = 0; i < n; ++i) {
                container.push_back(T{});
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Push back " << n << " elements: " << duration.count() << " μs" << std::endl;
        }
    }

    void test_random_access() {
        // Тестируем operator[]
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < container.size(); ++i) {
            volatile T value = container[i];  // volatile чтобы не оптимизировали
        }

        auto end = std::chrono::high_resolution_clock::now();
        // выводим время...
    }

private:
    ContainerT<T> create_initial_container(size_t size) {
        if constexpr (std::is_constructible_v<ContainerT<T>, std::initializer_list<T>>) {
            return ContainerT<T>{T{}};  // начинаем с одного элемента
        }
        else {
            return ContainerT<T>();  // конструктор по умолчанию
        }
    }

    template<size_t RowLen>
    MatrixArray<T> create_initial_matrix_container(size_t size) {
        return MatrixArray<T>(RowLen);  // для MatrixArray передаем размер строки
    }
};