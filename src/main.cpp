#include <iostream>
#include "Array.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "List.h"
#include "TestArrays.h"
#include "PriorityQueue.h"
#include "QueueTester.h"


int main() {
	setlocale(LC_ALL, "Russian");
	
	//переменные дл€ тестировани€
	const size_t init_size = 1;
	const size_t step_size = 10;
	const size_t max_elements = 1000000;
	
	// 1. сначала тестируем разные массивы
	
	/*
	std::cout << "1. Single array" << std::endl;
	TestArrays<SingleArray, int> singleTest{ init_size, step_size, max_elements };
	singleTest.complex_test();
	std::cout << "\n-----------end test-------------\n\n";
	
	std::cout << "2. Vector array" << std::endl;
	TestArrays<VectorArray, int, 10> vectorTest{ init_size, step_size, max_elements };
	vectorTest.complex_test();
	std::cout << "\n-----------end test-------------\n\n";

	std::cout << "3. Factor array" << std::endl;
	TestArrays<FactorArray, int, 2> factorTest{ init_size, step_size, max_elements };
	factorTest.complex_test();
	std::cout << "\n-----------end test-------------\n\n";
	
	std::cout << "4. List" << std::endl;
	TestArrays<List, int> listTest{ init_size, step_size, max_elements };
	listTest.complex_test();	
	std::cout << "\n-----------end test-------------\n\n";
	
	std::cout << "5. Matrix Array" << std::endl;
	TestArrays<MatrixArray, int> matirixTest{ init_size, step_size, max_elements };
	matirixTest.complex_test();
	std::cout << "\n-----------end test-------------\n\n";
	*/
	// 2. “естируем очередь
	std::cout << "\n** Queue tests ************************\n\n";
	// 2.1. ѕроверим корретность пор€дка извлечени€

	PriorityQueue<std::string> m_queue; //очередь из строк
	
	//параметризуем объект-тестер с этой очередью функцией, котора€ создает item'ы
	QueueTester<std::string> str_queue_tester(&m_queue,
		[](std::string name, size_t i) ->std::string {
			return "<" +name + " -> " + std::to_string(i) + ">"; });
	// дл€ теста возьмем по 20 элементов на каждый приоритет (тестируетс€ с трем€ приоритетами, всего 3 * 20 = 60)
	const size_t count = 20; 
	//первый вариант
	std::cout << "\n-----------Sequential queue test -------------\n\n";
	str_queue_tester.test_sequential(count);
	
	//второй вариант
	std::cout << "\n-----------Live queue test -------------\n\n";
	str_queue_tester.test_live(count);
	
	// 2.2. ѕроверим скорость добавлени€ / извлечени€
	PriorityQueue<int> int_queue; //очередь из чисел
	
	QueueTester<int> int_queue_tester(&int_queue,
		[](std::string name, size_t i) ->int {
			return i; }); //нам не важно содержание элемента, а так проще	
	std::cout << "\n-----------Enqueue / dequeue test -------------\n\n";
	int_queue_tester.test(init_size, max_elements, step_size);
	std::cout << "\n-----------end test-------------\n\n";			
		
	return 0;
}