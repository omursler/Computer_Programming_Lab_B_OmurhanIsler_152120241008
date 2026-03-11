#include <iostream>
#include <string>

using namespace std;

typedef struct Node {
    string title;
    struct Node *next;
} Node;

//Function templates
void menu(Node *Head);
void print_list(Node *Head);
Node *insert(Node *Head, string new_title);
void clearBuffer();
bool search_list(Node *Head, string target_song);


int main() {

    Node *Head = NULL;
    menu(Head);

    return 0;
}
//Functions
void menu(Node *Head) {

    int i = 0;
    string new_title;
    string target_song;
    bool if_exists;

    
    while (i != 4){
        cout << "MENU:\n\t1. Add\n\t2. Search\n\t3. List\n\t4. Exit" << endl;
        cout << "\vChoosing:";
        cin >> i;
        clearBuffer(); //Clears the "\n" from the enter for getline func.

        if(i == 1) {
            //add song
            cout << "Please enter the name of the song." << endl;
            cout << "->";
            getline(cin, new_title);
            Head = insert(Head, new_title);
        }
        else if(i == 2) {
            //search song
            cout << "Search for the song." << endl;
            cout << "->";
            getline(cin, target_song);
            if_exists = search_list(Head, target_song);
            if(if_exists) {
                cout << "The song " << target_song << " is in the list." << endl;
            } else {
                cout << "The song " << target_song << " does not exist in this list." << endl;
            }
        }
        else if(i == 3) {
            //List playlist
            print_list(Head);
        }
        else if(i == 4){
            // exit
            break;
        }
        else {
            cout << "Please enter a valid choice." << endl;
            continue;
        }
    };
    
    

    cout << "Thanks for visitting." <<  endl;
}

Node *insert(Node *Head, string new_title) {
    Node *p = new Node;
    p->title = new_title;
    p->next = Head;
    return p;
}

void print_list(Node *Head) {
    if (Head == nullptr) {
        cout << "The list is currently empty." << endl;
        return;
    }
    Node *current = Head;
    int i = 1;
    while (current != nullptr) {
        cout << i << ". " << current->title << endl;
        current = current->next;
        i++;
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool search_list(Node *Head, string target_song) {
    Node *current = Head;

    while (current != NULL) {
        if(current->title == target_song) {
            return true;
        } else {
            current = current->next;
        }
    }
    return false;
}