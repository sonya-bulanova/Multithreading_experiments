// Type your code here, or load an example.
#include <bits/stdc++.h>

template <typename T>
concept ComplexConcept = !std::has_virtual_destructor<T>::value && requires(T obj){
    {obj.hash()}
    -> std::convertible_to<long>;

    {obj.toString()}
    -> std::same_as<std::string>;
}; 

void TestConcept(ComplexConcept auto &t){
    std::cout << t.toString();
}

class test1{
    public:
    test1();
    int hash() {return 2;};
    std::string toString() {return "hello world";};
    virtual ~test1(){};
};

class test2{
    public:
    test2();
    int hash() {return 2;};
    std::string toString() {return "hello world";};
    ~test2(){};
};

int main(){
    test1 t1;
    //TestConcept(t1); //не работает
    test2 t2;
    TestConcept(t2); //завелось!!!
    return 0;
}