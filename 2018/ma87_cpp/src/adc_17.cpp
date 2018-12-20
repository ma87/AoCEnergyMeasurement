#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
using namespace std;



char VOID='.';
char CLAY='#';
char SOURCE='+';
char WATER='~';
char WATERFALL='|';


typedef struct
{
  int col;
  int row;
} coords_t;

typedef struct
{
  int fix_value_dim;
  int fix_value;
  int range_value_start;
  int range_value_stop;
} matrix_definitions_t;

template <class T>
class Reservoir
{
  public:
    typedef T* pointer_type;
    typedef T value_type;

    Reservoir(const vector<matrix_definitions_t> & defs)
    {
      initDimensions(defs);
    }

    void print()
    {
      for (int r = 0 ; r < nrows ; r++)
      {
        for (int c = 0 ; c < ncols ; c++)
        {
          cout << m_values[r + c * nrows];
        }
        cout << endl;
      }
    }

    bool process_waterfall(coords_t & waterfall_top, int * ystop)
    {
      int current_y = waterfall_top.row + 1;
      pointer_type p_value = get(current_y, waterfall_top.col);
      while ((*p_value == VOID) && (current_y < nrows))
      {
        *p_value = WATERFALL;
        p_value++;
        current_y++;
        if (*p_value == WATERFALL)
        {
          return false;
        }
      }

      *ystop = current_y - 1;
      return current_y < nrows;
    }

    bool is_waterfall(coords_t source, vector<coords_t> & waterfalls, coords_t * left_block, coords_t * right_block)
    {
      bool no_waterfall = true;

      int x = source.col;
      int y = source.row;
      pointer_type p_value = get(source.row,source.col);
      while (*p_value != CLAY)
      {
        p_value -= nrows;
        x--;
        if (*(p_value+1) == VOID)
        {
          waterfalls.push_back((coords_t){.col = x, .row = y});
          no_waterfall = false;
          x--;
          break;
        }
      }
      left_block->row = y;
      left_block->col = x+1;

      p_value = get(source.row,source.col);
      x = source.col;
      while (*p_value != CLAY)
      {
        p_value += nrows;
        x++;
        if (*(p_value+1) == VOID)
        {
          waterfalls.push_back((coords_t){.col = x, .row = y});
          no_waterfall = false;
          x++;
          break;
        }
      }

      right_block->row = y;
      right_block->col = x-1;

      return !no_waterfall;
    }

    void fill_sub_reservoir(int xstart, int ystop, vector<coords_t> & waterfalls)
    {
      char fill_water;
      bool waterfall_pop_up = false;

      coords_t source;
      source.row = ystop;
      source.col = xstart;

      while (!waterfall_pop_up)
      {
        coords_t left_block;
        coords_t right_block;

        waterfall_pop_up = is_waterfall(source, waterfalls, &left_block, &right_block);
        fill_water = (waterfall_pop_up) ? WATERFALL : WATER;

        pointer_type p_value = get(left_block.row, left_block.col);
        for (int x = left_block.col ; x <= right_block.col ; x++)
        {
          *p_value = fill_water;
          p_value += nrows;
        }

        source.row--;
      }
    }

    void fill()
    {
      int ystop;
      vector<coords_t> waterfalls;
      waterfalls.push_back((coords_t){.col = index_source , .row = 1});
      pointer_type start_waterfall = get(1, index_source);
      *start_waterfall = WATERFALL;
      int counter = 0;
      int counter_2 = 0;
      while (waterfalls.size())
      {
        coords_t top_waterfall = waterfalls.back();

        int xstart = top_waterfall.col;
        bool has_finished = process_waterfall(top_waterfall, &ystop);

        waterfalls.pop_back();

        if (has_finished)
        {
          fill_sub_reservoir(xstart, ystop, waterfalls);

        }
      }

    }

    int get_number_water_tiles()
    {
      int number_water_tiles = 0;
      pointer_type p_value = get(0,0);
      for (int col = 0 ; col < ncols ; col++)
      {
        for (int row = 0 ; row < nrows ; row++)
        {
          if ((*p_value == WATER) || (*p_value == WATERFALL))
          {
            number_water_tiles += 1;
          }
          p_value++;
        }
      }

      return number_water_tiles;
    }

    pointer_type get(int row, int col)
    {
      return &m_values[row + col * nrows];
    }

  private:
    void initDimensions(const vector<matrix_definitions_t> & defs)
    {
      int max_row = -1;
      int min_col = 1000;
      int max_col = -1;

      // Retrieve dimensions
      for (auto def : defs)
      {
        if (def.fix_value_dim == 1)
        {
          if (def.range_value_stop > max_row)
          {
            max_row = def.range_value_stop;
          }
          if (def.fix_value < min_col)
          {
            min_col = def.fix_value;
          }
          if (def.fix_value > max_col)
          {
            max_col = def.fix_value;
          }
        }
        else
        {
          if (def.fix_value > max_row)
          {
            max_row = def.fix_value;
          }
          if (def.range_value_start < min_col)
          {
            min_col = def.range_value_start;
          }
          if (def.range_value_stop > max_col)
          {
            max_col = def.range_value_stop;
          }
        }
      }

      ncols = (max_col + 1) - (min_col - 1) + 1;
      nrows = max_row + 1;

      m_values = new value_type[nrows * ncols];
      memset(m_values, VOID, nrows * ncols * sizeof(value_type));

      xoffset = min_col - 1;
      index_source = 500 - xoffset;
      m_values[index_source * nrows] = SOURCE;

      // Init values
      for (auto def : defs)
      {
        int shift_pointer;
        int x,y,range;
        if (def.fix_value_dim == 1)
        {
          shift_pointer = 1;
          x = def.fix_value;
          y = def.range_value_start;
        }
        else
        {
          shift_pointer = nrows;
          y = def.fix_value;
          x = def.range_value_start;
        }
        range = def.range_value_stop - def.range_value_start + 1;

        pointer_type p_value = get(y, x - xoffset);
        for (int i = 0 ; i < range ; i++)
        {
          *p_value = CLAY;
          p_value = p_value+shift_pointer;
        }
      }
    }


    value_type * m_values;
    int index_source;
    int nrows;
    int ncols;
    int xoffset;
};

int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);

    const regex r("(.*)=(.*), (.*)=([0-9]*)..([0-9]*)");
    smatch sm;

    string line;
    vector<matrix_definitions_t> defs;
    int fix_value, fix_value_dim, range_value_start, range_value_stop;
    while(getline(f, line))
    {
      if (regex_search(line, sm, r))
      {
        //cout << sm[1] << " = " << sm[2] << " and " << sm[3] << " = " << sm[4] << " -> " << sm[5] << endl;
        fix_value_dim = (sm[1]=='x') ? 1 : 0;
        fix_value     = stoi(sm[2]);
        range_value_start = stoi(sm[4]);
        range_value_stop  = stoi(sm[5]);
        defs.push_back((matrix_definitions_t){ .fix_value_dim = fix_value_dim, .fix_value = fix_value,
                                               .range_value_start = range_value_start, .range_value_stop = range_value_stop });
      }
    }

    Reservoir<char> reservoir(defs);
    reservoir.fill();
    reservoir.print();
    cout << "solution 1 = " << reservoir.get_number_water_tiles() << endl;
  }
  else
  {
    return -1;
  }
  return 0;
}
