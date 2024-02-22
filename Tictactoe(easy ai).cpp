#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cctype>
#include <ctime>

void drawIndexBoard();
void drawBoard(char board[3][3]);
int takePlayerInput();
bool chkValid(int, char board[3][3]);
int takeComputerInput(char board[3][3]);
int minimax(char board[3][3], bool);
void putMark(char board[3][3], int, char);
int evalBoard(char board[3][3], bool & isGameOver);
bool chkDraw(char board[3][3]);

int main()
{
    int score;
    char board[3][3];
    bool playerTurn = true;
    char mark;
    int input;
    bool isGameOver = false;
    bool isDraw;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
    drawIndexBoard();
    drawBoard(board);

    do
    {
        if(playerTurn)
        {
            mark = 'X';
            do
            {
                input = takePlayerInput();
            } while(!chkValid(input, board));
            playerTurn = false;
        }
        else
        {
            std::chrono::seconds sec = std::chrono::seconds(1);
            std::this_thread::sleep_for(sec);
            mark = 'O';
            input = takeComputerInput(board);
            playerTurn = true;
        }
        putMark(board, input, mark);
        drawBoard(board);
        score = evalBoard(board, isGameOver);
        if(score == 1)
        {
            std::cout << "O wins.\n";
            isGameOver = true;
            return 0;
        }
        else if(score == -1)
        {
            isGameOver = true;
            std::cout << "X wins.\n";
            return 0;
        }
        else if(score == 0)
        {
            if(chkDraw(board)) 
            {
                isGameOver = true;
                std::cout << "Draw\n";
                return 0;
            }
        }
    } while (!isGameOver);
    return 0;
}

void drawIndexBoard()
{
    std::cout << "\033[2J\033[0;0H";
    std::cout << "\033[2J\033[0;0H";
    std::cout << "  1 | 2  | 3  \n";
    std::cout << "----|----|----\n";
    std::cout << "  4 | 5  | 6  \n";
    std::cout << "----|----|----\n";
    std::cout << "  7 | 8  | 9  \n";
}

void drawBoard(char board[3][3])
{
    std::cout << "\033[7;0H\033[J";
    std::cout << "  "<< board[0][0] << " | " << board[0][1] << "  | "<< board[0][2] <<" \n";
    std::cout << "----|----|----\n";
    std::cout << "  " << board[1][0] << " | " <<  board[1][1] << "  | " << board[1][2] << " \n";
    std::cout << "----|----|----\n";
    std::cout << "  " << board[2][0] << " | " << board[2][1] << "  | " << board[2][2] << " \n";
}

int takePlayerInput()
{
    int input;
    std::cout << "Enter index:\n";
    std::cin >> input;
    return input;
}

bool chkValid(int input, char board[3][3])
{
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            count++;
            if(count == input && board[i][j] != ' ') return false;
        }
    }
    return true;
}

int takeComputerInput(char board[3][3])
{
    int bestScore = -10;
    int count = 0;
    int index;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            count++;
            if(board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int score = minimax(board, false);
                board[i][j] = ' ';
                if(score > bestScore)
                {
                    bestScore = score;
                    index = count;
                }
            }
        }
    }
    return index;
}

int minimax(char board[3][3], bool isMax)
{
    bool gameOver = false;
    if(chkDraw(board)) return 0;
    int score = evalBoard(board, gameOver);
    if(score == 1 || score == -1) gameOver = true;
    if(gameOver) return score;
    char mark;
    int bestScore;
    
    if(isMax)
    {
        bestScore = -10;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    score = minimax(board, !isMax);
                    board[i][j] = ' ';
                }
                bestScore = std::max(score, bestScore);
            }   
        }
        return bestScore;
    }
    else
    {
        bestScore = 10;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    score = minimax(board, !isMax);
                    board[i][j] = ' ';
                }
                bestScore = std::min(score, bestScore);
            }
        }
        return bestScore;
    }
}
void putMark(char board[3][3], int input, char mark)
{
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            count++;
            if(input == count)
            {
                if(board[i][j] == ' ') board[i][j] = mark;
            }
        }
    }
}

int evalBoard(char board[3][3], bool & isGameOver)
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if(board[i][0] == 'X') 
            {
                isGameOver = true;
                return -1;
            }
            else if(board[i][0] == 'O')
            {
                isGameOver = true;
                return 1;
            }
        }

        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if(board[0][i] == 'X') 
            {
                isGameOver = true;
                return -1;
            }
            else if(board[0][i] == 'O')
            {
                isGameOver = true;
                return 1;
            
            }
        }
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0] == 'X') 
        {
            isGameOver = true;
            return -1;
        }
        else if(board[0][0] == 'O')
        {
            isGameOver = true;
            return 1;
        }
    }
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2])
    {
        if(board[2][0] == 'X') 
        {
            isGameOver = true;
            return -1;
        }
        else if(board[2][0] == 'O')
        {
            isGameOver = true;
            return 1;
        }
    }
    return 0;
}

bool chkDraw(char board[3][3])
{
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ') count++;
        }
    }
    if(count == 9) return true;
    return false;
}