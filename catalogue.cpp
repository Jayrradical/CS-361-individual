#include "catalogue.h"
#include <iostream>

catalogue::catalogue () {
    this->num_book = 0;
    this->book_arr = NULL;
}


//CC (copy construstor)
catalogue::catalogue (const catalogue &old) { 
    this->num_book = old.num_book;
    
    this->book_arr = new book [this->num_book];
    for (int i = 0; i < this->num_book; i++) {
        this->book_arr[i] = old.book_arr[i];
    }

}

//AOO (assignment Operator Overload)
catalogue& catalogue::operator=(const catalogue &old) { 
    this->num_book = old.num_book;
    
    if (this->book_arr != NULL) {
        delete [] this->book_arr;
    }
    this->book_arr = new book [this->num_book];
    for (int i = 0; i < this->num_book; i++) {
        this->book_arr[i] = old.book_arr[i];
    }

    return *this;
}

//Destructor
catalogue::~catalogue() {  
    if (this->book_arr !=NULL) {
        delete [] this->book_arr;
        this->book_arr = NULL;
    }
} 

book catalogue::search_book_by_name(string name) {
    for (int i = 0; i < num_book; i++) {
        if (book_arr[i].get_name() == name) {
            cout << "paperback - " << book_arr[i].get_paperback_cost() << endl;
            cout << "hardcover - " << book_arr[i].get_hardcover_cost() << endl;
            cout << "collector_edition - " << book_arr[i].get_collector_edition_cost() << endl;
            return book_arr[i];
        }
    }
    book empty;
    empty.set_paperback_cost(-1);
    return empty;
}

catalogue catalogue::search_book_by_price(int upper_bound) {
    catalogue price;
    int counter = 0;
    for (int i = 0; i < num_book; i++) {
        if (upper_bound >= book_arr[i].get_paperback_cost()) {
            price.add_to_catalogue(book_arr[i]);
            cout << counter + 1 << ". " << book_arr[i].get_name() << endl;
            cout << "paperback - " << book_arr[i].get_hardcover_cost() << endl;
            counter += 1;

        }
        if (upper_bound >= book_arr[i].get_hardcover_cost()) {
            cout << "hardcover - " << book_arr[i].get_hardcover_cost() << endl;
        }
        if (upper_bound >= book_arr[i].get_collector_edition_cost()) {
            cout << "collector_edition - " << book_arr[i].get_collector_edition_cost() << endl;
        }
    }
    return price;
} 

void catalogue::add_to_catalogue(book& book_to_add) {  //add a book into the catalogue
    book* temp = new book [this->num_book + 1];
    for (int i = 0; i < this->num_book; i++) {
        temp[i] = this->book_arr[i];
    }
    temp[this->num_book] = book_to_add;

    delete [] this->book_arr;
    this->book_arr = temp;
    ++this->num_book;
} 

void catalogue::remove_from_catalogue(int index_of_book_on_catalogue) {  //remove a book from the catalogue
    book* temp = new book [this->num_book - 1];

    for (int i = 0; i < index_of_book_on_catalogue; i++) {
        temp[i] = this->book_arr[i];
    }
    for (int i = index_of_book_on_catalogue; i < this->num_book - 1; i++) {
        temp[i] = this->book_arr[i + 1];
    }

    delete [] this->book_arr;
    this->book_arr = temp;
    --this->num_book;
} 

void catalogue::load_catalogue() { 
    ifstream fin;
    fin.open("catalogue.txt");

    fin >> this->num_book;
    this->book_arr = new book[num_book];
    for (int i = 0; i < num_book; i++) {
        this->book_arr[i].load_book(fin);
    }
}

void catalogue::print_catalogue() {
    for (int i = 0; i < num_book; i++) {
        cout << "(" << i + 1 << ") ";
        this->book_arr[i].print_book();
    }
}

int catalogue::get_num_book() {return this->num_book;}
book* catalogue::get_book_arr() {return this->book_arr;}

void catalogue::write_to_file(ofstream &fout) {
    for (int i = 0; i < this->num_book; i++) {
        fout << this->book_arr[i].get_name() << " ";
        fout << this->book_arr[i].get_paperback_cost() << " ";
        fout << this->book_arr[i].get_hardcover_cost() << " ";
        fout << this->book_arr[i].get_collector_edition_cost() << endl;
    }
}