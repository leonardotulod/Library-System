#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

using namespace std;

class Record {
private:
    string title,ISBN,author,year,edition;
public:
    string get_title() const;
    string get_ISBN() const;
    string get_author() const;
    string get_year() const;
    string get_edition() const;

    void set_title(string _title);
    void set_ISBN(string _ISBN);
    void set_author(string _author); 
    void set_year(string _year); 
    void set_edition(string _edition);
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif
