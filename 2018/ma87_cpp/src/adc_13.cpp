#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef enum {UP, DOWN, LEFT, RIGHT} DIRECTION;
typedef enum {TURN_LEFT = 0, STRAIGHT = 1, TURN_RIGHT = 2} ACTION;

typedef struct
{
  int x;
  int y;
  int counter;
} intersection_t;

class Cart
{
  public:
    Cart(int id, int x, int y, DIRECTION d)
    {
      this->id = id;
      this->x  = x;
      this->y  = y;
      this->d  = d;
      this->counter_intersection = 0;
    }

    void process_intersection()
    {
      if (counter_intersection == TURN_LEFT)
      {
        cout << id << " TURN_LEFT" << endl;
        switch(d)
        {
          case UP:
            d = LEFT;
            break;
          case LEFT:
            d = DOWN;
            break;
          case RIGHT:
            d = UP;
            break;
          case DOWN:
            d = RIGHT;
            break;
        }
      }
      else if (counter_intersection == TURN_RIGHT)
      {
        cout << id << " TURN_RIGHT" << endl;
        switch(d)
        {
          case UP:
            d = RIGHT;
            break;
          case LEFT:
            d = UP;
            break;
          case RIGHT:
            d = DOWN;
            break;
          case DOWN:
            d = LEFT;
            break;
        }
      }
      else
      {
        cout << id << " STRQIGHT" << endl;
      }
      counter_intersection = (counter_intersection + 1) % 3;
    }

    void move()
    {
      switch(d)
      {
        case UP:
          y--;
          break;
        case DOWN:
          y++;
          break;
        case LEFT:
          x--;
          break;
        case RIGHT:
          x++;
          break;
      }
    }

    void print()
    {
      switch(d)
      {
        case LEFT:
          cout << "<";
          break;
        case RIGHT:
          cout << ">";
          break;
        case UP:
          cout << "^";
          break;
        case DOWN:
          cout << "v";
          break;
      }
    }

  public:
    int id;
    int x;
    int y;
    int counter_intersection;
    DIRECTION d;
};

typedef void (*operator_t)(Cart * cart);

typedef struct
{
  char dbg;
  int x;
  int y;
  operator_t command;
} rail_t;

typedef vector<vector<rail_t>> map_t;

// | or -
void go_straight(Cart * c)
{
//DO NOTHING
}

// '\'
void go_left_or_down(Cart * c)
{
  if (c->d == RIGHT)
  {
    c->d = DOWN;
  }
  else if (c->d == UP)
  {
    c->d = LEFT;
  }
  else if (c->d == LEFT)
  {
    c->d = UP;
  }
  else if (c->d == DOWN)
  {
    c->d = RIGHT;
  }
  else
  {
    cout << "ERROR IN GO_LEFT_OR_DOWN , cart direction = " << c->d << endl;
  }
}

// '/'
void go_right_or_up(Cart * c)
{
  if (c->d == UP)
  {
    c->d = RIGHT;
  }
  else if (c->d == LEFT)
  {
    c->d = DOWN;
  }
  else if (c->d == RIGHT)
  {
    c->d = UP;
  }
  else if (c->d == DOWN)
  {
    c->d = LEFT;
  }
  else
  {
    cout << "ERROR IN GO_RIGHT_OR_UP , cart direction = " << c->d << endl;
  }
}

void process_intersection(Cart * c)
{
  c->process_intersection();
}

rail_t init_rail(int x, int y, char op, vector<Cart *> & carts)
{
  //rail_t * rail = (rail_t*)malloc(sizeof(rail_t));
  rail_t rail;
  rail.dbg = op;
  rail.x = x;
  rail.y = y;
  switch (op)
  {
    case '-':
      rail.command = &go_straight;
      break;
    case '|':
      rail.command = &go_straight;
      break;
    case '/':
      rail.command = &go_right_or_up;
      break;
    case '\\':
      rail.command = &go_left_or_down;
      break;
    case '+':
      rail.command = &process_intersection;
      break;
    case '<':
      carts.push_back(new Cart(carts.size(), x, y, LEFT));
      rail.command = &go_straight;
      break;
    case '>':
      carts.push_back(new Cart(carts.size(),x, y, RIGHT));
      rail.command = &go_straight;
      break;
    case '^':
      carts.push_back(new Cart(carts.size(),x, y, UP));
      rail.command = &go_straight;
      break;
    case 'v':
      carts.push_back(new Cart(carts.size(),x, y, DOWN));
      rail.command = &go_straight;
      break;
  }
  return rail;
}

Cart * get_cart(vector<Cart *> & carts, int x, int y)
{
  for (vector<Cart *>::iterator c = carts.begin() ; c != carts.end() ; ++c)
  {
    // process rail operation
    if (((*c)->y == y) && ((*c)->x == x))
      return *c;
  }
  return NULL;
}

// sort using a custom function object
struct cartSort {
    inline bool operator()(const Cart * a, const Cart * b)
    {
        if (a->y == b->y)
        {
          return a->x < b->x; // a.x == b.x -> crash
        }
        return a->y < b->y;
    }
};

int main(int argc, char * argv[])
{
  if (argc > 1)
  {
    ifstream f;
    f.open(argv[1]);

    vector<Cart *> carts;
    map_t map;
    string line;
    int y = 0;
    int number_cols = 0;
    while (getline(f, line))
    {
      // Manually check that first line contain number of cols
      if (line.size() > number_cols)
      {
        number_cols = line.size();
      }
      vector<rail_t> tmp_rail;
      for (int x = 0 ; x < line.size() ; x++)
      {
        tmp_rail.push_back(init_rail(x, y, line[x], carts));
      }
      for (int x = line.size() ; x < number_cols ; x++)
      {
        tmp_rail.push_back(init_rail(x, y, ' ', carts));
      }
      cout << tmp_rail.size() << endl;
      map.push_back(tmp_rail);
      y++;
    }

    bool crash = false;
    int x_crash,y_crash;

    while(!crash)
    {
      // Sort carts by top to bottom, left to right
      sort(carts.begin(), carts.end(), cartSort());

      // loop over carts
      for (vector<Cart *>::iterator c = carts.begin() ; c != carts.end() ; ++c)
      {
        // process rail operation
        map[(*c)->y][(*c)->x].command((*c));

        // move
        (*c)->move();
      }

      // Cart * p_cart;
      // for(int col = 0 ; col < map.size() ; col++)
      // {
      //   for(int row = 0 ; row < map[0].size() ; row++)
      //   {
      //     p_cart = get_cart(carts, row, col);
      //     if (p_cart == NULL)
      //     {
      //       cout << map[col][row].dbg;
      //     }
      //     else
      //     {
      //       p_cart->print();
      //     }
      //   }
      //   cout << endl;
      // }
      // cout << endl;

      // Check crash
      for (int i = 0 ; i < carts.size() - 1; i++)
      {
        for(int j = i + 1 ; j < carts.size() ; j++)
        {
          if ((carts[i]->x == carts[j]->x) && (carts[i]->y == carts[j]->y))
          {
            crash = true;
            x_crash = carts[i]->x;
            y_crash = carts[i]->y;
            break;
          }
        }
        if (crash)
        {
          break;
        }
      }
    }

    cout << "crash append at " << x_crash << "," << y_crash << endl;


    return 0;
  }
  return 1;
}
