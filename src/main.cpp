#include <iostream>
#include "Array.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"


void print(Array<int>& array) {
	
	for (auto& item : array) {
		std::cout << item << "  ";
	};
}

int main() {
	setlocale(LC_ALL, "Russian");
	/*
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
	*/
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
	
	return 0;
}