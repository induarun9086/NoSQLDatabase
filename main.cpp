/* 
 * File:   main.cpp
 * Author: chirag
 *
 * Created on April 22, 2015, 11:40 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using namespace std;

class item
{
private :
    string name;
    string des;
    int price;
public:
    void add(){
        ofstream outfile("Data.txt", ios::out | ios::app);
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        std::cout << uuid << std::endl;
        outfile << uuid<<"\t";
        std::cout << "enter item name : " << std::endl;
        std::cin >> name ;
        outfile << name <<setw(20);
        std::cout << "enter item Description : " << std::endl;
        std::cin >> des ;
        outfile << des <<setw(20);
        std::cout << "enter item price : " << std::endl;
        std::cin >> price ;
        outfile << price <<endl;

        std::cout << "Data are successfully entered" << std::endl;
       // std::cout<< uuid("ea3c79f0-a0dc-4328-a3bb-b23b803f54d8") <<std::endl;
        return;
    }
    void show(){
        string line;
				fstream outfile ("Data.txt", ios::in | ios::out);
				if (outfile.is_open())
				{
					while (! outfile.eof() )
					{
						getline (outfile,line);
						cout << line << endl << " ";
					}

					outfile.close();
				}
				else
					cout << "Unable to open file";
    }
    void manip(){
        
    }
};


int main ()
{
   char choice;
   do
	{
            std::cout << "Welcome" << std::endl;
            std::cout << "What would you like to do?" << std::endl;
            std::cout << "1. Add" << std::endl;
            std::cout << "2. Manipulate" << std::endl;
            std::cout << "3. See All Items" << std::endl;
            std::cout << "4. Quit" << std::endl;
   
            std::cout << "Enter number...." << std::endl;
            cin >> choice;

   
   
            while ( choice != '1' && choice != '2' && choice != '3' && choice != '4')
		{
			std::cout << "Bad choice ( 1,2,3) , enter choice : ";
			std::cin >> choice;
		}

		// Switch statement
		switch ( choice )
		{
			case '1': //ADD
			{
                           item i1; 
                            i1.add();
                            
			}	
			break;

			case '2':  //Manipulate
			{
				
			}
			break;
                        
                        case '3':   //See all Items
			{
                            item i2;
                            i2.show();
			}
			break;




		}; // end of switch

	}while ( choice != '4' );

   return 0;
}
