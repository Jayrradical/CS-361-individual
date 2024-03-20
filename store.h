#ifndef store_H
#define store_H

#include <string>
#include <fstream>
#include <iostream>
#include "catalogue.h"
#include "order.h"

using namespace std;

class store {
  private:
    
    catalogue m;
    string phone;
    string address;
    float revenue;
    Order *order_arr;  
    int num_orders;

  public:
    
    store();
    store& operator=(const store &); 
    ~store(); 

    void load_data(); 
    void view_store_detail();
    void view_revenue();
    void search_by_price();
    void search_by_name();
    void place_order(book&);
    float get_order_cost (book &, Order &);
    void place_order_option();
    void microservice_option();

    void add_order(Order&);
    void add_to_catalogue();
    void remove_from_catalogue();
    void view_orders();

    void couts(bool);
    int Shopper();
    int employee();
    char choose_user();
    bool check_file();
    void print_order();
    
    void catalogue_copy();
    void store_info_copy();
    void run();

};

#endif
