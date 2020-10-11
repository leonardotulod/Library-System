//implementation of record class
#include<iostream>
#include "Record.h"
using namespace std;

string Record::get_author() const {
	return this->author;
}

void Record::set_author(string s) {
	this->author = s;
}

string Record::get_title() const {
	return this->title;
}

void Record::set_title(string s) {
	this->title = s;
}

string Record::get_ISBN() const {
	return this->ISBN;
}

void Record::set_ISBN(string s) {
	this->ISBN = s;
}

string Record::get_edition() const {
	return this->edition;
}

void Record::set_edition(string s) {
	this->edition = s;
}

string Record::get_year() const{
	return this->year;
}

void Record::set_year(string s) {
	this->year = s;
}





std::istream& operator>>(std::istream& is, Record& rec){
	
    string line;

    char c;
    is >> c;
    is.putback(c);

    // Retreive each line from the stream and set in the record
    getline(is, line);
    if (line.back() == '\r')
        line.pop_back();
    rec.set_title(line);

    getline(is, line);
    if (line.back() == '\r')
        line.pop_back();
    rec.set_author(line);
    
    getline(is, line);
    if (line.back() == '\r')
        line.pop_back();
    rec.set_ISBN(line);

    getline(is, line);
    if (line.back() == '\r')
        line.pop_back();
    rec.set_year(line);

    getline(is, line);
    if (line.back() == '\r')
        line.pop_back();
    rec.set_edition(line);

    // Return the stream
    return is;
}





std::ostream& operator<<(std::ostream& os, Record& rec){
	os<<rec.get_title()<<endl;
	os<<rec.get_author()<<endl;
	os<<rec.get_ISBN()<<endl;
	os<<rec.get_year()<<endl;
	os<<rec.get_edition(); //maybe endl after
	return os;
}

bool operator==(const Record& r1, const Record& r2){ 
	if((r1.get_author() == r2.get_author()) && (r1.get_ISBN() == r2.get_ISBN()) && (r1.get_title() == r2.get_title())){
		return true;
	}
	else {
		return false;
	}
}





