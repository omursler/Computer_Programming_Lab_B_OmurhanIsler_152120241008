#include <iostream>
#include <string>

using namespace std;

typedef struct Page{
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
} Page;

//Function Prototypes
void menu(Page*& Head, Page*& Current);
void append(Page*& Head, Page*& Current, string new_url, string new_title);
void deleteEntry(Page*& Head, Page*& Current);
void displayHistory(Page* head, Page* current);
void move(Page*& current);
void clearMemory(Page*& Head);

//Functions
int main() {
    
    Page* Head = nullptr;
    Page* Current = nullptr;
    menu(Head, Current);

    return 0;
}

void menu(Page*& Head, Page*& Current) {
    int choice = 0;

    cout << "Welcome to the Browser History Manager." << endl;
    
    while(choice != 5) {
        cout << "\n1- Visit\n2- Back / Forward\n3- Delete Entry\n4- Display History\n5- EXIT" << endl;
        cout << "->";

        cin >> choice;
        

        if(choice == 1) {
            string new_url, new_title;
            cout << "Please enter the URL: "; 
            cin >> new_url;
            cout << "Please enter the title: "; 
            cin.ignore(); 
            getline(cin, new_title);
            append(Head, Current, new_url, new_title);
        }
        else if(choice == 2) {
            move(Current);
        }
        else if(choice == 3) {
            deleteEntry(Head, Current);
        }
        else if(choice == 4) {
            displayHistory(Head, Current);
        }
        else if(choice == 5) {
            clearMemory(Head);
            cout << "exitting..." << endl;
        }
    }
}

void append(Page*& Head, Page*& Current, string new_url, string new_title) {
    Page* p = new Page;
    p->url = new_url;
    p->title = new_title;
    
    cout << "Enter Time (H M S): ";
    cin >> p->accessTime[0] >> p->accessTime[1] >> p->accessTime[2];
    
    p->next = nullptr;

    if(Head == nullptr) {
        p->prev = nullptr;
        Head = p;
    } else {
        Page* temp = Head;
        while(temp->next != nullptr) temp = temp->next;
        temp->next = p;
        p->prev = temp;
    }
    Current = p; // Yeni eklenen sayfa 'current' olur
    cout << "Added: " << p->title << endl;
}

void deleteEntry(Page*& Head, Page*& Current) {
    if (Current == nullptr) { 
        cout << "Current page is already deleted." << endl;
        return; 
    }

    Page* toDelete = Current;

    if (toDelete->prev != nullptr) {
        toDelete->prev->next = toDelete->next;
    } 
    else {
        Head = toDelete->next;
    }
    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
        
        Current = toDelete->next;
    } 
    else {
        Current = toDelete->prev;
    }

    delete toDelete;
    cout << "Current page deleted." << endl;
}

void displayHistory(Page* head, Page* current) {
    if (!head) { cout << "History is empty." << endl; return; }

    cout << "\nHistory:" << endl;
    for (Page* temp = head; temp != nullptr; temp = temp->next) {
        if (temp == current) cout << "[CURRENT] ";
        else cout << "          ";

        cout << temp->title << " (" << temp->url << ") Time: ";
        for (int i = 0; i < 3; i++) {
            cout << (temp->accessTime[i] < 10 ? "0" : "") << temp->accessTime[i] << (i < 2 ? ":" : "");
        }
        cout << endl;
    }
}

void move(Page*& current) {
    if (!current) { cout << "History is empty." << endl; return; }
    
    int dir;
    cout << "1- Back / 2- Forward: "; cin >> dir;
    
    if (dir == 1 && current->prev) {
        current = current->prev;
    } else if (dir == 2 && current->next) {
        current = current->next;
    } else {
        cout << "No page anymore." << endl;
    }
}

void clearMemory(Page*& Head) {
    while(Head) {
        Page* n = Head->next;
        delete Head;
        Head = n;
    }
    cout << "Memory Cleared." << endl;
}
