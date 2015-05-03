/*
 * Item.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include <boost/uuid/uuid.hpp>          // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>        // streaming operators etc.

#include "Item.h"

using namespace std;

std::string replace(std::string line, const std::string& substr,
		const std::string& replace_with) {
	std::string::size_type pos = 0;
	while ((pos = line.find(substr, pos)) != std::string::npos) {
		line.replace(pos, substr.size(), replace_with);
		pos += replace_with.size();
	}
	return line;
}

Item::Item()
{
}

void Item::addItem() {
	ofstream outfile("Data", ios::out | ios::app);
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	std::cout << uuid << std::endl;
	outfile << setw(20) << uuid;

	std::cout << "enter item name : " << std::endl;
	std::cin >> name;
	outfile << setw(20) << name;
	std::cout << "enter item Description : " << std::endl;
	std::cin >> des;
	outfile << setw(20) << des;
	std::cout << "enter item price : " << std::endl;
	std::cin >> price;
	outfile << setw(20) << price << endl;

	std::cout << "Data are successfully entered" << std::endl;
	// std::cout<< uuid("ea3c79f0-a0dc-4328-a3bb-b23b803f54d8") <<std::endl;
	return;
}

void Item::showItem() {
	string line;
	//cout<< "ItemId \t\t\t\t\t\t\t"<<"Name \t\t"<<"Description\t\t"<<"Price"<<endl;
	fstream outfile("Data", ios::in | ios::out);
	if (outfile.is_open()) {
		while (!outfile.eof()) {
			getline(outfile, line);
			cout << line << endl << " ";
		}
		outfile.close();
	} else
		cout << "Unable to open file";
}

void Item::manipulateItem() {
	const char* const original_file_name = "Data";
	std::string original_substr, replacement;
	std::cout << "Enter the item's existing value" << std::endl;
	std::cin >> original_substr;
	std::cout << "Enter the item's new value" << std::endl;
	std::cin >> replacement;
	// get a temporary file name
	char tmp_file_name[ L_tmpnam];
	std::tmpnam(tmp_file_name);
	// create a temporary file with replaced text
	{
		std::ifstream original_file(original_file_name);
		std::ofstream temp_file(tmp_file_name);
		std::string line;
		while (std::getline(original_file, line))
			temp_file << replace(line, original_substr, replacement) << '\n';
	}
	// overwrite the original file with the temporary file
	{
		std::ifstream temp_file(tmp_file_name);
		std::ofstream original_file(original_file_name);
		original_file << temp_file.rdbuf();
	}
	// and delete the temporary file
	std::remove(tmp_file_name);
	std::cout << "Value has been changed successfully" << std::endl;
}

//

