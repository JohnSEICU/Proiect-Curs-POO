// file posible words
// is valid
// reshuffle function


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream> // file reading
#include <ctime> // timer for the player to write the word

// litera mica - letter multiplier
// litera mare - word multiplier

// T 1 1 d 1 1 1 T 1 1 1 d 1 1 T
// 1 D 1 1 1 t 1 1 1 t 1 1 1 D 1
// 1 1 D 1 1 1 d 1 d 1 1 1 D 1 1
// d 1 1 D 1 1 1 d 1 1 1 D 1 1 d
// 1 1 1 1 D 1 1 1 1 1 D 1 1 1 1
// 1 t 1 1 1 t 1 1 1 t 1 1 1 t 1
// 1 1 d 1 1 1 d 1 d 1 1 1 d 1 1
// T 1 1 d 1 1 1 S 1 1 1 d 1 1 T
// 1 1 d 1 1 1 d 1 d 1 1 1 d 1 1
// 1 t 1 1 1 t 1 1 1 t 1 1 1 t 1
// 1 1 1 1 D 1 1 1 1 1 D 1 1 1 1
// d 1 1 D 1 1 1 d 1 1 1 D 1 1 d
// 1 1 D 1 1 1 d 1 d 1 1 1 D 1 1
// 1 D 1 1 1 t 1 1 1 t 1 1 1 D 1
// T 1 1 d 1 1 1 T 1 1 1 d 1 1 T

class Player
{
    public:
        int points;
        int pointCalculator(std::string word);

        subclass - word
            public:
                std::string word;
                boolean canBeUsed();
                void returnPlayerPoints();
};

class Board
{
    public:
        std::string type;
        int multiplier;
        boolean is_word; // ???
};

class Letter
{
    public:
        int value_of_letter;
        int count_of_letter;
        std::string letter;
};

void pointCalculator()
{
    if(is_word == true)
    {
        for(int i = 0 ; i < sizeof(word) ; i++)
        {
            sum = sum + litere.value_of_letter;
        }

        points = points + sum*multiplier;
    }
    else
    {
        for(int i = 0 ; i < sizeof(word) ; i++)
        {
            sum = sum + litere.value_of_letter*multiplier;
        }

        points = points + sum;
    }
}

int main()
{
    Player player1;
    Player player2;
    Player player3;
    Player player4;

    Board board[15][15]; // file reading - csv

    Letter litere[26]; // file reading - csv
    int total_letter_count;
}