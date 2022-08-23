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

    void borrow (){
        if (total_quantity  - total_borrowed == 0)
            return;
        total_borrowed++;

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


int main(){
    return 0;
}