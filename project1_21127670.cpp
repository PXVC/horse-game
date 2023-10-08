#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
// basics
int verline(int size)
{
    for (int i = 0; i <= size - 1; i++)
    {
        cout << "        |";
    }
    cout << endl;
    return 0;
}
int horline(int size)
{
    for (int i = 0; i <= size - 1; i++)
    {
        cout << " --------";
    }
    cout << endl;
    return 0;
}
int SetBoard(char board[][5], int size, int numplayer, int p_pos[][100], char p_name[][5], int horse_num)
{
    for (int i = 0; i < size * size; i++)
    {
        memcpy(board[i], "    ", 5);
    }
    for (int i = 0; i < numplayer; i++)
    {
        for (int j = 0; j < horse_num; j++)
        {
            if (p_pos[i][j] != -1)
            {
                memcpy(board[p_pos[i][j]], p_name[i], 5);
            }
        }
    }
    return 0;
}

// 3x3play
int map_3x3_z[3][3] = {{0, 1, 2}, {5, 4, 3}, {6, 7, 8}};
int map_3x3_s[3][3] = {{0, 1, 2}, {7, 8, 3}, {6, 5, 4}};
int printboard3x3(char board[][5], int size, int map[][3])
{

    for (int i = 0; i < size; i++)
    {
        horline(size);
        cout << "|";
        verline(size);
        cout << "|";
        for (int j = 0; j < size; j++)
        {
            cout << "  " << board[map[i][j]] << "  |";
        }
        cout << "\n"
             << "|";
        verline(size);
        horline(size);
    }
    return 0;
}
void PlayGame3x3(char board[][5], int size, int numplayer, int p_pos[][100], char p_name[][5], int map[][3], int horse_num, int dice)
{
    int horse_winner[numplayer]; // number of horses which cross the finishing line
    int win_count[numplayer];    // how many times a player have wins
    for (int i = 0; i < numplayer; i++)
    {
        win_count[i] = 0;
    }
    int option;
    int gameplayed = 0; // number of games played
    int winner = -1;
    int move;
    while (option != 0)
    {
        // reset winning condition
        for (int i = 0; i < numplayer; i++)
        {
            horse_winner[i] = -1;
        }
        // reset steps
        for (int i = 0; i < numplayer; i++)
        {
            for (int j = 0; j < horse_num; j++)
            {
                p_pos[i][j] = -1;
            }
        }

        while (winner == -1)
        {
            std::system("cls");
            for (int i = 0; i < numplayer; i++)
            {
                for (int g = 0; g < horse_num; g++)
                {
                    if (p_pos[i][g] > size * size - 1)
                    {
                        continue;
                    }
                    move = rand() % dice + 1; // roll dice
                    cout << p_name[i] << "'s " << g + 1 << " horse"
                         << " moved " << move << "steps." << endl; // move
                    if (p_pos[i][g] + move > size * size - 1)
                    {
                        cout << p_name[i] << "'s " << g + 1 << " horse is unable to move." << endl;
                    } // check valid
                    else
                    {
                        p_pos[i][g] = p_pos[i][g] + move;
                        cout << p_name[i] << "'s " << g + 1 << " horse"
                             << " moved forward." << endl;
                        if (p_pos[i][g] == size * size - 1)
                        {
                            horse_winner[i] = horse_winner[i] + 1;
                        } // check horse cross finish line
                        for (int j = 0; j < numplayer; j++)
                        {
                            for (int e = 0; e < horse_num; e++)
                            {
                                if (p_pos[i][g] == p_pos[j][e] && i != j)
                                {
                                    p_pos[j][e] = -1;
                                    cout << p_name[j] << " was kicked by " << p_name[i] << endl;
                                    break;
                                } // kick
                            }
                        }
                    }
                    if (p_pos[i][g] >= size * size - 1 && p_pos[i][g] != 9)
                    {
                        p_pos[i][g] = 9; // remove horse that cross finish line from game
                    }
                }
                if (horse_winner[i] == horse_num - 1)
                {
                    winner = i;
                    cout << "player " << i + 1 << " winned the game!" << endl;
                    win_count[i] += 1;
                    gameplayed += 1;
                } // check winner
            }
            SetBoard(board, size, numplayer, p_pos, p_name, horse_num);
            printboard3x3(board, size, map);
            getch();
        }
        winner = -1;
        cout << "Total game played:" << gameplayed << endl;
        for (int i = 0; i < numplayer; i++)
        {
            cout << "player " << i + 1 << " has won " << win_count[i] << "games" << endl; // statistical display
        }
        cout << "\n"
             << "\n"
             << "Do you wish to continue, if so, press any keys aside '0':"; // replay
        cin >> option;
    }
}

// 5x5play
int map_5x5_s[5][5] = {{0, 1, 2, 3, 4}, {15, 16, 17, 18, 5}, {14, 23, 24, 19, 6}, {13, 22, 21, 20, 7}, {12, 11, 10, 9, 8}};
int map_5x5_z[5][5] = {{0, 1, 2, 3, 4}, {9, 8, 7, 6, 5}, {10, 11, 12, 13, 14}, {19, 18, 17, 16, 15}, {20, 21, 22, 23, 24}};
int printboard5x5(char board[][5], int size, int map[][5])
{

    for (int i = 0; i < size; i++)
    {
        horline(size);
        cout << "|";
        verline(size);
        cout << "|";
        for (int j = 0; j < size; j++)
        {
            cout << "  " << board[map[i][j]] << "  |";
        }
        cout << "\n"
             << "|";
        verline(size);
        horline(size);
    }
    return 0;
}
void PlayGame5x5(char board[][5], int size, int numplayer, int p_pos[][100], char p_name[][5], int map[][5], int horse_num, int dice)
{
    int horse_winner[numplayer]; // number of horses which cross the finishing line
    int win_count[numplayer];    // how many times a player have wins
    for (int i = 0; i < numplayer; i++)
    {
        win_count[i] = 0;
    }
    int option;
    int gameplayed = 0; // number of games played
    int winner = -1;
    int move;
    while (option != 0)
    {
        // reset winning condition
        for (int i = 0; i < numplayer; i++)
        {
            horse_winner[i] = -1;
        }
        // reset steps
        for (int i = 0; i < numplayer; i++)
        {
            for (int j = 0; j < horse_num; j++)
            {
                p_pos[i][j] = -1;
            }
        }

        while (winner == -1)
        {
            std::system("cls");
            for (int i = 0; i < numplayer; i++)
            {
                for (int g = 0; g < horse_num; g++)
                {
                    if (p_pos[i][g] > size * size - 1)
                    {
                        continue;
                    }
                    move = rand() % dice + 1; // roll dice
                    cout << p_name[i] << "'s " << g + 1 << " horse"
                         << " moved " << move << "steps." << endl; // move
                    if (p_pos[i][g] + move > size * size - 1)
                    {
                        cout << p_name[i] << "'s " << g + 1 << " horse is unable to move." << endl;
                    } // check valid
                    else
                    {
                        p_pos[i][g] = p_pos[i][g] + move;
                        cout << p_name[i] << "'s " << g + 1 << " horse"
                             << " moved forward." << endl;
                        if (p_pos[i][g] == size * size - 1)
                        {
                            horse_winner[i] = horse_winner[i] + 1;
                        } // check horse cross finish line
                        for (int j = 0; j < numplayer; j++)
                        {
                            for (int e = 0; e < horse_num; e++)
                            {
                                if (p_pos[i][g] == p_pos[j][e] && i != j)
                                {
                                    p_pos[j][e] = -1;
                                    cout << p_name[j] << " was kicked by " << p_name[i] << endl;
                                    break;
                                } // kick
                            }
                        }
                    }
                    if (p_pos[i][g] >= size * size - 1)
                    {
                        p_pos[i][g] = 25; // remove horse that cross finish line from game
                    }
                }
                if (horse_winner[i] == horse_num - 1)
                {
                    winner = i;
                    cout << "player " << i + 1 << " winned the game!" << endl;
                    win_count[i] += 1;
                    gameplayed += 1;
                } // check winner
            }
            SetBoard(board, size, numplayer, p_pos, p_name, horse_num);
            printboard5x5(board, size, map);
            getch();
        }
        winner = -1;
        cout << "Total game played:" << gameplayed << endl;
        for (int i = 0; i < numplayer; i++)
        {
            cout << "player " << i + 1 << " has won " << win_count[i] << "games" << endl; // statistical display
        }
        cout << "\n"
             << "\n"
             << "Do you wish to continue, if so, press any keys aside '0':"; // replay
        cin >> option;
    }
}
// 7x7play
int map_7x7_z[7][7] = {{0, 1, 2, 3, 4, 5, 6}, {13, 12, 11, 10, 9, 8, 7}, {14, 15, 16, 17, 18, 19, 20}, {27, 26, 25, 24, 23, 22, 21}, {28, 29, 30, 31, 32, 33, 34}, {41, 40, 39, 38, 37, 36, 35}, {42, 43, 44, 45, 46, 47, 48}};
int map_7x7_s[7][7] = {{0, 1, 2, 3, 4, 5, 6}, {23, 24, 25, 26, 27, 28, 7}, {22, 39, 40, 41, 42, 29, 8}, {21, 38, 47, 48, 43, 30, 9}, {20, 37, 46, 45, 44, 31, 10}, {19, 36, 35, 34, 33, 32, 11}, {18, 17, 16, 15, 14, 13, 12}};
int printboard7x7(char board[][5], int size, int map[][7])
{
    for (int i = 0; i < size; i++)
    {
        horline(size);
        cout << "|";
        verline(size);
        cout << "|";
        for (int j = 0; j < size; j++)
        {
            cout << "  " << board[map[i][j]] << "  |";
        }
        cout << "\n"
             << "|";
        verline(size);
        horline(size);
    }
    return 0;
}
void PlayGame7x7(char board[][5], int size, int numplayer, int p_pos[][100], char p_name[][5], int map[][7], int horse_num, int dice)
{
    int horse_winner[numplayer]; // number of horses which cross the finishing line
    int win_count[numplayer];    // how many times a player have wins
    for (int i = 0; i < numplayer; i++)
    {
        win_count[i] = 0;
    }
    int option;
    int gameplayed = 0; // number of games played
    int winner = -1;
    int move;
    while (option != 0)
    {
        // reset winning condition
        for (int i = 0; i < numplayer; i++)
        {
            horse_winner[i] = -1;
        }
        // reset steps
        for (int i = 0; i < numplayer; i++)
        {
            for (int j = 0; j < horse_num; j++)
            {
                p_pos[i][j] = -1;
            }
        }

        while (winner == -1)
        {
            std::system("cls");
            for (int i = 0; i < numplayer; i++)
            {
                for (int g = 0; g < horse_num; g++)
                {
                    if (p_pos[i][g] > size * size - 1)
                    {
                        continue;
                    }
                    move = rand() % dice + 1; // roll dice
                    cout << p_name[i] << "'s " << g + 1 << " horse"
                         << " moved " << move << "steps." << endl; // move
                    if (p_pos[i][g] + move > size * size - 1)
                    {
                        cout << p_name[i] << "'s " << g + 1 << " horse is unable to move." << endl;
                    } // check valid
                    else
                    {
                        p_pos[i][g] = p_pos[i][g] + move;
                        cout << p_name[i] << "'s " << g + 1 << " horse"
                             << " moved forward." << endl;
                        if (p_pos[i][g] == size * size - 1)
                        {
                            horse_winner[i] = horse_winner[i] + 1;
                        } // check horse cross finish line
                        for (int j = 0; j < numplayer; j++)
                        {
                            for (int e = 0; e < horse_num; e++)
                            {
                                if (p_pos[i][g] == p_pos[j][e] && i != j)
                                {
                                    p_pos[j][e] = -1;
                                    cout << p_name[j] << " was kicked by " << p_name[i] << endl;
                                    break;
                                } // kick
                            }
                        }
                    }
                    if (p_pos[i][g] >= size * size - 1)
                    {
                        p_pos[i][g] = 49; // remove horse that cross finish line from game
                    }
                }
                if (horse_winner[i] == horse_num - 1)
                {
                    winner = i;
                    cout << "player " << i + 1 << " winned the game!" << endl;
                    win_count[i] += 1;
                    gameplayed += 1;
                } // check winner
            }
            SetBoard(board, size, numplayer, p_pos, p_name, horse_num);
            printboard7x7(board, size, map);
            getch();
        }
        winner = -1;
        cout << "Total game played:" << gameplayed << endl;
        for (int i = 0; i < numplayer; i++)
        {
            cout << "player " << i + 1 << " has won " << win_count[i] << "games" << endl; // statistical display
        }
        cout << "\n"
             << "\n"
             << "Do you wish to continue, if so, press any keys aside '0':"; // replay
        cin >> option;
    }
}
// 9x9play
int map_9x9_z[9][9] = {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {17, 16, 15, 14, 13, 12, 11, 10, 9}, {18, 19, 20, 21, 22, 23, 24, 25, 26}, {35, 34, 33, 32, 31, 30, 29, 28, 27}, {36, 37, 38, 39, 40, 41, 42, 43, 44}, {53, 52, 51, 50, 49, 48, 47, 46, 45}, {54, 55, 56, 57, 58, 59, 60, 61, 62}, {71, 70, 69, 68, 67, 66, 65, 64, 63}, {72, 73, 74, 75, 76, 77, 78, 79, 80}};
int map_9x9_s[9][9] = {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {31, 32, 33, 34, 35, 36, 37, 38, 9}, {30, 55, 56, 57, 58, 59, 60, 39, 10}, {29, 54, 71, 72, 73, 74, 61, 40, 11}, {28, 53, 70, 79, 80, 75, 62, 41, 12}, {27, 52, 69, 78, 77, 76, 63, 42, 13}, {26, 51, 68, 67, 66, 65, 64, 43, 14}, {25, 50, 49, 48, 47, 46, 45, 44, 15}, {24, 23, 22, 21, 20, 19, 18, 17, 16}};
int printboard9x9(char board[][5], int size, int map[][9])
{

    for (int i = 0; i < size; i++)
    {
        horline(size);
        cout << "|";
        verline(size);
        cout << "|";
        for (int j = 0; j < size; j++)
        {
            cout << "  " << board[map[i][j]] << "  |";
        }
        cout << "\n"
             << "|";
        verline(size);
        horline(size);
    }
    return 0;
}
void PlayGame9x9(char board[][5], int size, int numplayer, int p_pos[][100], char p_name[][5], int map[][9], int horse_num, int dice)
{
    int horse_winner[numplayer]; // number of horses which cross the finishing line
    int win_count[numplayer];    // how many times a player have wins
    for (int i = 0; i < numplayer; i++)
    {
        win_count[i] = 0;
    }
    int option;
    int gameplayed = 0; // number of games played
    int winner = -1;
    int move;
    while (option != 0)
    {
        // reset winning condition
        for (int i = 0; i < numplayer; i++)
        {
            horse_winner[i] = -1;
        }
        // reset steps
        for (int i = 0; i < numplayer; i++)
        {
            for (int j = 0; j < horse_num; j++)
            {
                p_pos[i][j] = -1;
            }
        }
        std::system("cls");
        while (winner == -1)
        {
            for (int i = 0; i < numplayer; i++)
            {
                for (int g = 0; g < horse_num; g++)
                {
                    if (p_pos[i][g] > size * size - 1)
                    {
                        continue;
                    }
                    move = rand() % dice + 1; // roll dice
                    cout << p_name[i] << "'s " << g + 1 << " horse"
                         << " moved " << move << "steps." << endl; // move
                    if (p_pos[i][g] + move > size * size - 1)
                    {
                        cout << p_name[i] << "'s " << g + 1 << " horse is unable to move." << endl;
                    } // check valid
                    else
                    {
                        p_pos[i][g] = p_pos[i][g] + move;
                        cout << p_name[i] << "'s " << g + 1 << " horse"
                             << " moved forward." << endl;
                        if (p_pos[i][g] == size * size - 1)
                        {
                            horse_winner[i] = horse_winner[i] + 1;
                        } // check horse cross finish line
                        for (int j = 0; j < numplayer; j++)
                        {
                            for (int e = 0; e < horse_num; e++)
                            {
                                if (p_pos[i][g] == p_pos[j][e] && i != j)
                                {
                                    p_pos[j][e] = -1;
                                    cout << p_name[j] << " was kicked by " << p_name[i] << endl;
                                    break;
                                } // kick
                            }
                        }
                    }
                    if (p_pos[i][g] >= size * size - 1)
                    {
                        p_pos[i][g] = 81; // remove horse that cross finish line from game
                    }
                }
                if (horse_winner[i] == horse_num - 1)
                {
                    winner = i;
                    cout << "player " << i + 1 << " winned the game!" << endl;
                    win_count[i] += 1;
                    gameplayed += 1;
                } // check winner
            }
            SetBoard(board, size, numplayer, p_pos, p_name, horse_num);
            printboard9x9(board, size, map);
            getch();
        }
        winner = -1;
        cout << "Total game played:" << gameplayed << endl;
        for (int i = 0; i < numplayer; i++)
        {
            cout << "player " << i + 1 << " has won " << win_count[i] << "games" << endl; // statistical display
        }
        cout << "\n"
             << "\n"
             << "Do you wish to continue, if so, insert any keys aside '0':"; // replay
        cin >> option;
    }
}

int main()
{
    // Title slide
    cout << " __    __    ______   .______          _______. _______      _______      ___      .___  ___.  _______ \n";
    cout << "|  |  |  |  /  __  |  |   _   |       /       ||   ____|    /  _____|    /   |     |   |/   | |   ____|\n";
    cout << "|  |__|  | |  |  |  | |  |_)  |      |   (----`|  |__      |  |  __     /  ^  |    |  || /  | |  |__   \n";
    cout << "|   __   | |  |  |  | |      /        |   |    |   __|     |  | |_ |   /  /_|  |   |  ||/|  | |   __|  \n";
    cout << "|  |  |  | |  `--'  | |  ||  |----.----)   |   |  |____    |  |__| |  /  _____  |  |  |  |  | |  |____ \n";
    cout << "|__|  |__|  |______/  | _| `._____|_______/    |_______|    |______| /__/     |__| |__|  |__| |_______|\n";
    srand(time(0));
    cout << "\n\n\n";
    cout << "INTRODUCTION";
    cout << "The rule of this game is straightforward, it imitate the classic board game \"Horse Race.\" There \n";
    cout << "will be a board and a predetermined amount of horses for playing. Each player takes turns to \n";
    cout << "roll the dice; the number rolled is equivalent to the number of steps the horse can move. To \n";
    cout << "win, players have to move all of their horses to the finishing line.\n";
    cout << "\n\n\n";
    // change color
    char color_scheme;
    cout << "LET'S PLAY HORSE GAME !!!" << endl;
    cout << "But first, are you okay with this color scheme? The option are:"
         << "\n";
    cout << "        a.black text, white backgroud\n";
    cout << "        b.white text, blue background\n";
    cout << "        c.green text, black background\n";
    cout << "        else. default white text, black background\n";
    cout << "Please, decide:\n";
    cin >> color_scheme;
    switch (color_scheme)
    {
    case 'a':
    case 'A':
        system("color 70");
        break;
    case 'b':
    case 'B':
        system("color 17");
        break;
    case 'c':
    case 'C':
        system("color 02");
    default:
        break;
    }

    cout << "GAME SETTING:\n";
    // board size
    int size;
    cout << "Insert the board's size (3,5,7,9): ";
    cin >> size;

    // dice range
    int dice;
    cout << "Dice range(or the maximum steps the horses can move):";
    cin >> dice;
    // player number
    int numplayer;
    cout << "Insert the number of player:";
    cin >> numplayer;

    // horse cage
    int horse_num;
    cout << "How many horses are they going to have? (can only have less than 100):";
    cin >> horse_num;

    // players names and set player original position
    char p_name[numplayer][5];
    for (int i = 0; i < numplayer; i++)
    {
        cout << "Enter the name of player" << i + 1 << " (have to be 4 characters): ";
        cin >> p_name[i];
    }

    int p_pos[numplayer][100];
    for (int i = 0; i < numplayer; i++)
    {
        for (int j = 0; j < horse_num; j++)
        {
            p_pos[i][j] = -1;
        }
    }

    // board
    char board[size * size][5];

    // playtime
    char style;
    cout << "Choose what kind of map you want to play in(spiral(s) or zigzag(z)):" << endl;
    cin >> style;
    switch (style)
    {
    case 's':
    case 'S':
    {
        switch (size)
        {
        case 3:
        {
            PlayGame3x3(board, size, numplayer, p_pos, p_name, map_3x3_s, horse_num, dice);
            break;
        }
        case 5:
        {
            PlayGame5x5(board, size, numplayer, p_pos, p_name, map_5x5_s, horse_num, dice);
            break;
        }
        case 7:
        {
            PlayGame7x7(board, size, numplayer, p_pos, p_name, map_7x7_s, horse_num, dice);
            break;
        }
        case 9:
        {
            PlayGame9x9(board, size, numplayer, p_pos, p_name, map_9x9_s, horse_num, dice);
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'z':
    case 'Z':
    {
        switch (size)
        {
        case 3:
        {
            PlayGame3x3(board, size, numplayer, p_pos, p_name, map_3x3_z, horse_num, dice);
            break;
        }
        case 5:
        {
            PlayGame5x5(board, size, numplayer, p_pos, p_name, map_5x5_z, horse_num, dice);
            break;
        }
        case 7:
        {
            PlayGame7x7(board, size, numplayer, p_pos, p_name, map_7x7_z, horse_num, dice);
            break;
        }
        case 9:
        {
            PlayGame9x9(board, size, numplayer, p_pos, p_name, map_9x9_z, horse_num, dice);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    cout << "\n";
    cout << "THAT'S IT, HOPE YOU HAD FUN, THANK YOU FOR PLAYING MY GAME, SEE YOU NEXT TIME!" << endl;
}
// Howkteam
// Stackoverflow
// w3school
// Starting out with c++