#pragma once
#include "PriorityQueue.h"
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iomanip>

//Класс для тестирования очереди с дискретными приоритетами
template<typename T> 
class QueueTester {

public:    
    QueueTester(PriorityQueue<T>* q,
        std::function<T(std::string, size_t)> gen) 
        : queue(q), generate_value(gen) {};
    
    QueueTester() = delete;
    QueueTester(const QueueTester&) = default;
    QueueTester(QueueTester&&) = default;    
    QueueTester& operator=(const QueueTester&) = default;
    QueueTester& operator=(QueueTester&&) = default;
    ~QueueTester() = default;    
    
    //функции тестирования    
    //тест добавления и извлечения большого количества элементов
    void test(size_t initial_size, size_t max_count, size_t step) {
        
        queue->clear();
        
        std::cout << "Enqueue test\n";        
        std::cout << "\n-------------------------------------\n";

        for (size_t n = initial_size; n <= max_count; n *= step) {

            auto start = std::chrono::high_resolution_clock::now();
            try {

                for (size_t i = 0; i < n; ++i) {
                    T value = generate_value("", i); //нам все равно, какой элемент, поэтому передаем "пустышку" 
                    size_t priority = i % 3; //по очереди - 0,1,2 - чтобы разные приоритеты были
                    queue->enqueue(value, priority);               
                }                

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                auto size = queue->size();

                std::cout << "Enqueued " << n << " elements: " << duration.count() << " us,"
                    << " queue size " << size << "\n";

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

        std::cout << "\n-------------------------------------\n";
        std::cout << "Dequeue test\n";
        
        auto start = std::chrono::high_resolution_clock::now();
        size_t count = 0;
        while (!queue->is_empty()) {
            queue->dequeue();
            ++count;            
        }                        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        auto size = queue->size();        

        std::cout << "Dequeued " << count << " elements: " << duration.count() << " us,"
            << " queue size " << size << "\n";
    }
    
        
    //проверка корректности порядка добавления - извлечения
    //"живой" тест - добавляем и извлекаем параллельно
    void test_live(size_t elements_count) {
        
        queue->clear();
        atomic_counter = 0;
        size_t elements_to_consume = (elements_count * 3) * 8 / 10; //параллельно заберем 80%, 20 останется

        const std::string name_0 = "Wolf";
        const std::string name_1 = "Fox";
        const std::string name_2 = "Rabbit";
        const std::string name_consumer = "Rat";
        const std::string name_consumer_rem = "Mouse";

        std::cout << "Queue live test ------------------------------------\n";

        auto start = std::chrono::high_resolution_clock::now();
        // Запускаем 3 производителя с разными приоритетами
        std::thread thread_0(&QueueTester::producer, this, 0, name_0, elements_count);
        std::thread thread_1(&QueueTester::producer, this, 1, name_1, elements_count);
        std::thread thread_2(&QueueTester::producer, this, 2, name_2, elements_count);
        //запускаем "извлекателя"
        std::thread consumer_thread(&QueueTester::consumer, this, name_consumer, elements_to_consume);

        // Ждём завершения
        thread_0.join();
        thread_1.join();
        thread_2.join();
        consumer_thread.join();

        std::cout << "------------------------------------\n";

        // Дозабираем оставшиеся элементы
        size_t remain_el = queue->size();
        std::cout << "Remaining elements: " << remain_el << "\n";

        if (remain_el > 0) {
            consumer(name_consumer_rem, remain_el);
        }
        if (queue->is_empty()) {
            std::cout << "Queue is empty!\n";
        }
        else std::cout << "There are "<< queue->size() <<" items left in the queue\n";

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "\nItems procecced " << elements_to_consume + remain_el << "\n";
        std::cout << "Time spent " << duration << "\n";
        std::cout << "\nTest finished   ------------------------------------\n";
    }
    
    //проверка корректности порядка добавления - извлечения
    //последовательно - сначала все добавляем, потом все извлекаем
    void test_sequential(size_t elements_count) {
        
        queue->clear();
        atomic_counter = 0;
        
        size_t elements_total = elements_count * 3;

        const std::string name_0 = "Wolf";
        const std::string name_1 = "Fox";
        const std::string name_2 = "Rabbit";
        
        const std::string name_consumer = "Mouse";
        
        std::cout << "Sequential test  ------------------------------------\n";
        auto start = std::chrono::high_resolution_clock::now();
        // Запускаем 3 производителя с разными приоритетами
        std::thread thread_0(&QueueTester::producer, this, 0, name_0, elements_count);
        std::thread thread_1(&QueueTester::producer, this, 1, name_1, elements_count);
        std::thread thread_2(&QueueTester::producer, this, 2, name_2, elements_count);
        
        // Ждем завершения
        thread_0.join();
        thread_1.join();
        thread_2.join();               
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "\nItems added " << elements_total << "\n";
        std::cout << "Time spent " << duration << "\n";
        std::cout << "------------------------------------\n";

        // Извлекаем элементы
        size_t remain_el = queue->size();        
        start = std::chrono::high_resolution_clock::now();
        if (remain_el > 0) {
            consumer(name_consumer, remain_el);
        }

        if (queue->is_empty()) {
            std::cout << "Queue is empty!\n";
        }
        else std::cout << "There are " << queue->size() << " items left in the queue\n";
        
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "\nItems consumed " << elements_total << "\n";
        std::cout << "Time spent " << duration << "\n";
        std::cout << "\nTest finished   ------------------------------------\n";
    }

private:
    //служебная функция - добавляет элементы в очередь
    void producer(size_t priority, const std::string& name, size_t elements_count) {
        
        size_t inner_counter;

        for (size_t i = 0; i < elements_count; ++i) {
            T value = generate_value(name, i);        
                
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                queue->enqueue(value, priority);                
                inner_counter = atomic_counter++;                        
                
                std::cout << "[" << std::setw(4) << std::right << inner_counter << "] "
                    << std::setw(8) << std::left << name
                    << " added: " << value
                    << " (priority " << priority << ")\n";
            }
        }
    }
    //служебная функция - извлекает элементы из очереди
    void consumer(const std::string& name, size_t elements_to_consume) {        
        size_t inner_counter;
        size_t counter = 0;
        while (counter < elements_to_consume) {
            std::optional<T> item;            
                
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                if (!queue->is_empty()) {
                    item = queue->dequeue();
                    inner_counter = atomic_counter++;
                }
                
                if (item.has_value()) {
                    std::cout << "[" << std::setw(4) << std::right << inner_counter << "] "
                        << std::setw(8) << std::left << name
                        << " consumed: " << *item << "\n";
                    ++counter;
                }
                else {                    
                    std::cout << " - "
                        << std::setw(8) << std::left << name
                        << " found empty queue\n";
                }

                if (!item.has_value()) {
                    std::this_thread::yield();
                }
            }
        }
    }

private:
    PriorityQueue<T>* queue; //очередь
    
    std::function<T(std::string, size_t)> generate_value; //функция создания значений элементов
    
    std::atomic<size_t> atomic_counter = 0; //счетчик операций    
    std::mutex queue_mutex; //для очереди        
};
