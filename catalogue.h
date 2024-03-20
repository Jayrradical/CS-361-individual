#ifndef catalogue_H
#define catalogue_H 

#include <string>
#include <fstream>
#include "book.h"

using namespace std;

class catalogue {
  private:
    int num_book;
    book* book_arr;
  public:
    catalogue();
    catalogue (const catalogue &); 
    catalogue& operator=(const catalogue &); 
    ~catalogue(); 
    
    book search_book_by_name(string); 
    catalogue search_book_by_price(int); 
    //add a book into the catalogue
    void add_to_catalogue(book&); 
    //remove a book from the catalogue
    void remove_from_catalogue(int); 
    
    void load_catalogue();
    void print_catalogue();
    
    int get_num_book();
    book* get_book_arr();
    void write_to_file(ofstream &);
};

#endif
