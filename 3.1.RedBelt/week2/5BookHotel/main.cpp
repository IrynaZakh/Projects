#include <iostream>
#include <set>
#include <queue>
//#include <algorithm>
#include <cstdint>

#include "profile.h"

using namespace std;

struct BookStruct {
    string hotel_name;
    int room_count{0};
    int client_id{0};
    int64_t book_time{0};
};

class HotelManager {
    queue<BookStruct> book_db;

public:
    HotelManager() {}

    void Book (BookStruct bs) {
        book_db.push(bs);
        if (book_db.size() != 1){
            while ((book_db.back().book_time - 86400 >= book_db.front().book_time) || 
                    (book_db.front().book_time > book_db.back().book_time)){
               book_db.pop(); }}}
    
    int RoomsCount (const string& hotel) {
        int rooms{0};
        queue<BookStruct> book_db_copy = book_db;
        while (!book_db_copy.empty()) {
            if (book_db_copy.front().hotel_name == hotel) {
                rooms += book_db_copy.front().room_count;
            }
            book_db_copy.pop();
        }
        return rooms;
    }

    int ClientsCount (const string& hotel) {
        set<int> clients_id;
        queue<BookStruct> book_db_copy = book_db;
        while (!book_db_copy.empty()) {
            if (book_db_copy.front().hotel_name == hotel) {
                clients_id.insert(book_db_copy.front().client_id);
            }
            book_db_copy.pop();
        }
        return clients_id.size();
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id{0}; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            BookStruct bs;
            cin >> bs.book_time >> bs.hotel_name;
            cin >> bs.client_id >> bs.room_count;
            manager.Book(bs);

        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.ClientsCount(hotel_name) << endl;

        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name; 
            cout << manager.RoomsCount(hotel_name) << endl;           
        }
    }
    return 0;
}
