
#Code taken from: https://rosettacode.org/wiki/Keyboard_input/Keypress_check#Python
import tty, termios
import sys
if sys.version_info.major < 3:
    import thread as _thread
else:
    import _thread
import time
import re
 
try:
    from msvcrt import getch  # try to import Windows version
except ImportError:
    def getch():   # define non-Windows version
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch
 
def keypress():
    global char
    char = getch()

class Star():
    def __init__(self, pos_x, pos_y, vel_x, vel_y):
        self.x = pos_x
        self.y = pos_y
        self.dx = vel_x
        self.dy = vel_y

    def move_forward(self):
        self.x += self.dx
        self.y += self.dy

    def move_backward(self):
        self.x -= self.dx
        self.y -= self.dy

def print_grid(grid):
    for rows in grid:
        for col in rows:
            print(col, end='')
        print('')

def get_coords(s, size_x, size_y):
    return int(s.x + size_x / 2) , int(s.y + size_y / 2)

def set_stars(grid, stars):
    min_x = min([s.x for s in stars])
    min_y = min([s.y for s in stars])

    for s in stars:
        grid[s.y - min_y][s.x - min_x] = "#"


def stars_closed(stars, size_x, size_y):
    min_x = min([s.x for s in stars])
    max_x = max([s.x for s in stars])

    min_y = min([s.y for s in stars])
    max_y = max([s.y for s in stars])

    return (max_x - min_x) < size_x and (max_y - min_y) < size_y


def main():
    global char
    char = None
    _thread.start_new_thread(keypress, ())

    filename = sys.argv[1]

    stars = []
    with open(filename, 'r') as f:
        contents = f.readlines()
        reg_exp = re.compile(r'position=<([-\ ]?)(\w*), ([-\ ]?)(\w*)> velocity=<([-\ ]?)(\w*), ([-\ ]?)(\w*)>') 
        
        for content in contents:
            if content.split():
                sign_pos_x, pos_x, sign_pos_y, pos_y, sign_vel_x, vel_x, sign_vel_y, vel_y = tuple(reg_exp.match(content).groups())

                stars.append(Star(int("{}{}".format(sign_pos_x,pos_x)), 
                                  int("{}{}".format(sign_pos_y,pos_y)),
                                  int("{}{}".format(sign_vel_x,vel_x)),
                                  int("{}{}".format(sign_vel_y,vel_y))))

        size_y = 78
        size_x = 240

        grid = [['.' for col in range(size_x)] for row in range(size_y)]

    t = 0
    while not stars_closed(stars, size_x, size_y):
        for s in stars:
            s.move_forward()
        t += 1

    while True:
        if char in ['n', 'b', 'q']:
            set_stars(grid, stars)

            print('t = ' + str(t))
            print_grid(grid)

            grid = [['.' for col in range(size_x)] for row in range(size_y)]

            if char=='n':
                for s in stars:
                    s.move_forward()
                t += 1
            elif char=='b':
                for s in stars:
                    s.move_forward()
                t -= 1

            print('')

            _thread.start_new_thread(keypress, ())
            if char == 'q' or char == '\x1b':  # x1b is ESC
                exit()
            char = None
        time.sleep(0.020)
 
if __name__ == "__main__":
    main()
