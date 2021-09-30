#include "libs/PhoneBook.hpp"
#include <array>

int main() {
       std::ifstream file("PhoneBook.txt"); // path to the file PhoneBook.txt
       PhoneBook book(file);
       file.close();
       std::cout << book;
 
       std::cout << "------SortByPhone-------" << std::endl;
       book.SortByPhone();
       std::cout << book;
 
       std::cout << "------SortByName--------" << std::endl;
       book.SortByName();
       std::cout << book;
 
       std::cout << "-----GetPhoneNumber-----" << std::endl;
       // lambda that gets a surname and returns the telephone number
       auto print_phone_number = [&book](const std::string& surname) { 
              std::cout << surname << "\t"; 
              auto answer = book.GetPhoneNumber(surname); 
              if (std::get<0>(answer).empty()) 
                     std::cout << std::get<1>(answer); 
              else 
                     std::cout << std::get<0>(answer); 
              std::cout << std::endl; 
       };

       // calls of lambdas
       print_phone_number("Ivanov");
       print_phone_number("Petrov");
       print_phone_number("Solovev");
 
       std::cout << "----ChangePhoneNumber----" << std::endl;
       book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },                    PhoneNumber{7, 123, "15344458", std::nullopt});
       book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
       std::cout << book;
}