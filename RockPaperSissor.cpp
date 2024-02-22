#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include <cstring>
#include <vector>
#include <conio.h>

int menu()
{
    int decision;
    std::cout << "Play[1]" << "\n" << "Quit[0]" << std::endl;
    std::cin >> decision;
    system("cls");
    return decision;

}
std::string computer_choice_generator(std::vector<std::string> choice)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    int index = dist(generator);
    return choice[index];
}
char play()
{
    char move;
    std::cout << "What is your move?\n" << "Rock[R]\n" << "Paper[P]\n" << "Sissor[S]" << std::endl;
    std::cin >> move;
    return move;
}
void result(char move, std::string computer_choice, int & player_score, int & computer_score)
{
    switch(move)
    {
        case 'R':
            if(computer_choice == "Rock")
            {
                std::cout << "Your choice: Rock\n" << "Computer's choice: Rock\n";
                std::cout << "Draw!\n";
                computer_score++;
                player_score++;   
            }
            else if(computer_choice == "Paper")
            {
                std::cout << "Your choice: Rock\n" << "Computer's choice: Paper\n";
                std::cout << "You lost!\n";
                computer_score++;
            }
            else 
            {
                std::cout << "Your choice: Rock\n" << "Computer's choice: Sissors\n";
                std::cout << "You win!\n";
                player_score++;
            }
            break;
       case 'P':
            if(computer_choice == "Rock")
            {
                std::cout << "Your choice: Paper\n" << "Computer's choice: Rock\n";
                std::cout << "You win!\n";
                player_score++;
            }
            else if(computer_choice == "Paper")
            {
                std::cout << "Your choice: Paper\n" << "Computer's choice: Paper\n";
                std::cout << "Draw!\n";
                player_score++;
                computer_score++;
            }
            else 
            {
                std::cout << "Your choice: Paper\n" << "Computer's choice: Sissors\n";
                std::cout << "You lost!\n";
                computer_score++;
            }
            break;            
       case 'S':
            if(computer_choice == "Rock")
            {
                std::cout << "Your choice: Sissors\n" << "Computer's choice: Rock\n";
                std::cout << "You lost\n";
                computer_score++;   
            }
            else if(computer_choice == "Paper")
            {
                std::cout << "Your choice: Sissors\n" << "Computer's choice: Paper\n";
                std::cout << "You win!\n";
                player_score++;
            }
            else 
            {
                std::cout << "Your choice: Sissors\n" << "Computer's choice: Sissors\n";
                std::cout << "Draw!\n";
                computer_score++;
                player_score++;
            }
            break;
    }
}
void final_result(int computer_score, int player_score)
{
    int show;

    std::cout << "Show final result[1]/ Exit directly[0]: ";
    std::cin >> show;
    while(show != 1 && show != 0)
    {
        std::cout << "Enter a valid number.\n";
        std::cout << "Show final result[1]/ Exit directly[0]: ";
        std::cin >> show;
    }
    if(show == 1)
    {
        system("cls");
        if(computer_score > player_score)
        {
            std::cout << "You lost the game\n";
        }
        else if(computer_score < player_score)
        {
            std::cout << "You won the game\n";
        }
        else 
        {
            std::cout << "Draw!\n";
        }

        std::cout << "FINAL SCORE\n";
        std::cout << "player's score: " << player_score << "\n";
        std::cout << "Computer's score: " << computer_score << "\n";
    }
    else if(show == 0) exit(0);
}
int main()
{
    std::vector<std::string> choice = {"Rock", "Paper", "Sissor"};
    int decision = menu();
    char move;
    std::string computer_choice;
    int computer_score = 0, player_score = 0;

    int round = 1;
    while(round != 6)
    {
        if(computer_score == 3 || player_score == 3) break;
        if(decision == 1) 
        {
            computer_choice = computer_choice_generator(choice);                move = std::toupper(play());
        }
        else if(decision == 0) 
        {
            std::cout << "Thanks for nothing.";
            return 0;
        }

        while(move != 'R' && move != 'P' && move != 'S')
        {
            std::cout << "Enter a valid move." << std::endl;
            move = std::toupper(play());
        }
        system("cls");
        result(move, computer_choice, player_score, computer_score);
        round++;
    }
    final_result(computer_score, player_score);
        
    std::cout << "Press any key to exit.";
    getch();
    return 0;
}