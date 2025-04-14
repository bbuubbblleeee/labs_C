#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#include <cassert>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

enum class Operation {
    Quit,
    Sherlock,
    Cat,
    Forward,
    Backward,
    Right,
    Left,
    Stats,
    Start_macro,
    Run_macro,
};

Operation get_operation(const std::string &operation) {
    if (operation == "quit" || operation == "exit") {
        return Operation::Quit;
    } else if (operation == "sherlock" || operation == "sherlock-holmes") {
        return Operation::Sherlock;
    } else if (operation == "cat" || operation == "cat-jeoffry") {
        return Operation::Cat;
    } else if (operation == "forward" || operation == "fwd") {
        return Operation::Forward;
    } else if (operation == "backward" || operation == "bwd") {
        return Operation::Backward;
    } else if (operation == "turn-right" || operation == "right") {
        return Operation::Right;
    } else if (operation == "turn-left" || operation == "left") {
        return Operation::Left;
    } else if (operation == "print-statistics" || operation == "stats") {
        return Operation::Stats;
    } else if (operation == "start-macro") {
        return Operation::Start_macro;
    } else if (operation == "run-macro") {
        return Operation::Run_macro;
    } else {
        assert(false);
    }
}

void quote_sherlock() {
    std::cout
        << "I had had so many reasons to believe in my friend's subtle powers of\n\
reasoning and extraordinary energy in action that I felt that he must\n\
have some solid grounds for the assured and easy demeanour with which\n\
he treated the singular mystery which he had been called upon to\n\
fathom. Once only had I known him to fail, in the case of the King of\n\
Bohemia and of the Irene Adler photograph; but when I looked back to\n\
the weird business of the Sign of Four, and the extraordinary\n\
circumstances connected with the Study in Scarlet, I felt that it would\n\
be a strange tangle indeed which he could not unravel.\n";
}

void quote_cat() {
    std::cout << R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.)"
              << '\n';
}

std::pair<int, int>
go_forward(std::pair<int, int> &coordinates_x_y, const char &player_watching) {
    switch (player_watching) {
        case '^': {
            coordinates_x_y.second++;
        } break;
        case '>': {
            coordinates_x_y.first++;
        } break;
        case 'v': {
            coordinates_x_y.second--;
        } break;
        case '<': {
            coordinates_x_y.first--;
        } break;
    }
    return coordinates_x_y;
}

std::pair<int, int>
go_backward(std::pair<int, int> &coordinates_x_y, const char &player_watching) {
    switch (player_watching) {
        case '^': {
            coordinates_x_y.second--;
        } break;
        case '>': {
            coordinates_x_y.first--;
        } break;
        case 'v': {
            coordinates_x_y.second++;
        } break;
        case '<': {
            coordinates_x_y.first++;
        } break;
    }
    return coordinates_x_y;
}

char after_turn_right(const char &player_watching) {
    if (player_watching == '^') {
        return '>';
    } else if (player_watching == '>') {
        return 'v';
    } else if (player_watching == 'v') {
        return '<';
    } else if (player_watching == '<') {
        return '^';
    } else {
        assert(false);
    }
}

char after_turn_left(const char &player_watching) {
    if (player_watching == '^') {
        return '<';
    } else if (player_watching == '>') {
        return '^';
    } else if (player_watching == 'v') {
        return '>';
    } else if (player_watching == '<') {
        return 'v';
    } else {
        assert(false);
    }
}

void macros_output(
    const std::vector<std::string> &macros,
    char &player_watching,
    std::pair<int, int> &coordinates_x_y,
    std::set<std::pair<int, int>> &visited_cells
) {
    for (const auto &command : macros) {
        if (command == "forward" || command == "fwd") {
            coordinates_x_y = go_forward(coordinates_x_y, player_watching);
            visited_cells.insert(coordinates_x_y);
        } else if (command == "backward" || command == "bwd") {
            coordinates_x_y = go_backward(coordinates_x_y, player_watching);
            visited_cells.insert(coordinates_x_y);
        } else if (command == "turn-right" || command == "right") {
            player_watching = after_turn_right(player_watching);
        } else if (command == "turn-left" || command == "left") {
            player_watching = after_turn_left(player_watching);
        } else if (command == "print-statistics" || command == "stats") {
            std::cout << "Player " << player_watching << " stands "
                      << abs(coordinates_x_y.first) << " away from OY, "
                      << abs(coordinates_x_y.second) << " away from OX. "
                      << visited_cells.size() << " cell(s) has been visited.\n";
        }
    }
}

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    char player_watching = '^';
    std::pair<int, int> coordinates_x_y = {0, 0};
    std::set<std::pair<int, int>> visited_cells;
    visited_cells.insert(coordinates_x_y);
    std::vector<std::string> macros;

    while (true) {
        std::string operation;
        if (!(std::cin >> operation)) {
            break;
        }
        const Operation operation_id = get_operation(operation);
        switch (operation_id) {
            case Operation::Quit: {
                return 0;
            } break;
            case Operation::Sherlock: {
                quote_sherlock();
            } break;
            case Operation::Cat: {
                quote_cat();
            } break;

            case Operation::Forward: {
                coordinates_x_y = go_forward(coordinates_x_y, player_watching);
                visited_cells.insert(coordinates_x_y);
            } break;
            case Operation::Backward: {
                coordinates_x_y = go_backward(coordinates_x_y, player_watching);
                visited_cells.insert(coordinates_x_y);
            } break;
            case Operation::Right: {
                player_watching = after_turn_right(player_watching);
            } break;
            case Operation::Left: {
                player_watching = after_turn_left(player_watching);
            } break;
            case Operation::Stats: {
                std::cout << "Player " << player_watching << " stands "
                          << abs(coordinates_x_y.first) << " away from OY, "
                          << abs(coordinates_x_y.second) << " away from OX. "
                          << visited_cells.size()
                          << " cell(s) has been visited.\n";
            } break;
            case Operation::Start_macro: {
                macros.clear();
                std::string macro_command;
                while (std::cin >> macro_command) {
                    if (macro_command == "end-macro") {
                        std::cout << "New macro of " << macros.size()
                                  << " command(s)\n";
                        break;
                    } else {
                        macros.push_back(macro_command);
                        std::cout << "Recorded\n";
                    }
                }
            } break;
            case Operation::Run_macro: {
                macros_output(
                    macros, player_watching, coordinates_x_y, visited_cells
                );
            } break;
        }
    }
    return 0;
}
