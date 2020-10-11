#include "Library.h"
#include "TemplatedDLList.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <limits>
using namespace std;

//This is the mimir version

//Searches for a title in the database and returns vector of matching records
std::vector<Record> Library::search(std::string title){
	vector<Record> vec = {};
	char letter = (char)title[0];
	int index = (int)letter - 65;
	DLListNode<Record> *nodeHead = book_db[index].first_node();
			while(nodeHead != book_db.at(index).after_last_node()){
				if(nodeHead->obj.get_title() == title) {
					vec.push_back(nodeHead->obj);
					//return vec; uncomment this if you are looking for only the first instance of the book. 
					//This way you could iterate through multiple editions
				}
				nodeHead = nodeHead->next;
			}
	return vec;
}


        //Imports records from a file.  Does not import duplicates.
        // Return the number of records added to the database
		
int Library::import_database(std::string filename){
	
	ifstream ifs(filename);
	
	int counter = 0;
	
	if(ifs.is_open()){
		
		Record rec;
		
		while(ifs >> rec) {
			int ind = rec.get_title()[0]-65;
			
			book_db.at(ind).insert_first(rec);
			
			counter++;
		}
	}
	
	return counter;
}


        //Exports the current database to a file
        //Return the number of records exported
int Library::export_database(std::string filename){
	
	ofstream ofs;
	
	ofs.open(filename);
	
	int count_export;
	
	count_export=0;
	
	for(int i=0; i<book_db.size(); ++i) {
		
		DLListNode<Record> *nodeHead = book_db.at(i).first_node();
		
		while(book_db.at(i).after_last_node() != nodeHead) {
			
			ofs<<"\n"<<nodeHead->obj.get_title()<<endl<<nodeHead->obj.get_author()<<endl<<nodeHead->obj.get_ISBN();
			ofs<<endl<<nodeHead->obj.get_year()<<endl<<nodeHead->obj.get_edition();
			ofs<<"\n";
			
			nodeHead = nodeHead->next;
			
			count_export+=1;
		}
		
	}
	ofs.close();
	
	return count_export;		
}

void Library::print_database(){
	
	for(int i = 0; i<book_db.size(); ++i) {
		
		DLListNode<Record> *nodeHead = book_db.at(i).first_node();
		
		while(nodeHead != book_db.at(i).after_last_node()){
			
			cout<<nodeHead->obj<<endl;
			
			nodeHead = nodeHead->next;
			
		}
	}
}



        //Prompts user for yes or no and returns choice Y or N	


char Library::prompt_yes_no(){
	
	cout<<"Yes or No?"<<endl;
	cout<<"Enter Y for yes and N for no"<<endl;
	
	
	char binary;
	
	cin>>binary;
	
	return binary;
}





        //Given a vector of menu options returns index of choice
        int Library::prompt_menu(std::vector<std::string>Menu){
			int pick = 1;
			
			for(string i : Menu){
				
				cout<<pick<<" "<<i<<"\n";
				
				pick=pick+1;
			}
			
			int choice;
			
			cout<<"Choice: ";
			
			cin>>choice;
			
			choice = choice-1;
			
			return choice;
		}

        //Prompts user for a new record
Record Library::prompt_record(){
	Record additional;
	string line;
	cin.ignore();
	
	
	cout<<"Author:";
	getline(cin, line);
	additional.set_author(line);
	
	cout<<"Edition:";
	getline(cin,line);
	additional.set_edition(line);
	
	cout<<"ISBN:";
	getline(cin,line);
	additional.set_ISBN(line);
	
	cout<<"Title:";
	getline(cin,line);
	additional.set_title(line);
	
	cout<<"Year Published:"; // line might not be correct
	getline(cin,line);
	additional.set_year(line);
	
	return additional;
}


        //Prompt for a valid title
std::string Library::prompt_title(){
	
	string valid;
	
	cout<<"Enter a title: ";
	
	getline(cin, valid);
	
	if(cin.bad()){
		cout<<"Error: "<<endl;
	}
	
	cout<<endl;
	
	return valid;
}
	
        // Prompt for a valid string
std::string Library::prompt_string(std::string prompt){
	cout<<prompt;
	
	getline(cin, prompt);
	
	return prompt;
}


//add record to database, avoid complete duplicates
bool Library::add_record(Record book){
	
	vector<Record> answer_search;
	
	answer_search = search(book.get_title());
	
	if(answer_search.size() == 0){ //see if that makes sense
		
		int ind = (int)book.get_title()[0] - 65;
		
		book_db.at(ind).insert_last(book);
		
		return true;
	}
	else {	
		return false;
	}
	return false;
}


//Deletes a record from the database
void Library::remove_record(Record book){
	
	int ind = book.get_title()[0]-65;
	
	DLListNode<Record> *nodeHead = book_db.at(ind).first_node();
	
	if(nodeHead-> obj == book) {
				
		book_db.at(ind).remove_first();
				
		return;
	}
	
	while(nodeHead != book_db.at(ind).after_last_node()){
		
			 if(book == nodeHead->next->obj ) {
				
				book_db.at(ind).remove_after(*nodeHead);
				
				break;
				
			}
			
		nodeHead = nodeHead->next;
	}
	return;
}	
	
	
	
	
	
	