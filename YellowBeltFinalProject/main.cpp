#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Конечние цели рефакторинга:
/* 
упростить дальнейшую поддержку кода;
уменьшить сложность кода;
упростить добавление новых абстракций в программу.


Review criteria

// Задание будет оцениваться по следующим критериям:

эффективность выполнения кода;
задублированность кода;
эффективность использования приёмов рефакторинга кода, показанных в лекциях.

 */

class Person {
public:
    Person(const string& name) : Name(name) {
    }

    const string GetName() const { return Name; }

    virtual void Walk(const string& destination) const = 0;

private:
    const string Name;
};

class Student : public Person {
public:
    Student(const string& name, const string&  favouriteSong) : Person(name), FavouriteSong(favouriteSong) {
    }

    void Learn() const {
        cout << "Student: " << Name << " learns" << endl;
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        SingSong();
    }

private:
    const string Name;
    string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name), Subject(subject) {
    }
    
    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

private:
    const string Name;
    string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name) {
    }

    void Check(Person& person) {
        string class_name = typeid(person).name();
        class_name[0] = ' ';
        cout << "Policeman: " << Name << " checks" << class_name << "." << class_name << "'s name is: " << person.GetName() << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

private:
    const string Name;
};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    p.Check(p);
    p.Check(t);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}