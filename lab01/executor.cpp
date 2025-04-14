#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
enum class Commands {
    SherlockHolmes,
    CatJeoffry,
    Quit,
    Forward,
    Backward,
    TurnRight,
    TurnLeft,
    PrintStatistics,
    StartMacro,
    EndMacro,
    RunMacro,
    ShowMap
};
enum class Direction { Up, Left, Down, Right };

struct Point {
    int x = 0, y = 0;
    std::vector<Commands> all_macro;
    std::map<std::pair<int, int>, char> Map{{{0, 0}, '0'}};
    char final_direction = '^';
    std::vector<int> max = {0, 0};
    std::vector<int> min = {0, 0};
    bool is_macro = false;
    int current_direction = 0;
};

Commands get_command(const std::string &command) {
    if (command == "sherlock" || command == "sherlock-holmes") {
        return Commands::SherlockHolmes;
    } else if (command == "cat" || command == "cat-jeoffry") {
        return Commands::CatJeoffry;
    } else if (command == "forward" || command == "fwd") {
        return Commands::Forward;
    } else if (command == "backward" || command == "bwd") {
        return Commands::Backward;
    } else if (command == "turn-left" || command == "left") {
        return Commands::TurnLeft;
    } else if (command == "turn-right" || command == "right") {
        return Commands::TurnRight;
    } else if (command == "print-statistics" || command == "stats") {
        return Commands::PrintStatistics;
    } else if (command == "start-macro") {
        return Commands::StartMacro;
    } else if (command == "end-macro") {
        return Commands::EndMacro;
    } else if (command == "run-macro") {
        return Commands::RunMacro;
    } else if (command == "show-map") {
        return Commands::ShowMap;
    } else {
        return Commands::Quit;
    }
}

Direction get_direction(const int &direction) {
    if (direction % 4 == 0) {
        return Direction::Up;
    } else if (direction % 4 == 1) {
        return Direction::Left;
    } else if (direction % 4 == 2) {
        return Direction::Down;
    } else {
        return Direction::Right;
    }
};

void sherlock() {
    std::cout << "I had had so many reasons to believe in my friend's subtle "
                 "powers of\n"
                 "reasoning and extraordinary energy in action that I felt "
                 "that he must\n"
                 "have some solid grounds for the assured and easy demeanour "
                 "with which\n"
                 "he treated the singular mystery which he had been called "
                 "upon to\n"
                 "fathom. Once only had I known him to fail, in the case of "
                 "the King of\n"
                 "Bohemia and of the Irene Adler photograph; but when I "
                 "looked back to\n"
                 "the weird business of the Sign of Four, and the "
                 "extraordinary\n"
                 "circumstances connected with the Study in Scarlet, I felt "
                 "that it would\n"
                 "be a strange tangle indeed which he could not unravel.\n";
}

void cat() {
    std::cout << R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.
)";
}

void data_update(Point &p) {
    const std::pair<int, int> current_cell = {p.x, p.y};
    if (p.x != 0 || p.y != 0) {
        p.Map.emplace(current_cell, 'o');
    }
    p.max[0] = std::max(p.max[0], p.x);
    p.min[0] = std::min(p.min[0], p.x);
    p.max[1] = std::max(p.max[1], p.y);
    p.min[1] = std::min(p.min[1], p.y);
}

void move_forward(Direction &direction, Point &p) {
    if (!p.is_macro) {
        switch (direction) {
            case Direction::Up: {
                p.y++;
            } break;
            case Direction::Down: {
                p.y--;
            } break;
            case Direction::Right: {
                p.x++;
            } break;
            case Direction::Left: {
                p.x--;
            } break;
        }
        data_update(p);
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::Forward);
    }
}

void move_backward(Direction &direction, Point &p) {
    if (!p.is_macro) {
        switch (direction) {
            case Direction::Up: {
                p.y--;
            } break;
            case Direction::Down: {
                p.y++;
            } break;
            case Direction::Right: {
                p.x--;
            } break;
            case Direction::Left: {
                p.x++;
            } break;
        }
        data_update(p);
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::Backward);
    }
}

void turn_left(Point &p) {
    if (!p.is_macro) {
        p.current_direction += 1;
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::TurnLeft);
    }
}

void turn_right(Point &p) {
    if (!p.is_macro) {
        p.current_direction += 3;  // 3 раза налево
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::TurnRight);
    }
}

void stats(Direction &direction, Point &p) {
    if (!p.is_macro) {
        std::cout << "Player ";
        switch (direction) {
            case Direction::Up: {
                std::cout << "^";
            } break;
            case Direction::Down: {
                std::cout << "v";
            } break;
            case Direction::Left: {
                std::cout << "<";
            } break;
            case Direction::Right: {
                std::cout << ">";
            } break;
        }
        std::cout << " stands " << abs(p.x) << " away from OY, " << abs(p.y)
                  << " away from OX. " << p.Map.size()
                  << " cell(s) has been visited.\n";
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::PrintStatistics);
    }
}

void show_map(Point &p, Direction &direction) {
    if (!p.is_macro) {
        switch (direction) {
            case Direction::Up: {
                p.final_direction = '^';
            } break;
            case Direction::Down: {
                p.final_direction = 'v';
            } break;
            case Direction::Right: {
                p.final_direction = '>';
            } break;
            case Direction::Left: {
                p.final_direction = '<';
            } break;
            default:
                p.final_direction = '^';
        }
        p.Map[{p.x, p.y}] = p.final_direction;
        for (int i = 0; i <= 2 * (p.max[0] - p.min[0] + 1); i++) {
            std::cout << ' ';
        }
        std::cout << '\n';
        for (int y = p.max[1]; y >= p.min[1]; y--) {
            std::cout << " ";
            for (int x = p.min[0]; x <= p.max[0]; x++) {
                if (p.Map.find({x, y}) != p.Map.end()) {
                    std::cout << p.Map[{x, y}] << ' ';
                } else {
                    std::cout << '.' << ' ';
                }
            }
            std::cout << '\n';
            for (int i = 0; i <= 2 * (p.max[0] - p.min[0] + 1); i++) {
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        p.Map[{p.x, p.y}] = 'o';
    } else {
        std::cout << "Recorded\n";
        p.all_macro.push_back(Commands::ShowMap);
    }
}

bool execute_command(  // NOLINT [misc-no-recursion]
    Commands command,
    Direction direction,
    Point &p
) {
    switch (command) {
        case Commands::SherlockHolmes: {
            sherlock();
        } break;
        case Commands::CatJeoffry: {
            cat();
        } break;
        case Commands::Forward: {
            move_forward(direction, p);

        } break;
        case Commands::Backward: {
            move_backward(direction, p);
        } break;
        case Commands::TurnLeft: {
            turn_left(p);
        } break;
        case Commands::TurnRight: {
            turn_right(p);
        } break;
        case Commands::PrintStatistics: {
            stats(direction, p);
        } break;
        case Commands::StartMacro: {
            if (!p.all_macro.empty()) {
                p.all_macro.clear();
            }
            p.is_macro = true;
        } break;
        case Commands::EndMacro: {
            p.is_macro = false;
            std::cout << "New macro of " << p.all_macro.size()
                      << " command(s)\n";
        } break;
        case Commands::RunMacro: {
            p.is_macro = false;
            for (auto i : p.all_macro) {
                const Direction macro_direction =
                    get_direction(p.current_direction);
                execute_command(i, macro_direction, p);
            }
        } break;
        case Commands::ShowMap: {
            show_map(p, direction);
        } break;
        case Commands::Quit: {
            if (p.is_macro) {
                std::cout << "New macro of " << p.all_macro.size()
                          << " command(s)\n";
            }
            return false;
        }
    }
    return true;
}

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

    Point p;
    while (true) {
        std::string in_command;
        std::getline(std::cin, in_command);
        const Commands command = get_command(in_command);
        const Direction direction = get_direction(p.current_direction);
        if (!execute_command(command, direction, p)) {
            return 0;
        }
    }
    return 0;
}