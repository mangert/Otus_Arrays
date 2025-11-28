#pragma once
#include <optional>
#include "List.h"

//очередь с дискретными приоритетами
template<typename T>
class PriorityQueue {

public:
    PriorityQueue() = default;    
    PriorityQueue(const PriorityQueue&) = default;
    PriorityQueue(PriorityQueue&&) = default;
    PriorityQueue& operator=(const PriorityQueue&) = default;
    PriorityQueue& operator=(PriorityQueue&&) = default;    
    
    virtual ~PriorityQueue() = default;
    
    //добавляем элемент в очередь
    virtual void enqueue(const T& item, size_t priority) {
        // Добавляем в конец списка соответствующего приоритета
        while (priority >= buckets.size()) {
            buckets.push_back(List<T>());  // добавляем пустые bucket'ы
        };
        if (priority > current_max_priority) {
            current_max_priority = priority;
        }
        buckets[priority].push_back(item);
    };

    //извлекаем элемент из очереди
    virtual std::optional<T> dequeue() {
        for (size_t i = 0; i <= current_max_priority; ++i) {
            if (!buckets[i].is_empty()) {
                return buckets[i].del(0);
            }
        }
        return std::nullopt;  // явно показывает "нет значения"
    };

    //посмотреть без извлечения
    virtual std::optional<T> peek() const {
        for (size_t i = 0; i <= current_max_priority; ++i) {
            if (!buckets[i].is_empty()) {
                return buckets[i][0];  // первый элемент высшего приоритета
            }
        }
        return std::nullopt;
    }

    //очистка
    virtual void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        current_max_priority = 0;
    }

    // Статистические данные
    //проверяем, не пустая ли очередь
    virtual bool is_empty() const {
        for (auto& bucket : buckets) {
            if (!bucket.is_empty())
                return false;
        }
        return true;
    };

    //общий размер
    virtual size_t size() const {
        size_t total = 0;
        for (const auto& bucket : buckets) {
            total += bucket.size();
        }
        return total;
    }
    //характеристики
    size_t get_max_priority() const { return current_max_priority; }
    size_t get_buckets_count() const { return buckets.size(); }

private:
    List<List<T>> buckets;  // buckets[0] - высший приоритет
    size_t current_max_priority = 0;

};
