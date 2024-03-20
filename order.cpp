#include "order.h"

Order::Order() {}

Order::Order(int id, string book_name, char book_size, int quantity) {
    this->id = id;
    this->book_name = book_name;
    this->book_size = book_size;
    this->quantity = quantity;
}

float Order::get_id () const {return this->id;}
string Order::get_book_name () const {return this->book_name;}
char Order::get_book_size () const {return this->book_size;}
float Order::get_quantity () const {return this->quantity;}


    