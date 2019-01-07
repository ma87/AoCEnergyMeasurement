#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct coords_t
{
	int x;
	int y;
	bool operator<(const coords_t& c) const
	{
		if (y == c.y)
			return x < c.x;
		return y < c.y;
	}
	bool operator>(const coords_t& c) const
	{
		int sum = abs(x) + abs(y);
		int sum_c = abs(c.x) + abs(c.y);
		return sum > sum_c;
	}
} coords_t;
template <class T>
class Elem
{
  public:
    typedef T* pointer_type;
    typedef T  value_type;

    Elem(int x, int y, value_type v)
    {
	    coords = { .x=x , .y=y};
	    value = v;
    }

    coords_t coords;
    value_type   value;
};
class Map
{
  public:

    typedef map<coords_t, int> map_t;
    Map()
    {
            elems.insert(make_pair(coords_t{.x=0, .y=0}, 0));
    }

    void visit(int x, int y, int steps)
    {
	    coords_t visited_coords = {.x=x, .y=y};
	    typename map_t::iterator it = elems.find(visited_coords);
	    if (it != elems.end())
	    {
		    if (it->second > steps)
			    it->second = steps;
	    }
	    else
	    {
		    elems.insert(make_pair(visited_coords, steps));
	    }
    }

    int getSolution1()
    {
	    typename map_t::iterator it;
	    int max_distance = 0;
	    for (it = elems.begin() ; it != elems.end() ; it++)
	    {
		    if (it->second > max_distance)
		    {
			    max_distance = it->second;
		    }
	    }
	    return max_distance;
    }
    int getSolution2()
    {
	    int c = 0;
	    typename map_t::iterator it;
	    int max_distance = 1000;
	    for (it = elems.begin() ; it != elems.end() ; it++)
	    {
		    if (it->second >= max_distance)
		    {
			    c++;
		    }
	    }
	    return c;
    }

    map_t elems;
};
void process_regexp(int * index, string & regexp, Map &m, int x, int y, int steps)
{
	while (*index < regexp.size())
	{
		char cur = regexp[*index];
		*index += 1;
		switch (cur)
		{
			case '|':
				return;
				break;
			case '(':
	  			process_regexp(index, regexp, m, x, y, steps);
	  			process_regexp(index, regexp, m, x, y, steps);
				break;
			case ')':
				return;
				break;
			case 'N':
				steps++;
				y -= 1;
				m.visit(x, y, steps);
				break;
			case 'S':
				steps++;
				y += 1;
				m.visit(x, y, steps);
				break;
			case 'W':
				steps++;
				x -= 1;
				m.visit(x, y, steps);
				break;
			case 'E':
				steps++;
				x += 1;
				m.visit(x, y, steps);
				break;
		}
	}
}
int main(int argc, char * argv[])
{
  if (argc > 1)
  {
	  ifstream f;
          f.open(argv[1]);

	  string regexp;
          f >> regexp;
	  Map m;
	  int x = 0;
	  int y = 0;
	  int i = 1;
	  int steps = 0;
	  process_regexp(&i, regexp, m, x, y, steps);
	  cout << "solution 1 = " << m.getSolution1() << endl;
	  cout << "solution 2 = " << m.getSolution2() << endl;
  }
}
