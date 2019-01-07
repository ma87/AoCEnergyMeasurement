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
class Recipes
{
  public:
    typedef Elem<T> * pointer_elem_t;
    Recipes(pointer_elem_t elf1, pointer_elem_t elf2, vector<T> & pattern)
    {
	this->elf1 = elf1;
	this->elf2 = elf2;
	this->elf1->prev = elf2;
	this->elf1->next = elf2;

	this->elf2->prev = elf1;
	this->elf2->next = elf1;

	this->head = elf1;
	this->tail = elf2;
	size = 2;
	solution2 = 0;
	index_pattern = 0;
	this->pattern = pattern;
    }

    void print()
    {
	    pointer_elem_t current = head;
	    do 
	    {
		    cout << current->value << " "; 
		    current = current->next;
	    } while (current != head);
	    cout << endl;
    }

    void move()
    {
	    int n_elf1 = 1 + elf1->value;
	    int n_elf2 = 1 + elf2->value;

	    for (int i = 0 ; i < n_elf1 ; i++)
		    elf1 = elf1->next;
	    for (int i = 0 ; i < n_elf2 ; i++)
		    elf2 = elf2->next;

    }
    void append(T v)
    {
	    append(new Elem<T>(v));
    }
    void append(pointer_elem_t e)
    {
	    e->prev = tail;
	    e->next = head;
	    head->prev = e;
	    tail->next = e;
	    tail = e;
	    size++;
	    if (tail->value == pattern[index_pattern])
	    {
		    index_pattern++;
		    if (index_pattern == pattern.size())
			    solution2 = size - pattern.size();

	    }
	    else
	    {
		    index_pattern = 0;
	    }
    }

    uint64_t getRecept(int start_index)
    {
	    uint64_t recept = 0;
	    int counter = size - 1;
	    pointer_elem_t p = tail;
	    while(counter != start_index)
	    {
		    p = p->prev;
		    counter--;
	    }
	    cout << "solution 1 = ";
	    for(int i=0 ; i < 10 ; i++)
	    {
		    cout << p->value;
		    recept += 10 * recept + p->value;
		    p = p->next;
	    }
	    cout << endl;
	return recept;
    }
    pointer_elem_t elf1;
    pointer_elem_t elf2;
    pointer_elem_t head;
    pointer_elem_t tail;
    int size;
    uint64_t solution2;
    int index_pattern;
    vector<T> pattern;
};
int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    Elem<uint16_t> r1(3);
    Elem<uint16_t> r2(7);
    vector<uint16_t> pattern({7,6,5,0,7,1});
    Recipes<uint16_t> r(&r1, &r2, pattern);
    int next_recipes = 765071;
    int max_size = next_recipes + 11;
    bool sol1printed = false;
    while(!r.solution2)
    {
	    uint16_t sum = r.elf1->value + r.elf2->value;
	    if (sum > 9)
	    {
		    r.append(1);
		    r.append(sum - 10);
	    }
	    else
	    {
		    r.append(sum);
	    }
	    r.move();
	    if (!sol1printed && r.size >= max_size)
	    {
		    r.getRecept(next_recipes);
		    sol1printed = true;
	    }
    }
    cout << "solution 2 = " << r.solution2 << endl;
  }
}
