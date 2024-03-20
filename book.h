#ifndef book_H
#define book_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class book {
  private:
    string name;
    float paperback_cost;
    float hardcover_cost;
    float collector_edition_cost;
    
  public:
    string get_name() const; 
    float get_paperback_cost () const; 
    float get_hardcover_cost () const;
    float get_collector_edition_cost () const;
    
    void set_name (const string);
    void set_paperback_cost(const float);
    void set_hardcover_cost(const float);
    void set_collector_edition_cost(const float);
    
    void print_book() const;
    void load_book(ifstream &);

};

#endif