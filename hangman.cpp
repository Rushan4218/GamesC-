#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <string>
#include <cctype>

class HangmanGame
{   
    private:
        std::vector<std::string> words;
        std::string word;
        std::string currentState;
        char guess;
        int count;
        std::set<char> guessedLetters;
        int maxWrongGuesses;
        int currentWrongGuesses;
        bool gameOver;

        void drawBoard()
        {
            std::cout << "Guess the word:\t\t\tGuessed Letters:\n";
            std::cout << "\n";
            for(int i = 0; i < currentState.size(); i++)
            {
                currentState[i] = '_';
            }
            std::cout << currentState << "\n\t\t\t\t|___\n";
            std::cout << "\t\t\t\t|\n";
            std::cout << "\t\t\t\t|\n";
            std::cout << "\t\t\t\t|\n";
            std::cout << "\t\t\t\t|\n";

        }   
        
        void makeGuess()
        {
            std::cout << "\033[9;1H";
            for(int i = 0; i < 80; i++) std::cout << " ";
            std::cout << "\033[9;1H";
            std::cin >> guess;
            if(isalpha(guess)) guessedLetters.insert(guess);
        }
        
        void chkGuess()
        {
            count = 0;
            if(isalpha(guess))
            {
            for(int i = 0; i < word.size(); i++)
            {
                if(word[i] == guess)
                {
                    currentState[i] = guess;
                    count++;
                }
            }
            }
            else
            { 
                std::cout << "Please enter an alphabet character.\n";
                makeGuess();
                chkGuess();
            }
            

        }

        void updateBoard()
        {
            //system("cls");
            std::cout << "\033[2J\033[0;0H";
            std::cout << "Guess the word:\t\t\tGuessed Letters:";
            for(char guessedLetter: guessedLetters)
            {
                std::cout << " " << guessedLetter; 
            }
            std::cout << "\n";
            std::cout << "\n";
            std::cout << currentState << "\n";

            switch(currentWrongGuesses)
            {
                case 0:
                    std::cout << "\t\t\t\t|___\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 1:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 2:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|   |\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 3:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|  /|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 4:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|  /|\\\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 5:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|  /|\\\n";
                    std::cout << "\t\t\t\t|  /\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n";
                    break;
                case 6:
                    std::cout << "\t\t\t\t|___O\n";
                    std::cout << "\t\t\t\t|  /|\\\n";
                    std::cout << "\t\t\t\t|  / \\\n";
                    std::cout << "\t\t\t\t|\n";
                    std::cout << "\t\t\t\t|\n"; 
            }
        }
    public:
        HangmanGame()
        {
            srand(std::chrono::system_clock::now().time_since_epoch().count());
            words = 
            {
                "watermelon", "cheesecake", "muffin", "doughnut", "strawberry",
                "crackers", "mango", "onion", "gingerbread", "butterfly", "elephant", "pumpkin", "villager", "mahine"
            };
            int index = rand()% (words.size() - 1);
            word = words[index];
            currentState = word;
            guess = ' ';
            guessedLetters.clear();
            maxWrongGuesses = 6;
            currentWrongGuesses = 0;
            gameOver = false;
        }




        void playGame()
        {
            std::cout << "\033[2J\033[1;1H";
            drawBoard();
            while(currentWrongGuesses != 6)
            {
                makeGuess();
                chkGuess();
                if(count == 0) currentWrongGuesses++;
                updateBoard();
                if(currentState == word)
                {
                    std::cout << "You got it.";
                    break;
                }
            }
            if(currentWrongGuesses == 6)
            {
                std::cout << "You lost. The word is " << word << "\n";
            }
        }
};
int main()
{
    int again = 1;
    while(again == 1) 
    {
        HangmanGame Game;
        Game.playGame();
        std::cout << "Play again?[1]\nExit[Any key]\n";
        std::cin >> again;
    }
    return 0;
}