#pragma once
#include "PriorityQueue.h"
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

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
    
    void test(size_t elements_count) {
        size_t elements_to_consume = (elements_count * 3) * 8 / 10;

        const std::string name_0 = "Wolf";
        const std::string name_1 = "Fox";
        const std::string name_2 = "Rabbit";
        const std::string name_consumer = "Rat";

        std::cout << "------------------------------------\n";

        // Запускаем 3 производителя с разными приоритетами
        std::thread thread_0(&QueueTester::producer, this, 0, name_0, elements_count);
        std::thread thread_1(&QueueTester::producer, this, 1, name_1, elements_count);
        std::thread thread_2(&QueueTester::producer, this, 2, name_2, elements_count);

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
            consumer("Mouse", remain_el);  // метод класса
        }

        std::cout << "------------------------------------\n";
    }
    
    void producer(size_t priority, const std::string& name, size_t elements_count) {
        static std::mutex cout_mutex;

        for (size_t i = 0; i < elements_count; ++i) {
            T value = generate_value(name, i);

            {
                std::lock_guard<std::mutex> lock(cout_mutex);  //
                {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    queue->enqueue(value, priority);
                }
                std::cout << name << " added: " << value << " (priority " << priority << ")\n";
            } 
        }
    }

    void consumer(const std::string& name, size_t elements_to_consume) {
        static std::mutex cout_mutex;

        size_t counter = 0;
        while (counter < elements_to_consume) {
            std::optional<T> item;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);  // ← ЗАХВАТ ДО операции!
                {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    if (!queue->is_empty()) {
                        item = queue->dequeue();
                    }
                }

                if (item.has_value()) {
                    std::cout << name << " consumed: " << *item << "\n";
                    ++counter;
                }
                else {
                    std::cout << name << " found empty queue\n";
                }
            }

            if (!item.has_value()) {
                std::this_thread::yield();
            }
        }
    }

private:
    PriorityQueue<T>* queue; //очередь
    std::function<T(std::string, size_t)> generate_value; //функция создания значений элементов элементов
    std::mutex queue_mutex; //для очереди    
};
