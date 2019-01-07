#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
void process_header(ifstream * f, int * number_child, int * number_metadata)
{
	*f >> *number_child;
	*f >> *number_metadata;
}
void process_metadata(ifstream * f, uint64_t * sum)
{
	int a;
	*f >> a;
	*sum += a;
}

uint64_t process_node(ifstream * f, uint64_t * sum)
{

  vector<uint64_t> child_values;
  int number_child,number_metadata;
  process_header(f, &number_child, &number_metadata);
  for(int i = 0 ; i < number_child ; i++)
  {
	  child_values.push_back(process_node(f, sum));
  }
  uint64_t child_sum = 0;
  uint64_t child_refs_sum = 0; 
  for(int i = 0 ; i < number_metadata ; i++)
  {
	  int a;
	  *f >> a;
	  child_sum += a;
	  if (number_child > 0)
	  {
		  if (a <= child_values.size())
		  	child_refs_sum += child_values[a-1];
	  }
  }
  *sum += child_sum;
  if (number_child == 0)
  {
	  return child_sum;
  }
  else
  {
	  return child_refs_sum;
  }
}
int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);
    int a;
    uint64_t sum = 0;
    vector<uint64_t> child_values;
    uint64_t sol = process_node(&f, &sum);
    cout << "solution 1 = " << sum << endl;
    cout << "solution 2 = " << sol << endl;
  }
}
