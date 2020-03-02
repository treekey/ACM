#include <iostream>


class Base
{
public:
    Base(int type, int id);
    virtual ~Base() {};

    int type() const {return type_;}

private:
    int type_;
    int id_;
};

Base::Base(int type, int id)
    : type_(type)
    , id_(id)

{
}    

class Icon : public Base
{
public: 
    Icon(int type, int id, int x, int y);
    
private:
    int x_;
    int y_;
};

Icon::Icon(int type, int id, int x, int y) 
    : Base(type, id)
    , x_(x)
    , y_(y)
{

}




int main()
{
    


    return 0;
}
