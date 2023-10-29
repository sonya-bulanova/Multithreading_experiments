#include "FineGrainedQueue.h"

FineGrainedQueue::~FineGrainedQueue()
{
    delete queue_mutex;
    Node* current = head;
    while (current->next)
    {
        Node* old_current = current;
        current = old_current->next;
        delete old_current;
    }
    delete current;
}

void FineGrainedQueue::push_front(int data)
{
    Node* node = new Node(data);
    if (head == nullptr)
    {
        head = node;
        return;
    }
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = node;
}

void FineGrainedQueue::push_back(int data)
{
    Node* node = new Node(data);
    if (head == nullptr)
    {
        head = node;
        return;
    }
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = node;
    return;
}

void FineGrainedQueue::insertIntoMiddle(int pos, int data)
{
    queue_mutex->lock();

    Node* newNode = new Node(data); 
    Node* current = head;          
    current->node_mutex->lock();

    current->next->node_mutex->lock();
    queue_mutex->unlock();

    int currPos = 0;
    while (currPos < pos - 1 && current->next != nullptr)
    {
        Node* old_current = current; 
        current = current->next;     
        if (current->next)
        {
            current->next->node_mutex->lock();
        }

        old_current->node_mutex->unlock();
        currPos++;
    }
    Node* next = current->next;
    current->next = newNode;
    newNode->next = next;
    newNode->node_mutex->unlock();
    current->node_mutex->unlock();
    if (next)
    {
        next->node_mutex->unlock();
    }
}

void FineGrainedQueue::remove(int value)
{
    Node* prev, * cur;
    queue_mutex->lock();
    prev = this->head;
    cur = this->head->next;
    prev->node_mutex->lock();
    queue_mutex->unlock();

    if (cur) 
        cur->node_mutex->lock();
    while (cur)
    {
        if (cur->value == value)
        {
            prev->next = cur->next;
            prev->node_mutex->unlock();
            cur->node_mutex->unlock();
            delete cur;
            return;
        }
        Node* old_prev = prev;
        prev = cur;
        cur = cur->next;
        old_prev->node_mutex->unlock();
        if (cur) 
            cur->node_mutex->lock();
    }
    prev->node_mutex->unlock();
}

void FineGrainedQueue::show()
{
    Node* current = head;
    while (current->next)
    {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << current->value << std::endl;
}
