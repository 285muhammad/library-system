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
};


int main(){
    return 0;
}