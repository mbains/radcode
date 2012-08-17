#include <iostream>
#include <map>
using namespace std;


class BaseClass{ 
public:
    virtual int funk() {
        return 0;
    }
};

class DerivedClassA : public BaseClass
{
private:
    static short ID;
    virtual int funk() {
    
        return 42;
    }

public:
    DerivedClassA(){};
    virtual ~DerivedClassA(){};
};

class DerivedClassB : public BaseClass
{
private:
    static short ID;
    virtual int funk() {
    
        return 63;
    }

public:
    DerivedClassB(){};
    virtual ~DerivedClassB(){};
};

template<typename Type> BaseClass* createType() { 
    cout << "creating type \n";
    return new Type; 
}

class TemplatedFactory
{
public:
    typedef BaseClass* (*ComponentFactoryFuncPtr)();
    typedef map<const char*, ComponentFactoryFuncPtr> map_type;

    map_type m_Map;

public:


    template<typename Type>
    short AddType(const char* componentName){
          ComponentFactoryFuncPtr function = &createType<Type>;
        m_Map.insert(std::make_pair(componentName, function));

    return 0;
    };
};




int main(int argc, char ** argv)
{

    TemplatedFactory * factory_p = new TemplatedFactory();
    factory_p->AddType<DerivedClassA>("DerivedClassA");
    factory_p->AddType<DerivedClassB>("DerivedClassB");
    
    cout << "Done registering\n";
    
    TemplatedFactory::map_type::iterator iterA = factory_p->m_Map.find("DerivedClassA");
    TemplatedFactory::map_type::iterator iterB = factory_p->m_Map.find("DerivedClassB");
    cout << "DerivedClassA: " << iterA->second()->funk() << "\n";
    cout << "DerivedClassB: " << iterB->second()->funk() << "\n";
    return 0;
}

