#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define CMD_FIRST_CHILD "first_child"
#define CMD_NEXT_SIBLING "next_sibling"
#define CMD_PREVIOS_SIBLING "previous_sibling"
#define CMD_PARENT "parent"

struct Node {
    string value_;
    Node* parent_;
    vector<Node*> childs_;
};

class Parser 
{
public:
    Parser(const vector<string>& lines);
    virtual ~Parser() { for (int i = 0; i < nodes_.size(); ++i) { delete nodes_[i]; } };
    const Node* root() const { return nodes_[0]; };
    const Node* find_node(const Node* current_node, string cmd);

private:
    vector<Node*> nodes_; 
};

string extract_value(string s)
{
    size_t first = s.find_first_of("'") + 1;
    size_t last = s.find_last_of("'") - 1;

    return s.substr(first, last - first + 1);
}

Parser::Parser(const vector<string>& lines)
{
    Node* current_node = NULL;
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i] == "</n>")
        {
            current_node = current_node->parent_;
        }
        else 
        {
            Node* new_node = new Node();
            new_node->value_ = extract_value(lines[i]);
            
            if (current_node != NULL)
            {
                new_node->parent_ = current_node;
                current_node->childs_.push_back(new_node);
            }

            current_node = new_node;
            nodes_.push_back(new_node);
        }
    }
}

const Node* Parser::find_node(const Node* current_node, string cmd)
{
    if (cmd == CMD_FIRST_CHILD)
    {
        if (current_node->childs_.size() > 0)
        {
            return current_node->childs_[0];
        }
    }
    else if (cmd == CMD_PARENT)
    {
        if (current_node->parent_)
        {
            return current_node->parent_;
        }
    }
    else if (cmd == CMD_NEXT_SIBLING || cmd == CMD_PREVIOS_SIBLING)
    {
        const Node* parent = current_node->parent_;
        int count = parent? parent->childs_.size() : 0;
        for (int i = 0; i < count; ++i)
        {
            if (parent->childs_[i] == current_node)
            {
                if (cmd == CMD_NEXT_SIBLING && i + 1 < count)
                {
                    return parent->childs_[i + 1];
                }
                else if (cmd == CMD_PREVIOS_SIBLING && i - 1 >= 0)
                {
                    return parent->childs_[i - 1];
                }
            }
        }
    }
    return current_node;
}


int main()
{
    int n;
    int c = 1;
    while (cin >> n)
    {
        cin.ignore();
        if (n == 0) 
        {
            break;
        }
       
        vector<string> lines; 
        while (n--)
        {
            string s;
            getline(cin, s);
            lines.push_back(s);
        }
        
        Parser parser(lines);

        int command_count = 0;
        cin >> command_count;
        cin.ignore();
        const Node* current_node = parser.root(); 
        cout << "Case " << c++ << ":" << endl;
        while (command_count --)
        {
            string s;
            getline(cin, s);
            current_node = parser.find_node(current_node, s);
            cout << current_node->value_ << endl;
        }
    }
    return 0;
}
