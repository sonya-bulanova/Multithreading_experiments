#include "FineGrainedQueue.h"

int main()
{
    FineGrainedQueue q;
    q.push_front(0);
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);
    q.push_back(6);
    q.push_back(7);
    q.push_back(8);
    q.push_back(9);
    std::cout << "before:\t";
    q.show();

    std::thread t1([&q]()
        { q.insertIntoMiddle(1, 111); });
    std::thread t2([&q]()
        { q.insertIntoMiddle(1, 222); });


    std::thread t3del([&q]()
        { q.remove(3); });
    std::thread t3([&q]()
        { q.insertIntoMiddle(5, 333); });
    std::thread t4del([&q]()
        { q.remove(4); });
    std::thread t4([&q]()
        { q.insertIntoMiddle(5, 444); });

    std::thread t5([&q]()
        { q.insertIntoMiddle(222, 555); });
    std::thread t6([&q]()
        { q.insertIntoMiddle(222, 666); });
    t1.join();
    t2.join();
    t3.join();
    t3del.join();
    t4del.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "after:\t";
    q.show();
    return 0;
}