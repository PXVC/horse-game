#include <iostream>
#include <cstdlib>
#include <iomanip>
// #include <cmath>
#include <conio.h>
#include <time.h>
#define MAX 5

using namespace std;

void horLine(int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << " -------";
  }
  cout << endl;
}

void verLine(int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << "       |";
  }
  cout << endl;
}

int rollDice(int dice_rolls)
{
  return (rand() % (6 * dice_rolls - 1 + 1)) + 1;
}

void getSpiralMap(int size, int map[MAX])
{
  int top, left, bottom, right, k;
  int arr[size][size];
  k = 0;
  top = left = 0;
  bottom = right = size - 1;

  while (top <= bottom && left <= right)
  {
    for (int i = left; i <= right; i++)
    {
      arr[i][top] = k;
      k++;
    }
    top++;
    for (int i = top; i <= bottom; i++)
    {
      arr[right][i] = k;
      k++;
    }
    right--;
    for (int i = right; i >= left; i--)
    {
      arr[i][bottom] = k;
      k++;
    }
    bottom--;
    for (int i = bottom; i >= top; i--)
    {
      arr[left][i] = k;
      k++;
    }
    left++;
  }
  k = 0;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      map[k] = arr[i][j];
      k++;
    }
  }
}

void getZigZagMap(int size, int map[MAX])
{
  int k = 0;
  int arr[size][size];
  for (int i = 0; i < size; i++)
  {
    if (i % 2 == 0)
    {
      for (int j = 0; j < size; j++)
      {
        arr[i][j] = k;
        k++;
      }
    }
    else
    {
      for (int j = size - 1; j >= 0; j--)
      {
        arr[i][j] = k;
        k++;
      }
    }
  }
  k = 0;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      map[k] = arr[i][j];
      k++;
    }
  }
}

void printBoard(int size, char board[][MAX])
{
  horLine(size);
  for (int i = 0; i < size; i++)
  {
    cout << "|";
    verLine(size);
    cout << "|";
    for (int j = 0; j < size; j++)
    {
      // nếu ở ô đó có con ngựa thì -1 cho vòng lặp
      if (board[i][j] == '\0')
        for (int k = 0; k < (7 - sizeof(board[i][j])) / 2; k++)
          cout << " ";
      else
        for (int k = 0; k < ((7 - sizeof(board[i][j])) / 2) - 1; k++)
          cout << " ";

      cout << setw(2) << board[i][j];
      for (int k = 0; k < (7 - sizeof(board[i][j])) / 2; k++)
      {
        cout << " ";
      }
      cout << "|";
    }
    cout << "\n"
         << "|";
    verLine(size);
    horLine(size);
  }
}

int main()
{
  int n, choose, num_players, dice_rolls, num_horses, win_count[MAX] = {0};
  bool running = true, has_winner = false;

  while (running)
  {
    srand(time(0));

    system("cls");
    cout << "Enter map size: ";
    cin >> n;
    int map[n * n];
    char players[MAX];
    int horses[n][MAX] = {1};

    while (true)
    {
      cout << "Enter amount of dices (max 2): ";
      cin >> dice_rolls;
      if (dice_rolls > 0 && dice_rolls <= 2)
        break;
    }

    while (true)
    {
      cout << "Choose map style (spiral = 1, zigzag = 2): ";
      cin >> choose;
      if (choose == 1)
      {
        getSpiralMap(n, map);
        break;
      }
      else if (choose == 2)
      {
        getZigZagMap(n, map);
        break;
      }
    }

    while (true)
    {
      cout << "Enter amount of players (max 4): ";
      cin >> num_players;
      if (num_players > 0 && num_players <= 4)
        break;
    }

    cout << "Enter name for every player:" << endl;
    for (int i = 0; i < num_players; i++)
    {
      cin >> players[i];
    }

    cout << "Enter amount of horses (max 4): ";
    cin >> num_horses;
    for (int i = 0; i < num_players; i++)
    {
      for (int j = 0; j < num_horses; j++)
      {
        horses[i][j] = 0;
      }
    }

    while (!has_winner)
    {
      int steps, horse_count[MAX] = {0};

      for (int i = 0; i < num_players; i++)
      {
        for (int j = 0; j < num_horses; j++)
        {
          system("cls");
          char board[n][MAX] = {'\0'};
          if (horses[i][j] >= n * n - 1)
          {
            continue;
          }
          cout << "Press any key to roll dice" << endl;
          getch();
          steps = rollDice(dice_rolls);
          cout << players[i] << " rolled to " << steps << endl;

          if (horses[i][j] + steps > n * n - 1)
          {
            cout << players[i] << " no." << j + 1 << " horse is unable to move." << endl;
          }
          else if (horses[i][j] + steps == n * n - 1)
          {
            cout << players[i] << " no." << j + 1 << " horse has reached the final square." << endl;
            horses[i][j] += 999;
            horse_count[i]++;
          }
          else
          {
            cout << players[i] << " no." << j + 1 << " horse's moving " << steps << " steps forward." << endl;
            for (int k = 0; k < num_players; k++)
            {
              for (int l = 0; l < num_horses; l++)
              {
                if (horses[i][j] + steps == horses[k][l])
                {
                  cout << players[k] << " no." << l + 1 << " horse has been kicked." << endl;
                  horses[k][l] == 1;
                  break;
                }
              }
            }
            horses[i][j] += steps;
          }

          for (int k = 0; k < num_players; k++)
          {
            for (int l = 0; l < num_horses; l++)
            {
              for (int m = 0; m < n * n; m++)
              {
                if (horses[k][l] == map[m])
                {
                  board[m / n][m % n] = players[i];
                }
              }
            }
          }

          printBoard(n, board);
          cout << "Press any key to continue..." << endl;
          getch();

          if (horse_count[i] == num_horses)
          {
            cout << players[i] << " has won the game! GG!!" << endl;
            win_count[i]++;
            cout << players[i] << " win time: " << win_count[i] << endl;
            has_winner = true;
          }
        }
      }
    }
    cout << "\nThat was a cool game. Wanna play again?" << endl;
    cout << "Type 1 if yes" << endl;
    cout << "Type anything if no" << endl;
    cin >> choose;
    if (choose == 1)
    {
      running = true;
      has_winner = false;
    }
    else
    {
      running = false;
    }
  }
}