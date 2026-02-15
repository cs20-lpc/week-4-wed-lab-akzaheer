template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    // TO DO: Implement the code for the append

    Node* newNode = new Node(elem);     // new node with value
    Node* last = trailer-> prev;        // make last node the trailer prev

    newNode->prev = last;                   // connect new one between last and trailer
    newNode->next = trailer;
    last->next = newNode;
    trailer->prev = newNode;

    this->length++;         // increase length
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    // TO DO: Implent code for getElement at position
    if(position < 0 || position >= this->length){  
        throw "Out of range!!";                       /// check if position is validf and throw a error if not 
    }

    Node* curr = header->next;              // make node for first eleent after header 
    for(int i = 0; i < position; i++){  
        curr = curr->next;                      // go throiugh the list until position found
    }
    return curr->value;    // return the elelemt found

}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}


template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
  // TO DO: Implement code to insert an element to list
    if(position < 0 || position > this->length){  
        throw "Out of range!!";                       /// check if position is validf and throw a error if not 
    }
    Node* curr = header->next;              // make node curr
    for(int i = 0; i < position; i++){              // moved throiugh node to postiton
        curr = curr->next; 
    }
    Node* newNode = new Node(elem);         // crwate new node

    newNode->prev = curr->prev;         /// connect the new node between curr and prev
    newNode->next = curr;
    curr->prev->next = newNode;
    curr-> prev = newNode;

    this->length++;             // increase length
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    // TO DO: Implement code to remove element at given position
    if(position < 0 || position >= this->length){  
        throw "Out of range!!";                       /// check if position is validf and throw a error if not 
    }
    Node* curr = header->next;              // make node curr
    for(int i = 0; i < position; i++){              // moved throiugh node to postiton
        curr = curr->next; 
    }

    curr->prev->next = curr->next;          // connect new node connect the node before and after cuyrr
    curr-> next-> prev = curr->prev;
    delete curr;                // deletge it
    this->length--;             // change length
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    // TO DO: Implement code to search for element

    Node* curr= header->next;           // make curr start at first node
    
    while (curr != trailer){            // go through list till trailer
        if(curr->value == elem){
            return true;                        // if found then return true
        }
        curr = curr->next;      // move to next if not found yet
    }

    return false;       // if not found in whole list return false
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    // TO DO: Add code for replace method
    if(position < 0 || position >= this->length){  
        throw "Out of range!!";                       /// check if position is valid and throw a error if not 
    }
    Node* curr = header->next;              // make node curr
    for(int i = 0; i < position; i++){              // moved throiugh node to postiton
        curr = curr->next; 
    }

    curr->value = elem;     //replace value
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename DoublyList<T>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) {
                outStream << " <--> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
