#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
template <class T>
class Elem
{
  public:
    typedef T* pointer_type;
    typedef T  value_type;

    Elem(value_type v)
    {
	    value = v;
	    prev = next = NULL;
    }

    pointer_type get()
    {
	    return &value;
    }
    Elem<T> * prev;
    Elem<T> * next;
    value_type   value;
};
template <class T>
class DoubleChainedList
{
  public:
    typedef Elem<T> * pointer_elem_t;
    DoubleChainedList(pointer_elem_t e)
    {
	current = e;
	e->prev = e;
	e->next = e;
    }

    void move(int n)
    {
	if (n > 0)
	{
		for (int i = 0 ; i < n ; i++)
			current = current->next;
	}
	else 
	{
		for (int i = n ; i < 0 ; i++)
			current = current->prev;
	}
    }

    pointer_elem_t remove()
    {
	pointer_elem_t p_current = current;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	current = current->next;
	return p_current;
    }

    void append(pointer_elem_t e)
    {
	    e->prev = current;
	    e->next = current->next;
	    e->next->prev = e;
	    current->next = e;
	    current = e;
    }
    pointer_elem_t current;
};
int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);

    Elem<uint64_t> m(0);
    DoubleChainedList<uint64_t> marbles(&m);
    int counter = 23;
    int number_players;
    f >> number_players;
    cout << "number players = " << number_players << endl;
    string unused;
    for (int i = 0 ; i < 5 ; i++)
	    f >> unused;
    int max_marble_number;
    f >> max_marble_number;
    cout << "max = " <<  max_marble_number << endl;
    uint64_t max_marble_number_2 = max_marble_number * 100;
    int current_player = 1;
    vector<uint64_t> scores(number_players, 0);
    uint64_t max_score_1 = 0;
    for (int m = 1 ; m <= max_marble_number_2 ; m++)
    {
	    counter--;
	    if (counter > 0)
	    {
		    marbles.move(1);
		    marbles.append(new Elem<uint64_t>(m));
	    }
	    else
	    {
		    scores[current_player - 1] += m;
		    marbles.move(-7);
		    Elem<uint64_t> * removed_elem = marbles.remove();
		    scores[current_player - 1] += removed_elem->value;
		    counter = 23;
	    }
	    current_player += 1;
	    if (current_player > number_players)
	    {
		    current_player = 1;
	    }
	    if (m==max_marble_number)
	    {
		    for(int i = 0 ; i < number_players ; i++)
		    {
			    if (scores[i] > max_score_1)
				    max_score_1 = scores[i];
		    }
	    }
    }
    
    uint64_t max_score = 0;
    for(int i = 0 ; i < number_players ; i++)
    {
	    if (scores[i] > max_score)
		    max_score = scores[i];
    }
    cout << "solution 1 = " << max_score_1 << endl;
    cout << "solution 2 = " << max_score << endl;
  }
}
