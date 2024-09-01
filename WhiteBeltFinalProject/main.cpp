#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <iomanip>
#include <exception>
#include <format>

using namespace std;

class Date 
{
public:
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        month = new_month;
        day = new_day;
    }

	int GetYear() const {
        return year;
    }

	int GetMonth() const {
        return month;
    }

	int GetDay() const {
        return day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator < (const Date & lhs, const Date & rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        } else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0') << setw(4) << date.GetYear() << "-" << 
        setw(2) << date.GetMonth() << "-" << 
        setw(2) << date.GetDay();
    return stream;
}

Date GetDate(const string& y_m_d) {
    stringstream ss(y_m_d);
    int year, month, day;
    char ch1, ch2;
    ss >> year >> ch1 >> month >> ch2 >> day;
    if (ch1 != '-' || ch2 != '-' || !ss.eof()) {
        throw format_error("Wrong date format: " + y_m_d);
    }
    if (month < 1 || month > 12) {
        throw logic_error("Month value is invalid: " + to_string(month));
    }
    if (day < 1 || day > 31) {
        throw logic_error("Day value is invalid: " + to_string(day));
    }
    return {year, month, day};
}

class Database 
{
public:
	void AddEvent(const Date & date, const string & event) {
        db[date].insert(event);
    }

	bool DeleteEvent(const Date & date, const string & event) {
        if (db.count(date) > 0 && db[date].count(event)) {
            db[date].erase(event);
            return true;
        } else {
            return false;
        }
    }

	int  DeleteDate(const Date & date) {
        if (db.count(date) > 0) {
            int del_events = db[date].size();
            db.erase(date);
            return del_events;
        } else {
            return 0;
        }
    }

	set<string> Find(const Date & date) const {
        if (db.count(date) > 0) {
            return db.at(date);
        } else {
            return {};
        }
    }

	void Print() const {
        for (const auto& [key, value] : db) {
            for (const auto& event : value) {
                cout << key << " " << event << "\n";
            }
        }
    }

private:
    map<Date, set<string>> db;
};

int main() 
{
    try{
        Database database;

	    string full_command;
	    while (getline(cin, full_command)) {

            stringstream ss(full_command);
            string command;
            ss >> command;

            if (command == "Add") {
                string y_m_d, event;
                ss >> y_m_d >> event;
                const Date date = GetDate(y_m_d);
                database.AddEvent(date, event);

            } else if (command == "Del") {
                string y_m_d, event;
                ss >> y_m_d;
                if (!ss.eof()) {
                    ss >> event;
                }
                const Date date = GetDate(y_m_d);

                if (event.empty()) {
                    int del_events = database.DeleteDate(date);
                    cout << "Deleted " << del_events << " events" << "\n";
                } else {
                    if (database.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << "\n";
                    } else {
                        cout << "Event not found" << "\n";
                    }
                }

            } else if (command == "Find") {
                string y_m_d;
                ss >> y_m_d;
                const Date date = GetDate(y_m_d);
                for (const auto& event : database.Find(date)) {
                    cout << event << "\n";
                }

            } else if (command == "Print") {
                database.Print();

            } else if (command.empty()) {

            } else {
                throw logic_error("Unknown command: " + command);

            }
	    }
    } catch (exception& ex){
        cout << ex.what() << "\n";
    }
	
	return 0;
}