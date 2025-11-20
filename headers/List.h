#pragma once

template <typename T>
class List {
public:
	struct Node {
		T data; //данные
		Node* next;
		//конструкторы
		Node() : next(nullptr) {};
		Node(T data) : data(data), next(nullptr) {};
		Node(const Node& other) = delete;
		Node(Node&& other) = delete;
		Node& operator=(Node&&) = delete;
		Node& operator=(const Node&) = delete;

		~Node() = default;
	};

	// Конструкторы
	List() : head(nullptr), tail(nullptr) {};

	// Конструктор размера (заполненный default значениями)
	Array(size_t size, const T& value = T{})
		: data(new T[size]), size_(size), capacity_(size)
	{
		for (size_t i = 0; i < size_; ++i) {
			data[i] = value;
		}
	}

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

	//итератор для работы с нашим списком
public:
	class ListIterator {
	public:
		ListIterator() : ptr(nullptr) {}
		ListIterator(T* item) : ptr(item) {}
		ListIterator(const ListIterator& other) : ptr(other.ptr) {}
		~ListIterator() = default;

		// Оператор доступа к членам
		T* operator->() const { return ptr; }

		// Обмен
		void swap(ListIterator& other) {
			std::swap(ptr, other.ptr);
		}

		// Присваивание
		ListIterator& operator=(const ListIterator& other) {
			ptr = other.ptr;
			return *this;
		}

		// Разыменование
		T& operator*() { return *ptr; }
		const T& operator*() const { return *ptr; }

		// Инкремент
		ListIterator& operator++() {
			if (ptr) ptr = ptr->next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			if (ptr) ptr = ptr->next;
			return tmp;
		}

		// Декремент
		Iterator& operator--() = delete;

		Iterator operator--(int) = delete;

		// Сравнение
		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

	private:
		Node* ptr;
	};
	// Итераторы
	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }

private:
	Node* head = nullptr;
	Node* tail = nullptr;;


};

/*struct node {
		//данные
		T data;
		node * prev;
		node * next;
		//конструкторы
		node() : prev(nullptr), next(nullptr) {};
		node(T data) : data(data), prev(nullptr), next(nullptr) {};
		node(node& other) = delete; 
	};

public:
	//конструкторы
	List() : head(nullptr), tail(nullptr) {make_list();}
	List(List& other) {}
	~List();
//классы исключений
	
public:
	class bad_add : public std::bad_alloc //ошибка добавления элемента
	{
	public:
		const char* what() const {
			return "Элемент не добавлен! Нехватка памяти";
		}
	};	
	class bad_erase : public std::exception //удаление из пустого списка
	{
	public:
		const char* what() const {
			return "Ошибка! Попытка удаления из пустого списка";
		}
	};

public:	
	class ListIterator :public std::iterator<std::bidirectional_iterator_tag, T> //класс итератора для работы со списками
	{	
	public:
		ListIterator() : ptr(nullptr) {}
		ListIterator(node * item) : ptr(item) {}
		ListIterator(ListIterator& other) :ptr(other.ptr) {}
		~ListIterator() = default;

		node * operator->() const;		
		void swap(ListIterator& other);		
		ListIterator& operator=(const ListIterator& other);		
		node * operator*();		
		const node * operator*() const;		
		ListIterator& operator++();
		ListIterator operator++(int);		
		ListIterator& operator--();		
		ListIterator operator--(int);		
		bool operator==(const ListIterator& other) const;
		bool operator!=(const ListIterator& other) const;
	
	private:
		node * ptr;
	};

public:
	//открытые функции-члены	
	node * push_front(T item); //добавление элемента в начало списка	
	node * push_back(T item); //добавление элемента в конец списка	
	node * insert(T item, node * previous);//добавление элемента после любого	
	
	ListIterator begin();
	ListIterator end();
	
	void erase(ListIterator it); //удаление произвольного элемента из списка	
	bool empty(); //проверка списка на пустоту	
	void clear(); //уничтожение списка	
	
private:
	void make_list(); //внутренняя функция для создания списка 
private:
	node * head; //начало списка (пустой граничный элемент)
	node * tail; //конец списка (пустой граничный элемент)
};*/

