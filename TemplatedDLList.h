// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;


// doubly linked list node
template <typename T>
struct DLListNode {
    T obj;
    DLListNode *prev, *next;
    // constructor
    DLListNode(T e={}, DLListNode *p = nullptr, DLListNode *n = nullptr)
        : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
    DLListNode<T> header, trailer;
public:
    DLList() : header(DLListNode<T>()), trailer(DLListNode<T>()) // default constructor
    {header.next = &trailer; trailer.prev = &header; }
    DLList(const DLList<T>& dll); // copy constructor
    DLList(DLList<T>&& dll); // move constructor
    ~DLList(); // destructor
    DLList& operator=(const DLList<T>& dll); // copy assignment operator
    DLList& operator=(DLList<T>&& dll); // move assignment operator
    // return the pointer to the first node
    DLListNode<T> *first_node() const { return header.next; } 
    // return the pointer to the trailer
    const DLListNode<T> *after_last_node() const { return &trailer; }
    // return if the list is empty
    bool is_empty() const { return header.next == &trailer; }
    T first() const; // return the first object
    T last() const; // return the last object
    void insert_first(T obj); // insert to the first node
    T remove_first(); // remove the first node
    void insert_last(T obj); // insert to the last node
    T remove_last(); // remove the last node
    void insert_after(DLListNode<T> &p, T obj);
    void insert_before(DLListNode<T> &p, T obj);
    T remove_after(DLListNode<T> &p);
    T remove_before(DLListNode<T> &p);
};


// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll){
    DLListNode<T> *temp = dll.first_node();
    while(temp->next != nullptr){
        out <<temp->obj <<", ";
        temp = temp->next;
    }
    return out;
}

struct DLListEmpty : public std::runtime_error {
  explicit DLListEmpty(char const* msg=nullptr): runtime_error(msg) {}
};

struct LocationInvalidInsertion : public std::runtime_error {
  explicit LocationInvalidInsertion(char const* msg=nullptr): runtime_error(msg) {}
};

struct LocationInvalidRemove : public std::runtime_error {
  explicit LocationInvalidRemove(char const* msg=nullptr): runtime_error(msg) {}
};

template <typename T>
DLList<T>::DLList(const DLList<T>& dll){ // copy constructor
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode<T> *currNode = dll.header.next;
    while(currNode->next != nullptr)
    {
        this->insert_last(currNode->obj);
        currNode = currNode->next;
    }
}

template <typename T>
DLList<T>::DLList(DLList<T>&& dll){
    if(!dll.is_empty()){
    this->header.next = dll.header.next;
    dll.header.next->prev = &this->header;
    this->trailer.prev = dll.trailer.prev;
    dll.trailer.prev->next = &this->trailer;
    
    dll.header.next = &dll.trailer; 
    dll.trailer.prev = &dll.header;
    }
    else{
        this->header.next = &this->trailer;
        this->trailer.prev = &this->header;
    }
} // move constructor

template <typename T>
DLList<T>::~DLList(){
    DLListNode<T> *prev_node, *node = header.next;
    while (&trailer != node) 
    {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
} // destructor

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll){
    if(this != &dll){
        DLListNode<T> *currNode = dll.header.next;
        while(header.next != &trailer) {
        this->remove_last();
        }
        this->header.next = &this->trailer;
        this->trailer.prev = &this->header;

        while(currNode != &dll.trailer) {
            this->insert_last(currNode->obj);
            currNode = currNode->next;
        }
    }
    return *this;
} // copy assignment operator


template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll){
    if(dll.is_empty() == true || this == &dll){
        if(!this->is_empty() && dll.is_empty()){
            while(header.next->next != nullptr){
                remove_last();
            }
            header.next = &trailer;
            trailer.next = &header;
        }
    }
    else{
        if(!this->is_empty()){
            while(header.next->next != nullptr){
                remove_last();
            }
        }
        this->header.next = dll.header.next;
        this->trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &this->header;
        dll.trailer.prev->next = &this->trailer;
        dll.header.next = &dll.trailer; 
        dll.trailer.prev = &dll.header;
        
    }
    return *this;   
} // move assignment operator

template <typename T>
T DLList<T>::first() const{
    if(is_empty()) {
        throw DLListEmpty("*********************Empty Doubly Linked List");
    }
    return header.next->obj;
} // return the first object

template <typename T>
T DLList<T>::last() const{
    if (is_empty()) {
        throw DLListEmpty("*********************Empty Doubly Linked List");
    }
    return trailer.prev->obj;
} // return the last object

template <typename T>
void DLList<T>::insert_first(T obj){
    DLListNode<T> *temp = new DLListNode<T>;
    temp->obj = obj;
    if((header.next == &trailer) && (trailer.prev == &header)){
        temp->next = &trailer;
        temp->prev = &header;
        header.next = temp;
        trailer.prev = temp;
    }
    else{
        temp->next = header.next;
        temp->prev = &header;
        header.next->prev = temp;
        header.next = temp;
    }
} // insert to the first node

template <typename T>
T DLList<T>::remove_first(){
    if((header.next == &trailer) && (trailer.prev == &header)){
        throw DLListEmpty("///////////////////Cannot Remove the first object from an empty Linked List! \n \n ");
    }
    else{
        DLListNode<T> *ptr = header.next;
        ptr->next->prev = &header;
        header.next = ptr->next;
        T obj = ptr->obj;
        //Freeing the pointers
        ptr->next = nullptr;
        ptr->prev = nullptr;

        //Now delete ptr
        delete ptr;
        return obj;
    }
} // remove the first node


template <typename T>
void DLList<T>::insert_last(T obj){
    DLListNode<T> *temp = new DLListNode<T>;
    temp->obj = obj;
    if((header.next == &trailer) && (trailer.prev == &header)){
        temp->next = &trailer;
        temp->prev = &header;
        header.next = temp;
        trailer.prev = temp;
    }
    else{
        temp->prev = trailer.prev;
        temp->next = &trailer;
        trailer.prev = temp;
        temp->prev->next = temp;
    }
} 

template <typename T>
T DLList<T>::remove_last(){
    //removing last
    if((header.next == &trailer) && (trailer.prev == &header)){
        throw DLListEmpty("///////////////////Cannot Remove last from an empty Linked List ! \n \n ");
    }
    else{
        DLListNode<T> *ptr = trailer.prev;

        ptr->prev->next = &trailer;
        trailer.prev = ptr->prev;
        T obj = ptr->obj;

        //freeing ptrs
        ptr->prev = nullptr;
        ptr->next = nullptr;
        delete ptr;
        return obj;
    }
} 

template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj){  
    if(p.next == &trailer){
        this->insert_last(obj);
    }
    else if(header.next == &trailer && trailer.prev == &header){
        this->insert_last(obj);
    }
    else if(&p == &header){
        this->insert_first(obj);
    }
    else if(&p == &trailer){
        throw LocationInvalidInsertion("\n\n  /////////////////// Inserting After The Trailer is not allowerd  ///////////////////");
    }
    else{
        DLListNode<T> *a = new DLListNode<T>;
        DLListNode<T> *b = p.next;
        a->obj = obj;
        b->prev = a;
        a->next = b;
        p.next = a;
        a->prev = p.prev->next;
    }
}

template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj){
        if(p.prev == &header){
        this->insert_first(obj);
    }
    else if(header.next == &trailer && trailer.prev == &header){
        this->insert_last(obj);
    }
    else if(p.next == &trailer){
        this->insert_last(obj);
    }
    else if(p.prev == nullptr){
        //Throw Exception or trying to insert before the header !
        throw LocationInvalidInsertion(" /////////////////// Inserting Before The Header/Trailer /////////////////// ");
    }
    else{
        DLListNode<T> *prev = p.prev;
        DLListNode<T> *nodeNew = new DLListNode<T>;
        nodeNew->obj = obj;
        nodeNew->prev = prev;
        nodeNew->next = &p;
        prev->next = nodeNew;
        p.prev = nodeNew;
    }
}


template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p){
    if(&p == &header || p.prev == &header){
        throw LocationInvalidRemove("///////////////////Cannot Remove Before Header");
    }
    else if(&p == &trailer){
        
        return remove_last();
    }
    else if(is_empty() == true){
        throw DLListEmpty("///////////////////Empty DLList detected \n\n");
    }
    else{
        T obj = p.prev->obj;
        DLListNode<T> *c = p.prev;
        p.prev = c->prev;
        c->prev->next = &p;
        c->next = nullptr;
        c->prev = nullptr;
        delete c;
        return obj;
    }
}

template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p){
    if(&p == &header){
        return remove_first();
    }
    else if(&p == &trailer || p.next == &trailer){
        //This is because the Element trailer and the Element before trailer
        throw LocationInvalidRemove("///////////////////Cannot Remove This Element ! \n\n");
    }
    else if(is_empty()== true){
        throw DLListEmpty("///////////////////Empty DLList ! \n\n");
    }
    else{
        T obj = p.next->obj;
        DLListNode<T> *c = p.next;
        p.next = c->next;
        c->next->prev = &p;
        c->next = nullptr;
        c->prev = nullptr;
        delete c;
        return obj;
    }
}
#endif

