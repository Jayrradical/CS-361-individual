#include "book.h"
#include <iostream>

string book::get_name() const {return this->name;}  // Get the name of the book
float book::get_paperback_cost () const {return this->paperback_cost;}  // Get the cost of paperback edition
float book::get_hardcover_cost () const {return this->hardcover_cost;}  // Get the cost of hardcover edition
float book::get_collector_edition_cost () const {return this->collector_edition_cost;}  // Get the cost of collector's edition

void book::set_name (const string n) {this->name = n;}  // Set the name of the book
void book::set_paperback_cost(const float s) {this->paperback_cost = s;}  // Set the cost of paperback edition
void book::set_hardcover_cost(const float m) {this->hardcover_cost = m;}  // Set the cost of hardcover edition
void book::set_collector_edition_cost(const float l) {this->collector_edition_cost = l;}  // Set the cost of collector's edition 

void book::load_book(ifstream &fin) {  // Load book details from file
    fin >> this->name;
    fin >> this->paperback_cost;
    fin >> this->hardcover_cost;
    fin >> this->collector_edition_cost;
}

void book::print_book() const {  // Print book details
    cout << this->name << endl;
    cout << "paperback: " <<this->paperback_cost << endl;
    cout << "hardcover: " <<this->hardcover_cost << endl;
    cout << "collector_edition: " <<this->collector_edition_cost << endl;
}


