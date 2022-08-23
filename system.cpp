#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_BOOKS (10);
const int MAX_USERS (10);

struct book
{
    string name;
    int id;
    int total_quantity;
    int total_borrowed;

    book(){
        name = " ";
        id = -1 ;
        total_borrowed = total_quantity = 0 ;
    }

    void add_book (){
        cout << "Enter book ID & NAME & QUANTITAY " << endl;
        cin >> id >> name >> total_quantity;
    }

    bool search_by_prefix (string prefix){
        if(name.size() < prefix.size())
            return false;
        
        for (int i = 0 ; i < (int) prefix.size() ; i++){
            if(prefix[i] != name[i])
                return false;
        }
        return true;
    }

    bool  borrow (int user_id){
        if (total_quantity  - total_borrowed == 0)
            return false;
        total_borrowed++;
        return true;

    }
    void return_book(){
        assert (total_borrowed > 0 && total_quantity > 0 );
        total_borrowed--;
    }

    void print_books(){
        
        cout << "book id ==> " << id << " name ==> "<<name
            << " quantity ==> " << total_quantity 
            << " total borrowed ==> " << total_borrowed <<endl;

    }
};

bool compare_name (book &a ,book &b){
    return a.name < b.name ;
}

bool compare_id (book &a , book &b){
    return a.id < b.id ;
}

struct user
{
    string name ;
    int national_id;
    int borrowed_books_ids[MAX_BOOKS];
    int number_of_borrowed_books;

    user(){
        name = " ";
        national_id = -1 ;
        number_of_borrowed_books = 0;
    }

    void add_user(){
        cout <<"Enter user NAME & NATIONA ID " << endl;
        cin >> name >> national_id ;
    }




    void user_borrow(int book_id){
        borrowed_books_ids[number_of_borrowed_books++] = book_id ;
    }

    bool is_borrow (int book_id){
        for (int i = 0 ; i < number_of_borrowed_books ; i++){
            if(book_id == borrowed_books_ids[i])
                return true;
        }
        return false;
    }

    void user_return(int book_id){
        if(number_of_borrowed_books == 0){
            cout << "There is no borrowed books" << endl;
            return ;
        }

        int is_removed {false};
        
        for (int i = 0 ; i < number_of_borrowed_books ; i++){
            if(book_id = borrowed_books_ids [i]){
                for(int j = i+1 ; j < number_of_borrowed_books ; j++)
                    borrowed_books_ids[j-1] = borrowed_books_ids[j];
                is_removed = true ;
                number_of_borrowed_books --;
            }

        }

        if(!is_removed)
            cout << "User ==> " << name 
            << " never borrowed book with id " << national_id <<endl;
        

    }

    void print_all_users(){
        cout << "User Name ==>  "  << name 
            << " National Id ==> " << national_id << endl;
    }





};

struct libaray_system
{
    int total_books ;
    int total_users ;
    book books[MAX_BOOKS];
    user users[MAX_USERS];

    libaray_system(){
        total_books = total_users = 0;
    }

    void run(){
        while (true)
        {
            int choice {menu()};

            if(choice == 1)
                add_book();
            else if (choice == 2)
                search_book_by_prefix();
            else if (choice == 4)
                print_books_sorted_by_id();
            else if (choice == 5)
                print_books_sorted_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7 )
                user_want_to_borrow();
            else if (choice == 8)
                user_want_to_return_book();
            else if (choice == 9 )
                print_users();
            else 
                break;

        }
        
    }

    int menu(){
        int choice {0};

        while (choice ==0)
        {
            cout << "Library Menu " << endl;
            cout << "1) Add a book " << endl;
            cout << "2) Serach about books by prefix " << endl;
            cout << "3) Print names of who borrowed the book" << endl;
            cout << "4) Print books sorted by id " << endl ;
            cout << "5) Print books sorted by name " << endl;
            cout << "6) Add a user " << endl;
            cout << "7) User want to borrow a book " << endl;
            cout << "8) User want to retrun a book " << endl;
            cout << "9) Print Users " << endl;
            cout << "10) Exist " << endl;

            cin >> choice ;

            if(!(choice >=1 && choice <= 10)){
                cout << "Invalid Choice , Try Again" << endl;
                choice = 0;
            }

        }

        return choice;
        
    }

    void add_book(){
        books[total_books++].add_book();
    }

    void search_book_by_prefix(){
        string prefix;
        cout << "Enter the book prefix" << endl;
        cin >> prefix ;

        int cnt {0};

        for(int i=0 ; i<total_books ;i++){
            if(books[i].search_by_prefix(prefix)){
                cout << books[i].name << endl;
                cnt++;
            }
        }

        if (cnt == 0 )
            cout << "There is no books with this prefix "  << endl;

    }

    void print_books_sorted_by_id(){
        sort(books , books + total_books , compare_id);

        for(int i=0 ; i < total_books ; i++){
            cout << "Book id ==> " << books[i].id
                << " name ==> " << books[i].name
                << " total quantity " << books[i].total_quantity
                << " total borrowd " << books[i].total_borrowed << endl ;

        }
    }

    void print_books_sorted_by_name(){
        sort(books , books + total_books , compare_name);

        for(int i=0 ; i < total_books ; i++){
            cout << "Book id ==> " << books[i].id
                << " name ==> " << books[i].name
                << " total quantity " << books[i].total_quantity
                << " total borrowd " << books[i].total_borrowed << endl ;

        }

    }

    void add_user(){
        users[total_users++].add_user();
    }

    void print_users(){
        for(int i = 0 ; i < total_users ; i++ ){
            users[i].print_all_users();
        }
    }

    int find_user_idx_by_name (string user_name){
        for(int i=0 ; i < total_users ; i++){
            if(users[i].name == user_name)
                return i;
        }
        return -1;

    }

    int find_book_idx_by_name (string book_name){
        for(int i=0 ; i < total_books ; i++){
            if(books[i].name == book_name)
                return i;
        }
        return -1;
    }

    bool read_book_name_and_user_name (int &user_idx , int &book_idx , int tries = 3){

        string book_name , user_name;

        while (tries--)
        {
            cout<<"Enter User name and book name " << endl;
            cin >> user_name >> book_name ;

            user_idx = find_user_idx_by_name (user_name);

            if(user_idx == -1){
                cout << " There is no users with this name " << endl;
                continue; ;
                
            }
            
            int user_id {users[user_idx].national_id};

            book_idx = find_book_idx_by_name (book_name);

            if(book_idx == -1) {
                cout<< "There is no books with this name " << endl;
                continue;;

            }
            
            int book_id { books[book_idx].id};
            return true;

        }

            cout << "You tried several times and all are wrong " << endl;
            return false;

        
    }

    void user_want_to_borrow(){

        int book_idx, user_idx;
        if(!read_book_name_and_user_name(user_idx , book_idx))
            return ;
        
        int user_id {users[user_idx].national_id};
        int book_id {books[book_idx].id};


        if(!books[book_idx].borrow(user_id))
            cout << "There no copies form this book " << endl ;
        else 
            users[user_idx].user_borrow(book_id);

    }

    void user_want_to_return_book(){
        int user_idx , book_idx;

        if(!read_book_name_and_user_name(user_idx , book_idx))
            return ;
        
        int book_id {books[book_idx].id};
        int user_id {users[user_idx].national_id};

        users[user_idx].user_return(book_id);
        books[book_idx].return_book();


    }

    void print_names_who_borrowed_book(){
        string book_name;
        cout << "Enter the book name " << endl;
        cin >> book_name ;

        int book_idx {find_book_idx_by_name(book_name)};

        if(book_idx == -1){
            cout << "There is no books with this name " << endl;
            return ;
        }

        int book_id {books[book_idx].id};

        if(books[book_idx].total_borrowed == 0 ){
            cout << "There is no borrowed books " << endl;
            return ;
        }

        for (int i = 0 ; i < total_users ; i++){
            if(users[i].is_borrow(book_id))
                cout << users[i].name << endl;
        }
    }
};


int main(){
    libaray_system library;
    library.run();
    return 0;
}