#include <iostream>
#include <string>
#define N 5

using namespace std;

typedef struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
}MoneyBundle;

typedef struct Stack{
    MoneyBundle* top;
}Stack;

typedef struct Customer{
    string customerName;
    string transactionType;
}Customer;

typedef struct CustomerQueue{
    Customer customers[N];
    int front, rear, noItems;
}CustomerQueue;

//Function Prototypes of Stack
void createStack(Stack* stc);
bool isEmpty(Stack* stc);
void Push(Stack* stc,string serialNumber, string currencyType, int billCounts[3]);
void Pop(Stack* stc);
void printStack(Stack* stc);
void destroyStack(Stack* stc);
//Function Prototypes of Queue
void createQueue(CustomerQueue* queue);
bool isFull(CustomerQueue* queue);
void enqueue(CustomerQueue* queue, string name, string type);
void dequeue(CustomerQueue* queue);
void printQueue(CustomerQueue* queue);

//test

void runTests(Stack* stc, CustomerQueue* queue) {

    cout << "\n========== QUEUE TESTS ==========" << endl;

    // Normal enqueues
    cout << "\n-- Filling the queue --" << endl;
    enqueue(queue, "Ali",    "Withdraw");
    enqueue(queue, "Ayse",   "Deposit");
    enqueue(queue, "Mehmet", "Transfer");
    enqueue(queue, "Fatma",  "Balance Inquiry");
    enqueue(queue, "Kemal",  "Withdraw");

    // Overflow test
    cout << "\n-- Overflow test --" << endl;
    enqueue(queue, "Zeynep", "Deposit");    // Should print: queue is Full!

    cout << "\n-- Queue contents --" << endl;
    printQueue(queue);

    // Dequeue a few and re-enqueue (circular wrap test)
    cout << "\n-- Dequeue 2, enqueue 2 --" << endl;
    dequeue(queue);                          // Ali leaves
    dequeue(queue);                          // Ayse leaves
    enqueue(queue, "Zeynep", "Deposit");     // Should succeed
    enqueue(queue, "Burak",  "Transfer");    // Should succeed

    cout << "\n-- Queue contents after wrap --" << endl;
    printQueue(queue);

    // Drain completely
    cout << "\n-- Draining queue --" << endl;
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);

    // Underflow test
    cout << "\n-- Underflow test --" << endl;
    dequeue(queue);    // Should print: queue is currently empty


    cout << "\n========== STACK TESTS ==========" << endl;

    int bills1[3] = {5, 10, 20};
    int bills2[3] = {0,  3, 15};
    int bills3[3] = {8,  0,  2};

    // Normal pushes
    cout << "\n-- Pushing 3 bundles --" << endl;
    Push(stc, "SN-1001", "USD", bills1);
    Push(stc, "SN-1002", "EUR", bills2);
    Push(stc, "SN-1003", "TRY", bills3);

    cout << "\n-- Stack contents (SN-1003 should be on top) --" << endl;
    printStack(stc);

    // Pop one and reprint
    cout << "\n-- Pop once --" << endl;
    Pop(stc);
    cout << "\n-- Stack contents after pop --" << endl;
    printStack(stc);

    // Drain completely
    cout << "\n-- Draining stack --" << endl;
    Pop(stc);
    Pop(stc);

    // Underflow test
    cout << "\n-- Underflow test --" << endl;
    Pop(stc);          // Should print: Stack Underflow!

    cout << "\n-- Stack contents (should be empty) --" << endl;
    printStack(stc);
}


//Functions
int main() {
    Stack* stc = new Stack;
    CustomerQueue* queue = new CustomerQueue;
    createStack(stc);
    createQueue(queue);

    runTests(stc, queue);
    
    destroyStack(stc);
    delete stc; delete queue;
}
//stack
void createStack(Stack* stc) {
    stc->top = NULL;
}

bool isEmpty(Stack* stc) {
    return (stc->top == NULL);
}

void Push(Stack* stc,string serialNumber, string currencyType, int billCounts[3]) {
    MoneyBundle* money_bundle = new MoneyBundle;
    money_bundle->serialNumber = serialNumber;
    money_bundle->currencyType = currencyType;
    for(int i = 0; i < 3; i++){money_bundle->billCounts[i] = billCounts[i];}
    money_bundle->next = stc->top;
    stc->top = money_bundle;
}

void Pop(Stack* stc) {
    if(isEmpty(stc)){
        cout << "Stack Underflow!" << endl;
        return;
    }

    MoneyBundle* temp = stc->top;
    stc->top = stc->top->next;
    delete temp;
}

void printStack(Stack* stc) {
    if (isEmpty(stc)) {
        cout << "Safe is empty." << endl;
        return;
    }
    MoneyBundle* temp = stc->top;
    while (temp != NULL) {
        cout << "Serial: " << temp->serialNumber << " | Type: " << temp->currencyType;
        cout << " | Bills: [";
        for (int i = 0; i < 3; i++) {
            cout << temp->billCounts[i] << (i < 2 ? ", " : "");
        }
        cout << "]" << endl;
        temp = temp->next;
    }
}

void destroyStack(Stack* stc) {
    while (!isEmpty(stc)) {
        Pop(stc);  // Pop already deletes each node
    }
}

//queue

void createQueue(CustomerQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->noItems = 0;
}

bool isEmptyQueue(CustomerQueue* queue) {
    return queue->noItems == 0;
}

bool isFull(CustomerQueue* queue) {
    return queue->noItems == N;
}

void enqueue(CustomerQueue* queue, string name, string type) {
    if (isFull(queue)) {
        cout << "The queue is Full! " << name << " couldn't added." << endl;
        return;
    }

    queue->rear = (queue->rear) % N; 
    
    int insertPos = (queue->front + queue->noItems) % N;

    queue->customers[insertPos].customerName = name;
    queue->customers[insertPos].transactionType = type;
    
    queue->noItems++;
    cout << name << " added successfully." << endl;
}

void dequeue(CustomerQueue* queue) {
    if (queue->noItems == 0) {
        cout << "ERROR: The queue is currently empty, there is no custumer to dequeue." << endl;
        return;
    }

    cout << queue->customers[queue->front].customerName << " transaction is over, dequeuing." << endl;

    queue->front = (queue->front + 1) % N;
    
    queue->noItems--;
}

void printQueue(CustomerQueue* queue) {
    if (queue->noItems == 0) return;
    for (int i = 0; i < queue->noItems; i++) {
        int index = (queue->front + i) % N;
        cout << i + 1 << ". " << queue->customers[index].customerName << endl;
    }
}