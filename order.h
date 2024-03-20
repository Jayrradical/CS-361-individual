#ifndef ORDER_H
#define ORDER_H 

#include <string>

using namespace std;

class Order
{
private:
	int id;
	string book_name;
	char book_size;
	int quantity;

public:
	Order();  
	Order(int id, string book_name, char book_size, int quantity);  

	float get_id () const;
	string get_book_name () const;
	char get_book_size () const;
	float get_quantity () const;

};
#endif