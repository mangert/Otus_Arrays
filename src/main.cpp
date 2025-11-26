#include <iostream>
#include "Array.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "List.h"
#include "TestArrays.h"
/*
void print(Array<int>& array) {

	for (auto& item : array) {
		std::cout << item << "  ";
	};
};

void print(List<int>& list) {

	for (auto& item : list) {
		std::cout << item << "  ";
	};
};

void print(MatrixArray<int>& list) {

	for (auto& item : list) {
		std::cout << item << "  ";
	};
};*/

int main() {
	setlocale(LC_ALL, "Russian");

	const size_t init_size = 1;
	const size_t step_size = 10;
	const size_t max_elements = 1000000;
	
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
	
	/*
	std::cout << "Матричный массив" << std::endl;
	MatrixArray<int> simpleArray{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };	
	print(simpleArray);
	
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.push_back(21);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.del(5);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.push(5, 5);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.del(0);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.push(0, 0);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;

	
	simpleArray.del(21);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	simpleArray.push_back(21);
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;

	std::cout << simpleArray[9] << std::endl;

	simpleArray[9] = 19;
	print(simpleArray);
	std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
	std::cout << std::endl << "****************" << std::endl;
	
	auto it = std::find(simpleArray.begin(), simpleArray.end(), 10);
	if (it != simpleArray.end()) {
		std::cout << "Found: " << *it << std::endl;
	}
	// Пустой массив
	MatrixArray<int> empty(10);
	std::cout << "Empty: " << empty.is_empty() << std::endl;
	print(empty);
	std::cout << "====================" << std::endl;	// Один элемент 	
	std::cout << std::endl << "****************" << std::endl;
	MatrixArray<int> single{42};
	print(single);
	std::cout << std::endl << "****************" << std::endl;
	std::cout << std::endl << "size: " << single.size() << " capacity: " << single.capacity() << std::endl;
	single.push_back(43);
	print(single);
	std::cout << std::endl << "****************" << std::endl;	
	single.del(0);
	print(single);
	std::cout << std::endl << "****************" << std::endl;
	// Конструктор копирования
	MatrixArray<int> copy = MatrixArray<int>(simpleArray);
	print(copy);
	std::cout << std::endl << "****************" << std::endl;
	// Перемещение  
	MatrixArray<int> moved = std::move(simpleArray);
	print(moved);

	MatrixArray<int> other{ 100, 200 };
	other = std::move(simpleArray);  // перемещающее присваивание
	print(other);
	std::cout << std::endl << "****************" << std::endl;
	
	/*
	{
		List<int> list = List<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

		print(list);

		std::cout << std::endl << "****************" << std::endl;
		const List<int>& const_list = list;
		int const_item = const_list[8];

		int item = list[4];
		std::cout << item << std::endl;
		item = 9;
		list[5] = 8;
		print(list);
		std::cout << std::endl << "****************" << std::endl;

		int deleted = list.del(0);
		std::cout << "deleted " << deleted << std::endl;
		print(list);
		std::cout << std::endl << "****************" << std::endl;

		list.push_back(10);
		print(list);
		std::cout << std::endl << "****************" << std::endl;

		list.push_front(10);
		print(list);
		std::cout << std::endl << "****************" << std::endl;

		list.push(13, 0);
		print(list);
		std::cout << std::endl << "****************" << std::endl;
	}
	
	{
		std::cout << "1 Просто массив +1" << std::endl;
		SingleArray<int> simpleArray{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(5, 5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(0, 0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;


		simpleArray.del(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		std::cout << simpleArray[9] << std::endl;

		simpleArray[9] = 19;
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;
	}
	
	{
		std::cout << "1 Просто массив +K" << std::endl;
		VectorArray<int, 10> simpleArray{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(5, 5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(0, 0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;


		simpleArray.del(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		std::cout << simpleArray[9] << std::endl;

		simpleArray[9] = 19;
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;
	}	
	
	{
		std::cout << "1 Просто массив  * K" << std::endl;
		FactorArray<int, 2> simpleArray{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(5, 5);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.del(0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push(0, 0);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;


		simpleArray.del(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		simpleArray.push_back(11);
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;

		std::cout << simpleArray[9] << std::endl;

		simpleArray[9] = 19;
		print(simpleArray);
		std::cout << std::endl << "size: " << simpleArray.size() << " capacity: " << simpleArray.capacity() << std::endl;
		std::cout << std::endl << "****************" << std::endl;
	}		
	*/
	
	return 0;
}