#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class DataStructureGuessor {
public:
    DataStructureGuessor();
    virtual ~DataStructureGuessor() {};
    void throw_in(int element);
    void check_take_out(int element);

    string what();

private:
    stack<int> stack_;
    queue<int> queue_;
    priority_queue<int> pqueue_;

    bool is_queue_;
    bool is_priority_queue_;
    bool is_stack_;
};

DataStructureGuessor::DataStructureGuessor() :
    is_queue_(true),
    is_priority_queue_(true),
    is_stack_(true)
{
}

void DataStructureGuessor::throw_in(int element)
{
    stack_.push(element);
    queue_.push(element);
    pqueue_.push(element);
}

void DataStructureGuessor::check_take_out(int element)
{
    if (stack_.empty() || queue_.empty() || pqueue_.empty()) 
    {
        is_stack_ = false;
        is_queue_ = false;
        is_priority_queue_ = false;
        return ;
    }

    int v = 0;
    v = stack_.top();
    is_stack_ = is_stack_ && (v == element);

    v = queue_.front();
    is_queue_ = is_queue_ && (v == element);

    v = pqueue_.top();
    is_priority_queue_ = is_priority_queue_ && (v == element);

    stack_.pop();
    queue_.pop();
    pqueue_.pop();
}

string DataStructureGuessor::what()
{
    if (!is_queue_ && !is_priority_queue_ && !is_stack_)
    {
        return "impossible";
    }

    if (is_queue_ && !is_priority_queue_ && !is_stack_)
    {
        return "queue";
    }
    
    if (is_priority_queue_ && !is_queue_ && !is_stack_)
    {
        return "priority queue";
    }

    if (is_stack_ && !is_queue_ && !is_priority_queue_)
    {
        return "stack";
    }

    return "not sure";
}

int main()
{
    int n = 0;
    while (cin >> n)
    {
        DataStructureGuessor guessor;
        while (n--)
        {
            int op = 0, element = 0;
            cin >> op >> element;
            if (op == 1)
            {
                guessor.throw_in(element);
            }
            else if(op == 2)
            {
                guessor.check_take_out(element);
            }
        }

        cout << guessor.what() << endl;
    }
    return 0;
}

