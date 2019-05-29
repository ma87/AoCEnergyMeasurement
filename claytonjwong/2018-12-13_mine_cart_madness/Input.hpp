//
// Created by Clayton Wong on 2018-12-13.
//

#pragma once

#include <string>


const std::string INPUT = R"(                      /---------\                                                             /-------------------------------\
                    /-+---------+------------------------------\                              |                               |
                    | |         |/-----------------------------+------------------------------+-------------------------------+--------------\
                    | |         ||    /------------------------+------------------------------+-\                             |              |
                    | |         ||    |     /------------------+------------------------------+-+-----------------------------+------------\ |
              /-----+-+---------++----+-----+------------------+------------------------------+-+\                         /--+------------+-+------\
              |     | |         ||/---+-----+------------------+------------------------------+-++-------------------------+--+-\          | |      |
    /---------+-----+-+---------+++---+-----+------\           |                              | ||                         |  | |          | |      |
    |         |     | |    /----+++---+-----+------+-----------+------------------------------+-++-------------------------+--+-+\         | |      |
    |         |     | |    |    ||| /-+-----+------+-----------+---------------\          /---+-++-------------------------+--+-++---\     | |      |
    |       /-+-----+-+----+----+++-+-+-----+------+-----------+---------\     |          |   | ||                         |  | ||   |     | |      |
    |       | |     | |    |    ||| | |     |      |           |      /--+-----+----------+---+-++-------------------------+--+-++---+-----+-+--\   |
    |       | | /---+-+----+----+++-+-+-----+------+-----------+------+--+-----+----------+\  | ||        /----------------+--+\||   |     | |  |   |
    |       | | |   | |    |    ||| | |     |      |           |      |  |     |          ||  | ||        |                |  ||||   |     | |  |   |
    |       | | |   | |    |    ||| | |     |      |           |    /-+--+-----+----------++--+-++---\    |                |  ||||   |     | |  |   |
    |       | | |   | |    |    ||| | |     |      |           |/---+-+--+-----+----------++--+-++---+----+-------\        \--++++---+-----+-+--+---/
   /+-------+-+-+---+-+----+----+++\| |     |      |          /++---+-+--+-----+----------++--+-++---+----+-------+-----------++++--\|     | |  |
  /++-------+-+-+---+-+----+----+++++-+-----+------+----------+++-\ | |  |     |          ||  | ||   |    |       |           ||||  ||     | |  |
  |||       | | | /-+-+----+----+++++-+-----+------+----------+++-+-+-+-\|     |          ||  | ||   |    |       |           ||||  ||     | |  |
  |||       | | | | ^ |    |    ||||| |     |      |    /-----+++-+-+-+-++\    |/---------++--+-++---+----+-------+-----------++++--++----\| |  |
  |||       | | | | | |    |    ||||| |     |      |    |     ||| | | | |||    ||         ||  | ||   |    |       |/----------++++--++-\  || ^  |
  |||       | | | | \-+----+----+++++-+-----+------+----+-----+/| | | | |||    ||  /------++--+-++\  |    |       ||          ||||  || |  || |  |
  |||     /-+-+-+-+---+--\ |    ||||| |     |      |    |     | | | | | |||    ||  |    /-++--+-+++--+----+-------++----------++++--++-+--++-+--+----\
  |||     | | | | |   |  | |    ||||| |     |      | /--+-----+-+-+-+-+-+++----++--+----+-++--+-+++--+----+-------++----------++++--++-+--++-+--+--\ |
  |||     | | | | |   |/-+-+----+++++-+-----+------+-+--+----\| | | | | |||    ||  |    | || /+-+++--+----+--\    ||          ||||  || |  || |  |  | |
  |||     | | | | |  /++-+-+----+++++-+-----+------+-+--+----++-+-+-+-+-+++----++--+----+-++-++-+++--+---\|  |    ||          ||||  || |  || |  |  | |
  |||     | | | | |  ||| | |    ||||| |     |      | |  |    || | | | \-+++----++--+----+-++-++-+++--+---++--+----++----------++++--++-+--++-+--/  | |
  |||     | | | | |  ||| | |    ||||| |  /--+------+-+--+----++-+-+-+---+++----++--+----+-++-++-+++--+---++--+----++----------++++--++-+\ || |     | |
  |||     | | | | |  ||| | |    ||||| |/-+--+------+-+--+----++-+-+-+---+++----++--+----+-++\|| |||  |   ||  |    ||          ||||  || || || |     | |
/-+++-----+-+-+-+-+--+++-+-+----+++++-++-+--+------+-+--+----++-+-+-+---+++----++--+--\ | ||||| |||  |   ||  |    ||          ||||  || || || |     | |
| |||     v | | | |  ||| | |    ||||| || |  |      | |  |    || |/+-+---+++----++--+--+-+-+++++-+++-\|   ||  |    ||          ||||  || || || |     | |
| |||     | | | | |  ||| | |    ||||| || |  |      | |  |    || ||| |   |||    ||  |  | | \++++-+++-++---++--+----++----------++++--+/ || || |     | |
| |\+-----+-+-+-+-+--+++-+-+----+++/| || |  |      | |  |    ||/+++-+---+++----++--+--+-+--++++-+++-++---++--+----++----------++++--+--++-++-+-----+\|
| | |     | | | | |  ||| | |    ||| | || |  |   /--+-+--+----++++++-+---+++----++--+--+-+--++++-+++-++---++--+----++\         ||||  |  || || |     |||
| | |     | | | | |  ||| | |    ||| | || |  |/--+--+-+--+----++++++-+---+++----++--+--+-+--++++-+++-++---++--+----+++--\      ||||  |  || || |     |||
| | |     | | | | |  ||| | |    ||\-+-++-+--++--+--+-+--+----++++++-+---+++----++--+--+-+--++++-+++-++---++--+----+++--+------++/|  |  || || |     |||
| | |     |/+-+-+-+--+++-+-+----++--+-++-+-\||  |  | |  |    |||||| |   |||    ||  |  | |  |||| ||| ||   ||  |    |||  |      || |  |  || || |     |||
| | |     ||| | | |  ||| | |    ||  | || | |||  |  | |  |/---++++++-+---+++----++--+--+-+--++++-+++-++---++--+----+++--+------++-+--+--++<++-+--\  |||
| | |     ||| | | |  ||| | |    ||  | || | |||  |  | |  ||   |||||| |   |||    ||  |  | |  |||| ||| ||   ||  |    |||  |      || |  |  || || |  |  |||
| | |     ||| | | |  ||| | |    ||  | || | ||| /+--+-+--++---++++++\|   |||   /++--+--+-+--++++\||| ||   ||  |    |||  |      || |  |  || || |  |  |||
| | |     ||| | | |  ||| | |    ||  | ||/+-+++-++--+-+--++---++++++++---+++---+++--+--+-+--++++++++-++---++--+\   |||  |      || |  |  || || |  |  |||
| | |     ||| | | |  ||| |/+----++--+-++++-+++-++--+-+--++---++++++++---+++---+++\ |  | |  |||||||| ||   ||  ||  /+++--+--\   || |  |  || || |  |  |||
| | |    /+++-+-+-+--+++-+++----++--+-++++-+++-++--+\|  ||   ||||||||   |||   |||| |  | |  |||||||| || /-++--++--++++--+--+---++-+--+\ || || |  |  |||
| | |    |||| | \-+--+++-+++----++--+-++++-+++-++--+++--++---++++++++---+++---++++-+--+-+--/||||||| || | ||  ||  ||||  |  |   || |  || || || |  |  |||
| | |    |||| |   |  ||| |||    ||  | |||| ||| ||  |||  ||   ||||||||   |||   |||| |  | |   ||||||| || | ||  ||  ||||  |  |   || |  || || || |  |  |||
\-+-+----++++-+---+--+++-+++----++--+-++++-+++-++--+++--++---++++++++---+++---++++-+--/ |   ||||||| || | ||  ||  ||||  |  |   || |  || || || |  |  |||
  | |    |||| |   |  ||| |||    |\--+-++++-+++-++--+++--++---++++++++---+++---++++-+----+---+++++++-++-+-++--++--++++--+--+---++-+--++-++-++-/  |  |||
  | |    |||| |   |  ||| |||    |  /+-++++-+++-++--+++--++---++++++++---+++---++++-+----+---+++++++-++-+-++--++--++++--+--+---++-+-\|| || ||    |  |||
  | |    |||| |   |  ||| |||    |  || |||| ||| ||  |||  ||   ||||||||   |||   |||| |/---+---+++++++-++-+-++--++--++++--+--+-\ || | ||| || ||    |  |||
  | |  /-++++-+--\|  ||| |||    |  || |||| ||| \+--+++--++---++++++/|   ||| /-++++-++---+---+++++++-++-+-++--++--++++--+--+-+-++-+-+++-++-++---\|  |||
  | |  | |||| |  ||  ||| |||    |  || |||| |||  |  |||  ||   |||||| |  /+++-+-++++-++---+---+++++++-++-+-++--++--++++--+--+-+-++-+-+++-++-++--\||  |||
  | |  | |||| | /++--+++-+++----+--++-++++-+++--+--+++--++---++++++-+--++++-+-++++-++---+---+++++++-++-+-++--++\ ||||  |  | | || | ||| || ||  |||  |||
  | |  | ||||/+-+++--+++-+++----+--++-++++-+++--+--+++--++---++++++\|  |||| | |||| || /-+---+++++++-++\| ||  ||| ||||  |  | | || | ||| || ||  |||  |||
  | |  | |||||| |||  ||| |||    |  || |||| |||  |  |||/-++---++++++++--++++-+-++++-++\| |   ||||||| |||| ||  ||| ||||  |  | | || | ||| || ||  |||  |||
  | |  | |||||| |||  ||| |||    |  || |||| |\+--+--++++-++---++++++++--++++-+-++++-++++-+---+++++++-++++-++--+++-++++--+--+-+-++-+-+++-++-+/  |||  |||
  \-+--+-++++++-+++--+++-+++----+--++-++++-+-+--+--++++-++---+++++/||  |||| | \+++-++++-+---+++/||| |||| ||  ||| ||||  |  | | || | ||| || |   |||  |||
    |  | |||||| |||  ||| |||    |  || |||| | |  |  ||||/++---+++++-++--++++-+--+++-++++-+---+++-+++-++++-++--+++-++++--+--+-+-++\| ||| || |   |||  |||
    |  | |||||| |||  ||| |||    |  || |||| | |  |  |||||||   ||||| ||  |||| |  ||| |||| |   ||| ||| |||| ||  ||| ||||  |  | | |||| ||| || |   |||  |||
    |  | |||||| |||  |||/+++----+--++-++++-+-+--+--+++++++---+++++-++--++++-+--+++-++++-+---+++\||| |||| ||  |||/++++--+--+-+-++++-+++-++-+---+++\ |||
    |  | |||||| |||  |||||||    |  || |||| | |  |  |||||||   ||||| ||  |||| |  ||| |||| |   ||||||| |||| ||  ||||||||  |  | | |||| ||| || |   |||| |||
    |  | |\++++-+++--++++/||    |  || |||| | |  | /+++++++---+++++-++--++++-+--+++-++++-+---+++++++-++++-++--++++++++\ |  | | |||| ||| || |   |||| |||
    |  | | |||| |||  |||| ||    |  || |||| | |  | ||||||||   ||||| ||  |||| |  ||| |||| |   ||||||| |||| ||/-+++++++++-+--+-+-++++-+++-++-+-\ ||^| |||
    |  | | |||| \++--++++-++----+--++-++++-+-+--+-++++++++---+++++-++--++++-+--+++-++++>+---+++++++-++++-+++-++/|||||| |  | | |||| ||| || | | |||| |||
 /--+--+-+-++++--++-\|||| ||    |  || |||| | |  | ||||||||   ||||| ||  |||| |  ||| |||| |   ||||||| |||| ||| || |||||| |  | | |||| ||| || | | |||| |||
 |  |  | | ||||  ^| ||||| ||    |  ||/++++-+-+--+-++++++++---+++++-++-\|||| |  ||| |||| |   |||||||/++++-+++-++-++++++-+--+-+-++++-+++-++-+-+\|||| |||
 |  |  | | ||||  || ||||| ||    |  ||||||| | |  | ||||||||   ||||| |\-+++++-+--+++-++++-+---+++++++++/|| ||| || |||||| |  | | |||| ||| || | |||||| |||
 |  |  | | ||||  || ||||| ||    |  ||||||| | |  | |||||||\---+++++-+--+++++-+--+++-++++-+---+++++++++-++-+++-++-++++++-+--+-+-++++-+++-++-+-++++/| |||
 |  |  | | ||||  || ||||| ||    |  ||||||| | |  | |||||||    ||||| |  ||||| |  ||| |||| |   ||||||||| || ||| || |||||| |  | | |||| ||| || | |||| | |||
 |  |  | | v|||  |\-+++++-++----+--+++++++-+-+--+-+++++++----+++++-+--++/|| \--+++-++++-+---+++++++++-++-+++-++-++++++-+--+-+-++++-+++-++-+-+++/ | |||
 |  |  | | ||||  |  ||||| ||    |  ||||||| | | /+-+++++++----+++++-+--++-++----+++-++++-+---+++++++++-++-+++-++-++++++-+--+-+-++++-+++-++-+-+++--+\|||
 |  | /+-+-++++--+-\||||| ||    |  ||||||| | | ||/+++++++----+++++-+--++-++----+++-++++-+---+++++++++-++-+++-++-++++++\|  | | |||| ||| || | |||  |||||
 |  | || | ||||  | |||||| || /--+--+++++++-+-+-++++++++++----+++++-+--++-++----+++-++++-+--\||||||||| || ||| || ||||||||  | | |||| ||| || | |||  |||||
 |  | || | \+++--+-++++++-++-+--+--+++++++-/ | ||||||||||    |||||/+--++-++----+++-++++-+--++++++++++-++-+++-++-++++++++\/+-+-++++-+++-++-+\|||  |||||
 |  | || |  \++--+-++++++-++-+--+--+++++++---+-++++++++++----+++++++--++-/|    ||| |||| |  |||||||||| || ||| || ||||||||||| | |||| ||| || |||||  |||||
 |  v || |   ||  | |||||| || |  |  |||||||   | ||||||||||    ||\++++--++--+----+++>++++-+--++++++++++-++-+++-++-+++++++++++-+-++++-+++-++-+++++--+++/|
 |  | ||/+---++--+-++++++-++-+--+--+++++++---+-++++++++++----++-++++--++--+----+++-++++-+\ |||||||||| || ||| || ||||||||||| | |||| ||| || |||||  ||| |
 |  | ||||   ||  | ||||\+-++-+--+--+++++++---+-++++++++++----/| ||||  ||  |    ||| ||||/++-++++++++++-++-+++-++-+++++++++++\| |||| ||| || |||||  ||| |
 |  | ||||   ||  | |||| | || |  |  |||||||   | ||||||||||     | ||||/-++--+----+++-+++++++-++++++++++\|| ||| || ||||||||||||| |||| ||| || |||||  ||| |
 |  | ||||   || /+-++++-+-++-+--+--+++++++---+-++++++++++-----+-+++++-++\ |    ||| ||||||| ||||||||||||| ||| || ||||||||||||| |||| ||| || |||||  ||| |
 |  | ||||   || || |||| | || |  |  |||||||   | ||||||||||     | ||||| ||| |    ||| ||||||| ||\++++++++++-+++-/| ||||||||||||| |||| ||| || |||||  ||| |
 |  | ||||   || || |||| | || |  |  |||||||   | ||||||||||     | ||||| |||/+----+++-+++++++-++-++++++++++-+++--+-+++++++++++++-++++-+++\|| |||||  ||| |
 |  | ||||   || || |||| | || |  |  |||||||/--+-++++++++++-----+-+++++-+++++----+++-+++++++-++-++++++++++-+++\ | ||||||||||||| |||| |||||| |||||  ||| |
 |  | ||||   \+-++-++++-+-++-+--+--++++++++--+-++++++++++-----+-+++/| |||||    ||| ||||||| || |||||||||| |||| | ||||||||||||| |||| |||||| |||||  ||| |
 |  | ||||    | || |||| | || |  |  |\++++++--+-++++++++++-----+-+++-+-+++++----/|| ||||||| || \+++++++++-++++-+-+++++++++++++-/||| |||||| |||||  ||| |
 |  | ||||    | || |||| | || |  |  | ||||||  | ||||||||||     | ||| | |\+++-----++-+++++++-++--+++++++++-++++-+-+++++++++++++--+++-++++++-++++/  ||| |
 |  | ||||    | || |||| | || |  |  | ||||||  | |||||||||\-----+-+++-+-+-++/     || ||||||| ||  |||||||||/++++-+-+++++++++++++\ ||| |||||| ||||   ||| |
 |  | ||||    | || |||| | || |  |  | ||||||  | |||||||||      | ||| | | ||      || ||||||| ||  |||||||||||||| | |||||||||||||| ||| |||||| ||||   ||| |
 |  | ||||    | || |||| | || |  |  | ||||||  | |||||||||      | ||| |/+-++-----\|| ||||||| ||  |||||||||||||| | |||||||||||||| ||| |||||| ||||   ||| |
 |  | |||| /--+-++-++++-+-++-+--+--+\||||||  | |||||||||      | ||| ||| ||     ||| ||||||| v|  |||||||||||||| | |||\++++++++++-+++-++++/| ||||   ||| |
 |  | |||| |  | \+-++++-+-++-+--+--++++++++--+-+++++++++------+-+++-+++-/|     ||| ||||||| ||  ||||||||||||||/+-+++-++++++++++-+++-++++-+-++++--\||| |
 |  | |||| |  |  | |||| | || |  |  |||\++++--+-+++++++++------+-+++-+++--+-----+++-+++++++-++--+/|||||||||||||| ||| ||||||||||/+++-++++-+-++++-\|||| |
 |  | |||| |  |  | |||\-+-++-+--/  ||| |||\--+-+++++++++------+-+++-+++--+-----+++-+++++++-++--+-+++++++++++/|| |\+-++++++/||||||| |||| | |||| ||||| |
 |  | |||| |  |  | |||  | || |     ||| |||   | |||||||||      | |\+-+++--+-----+++-+++++++-++--+-+++/||||||| || | | |||||| ||||||| |||| | |||| ||||| |
 |/-+-++++-+-\|  | |||  | || |     ||| |||   | |||||||||      | | | |||  |     ||| ||||||| ||  | ||| ||||||| || | | |||||| ||||||| |||| | |||| ||||| |
 || | |||| | ||  | |||  | || |     ||| |||   | |||||||\+------+-+-+-+++--+-----+++-++/||\+-++--+-+++-+++++++-++-+-+-++++++-+++++++-++++-+-++++-+++++-/
 || | |||| | ||  | |||  | || |     ||| |||  /+-+++++++-+-----\| | | |||  |     ||| || ||/+-++--+-+++-+++++++-++-+\| |||||| ||||||| |||| | |||| |||||
 || | |||| | ||  | |||  | || |     ||| |||  || ||||||| |     || | | |||  |     |\+-++-++++-++--+-+++-+++++++-++-+++-++++++-+++++++-++++-+-/||| |||||
 || | |||| | |\--+-+++--+-++-+-----+++-+++--++-+++++++-+-----++-+-+-+++--+-----+-+-++-++++-++--+-/|| ||||||| || ||| |||||| ||||||| |||| |  ||| |||||
 || | |||| | |   | |||  | || |     ||| |||  || ||\++++-+-----++-+-+-+++--+-----+-+-++-++++-++--+--++-+++++++-++-+++-++/||| ||||||| |||| |  ||| |||||
 || | |||| | |   | |||  | || |/----+++-+++\ || || |||| |     || | | |||  |     | | || |||| ||  |  || |||||\+-++-+++-++-+++-++++/|| |||| |  ||| |||||
 || |/++++-+-+---+-+++--+-++-++----+++-++++-++-++-++++-+-----++-+-+-+++--+-\   | | || \+++-++<-+--++-+/||| | || ||| || ||| |||| || |||| |  ||| |||||
 || |||||| | |   | |||  | || ||    ||| |||| || || |||| |     || | | |||  | |   | | ||  ||| ||  |  || | ||| | || ||| || ||| |||| || |||| |  ||| |||||
 || |||||| | |   | |||  | |\-++----+++-++++-++-++-++++-+-----++-+-+-+++--+-+---+-+-++--+++-++--+--++-+-+++-+-++-+++-++-+++-++++-+/ |||| |  ||| |||||
 || ||||||/+-+---+-+++\ | |  ||  /-+++-++++-++-++-++++-+----\|| | | |||  | |   | | ||  ||| ||  |  || | ||| | || ||| || ||| |||| |  |||| |  ||| |||||
 || |||||||| |   | |||| | |  ||  | ||| |||| |\-++-++++-+----+++-+-+-+++--+-+---+-+-++--+++-++--+--++-+-+++-+-++-+++-++-/|| |||| |  |||| |  ||| |||||
 || |||||||| |   | |||| | |  ||  | ||| |||| |  || \+++-+----+++-+-+-+++--+-+---+-+-++--+++-++--+--++-+-+++-+-++-+++-+/  || |||| |  |||| |  ||| |||||
 || |||||||| |   | |||| | |  ||  | ||| |||| |  ||  ||| |/---+++-+<+\|||  | |   |/+-++--+++-++--+--++-+-+++-+-++-+++-+-\ || |||| |  |||| |  ||| |||||
 || |||||||| |   | |||| | |  ||  | ||| |||| |  ||  ||| ||   ||| | |||||  | |   ||| ||  ||| ||  |  || | ||| | || ||| | | || |||| |  |||| |  ||| |||||
 || |||||||| |   | |||| | |  ||  | ||| |||| |  ||  ||| ||   ||| | |||||  | |   ||| ||  ||| ||  |  || | ||| \-++-+++-+-+-++-++++-+--++++-+--+/| |||||
 || \+++++++-+---+-++++-+-+--++--+-+++-++++-+--++--/|| ||   ||| | |||||  | |   ||| ||  \++-++--+--++-+-+++---++-+++-+-+-++-/||| | /++++-+--+-+-+++++-\
 ||  ||||||| |   | |||| | |  ||  | ||| |\++-+--++---++-++---+++-+-+++++--+-+---+++-++---++-++--+--++-+-+++---+/ ||| | | ||  ||| | ||||| |  | | ||||| |
 ||  |||||||/+---+-++++-+-+--++--+-+++-+-++-+--++---++-++---+++-+-+++++--+-+---+++-++---++-++-\|  || | |||   |  ||| | | ||  ||| | ||||| |  | | ||||| |
 ||  |||||||||   | |||| | |  ||  | ||| | || |  ||   ^| || /-+++-+-+++++--+-+-\ ||| ||   || || ||  || | ||| /-+--+++-+-+-++--+++-+-+++++-+-\| | ||||| |
 ||  |||||||||   | |||| | |  ||  | ||| | || |  ||   || || | ||| | |||||  | | | ||| ||   || || ||  || | ||| | |  ||| | | ||  ||| | ||||| | || | ||||| |
 ||  ||\++++++---/ |||| | |  ||  | ||| | || |  ||   || || | ||| \-+++++--+-+-+-+++-++---++-++-++--++-+-+++-+-+--++/ | | ||  ||| | ||||| | || | ||v|| |
 ||  || ||||||     ||\+-+-+--++--+-+++-+-++-+--++---++-++-+-+++---+++++--+-+-+-+++-++---++-++-++--++-+-++/ | |  ||  | | ||  ||| | ||||| | || | ||||| |
 ||  || ||||||     || | | |  ||  | ||| | || |  ||   || |\-+-+++---+/|||  | | | ||| |\---++-++-++--++-+-++--+-+--++--+-+-++--/|| | ||||| | || | ||||| |
 ||  || ||||||     || | | |  ||  | ||| | || | /++---++-+--+-+++---+-+++--+-+-+-+++\|    || || ||  || | ||  | |  ||  | | ||   || | ||||| | || | ||||| |
 ||  || ||||||     || | | |  ||  | ||| | || | |||   || |  | |||   | |\+--+-+-+-/||||    || || ||  || | ||  | \--++--+-+-++---++-+-+++++-+-++-+-+/||| |
 ||  \+-++++++-----++-+-+-+--++--+-+++-+-++-+-+++---++-+--+-+++---+-+-+--+-/ |  ||||    || || ||  || | ||  |    ||  | | ||   || | ||||| | || | | ||| |
 ||   | ||||||     || | | |  ||  | ||| | || | |||   || |  | |||   | | |  |   |  ||||    \+-++-++--++-+-++--+----+/  | | ||   || | ||||| | || | | ||| |
 ||   | ||||||     || | | |  ||  | ||| | || | |||   || |  | ||\---+-+-+--+---+--++++-----+-++-++--++-+-++--+----+---+-+-++---++-+-++/|| | || | | ||| |
 ||   \-++++++-----/| | | |  ||  | ||| | || | |||   || |  | ||    | | |  |   |  ||||     | || ||  || | ||  |    |   | | |\---++-+-++-++-+-+/ | | ||| |
 ||     ||||||      | | | |  ||  | ||| | || | |||   || |  | ||    | | |  |   |  ||||     | || ||  || | ||  |    |   | | |    || | || || | |  | | ||| |
/++-----++++++------+-+-+-+--++--+-+++-+-++-+-+++---++-+--+\||    | | |  |   |  ||||     | || ||  || | ||  |    |   | | |    || | || || | |  | | ||| |
|||     ||||||      | | | |  ||  | ||| \-++-+-+++---++-+--++++----+-+-+--+---+--++++-----+-+/ ||  || | ||  |    |   | | |    || | || || | |  | | ||| |
|||     ||||||      | | | |  || /+-+++---++-+-+++---++-+--++++---\| | |  |   |  ||||     | |  ||  |\-+-++--+----+---+-+-+----++-+-++-++-+-+--/ | ||| |
|||   /-++++++------+-+-+-+-\|| || |||   || | |||   || |  ||||   || | |  |   |  |||\-----+-+--++--/  | ||  |    |   | | |    || | || || | |    | ||| |
|||   | ||||||      | | | | ||| || |||   \+-+-+++---++-+--++++---++-+-+--+---+--+++------+-+--++-----+-++--+<---+---+-+-+----++-+-++-++-/ |    | ||| |
|||   | ||||||      | | | | ||| || |||    | | |||   || |  ||||   || | |  \---+--+++------+-+--++-----+-++--+----+---+-+-+----++-+-++-+/   |    | ||| |
|||   | ||||||      | | | \-+++-++-+++----+-+-+++---++-+--++++---++-+-+------+--+/|      | |  ||     | \+--+----+---+-+-+----++-+-++-/    |    | ||| |
|||   | ||||||      | | |   ||\-++-+++----/ | |||   |\-+--++++---++-+-+------+--+-+------+-+--++-----+--+--+---<+---+-+-+----++-+-++------+----+-++/ |
|||   | ||||||      | | |   ||  || \++------+-+++---+--+--++++---++-+-+------+--+-+------+-+--++-----+--+--+----+---+-+-+----++-+-+/      |    | ||  |
|||   | ||||||      | | |   ||  ||  ||      \-+++---+--+--+++/   ||/+-+------+--+-+------+-+--++-\   |  |  |    |   | | |    || | |       |    | ||  |
|||   | ||||\+------+-+-+---++--++--++--------+++---+--+--+++----++++-+------+--+-+------+-+--/| |   |  |  |    |   | | |    || | |       |    | ||  |
|||   | ||\+-+------+-/ |   |\--++--++--------+++---+--+--+++----++++-+------+--+-+------+-/   | |   |  |  |    |   | | |    || | |       |    | ||  |
|||   | \+-+-+------+---+---+---++--++--------+++---+--+--+++----++++-+------+--+-+------/     | |   |  |  |    \---+-+-+----++-+-+-------+----+-/|  |
|||   |  | | |      |   |   |   ||  ||        |||   |  |  \++----++++-+------/  | |            | |   |  \--+--------+-+-+----/| | |       |    |  |  |
|\+---+--+-+-+------/   |   |   \+--++--------+++---+--+---++----/||| |         | |            | |   |     \--------+-+-+-----+-+-+-------/    |  |  |
| |   |  | \-+----------+---+----+--/|        |||   |  |   ||     ||| |         | |            | |   |              | | |     | | |            |  |  |
| |   |  |   |          \---+----+---+--------+++---+--+---++-----+++-+---------+-+------------/ |   |              | | |     | | |            |  |  |
| \---+--+---/              |    |   |        ||\---+--+---++-----+++-+---------+-+--------------+---+--------------/ | |     \-+-+------------/  |  |
|     |  |                  |    |   \--------++----+--+---++-----+++-/         \-+--------------+---+----------------/ |       | |               |  |
|     |  |                  |    \------------++----+--+---+/     |\+-------------+--------------/   |                  |       | |               |  |
\-----+--+------------------+-----------------++----+--+---/      \-+-------------+------------------+------------------/       | |               |  |
      |  \------------------+-----------------++----/  |            |             |                  |                          | \---------------+--/
      |                     |                 ||       |            \-------------+------------------/                          |                 |
      |                     |                 ||       \--------------------------+---------------------------------------------/                 |
      |                     |                 |\----------------------------------+---------------------------------------------------------------/
      \---------------------/                 \-----------------------------------/
)";


/*
const std::string INPUT = R"(  /--\
/-+-\|
^ | ||
\-+-/|
  \--/
)";
*/
