#include <iostream>
#include <list>
#include <algorithm>

#include "profile.h"

using namespace std;

class Athletes {
private:
    list<int> order_to_go; 
public:
    void Add(int id, int next) {
        auto it = find(begin(order_to_go), end(order_to_go), next);
        if (it == end(order_to_go)) {
            order_to_go.push_back(id);
        } else {
            order_to_go.insert(it, id);
        }
    }

    void Print() {
        for (const auto el : order_to_go) {
            cout << el << " " << endl;
        }
    }
};

int main(){
    int n;
    cin >> n;
    Athletes athletese;
    {
        LOG_DURATION("add");
    
    while (n != 0)
    {
        int id, next;
        cin >> id >> next;
        athletese.Add(id, next);
        --n;
    } 
    athletese.Print();
    }
    /* const int MAX_ATHLETES = 100'000;
    using Position = list<int>::iterator;

    int n_athletes;
    cin >> n_athletes;

    list<int> row;
    vector<Position> athlete_pos(MAX_ATHLETES + 1, row.end());
    {  LOG_DURATION("vector")
        for (int i = 0; i < n_athletes; ++i) {
            int athlete, next_athlete;
            cin >> athlete >> next_athlete;
            athlete_pos[athlete] = row.insert(
                athlete_pos[next_athlete],
                athlete
            );
        }

    for (int x : row) {
        cout << x << '\n';
    }
    } */
    return 0;
}
