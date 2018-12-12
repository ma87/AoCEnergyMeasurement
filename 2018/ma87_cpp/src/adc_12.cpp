#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

typedef pair<string, string> pattern_t;

bool is_a_pattern_matched(string & pots, vector<pattern_t> & patterns, pattern_t * matched_pattern)
{
  for(vector<pattern_t>::iterator p = patterns.begin() ; p != patterns.end() ; ++p)
  {
    if (!pots.compare(p->first))
    {
      *matched_pattern = *p;
      return true;
    }
  }
  return false;
}

int compute_sum(string & pots, int number_negative_pots)
{
  int sum = 0;
  for (int i = 0 ; i < pots.size() ; i++)
  {
    if (pots[i]=='#')
    {
      sum += i - number_negative_pots;
    }
  }
  return sum;
}

int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);

     
    string input;
    bool state_found = false;
    bool new_pattern = false;
    string pots;
    string processed_pots;
    vector<pattern_t> patterns;
    while (f >> input)
    {
      if (new_pattern)
      {
        string pattern = input;
        f >> input; // got =>
        f >> input;

        patterns.push_back(make_pair(pattern,input));
      }

      if (state_found)
      {
        state_found = false;
        new_pattern = true;
        pots = input;
      }
      
      if (input == "state:")
      {
        state_found = true;
      }
    }
    
    int number_pots = pots.size();

    pattern_t matched_pattern;
    string sub_pots;
    int number_negative_pots = 0;
    int solution1;
    int solution2;
    int solution2_d;
    int diff_prev;
    int counter_stab = 0;
    int g = 0;
    while (counter_stab < 10)
    {
      g++;
      size_t first_plant = pots.find("#");
      if (first_plant < 5)
      {
        pots = string(5, '.') + pots;
        number_negative_pots += 5;
      }
      
      size_t last_plant = pots.find_last_of("#");
      if (last_plant > (pots.size() - 5))
      {
        pots = pots + string(5, '.');
      }
      
      processed_pots = pots;
      for (int i = 2; i < pots.size() - 2 ; i++)
      {
        sub_pots = pots.substr(i - 2, 5);
        if (is_a_pattern_matched(sub_pots, patterns, &matched_pattern))
        {
          processed_pots[i] = matched_pattern.second[0];
        }
        else
        {
          processed_pots[i] = '.';
        }
      }

      pots = processed_pots;
      
      if (g==20)
      {
        solution1 = compute_sum(pots, number_negative_pots);
      }
      
      solution2 = compute_sum(pots, number_negative_pots);
      int diff = solution2 - solution2_d;
      if (diff == diff_prev)
      {
        counter_stab++;
      }
      else
      {
        counter_stab = 0;
        diff_prev = diff;
      }

      solution2_d = solution2;
    }

    cout << "solution 1 = " << solution1 << endl;
    cout << "solution 2 = " << solution2 + diff_prev * (50000000000 - g) << endl;

    return 0;
  }
  return 1;
} 
