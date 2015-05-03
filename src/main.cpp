/*
 * File:   main.cpp
 * Author: chirag
 *
 * Created on April 22, 2015, 11:40 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Item/Item.h"

using namespace std;


int main() {
	char choice;
	do {
		std::cout << "Welcome" << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Add" << std::endl;
		std::cout << "2. Manipulate" << std::endl;
		std::cout << "3. See All Items" << std::endl;
		std::cout << "4. Quit" << std::endl;

		std::cout << "Enter number...." << std::endl;
		cin >> choice;

		while (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
			std::cout << "Bad choice ( 1,2,3) , enter choice : ";
			std::cin >> choice;
		}

		// Switch statement
		switch (choice) {
		case '1': //ADD
		{
			Item i1;
			i1.addItem();

		}
			break;

		case '2':  //Manipulate
		{
			Item i2;
			i2.manipulateItem();
		}
			break;

		case '3':   //See all Items
		{
			Item i3;
			i3.showItem();
		}
			break;

		}; // end of switch

	} while (choice != '4');

	return 0;
}
