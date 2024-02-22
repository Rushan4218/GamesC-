#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>
#include <fstream>

void save_score(int count)
{   
    int prev_score;
    std::ifstream output_file("highscore.txt");
    output_file >> prev_score;
    int score = 10 - count;
    if(prev_score <= score)
    {
        std::ofstream input_file("highscore.txt");
        input_file << score;
        std::cout << "your score is " << score << std::endl;
    } 
    else std::cout << "your score is " << score << std::endl;
    
}

void see_score()
{
    system("cls");
    int score;
    std::ifstream file("highscore.txt");
    file >> score;
    std::cout << "The current high score is " << score << std::endl;
    int reset;
    std::cout << "Reset high score?"<< std::endl << "Yes[1] " << std::endl << "No[2]" << std::endl;
    std::cin >> reset;
    if(reset == 1)
    {
        score = 0;
        std::ofstream file("highscore.txt");
        file << score;
    }
    system("cls");
}
int menu(int secret_number)
{
    int play;
    std::cout << "Play[1]" << std::endl << "Quit[0]" << std::endl << "High score [2]" << std::endl;
    std::cin >>  play;
    return play; 
}
void play(int secret_number)
{
    int guess;
    std::vector<int> guesses;
    int count = 0;
    std::cout << "Guess the secret number, from 1 to 100" << std::endl;
    std::cin >> guess;
    guesses.push_back(guess);
    
    while(guess != secret_number)
    {
        count++;
        
        if(guess > secret_number)
        {
            system("cls");
            for(int n: guesses)
            {
                std::cout << n << "\t";
            }
            std::cout << std::endl;
            std::cout << "Go lower" << std::endl;
            std::cin >> guess;
            guesses.push_back(guess);
        }
        else if(guess < secret_number)
        {
            system("cls");
            for(int n: guesses)
            {
                std::cout << n << "\t";
            }
            std::cout << std::endl;            
            std::cout << "Go higher" << std::endl;
            std::cin >> guess;
            guesses.push_back(guess);
        }
        else
        {
            //do nothing
        }
       
        if(count == 9) break;
    }
    if(guess == secret_number) 
        {
            system("cls");
            for(int n: guesses)
            {
                std::cout << n << "\t";
            }
            std::cout << std::endl;
            std::cout << "You got it right! " << guess << " is the secret number and you got it in " << count + 1 << " tries." << std::endl;
            save_score(count);
    
        }
    else
    {
        std::cout << "Nice Try" << std::endl;
    }

}


int main()
{
    int again;
    start:
    srand(time(0));
    int secret_number = rand()%100 + 1;

    top:
    
    int decision = menu(secret_number);
    if(decision == 1) 
    {
        system("cls");
        play(secret_number);
    }
    else if(decision == 0)
    {
        std::cout << "Thanks for nothing." << std::endl;
        return 0;
    }
    else if(decision == 2)
    {
        see_score();
    }
    else
    {
        std::cout << "The term " << decision << " is not recognized. Please try again" << std::endl;
        goto top;
    }
    
    
    std::cout << "Play again?" << std::endl;
    goto start;
    return 0;
}