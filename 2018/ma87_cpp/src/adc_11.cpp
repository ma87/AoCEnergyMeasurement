#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

typedef struct 
{
  int col;
  int row;
} coords_t;

template <class T>
class Matrix
{
  public:
    typedef T* pointer_type;
    typedef T  value_type;

    Matrix(int nrows, int ncols)
      : m_nrows(nrows), m_ncols(ncols)
    {
      m_values = new T[nrows * ncols]();
    };

    void init(int grid_serial_number)
    {
      for (int col=1 ; col <= m_ncols ; col++)
      {
        pointer_type p_value = get(1, col);
        int rack_id = col + 10;
        for (int row=1 ; row <= m_nrows ; row++)
        {
          *p_value = rack_id * row + grid_serial_number;
          *p_value *= rack_id;
          *p_value = get_hundred_digits(*p_value) - 5;
          p_value++;
        }
      }
    }

    coords_t compute_power_level(int * default_size)
    {
      value_type max_power_level = -10000;
      coords_t max_coords = {.col = -1, .row = -1};
      int start_size, stop_size;
      if (*default_size > 0)
      {
        start_size = stop_size = *default_size;
      }
      else
      {
        start_size = 1;
        stop_size = 300;
      }
      for (int s = start_size ; s <= stop_size ; s++)
      {
        for (int col=1 ; col <= m_ncols - (s - 1); col++)
        {
          for (int row=1 ; row <= m_nrows - (s - 1); row++)
          {
            coords_t coords = {.col = col , .row = row};
            value_type power_level = get_power_level(row, col, s);
            if (power_level > max_power_level)
            {
              max_power_level = power_level;
              *default_size = s;
              max_coords = coords;
            }
          }
        }
      }
      return max_coords;
    }

    pointer_type get(int row, int col)
    {
      // Row and col are in range (1,300)
      return &m_values[((row - 1) + (col - 1) * m_nrows)];
    }

    void print()
    {
      for (int row=1 ; row <= m_nrows ; row++)
      {
        for (int col=1 ; col <= m_ncols ; col++)
        {
          pointer_type p_value = get(row, col);
          cout << *p_value << " ";
        }
        cout << endl;
      } 
    }

    void print(int row, int col)
    {
      pointer_type v = get(row, col);
      cout << *v << endl;
    }

    ~Matrix()
    {
      delete m_values;
    };

  private:
    value_type get_hundred_digits(value_type v)
    {
      if (v < 100)
      {
        return 0;
      }
      else
      {
        // From 123456, get 1234
        value_type t = v / 100;
        // From 123456, get 1230
        value_type t1 = (v / 1000) * 10;
        return t - t1;
      }
    }

    value_type get_power_level(int row, int col, int size)
    {
      value_type sum = 0;
      for(int c = 0 ; c < size ; c++)
      {
        pointer_type p_value = get(row, col + c);
        for (int r = 0 ; r < size ; r++)
        {
          sum += *p_value++;
        }
      }
      return sum;
    }

  private:
    pointer_type m_values;
    int m_nrows;
    int m_ncols;
};


int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);
  
    int grid_serial_number;
    f >> grid_serial_number;

    if (grid_serial_number <= 0)
    {
      cout << "error when parsing entry text" << endl;
      return -1;
    }

    Matrix<int> m(300,300);
    m.init(grid_serial_number);
    int size = 3;
    coords_t max_level = m.compute_power_level(&size);
    cout << "for grid serial number " << grid_serial_number << ", max_level for size 3 is at coords " << max_level.col << "," << max_level.row << endl;

    size = 0;
    max_level = m.compute_power_level(&size);
    cout << "for grid serial number " << grid_serial_number << ", max_level for any size is at coords " << max_level.col << "," << max_level.row << "," << size << endl;
  }

  return 0;
}
