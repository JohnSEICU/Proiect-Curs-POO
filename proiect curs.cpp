#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

int MAX_HEALTH = 3;
const int GAME_DURATION_MINUTES = 60;
const int QUESTION_DURATION_SECONDS = 120;

const std::vector <int> path_begin = 
{1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
const std::vector <int> path_end = 
{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 27, 28, 29, 30};
const std::vector <std::string> path_diretions = 
{"East", "North", "South", "East", "East", "North", "South", "West", "West", "North", "South", "East", "East", "East", "East", "East", "East", "South", "North", "South", "North", "East", "East", "East", "East", "South", "North", "East", "East", "East"};

class Room 
{
    private:
        
        std::string question;
        std::string answer;
        std::string hint;
        std::vector<std::string> exits;
        bool is_completed;
        bool is_end;

    public:
        //default constructor
        Room() = default;
        Room(std::string question, std::string answer, std::string hint, std::vector<std::string> exits, bool is_completed, bool is_end) : question(question), answer(answer), hint(hint), exits(exits), is_completed(is_completed), is_end(is_end) {}

        //gettes
        std::vector<std::string> getExits();
        std::string getQuestion();
        std::string getAnswer();
        std::string getHint();
        bool getIsCompleted();
        bool getIsEnd();

        //setters
        void setExits(std::vector<std::string> exits);
        void setQuestion(std::string question);
        void setAnswer(std::string answer);
        void setHint(std::string hint);
        void setIsCompleted(bool is_completed);
        void setIsEnd(bool is_end);

        // void printRoom();

        //default destructor
        ~Room() = default;

        friend class Map;
};


//getters implementation
std::vector<std::string> Room::getExits() 
{
    return exits;
}

std::string Room::getQuestion() 
{
    return question;
}

std::string Room::getAnswer() 
{
    return answer;
}

std::string Room::getHint() 
{
    return hint;
}

bool Room::getIsCompleted() 
{
    return is_completed;
}

bool Room::getIsEnd() 
{
    return is_end;
}

//setters implementation
void Room::setExits(std::vector<std::string> exits) 
{
    this->exits = exits;
}

void Room::setQuestion(std::string question) 
{
    this->question = question;
}

void Room::setAnswer(std::string answer) 
{
    this->answer = answer;
}

void Room::setHint(std::string hint) 
{
    this->hint = hint;
}

void Room::setIsCompleted(bool is_completed) 
{
    this->is_completed = is_completed;
}

void Room::setIsEnd(bool is_end) 
{
    this->is_end = is_end;
}

// *print method
// void Room::printRoom() 
// {
//     std::cout << "Question: " << question << std::endl;
//     std::cout << "Answer: " << answer << std::endl;
//     std::cout << "Hint: " << hint << std::endl;
//     std::cout << "Exits: ";
//     for(auto i : exits)
//         std::cout << i << " ";
//     std::cout << std::endl;
//     std::cout << "Is completed: " << is_completed << std::endl;
//     std::cout << "Is end: " << is_end << std::endl;
// }

//* operator<< overload for vector
// std::ostream& operator<<(std::ostream& os, std::vector <std::string> exits)
// {
//     for(auto i : exits)
//         std::cout << i << " ";

//     return os;
// }


class Map
{
    public:
        bool validMove(std::string move, std::vector<std::string> exits);
        int printRoom(Room room, int i);
        bool answerQuestion(std::string answer, std::string correct_answer, int &health, std::string hint, int &try_count);
        void showHint(std::string hint);
        int getMove(std::vector<std::string> exits, int i);

};

bool Map::validMove(std::string move, std::vector<std::string> exits) 
{
    auto it = find(exits.begin(), exits.end(), move);
    for(auto i : exits)
        if(it != exits.end())
            return true;
    return false;
}

int Map::printRoom(Room room, int i) 
{
    std::string move;
    std::string answer;
    int try_count = 0;
    if(room.is_completed == false)
    {
        std::cout << "Room " << i + 1 << std::endl;
        std::cout << "Question: " << room.question << std::endl;
        std::cout << "Answer: ";
        std::cin >> answer;
        room.is_completed = true;

        
        if(answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == true)
        {
            std::cout << "Correct answer!" << std::endl;
            room.is_completed = true;
            std::cout << "Exits: ";
            for(auto j : room.exits)
                std::cout << j << " ";
            std::cout << std::endl;


            i = getMove(room.exits, i);
        }
        else
        {   
            do
            {
                std::cout << "Wrong answer!" << std::endl;
                std::cout << "health: " << MAX_HEALTH << std::endl;
                std::cout << "Answer: ";
                std::cin >> answer;
                std::cout << try_count;
            } while (answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == false && MAX_HEALTH > 0);
        }
        
    }

    return i;
}

bool Map::answerQuestion(std::string answer, std::string correct_answer, int &health, std::string hint, int &try_count) 
{
    if(answer == correct_answer)
    {
        return true;
    }
    else
    {
        if(try_count == 0)
        {
            
            showHint(hint);
            try_count++;
            return false;
        }
        else
        {

            std::cout << "You have no more hints!" << std::endl;
            health--;
            return false;
        }

    }
}

void Map::showHint(std::string hint) 
{
    std::cout << "Hint: " << hint << std::endl;
}

int Map::getMove(std::vector<std::string> exits, int i) 
{   
    int pos;
    std::cout << "sunt in getMove" << std::endl;
    for(int k = 0; k < path_begin.size(); k++)
    {
        std::cout << "sunt in for pentru player pos" << std::endl;
        std::cout << i <<std::endl;
        if(i == path_begin.at(k))
        {
            std::cout << "det player move" << std::endl;
            pos = k;
            std:: cout << pos << " " << k << std::endl;
        }
    }

    int new_room;
    std::string move;
    std::cout << "Move: ";
    std::cin >> move;

    if(validMove(move, exits) == false)
    {
        do
        {
            std::cout << "Invalid move!" << std::endl;
            std::cout << "Move: ";
            std::cin >> move;
        } while(validMove(move, exits) == false);
    }

    for(int j = 0; j < path_begin.size(); j++)
    {
        std::cout << "sunt in for" << std::endl;
        if(move == path_diretions.at(j))
        {
            std::cout<<"path director"<<std::endl;
            std::cout << pos << " " << path_begin.at(j) << std::endl;
            if(pos == path_begin.at(j))
            {
                std::cout << "next room" << std::endl;
                return path_end.at(j)-1;
            }
        }
    }
}

int main()
{
    Map map;

    std::vector<Room> rooms;
    std::string question;
    std::string answer;
    std::string hint;
    std::vector <std::string> exits;
    bool is_completed;
    bool is_end;
    
    std::string aux;
    std::string row;
    std::ifstream fin;
    int room_count = -1;

    //filereading in vector
    fin.open("questions.csv");

    while(std::getline(fin, row))
    {
        std::stringstream sin(row);
        room_count++;

        std::getline(sin, aux, ',');
        question = aux;

        std::getline(sin, aux, ',');
        answer = aux;

        std::getline(sin, aux, ',');
        hint = aux;

        std::getline(sin, aux, ',');
        std::stringstream sin2(aux);
        while (std::getline(sin2, aux, ' ')) 
        {
            exits.push_back(aux);
        }

        std::getline(sin, aux, ',');
        is_completed = aux == "true" ? true : false;

        std::getline(sin, aux, ',');
        is_end = aux == "true" ? true : false;

        rooms.push_back(Room(question, answer, hint, exits, is_completed, is_end));

        exits.clear();
    }

    fin.close();

    //game loop
    //! TREBUIE SA RETURNZE POZITIA CAMEREI URMATOARE
    int i = 0;

    while(i < rooms.size() && MAX_HEALTH > 0)
    {
        i = map.printRoom(rooms[i], i);

        if(rooms[i].getIsEnd() == true)
        {
            std::cout << "You won!" << std::endl;
            return 0;
        }
    }

    std::cout << "You ran out of lives!" << std::endl;


    return 0;
}
