#pragma once
#include <chrono>
#include <stdexcept>  // для std::runtime_error
#include <new>        // для std::bad_alloc

template<template<typename, auto...> class ContainerT, typename T, auto... Args>
class TestArrays {
private:    
    ContainerT<T, Args...> container;
    size_t initial_size;
    size_t step;
    size_t max_count;

public:
    // Конструктор для обычных массивов/списков
    TestArrays(size_t init_size, size_t step_size, size_t max_elements)
        : container(create_initial_container()),
        initial_size(init_size), step(step_size), max_count(max_elements) {
        
        // Инициализируем начальными данными если нужно
        for (size_t i = 0; i < init_size; ++i) {
            container.push_back(T{});
        }
    }
    // Перегруженный конструктор для матричных массивов
    TestArrays(size_t init_size, size_t step_size, size_t max_elements, size_t row_len)
        : container(create_initial_container(row_len)),
        initial_size(init_size), step(step_size), max_count(max_elements) {
        
        // Инициализируем начальными данными если нужно
        for (size_t i = 0; i < init_size; ++i) {
            container.push_back(T{});
        }
    }
    //Комплексный сценарий
    void complex_test() {
        std::cout << "Complex test\n";
        std::cout << "\n------------- Push back -------------\n";
        test_push_back();
        std::cout << "\n-------------------------------------\n";
        std::cout << "\n----------- Random access -----------\n";
        test_random_access();
        std::cout << "\n-------------------------------------\n";
        std::cout << "\n----------- Random delete -----------\n";
        test_random_delete();
        std::cout << "\n------------- Random push -----------\n";
        test_random_push();
        std::cout << "\n-------------------------------------\n";
        std::cout << "Total container size " << container.size() << "\n";
        std::cout << "Total container capacity " << get_capacity() << "\n";
        std::cout << "Total container size in bytes " << sizeof(T) * get_capacity();
        std::cout << "\n-------------------------------------\n";
    }

    //тест добавления элементов в конец
    void test_push_back() {
        
        for (size_t n = initial_size; n <= max_count; n *= step) {
            
            auto start = std::chrono::high_resolution_clock::now();
            try {                
                
                for (size_t i = 0; i < n; ++i) {
                    container.push_back(T{});                   
                }                

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);                
                size_t size = container.size();
                size_t capacity = get_capacity();                
                size_t fullness = (size * 100) / capacity;

                std::cout << "Push back " << n << " elements: " << duration.count() << " us," 
                    << " array capacity " << capacity << ", fullness " << fullness << "%\n";

            }
            catch (const std::bad_alloc& e) {
                std::cout << "Out of memory at " << n << " elements" << std::endl;
                break;
            }
            catch (const std::exception& e) {
                std::cout << "Error at " << n << ": " << e.what() << std::endl;
                break;
            }            
        }
    }
    //тест произвольного доступа
    void test_random_access() {
        // Тестируем operator[] на 3 элементах                
        auto idxs = indexes();
        for (auto idx : idxs) {
            auto start = std::chrono::high_resolution_clock::now();
            T item = container[idx];
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Index " << idx << " get in: " << duration.count() << " us\n";
        }
    }

    //тест удаления элементов
    void test_random_delete() {
        // Тестируем удаление на трех элементах
        auto idxs = indexes();
        for (auto idx : idxs) {
            auto start = std::chrono::high_resolution_clock::now();
            if (idx < container.size()) { //чтобы не упало, если вруг в массиве было мало элементов, и мы удалили уже такой
                T item = container.del(idx);
            };
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Index " << idx << " deleted in: " << duration.count() << " us\n";
        }
    }

    //тест вставки элементов
    void test_random_push() {
        // Тестируем вставку на трех элементах
        auto idxs = indexes();
        for (auto idx : idxs) {
            auto start = std::chrono::high_resolution_clock::now();
            if (idx < container.size()) { //чтобы не упало, если вруг в массиве было мало элементов, и мы удалили уже такой
                container.push(T{}, idx);
            };
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Index " << idx << " inserted in: " << duration.count() << " us\n";
        }
    }

private:    
    //техническая функция для определения емкости
    //нужна, потому что у списка нет встроенной функции
    size_t get_capacity() const {
        if constexpr (requires { container.capacity(); }) {
            return container.capacity();
        }
        else {
            return container.size();  // для List и подобных
        }
    }
    //техническая функция, которая выбирает 3 индекса для тестирования
    //в начале 25%, середине и на уровне 75%
    std::vector<size_t> indexes() {
        std::vector<size_t> idx(3);
        idx[0] = container.size() / 4; 
        idx[1] = container.size() / 2;
        idx[2] = (container.size() / 4) * 3;
        return idx;
    }
    
    //функция создания массива на 1 элемент из инициализатора
    ContainerT<T, Args...> create_initial_container() {
        if constexpr (std::is_constructible_v<ContainerT<T, Args...>, std::initializer_list<T>>) {
            return ContainerT<T, Args...>{T{}};  // используем initializer_list
        }        
          else return ContainerT<T, Args...>();  // конструктор по умолчанию           
    }
    
    //перегрузка для матричных массивов
    ContainerT<T, Args...> create_initial_container(size_t row_len) {
        if constexpr (
                std::is_constructible_v<ContainerT<T, Args...>
                , std::initializer_list<T>, size_t>) {
                
            return ContainerT<T, Args...>({ T{} }, row_len);
            }
            else return ContainerT<T, Args...>();  // конструктор по умолчанию
    }    
};