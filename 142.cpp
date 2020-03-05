#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


struct Point
{
    int x_;
    int y_;

    Point(int x, int y):x_(x), y_(y) {}

    int square_distance(const Point& p) const 
    { 
        return (x_ - p.x_) * (x_ - p.x_) +
               (y_ - p.y_) * (y_ - p.y_); 
    }
};

class Icon 
{
public: 
    Icon(int id, Point p)
        : id_(id)
          , p_(p)
          , visible_(true)
    {
    }

    void set_visible(bool visible) { visible_ = visible; }

    int   id()       const { return id_;}
    Point position() const { return p_; }
    bool  visible()  const { return visible_; }

private:
    int id_;
    Point p_;
    bool visible_;
};


class Region
{
public: 
    Region(int id, Point left_top, Point right_bottom)
        : id_(id + 'A')
        , left_top_(left_top)
        , right_bottom_(right_bottom)
    {
    }

    bool contain(Point p) const
    {
        return (p.x_ >= left_top_.x_ && p.x_ <= right_bottom_.x_
                && p.y_ >= left_top_.y_ && p.y_ <= right_bottom_.y_);
    }

    string id () const { return string(1, id_); }
private:
    char id_;
    Point left_top_;
    Point right_bottom_;
};


class Window 
{
public:
    void add_icon(const Point& p);
    void add_region(const Point& left_top, const Point& right_bottom);
    string click (const Point& p);

private:
    vector<Icon> find_closet_icons(const Point& p);

private:
    vector<Icon> icons_;
    vector<Region> regions_;

};

void Window::add_icon(const Point& p)
{
    static int next_icon_id = 1;
    Icon icon(next_icon_id++, p);
    icons_.push_back(icon);
}

void Window::add_region(const Point& left_top, const Point& right_bottom)
{
    static int next_region_id = 0;
    Region region(next_region_id++, left_top, right_bottom);
    regions_.push_back(region);

    for (int i = 0; i < icons_.size(); ++i)
    {
        if (region.contain(icons_[i].position()))
        {
            cout << "icons " << icons_[i].id() << " hide" << endl;
            icons_[i].set_visible(false);
        }
    }
}


vector<Icon> Window::find_closet_icons(const Point& p)
{
    vector<Icon> closest_icons;
    if (icons_.size() > 0) 
    {
        int min = Point(0, 0).square_distance(Point(499, 499));
        for (int i = 0; i < icons_.size(); ++i)
        {
            if (icons_[i].visible())
            {
                int distance = p.square_distance(icons_[i].position());
                if (distance < min)
                {
                    min = distance;
                    closest_icons.clear();
                    closest_icons.push_back(icons_[i]);
                }
                else if (distance == min)
                {
                    closest_icons.push_back(icons_[i]);
                }
            }
        }
    }
    return closest_icons;
}

string Window::click(const Point& p)
{
    if (p.x_ < 0 || p.y_ < 0 || p.x_ > 499 || p.y_ > 499)
    {
        //assert(0);
        return "invalid operation";
    }


    for (int i = regions_.size() - 1; i >= 0; --i)
    {
        if (regions_[i].contain(p))
        {
            return regions_[i].id();
        }
    }


    vector<Icon> icons = find_closet_icons(p);
    ostringstream stream;
    for (int i = 0; i < icons.size(); ++i)
    {
        stream << setw(3) << setfill(' ') << icons[i].id();
    }
    return stream.str();
}

int main()
{
    char op;
    Window w;
    while (cin >> op)
    {
        switch (op)
        {
            case 'I':
            {
                int x, y;
                cin >> x >> y;
                w.add_icon(Point(x, y));
                break;
            }
            case 'R':
            {
                int x1, y1;
                int x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                w.add_region(Point(x1, y1), Point(x2, y2));
                break;
            }
            case 'M':
            {
                int x, y;
                cin >> x >> y;
                string result = w.click(Point(x, y));
                cout << result << endl;
                break;
            }
            case '#':
                return 0;
        }
    }

    return 0;
}
