//Citation: referenced own previous code from 162
//Author: Jared Yin
//Class: CS 361 Software Engineering 1

#include "store.h" 

store::store() {
    this->revenue = 0;
    this->order_arr = NULL;
    this->num_orders = 0;
}

store& store::operator=(const store &old) {  
    this->num_orders = old.num_orders;
    
    if (this->order_arr != NULL) {
        delete [] this->order_arr;
    }
    this->order_arr = new Order [this->num_orders]; 
    for (int i = 0; i < this->num_orders; i++) {
        this->order_arr[i] = old.order_arr[i];
    }
    return *this;
} 

store::~store() {  
    if (this->order_arr !=NULL) {
        delete [] this->order_arr;
        this->order_arr = NULL;
    }
}  

void store::load_data() {  
    ifstream fin;
    fin.open("store_info.txt");
    fin >> this->phone;
    fin.ignore();
    fin.clear();
    getline(fin, this->address, '\n');
    fin.close();

    this->m.load_catalogue();
}

void store::view_store_detail() {
    cout << " " << endl;
    cout << "Hi there! Our little bookstore here is located on the corner of the street, and we offer many different types of books. Feel free to stop by and take a peruse of our offerings when you get the chance!" << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << "Here is a list of our full catalogue, with prices listed in dollars: " << endl;
    cout << " " << endl;
    this->m.print_catalogue();
    cout << " " << endl;
    cout << "Reach us at: " << this->phone << endl;
    cout << "Find us at: " << this->address << endl;

}

void store::view_revenue() {
    cout << this->revenue << endl;
} 

void store::search_by_price() {
    float price;
    book C;
    int order;
    int index;

    cout << "Type your budget, and I will list every book we have that you can afford to get: " << endl;
    cin >> price;

    catalogue New_catalogue = this->m.search_book_by_price(price);
    if (New_catalogue.get_num_book() < 1) {
        cout << "You cant afford anything with your budget." << endl;
        return;
    }
    cout << "Would like to Buy a book! based off the search results above? 1-yes, 0-no: 0" << endl;
    cin >> order;
    while (order != 1 && order != 0) {
        cout << "Please try again, invalid input." << endl;
        cin >> order;
    }
    if (order == 1) {
        cout << "Enter the index number of the item you would like to order: " << endl;
        cin >> index;
        while (!(index >= 1 && index <= New_catalogue.get_num_book())) {
            cout << "Please try again, invalid input." << endl;
            cin >> index;
        }
        this->place_order(New_catalogue.get_book_arr()[index - 1]);
    }
    else if (order == 0) {
        return;
    }
}

void store::search_by_name() {
    string name;
    int choice;

    cout << "Enter the book name you want to search for: " << endl;
    cin >> name;
    
    book New_book = this->m.search_book_by_name(name);
    if (New_book.get_paperback_cost() < 0) {
        cout << "Sorry, we dont have that product at the moment." << endl;
        return;
    }
    cout << "Would like to Buy a book! based off the search results above? 1-yes, 0-no: 0" << endl;
    cin >> choice;
    while (choice != 1 && choice != 0) {
        cout << "Please try again, invalid input." << endl;
        cin >> choice;
    }
    if (choice == 1) {
        this->place_order(New_book);
    }
    else {return;}
}

void store::place_order(book &C) {
    C.print_book();
    char size;
    cout << "Which version of that book would you want (P)aperback, (H)ardcover, (C)ollector Edition" << endl;
    cin >> size;
    while (size != 'P' && size != 'H' && size != 'C') {
        cout << "Invalid input, please try again." << endl;
        cin >> size;
    }
    int quantity;
    cout << "How many would you like to order?" << endl;
    cin >> quantity;

    Order O(this->num_orders + 1, C.get_name(), size, quantity);
    this->add_order(O);
    this->revenue += get_order_cost(C, O);
}

float store::get_order_cost (book &C, Order &O) {
    if (O.get_book_size() == 'S') {
        return O.get_quantity() * C.get_paperback_cost();
    }
    if (O.get_book_size() == 'M') {
        return O.get_quantity() * C.get_hardcover_cost();
    }
    if (O.get_book_size() == 'L') {
        return O.get_quantity() * C.get_collector_edition_cost();
    }
    return 0;
} 

void store::place_order_option() {
    this->m.print_catalogue();
    int index;
    char size;
    cout << "Enter the index number of the book you would like to purchase: " << endl;
    cin >> index;
    while (!(index >= 1 && index <= this->m.get_num_book())) {
        cout << "Please try again, invalid input." << endl;
        cin >> index;
    }
    this->place_order(this->m.get_book_arr()[index - 1]);
    
    //Inclusivity Hueristic #2 message:
    cout << " " << endl;
    cout << "Cha Ching! An employee can now see how much you have spent in total by selecting:" << endl;
    cout << "'Display book orders' from the employee option screen." << endl;
    cout << " " << endl;
} 


void store::send_command(const string& command) {
    ofstream file_out("social_media_io.txt");
    if (file_out.is_open()) {
        file_out << command;
        file_out.close();
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Define the receive_response() function to receive a response from the microservice
string store::receive_response() {
    ifstream file_in("social_media_io.txt");
    string response;
    if (file_in.is_open()) {
        getline(file_in, response);
        file_in.close();
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
    return response;
}

void store::microservice_option() {
    
    cout << "Calling partner microservice..." << endl;

    int choice;
    cout << "Enter 1 to add a new social media link or 2 to retrieve links: ";
    cin >> choice;

    if (choice == 1) {
        string site, link;
        cout << "Enter the site name: ";
        cin >> site;
        cout << "Enter the site link: ";
        cin >> link;

        // Sending command to the microservice to add the link
        send_command("add\n" + site + " " + link + "\n");
    } else if (choice == 2) {
        // Sending command to the microservice to get links
        send_command("get links\n");

        // Receiving response from the microservice
        string response = receive_response();

        // Displaying the received links
        cout << "Received links from microservice:" << endl;
        cout << response << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

    

void store::add_order(Order &ord) {
    Order* temp = new Order [this->num_orders + 1];
    for (int i = 0; i < this->num_orders; i++) {
        temp[i] = this->order_arr[i];
    }
    temp[this->num_orders] = ord;

    delete [] this->order_arr;

    this->order_arr = temp;

    ++this->num_orders;
} 

void store::add_to_catalogue() {
    book New;
    string name;
    float paperback_cost;
    float hardcover_cost;
    float collector_edition_cost;

    //Inclusivity Hueristic #8 message:
    cout << " " << endl;
    cout << "Please follow the steps below and review the book information carefully before adding it to the catalogue. Incorrect entries may affect inventory accuracy." << endl;
    cout << " " << endl;

    cout << "What is the name of the item you want to add?" << endl;
    cin >> name;
    New.set_name(name);
    cout << "Cost of paperback: " << endl;
    cin >> paperback_cost;
    New.set_paperback_cost(paperback_cost);
    cout << "Cost of hardcover: " << endl;
    cin >> hardcover_cost;
    New.set_hardcover_cost(hardcover_cost);
    cout << "Cost of collector_edition: " << endl;
    cin >> collector_edition_cost;
    New.set_collector_edition_cost(collector_edition_cost);
    
    this->m.add_to_catalogue(New);
    
    //Inclusivity Hueristic #2 message:
    cout << " " << endl;
    cout << "You can now view your newly added item by displaying the catalogue with 'Display bookstore details'" << endl;
    cout << " " << endl;
}

void store::remove_from_catalogue() {
    this->m.print_catalogue();
    int index;
    cout << "Which item do you want to remove from the catalogue? (Enter number): " << endl;
    cin >> index;
    while (!(index >= 1 && index <= this->m.get_num_book())) {
        cout << "Please try again, invalid input." << endl;
        cin >> index;
    }
    this->m.remove_from_catalogue(index - 1);
}


void store::view_orders() { 
    for (int i = 0; i < num_orders; i++) {
        cout << order_arr[i].get_id() << " ";
        cout << order_arr[i].get_book_name() << " ";
        cout << order_arr[i].get_book_size() << " ";
        cout << order_arr[i].get_quantity() << endl;
    }
}

void store::couts(bool who) {
    if (who) {
        cout << "---------------------------------------------------------" << endl;
        cout << "As a Shopper, here are your options:" << endl;
        cout << "(1) Display book store details: catalogue, address and phone number" << endl;
        cout << "(2) Search by book price" << endl;
        cout << "(3) Search by book name" << endl;
        cout << "(4) Buy a book!" << endl;
        cout << "(5) Share with your friends! (Microservice)" << endl;
        cout << "(6) Go Back / Logoff" << endl;
        cout << "---------------------------------------------------------" << endl;

    }

    else {
        cout << "---------------------------------------------------------" << endl;
        cout << "As an Employee, here are your options:" << endl;
        cout << "(1) Display store revenue" << endl;
        cout << "(2) Display book orders" << endl;
        cout << "(3) Add a book to our catalogue" << endl;
        cout << "(4) Remove a book from our catalogue" << endl;
        cout << "(5) Display book store details: catalogue, address and phone number" << endl;
        cout << "(6) Go Back / Logoff" << endl;
        cout << "---------------------------------------------------------" << endl;

    }
}

int store::Shopper() {
    int c_action;
    while (c_action != 6) {
        this->couts(true);
        cin >> c_action;
        while (c_action < 1 || c_action > 6) {
            cout << "invalid input, please try again: " << endl;
            cin >> c_action;
        }
        if (c_action == 1) {
            this->view_store_detail();
        }
        else if (c_action == 2) {
            this->search_by_price();
        }
        else if (c_action == 3) {
            this->search_by_name();
        }
        else if (c_action == 4) {
            this->place_order_option();
        }
        else if (c_action == 5) {
            this->microservice_option();
        }
    }
    return c_action;
}

int store::employee() {
    int e_action;
    while (e_action !=6) {
        this->couts(false);
        cin >> e_action;
        while (e_action < 1 || e_action > 6) {
            cout << "invalid input, please try again: " << endl;
            cin >> e_action;
        }
        if (e_action == 1) {
            this->view_revenue();
        }
        else if (e_action == 2) {
            this->view_orders();
        }
        else if (e_action == 3) {
            this->add_to_catalogue();
        }
        else if (e_action == 4) {
            this->remove_from_catalogue();
        }
        else if (e_action == 5) {
            this->view_store_detail();
        }
    }
    return e_action;
} 

char store::choose_user() {
    char type;
    cout << "Hi there! Are you just (S)hopping around, an (E)mployee here, or do you want to (Q)uit?" << endl;
    cin >> type;
    while (type != 'S' && type != 'E' && type != 'Q') {
        cout << "invalid input, please try again: " << endl;
        cin >> type;
    }
    return type;
}

bool store::check_file() {
    ifstream fin;
    fin.open("catalogue.txt");
    if (fin.fail()) {
        return false;
    }
    fin.close();
    fin.open("store_info.txt");
    if (fin.fail()) {
        return false;
    }
    fin.close();   
    return true;
}

void store::print_order() {
    ofstream fout;
    fout.open("orders.txt");
    fout << num_orders << endl;
    for (int i = 0; i < num_orders; i++) {
        fout << order_arr[i].get_id() << " ";
        fout << order_arr[i].get_book_name() << " ";
        fout << order_arr[i].get_book_size() << " ";
        fout << order_arr[i].get_quantity() << endl;
    }
    fout.close();
} 

void store::catalogue_copy() {
    ofstream fout;
    catalogue m;
    fout.open("catalogue.txt");
    fout << m.get_num_book();
    this->m.write_to_file(fout);
}

void store::store_info_copy() {
    ofstream fout;
    fout.open("store_info.txt");
    fout << this->phone << endl;
    fout << this->address << endl;
}

void store::run() {
    if (check_file() == false) {
        cout << "Failed to open file(s)" << endl;
        return;
    }
    int c = 0;
    int e = 0;
    this->load_data();
    char type;
    do {
        cout << " " << endl;
        cout << " ____              _        _" << endl; 
        cout << "|  _ \\            | |      | |" << endl;
        cout << "| |_) | ___   ___ | | _____| |" << endl;
        cout << "|  _ < / _ \\ / _ \\| |/ / __| |" << endl;
        cout << "| |_) | (_) | (_) |   <\\__ \\_|" << endl;
        cout << "|____/ \\___/ \\___/|_|\\_\\___(_)" << endl;
        cout << " " << endl;

                               
        cout << "Welcome to Jared's Homegrown Book Store! (for CS 361)" << endl;
        type = this->choose_user(); 
        if (type == 'S') {
            c = this->Shopper();
        }
        else if (type == 'E') {
            e = this->employee();
        }
        else if (type == 'Q') {
            this->print_order();
            this->catalogue_copy();
            this->store_info_copy();
            cout << "Thank you for using Jared's CS 361 Online Bookstore Interface. Goodbye!" << endl;
            return;
        }
    } while (type != 'Q');
}








