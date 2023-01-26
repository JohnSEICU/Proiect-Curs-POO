#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>

int MAX_HEALTH = 3;
const int GAME_DURATION_MINUTES = 60;

const std::vector <int> path_begin = 
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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


// << overload far a matrix
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<std::string>>& matrix)
{
    for (const auto& row : matrix)
    {
        for (const auto& col : row)
        {
            os << col << " ";
        }
        os << std::endl;
    }
    return os;
}


class Map
{
    public:
        bool validMove(std::string move, std::vector<std::string> exits);
        void printRoom(Room room, int i, int save);
        bool answerQuestion(std::string answer, std::string correct_answer, std::string hint, int &try_count);
        void showHint(std::string hint);
        int getMove(std::vector<std::string> exits, int i);
        void saveGame(int i, int save);

};


bool Map::validMove(std::string move, std::vector<std::string> exits) 
{
    auto it = find(exits.begin(), exits.end(), move);

    for(auto i : exits)
        if(it != exits.end())
            return true;

    return false;
}

void Map::printRoom(Room room, int i, int save) 
{
    std::string close;
    std::string move;
    std::string answer;
    int try_count = 0;

    if(room.is_completed == false)
    {
        std::cout << "Room " << i + 1 << std::endl;
        std::cout << "Question: " << room.question << std::endl;
        std::cout << "Answer: ";
        std::getline(std::cin, answer);

        switch (save)
        {
            case 1:
            {
                std::ofstream fout;
                fout.open("save1.csv", std::ios::app);

                fout << room.question << "," << room.answer << "," << room.hint << "," ;

                for(auto j : room.exits)
                    fout << j << " ";

                fout << ",";

                if(answerQuestion(answer, room.answer, room.hint, try_count) == true)
                {
                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    getMove(room.exits, i);
                }
                else
                {   
                    do
                    {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "health: " << MAX_HEALTH << std::endl;
                        std::cout << "Answer: ";

                        std::getline(std::cin, answer);

                        if(answer == room.answer)
                        {
                            std::cout << "Correct answer!" << std::endl;
                            if(room.is_completed == true)
                                fout << "true" << ",";
                            else
                                fout << "false" << ",";

                            getMove(room.exits, i);
                        }

                    } while (answerQuestion(answer, room.answer, room.hint, try_count) == false && MAX_HEALTH > 0);
                }

            if(room.is_end == true)
                fout << "true" << std::endl;
            else
                fout << "false" << std::endl;

            fout.close();
            
            break;
            }

            case 2:
            {

                std::ofstream fout;
                fout.open("save2.csv", std::ios::app);

                fout << room.question << "," << room.answer << "," << room.hint << "," ;

                for(auto j : room.exits)
                    fout << j << " ";

                fout << ",";

                if(answerQuestion(answer, room.answer, room.hint, try_count) == true)
                {
                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    getMove(room.exits, i);
                }
                else
                {   
                    do
                    {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "health: " << MAX_HEALTH << std::endl;
                        std::cout << "Answer: ";

                        std::getline(std::cin, answer);

                        if(answer == room.answer)
                        {
                            std::cout << "Correct answer!" << std::endl;
                            if(room.is_completed == true)
                                fout << "true" << ",";
                            else
                                fout << "false" << ",";

                            getMove(room.exits, i);
                        }

                    } while (answerQuestion(answer, room.answer, room.hint, try_count) == false && MAX_HEALTH > 0);
                }

            if(room.is_end == true)
                fout << "true" << std::endl;
            else
                fout << "false" << std::endl;

            fout.close();

            break;
            }
            

            case 3:
            {

                std::ofstream fout;
                fout.open("save3.csv", std::ios::app);

                fout << room.question << "," << room.answer << "," << room.hint << "," ;

                for(auto j : room.exits)
                    fout << j << " ";

                fout << ",";

                if(answerQuestion(answer, room.answer, room.hint, try_count) == true)
                {
                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    getMove(room.exits, i);
                }
                else
                {   
                    do
                    {   
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "health: " << MAX_HEALTH << std::endl;
                        std::cout << "Answer: ";

                        std::getline(std::cin, answer);

                        if(answer == room.answer)
                        {
                            std::cout << "Correct answer!" << std::endl;
                            if(room.is_completed == true)
                                fout << "true" << ",";
                            else
                                fout << "false" << ",";

                            getMove(room.exits, i);
                        }

                    } while (answerQuestion(answer, room.answer, room.hint, try_count) == false && MAX_HEALTH > 0);
                }

            if(room.is_end == true)
                fout << "true" << std::endl;
            else
                fout << "false" << std::endl;

            fout.close();

            break;
            }
            
        
        default:
            break;
        }      

        if(MAX_HEALTH == 0)
        {
            std::cout << "You lost all your lives!" << std::endl;
            std::cout << "The game will close in\n";
            Sleep(1000);
            std::cout << "3\n";
            Sleep(1000);
            std::cout << "2\n";
            Sleep(1000);
            std::cout << "1\n";
            Sleep(1000);
            std::cout << "0\n";
            Sleep(1000);
            std::cout << "BYE!!\n";
            Sleep(1000);
            exit(0);
        }

        
        if(room.is_end == false)
        {
            std::cout << "Do you want to exit and save the game? (y/n): ";

            std::cin >> close;
            std::getchar();

            if(close == "y")
            {
                std::cout << "Game saved!" << std::endl;
                saveGame(i, save);
                std::cout << "The game will close in\n";
                Sleep(1000);
                std::cout << "3\n";
                Sleep(1000);
                std::cout << "2\n";
                Sleep(1000);
                std::cout << "1\n";
                Sleep(1000);
                std::cout << "0\n";
                Sleep(1000);
                std::cout << "BYE!!\n";
                Sleep(1000);
                exit(0);
            }
        }
    } 
}

bool Map::answerQuestion(std::string answer, std::string correct_answer, std::string hint, int &try_count) 
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
            MAX_HEALTH--;
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

    for(int k = 0; k < path_begin.size(); k++)
    {
        if(i == path_begin.at(k))
        {
            pos = k;
        }
    }

    std::cout << "Exits: ";

    for(auto j : exits)
        std::cout << j << " ";

    std::cout << std::endl;

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

    i = new_room - 1;

    return i;
}

void Map::saveGame(int i, int save) 
{

    switch (save)
    {
        case 1:
            {   
                std::ofstream fout;
                fout.open("save_room_1.csv", std::ios::out);
                
                fout << i + 1 << std::endl;

                fout.close();
                break;
            }


        case 2:
            {   
                std::ofstream fout;
                fout.open("save_room_2.csv", std::ios::out);
                
                fout << i + 1 << std::endl;

                fout.close();
                break;
            }

        case 3:
            {   
                std::ofstream fout;
                fout.open("save_room_3.csv", std::ios::out);
                
                fout << i + 1 << std::endl;

                fout.close();
                break;
            }
        
        default:
            break;
    }
}

int main()
{
    std::cout << "**********************************************************" << std::endl;
    std::cout << "****************  Welcome to ESCAPE ROOM  ****************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "****************  Choose a option (1-5)   ****************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "********************   1.Start Game   ********************" << std::endl;
    std::cout << "*********************   2.Load Game  *********************" << std::endl;
    std::cout << "***********************  3.Credits  **********************" << std::endl;
    std::cout << "*************************  4.Help  ***********************" << std::endl;
    std::cout << "*************************  5.Exit  ***********************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "**********************************************************" << std::endl;


    std::chrono::time_point<std::chrono::system_clock> start, end;

    Map map;
    std::vector<Room> rooms;
    std::vector <std::string> exits;
    std::string question;
    std::string answer;
    std::string hint;
    std::string aux;
    std::string row;
    bool is_completed;
    bool is_end;
    int num, i;
    int room_save;
    int file_save;
    int input;
    int room_count = -1;
    std::ifstream fin1;
    std::chrono::duration<double> duration;

    do
    {
        std::cout << "Option: ";
        std::cin >> input;
        
        switch (input)
        {
            case 1:
            {
                int save;
                std::ifstream fin;
                std::ofstream fout;
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
                    exits.push_back(aux);

                    std::getline(sin, aux, ',');
                    is_completed = aux == "true" ? true : false;

                    std::getline(sin, aux, ',');
                    is_end = aux == "true" ? true : false;

                    rooms.push_back(Room(question, answer, hint, exits, is_completed, is_end));

                    exits.clear();
                }

                Room room(question, answer, hint, exits, is_completed, is_end);
                rooms.push_back(room);
                exits.clear();

                fin.close();

                std::cout << "In which file do you want to save your progress? (1-3)" << std::endl;

                std::cin >> save;
                std::getchar();

                start = std::chrono::system_clock::now();

                for(i = 0; i < rooms.size() && MAX_HEALTH > 0; i++)
                {
                    system("cls");
                    
                    end = std::chrono::system_clock::now();
                    duration = start + std::chrono::minutes(GAME_DURATION_MINUTES) - end;
                    std::cout << "You have ";
                    std::cout << std::chrono::duration_cast<std::chrono::minutes>(duration).count() << " minutes left." <<std::endl;

                    map.printRoom(rooms[i], i, save);

                    if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                    {
                        std::cout << "You ran out of time!" << std::endl;
                        std::cout << "The game will close in\n";
                        Sleep(1000);
                        std::cout << "3\n";
                        Sleep(1000);
                        std::cout << "2\n";
                        Sleep(1000);
                        std::cout << "1\n";
                        Sleep(1000);
                        std::cout << "0\n";
                        Sleep(1000);
                        std::cout << "BYE!!\n";
                        Sleep(1000);
                        exit(0);
                    }
                    else if(rooms[i].getIsEnd() == true)
                    {
                        std::cout << "You won!" << std::endl;
                        std::cout << "The game will close in\n";
                        Sleep(1000);
                        std::cout << "3\n";
                        Sleep(1000);
                        std::cout << "2\n";
                        Sleep(1000);
                        std::cout << "1\n";
                        Sleep(1000);
                        std::cout << "0\n";
                        Sleep(1000);
                        std::cout << "BYE!!\n";
                        Sleep(1000);
                        exit(0);
                    }
                }
            }

            case 2:
            {
                int save;

                do
                {
                    std::cout << "Choose the file you saved your progress: " << std::endl;
                    std::cout << "1. Save 1" << std::endl;
                    std::cout << "2. Save 2" << std::endl;
                    std::cout << "3. Save 3" << std::endl;
                    std::cin >> save;
                    std::getchar();
                    
                    switch (save)
                    {
                        case 1:
                        {
                            system("cls");
                            
                            fin1.open("save_room_1.csv");

                            while(std::getline(fin1, row))
                            {
                                std::istringstream sin(row);

                                std::getline(sin, aux, ',');
                                room_save = std::stoi(aux);

                                std::cout << room_save << std::endl;
                            }

                            fin1.close();

                            std::cout << "Save 1" << std::endl;

                            std::ofstream fout;
                            std::ifstream fin;
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

                            start = std::chrono::system_clock::now();

                            for(int i = room_save; i < rooms.size() && MAX_HEALTH > 0; i++)
                            {
                                system("cls");

                                map.printRoom(rooms[i], i, save);
                                
                                end = std::chrono::system_clock::now();

                                if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                {
                                    std::cout << "You ran out of time!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }
                                else if(rooms[i].getIsEnd() == true)
                                {
                                    std::cout << "You won!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }
                            }
                            break;
                        }

                        case 2:
                        {
                            system("cls");
                            
                            fin1.open("save_room_2.csv");

                            while(std::getline(fin1, row))
                            {
                                std::istringstream sin(row);

                                std::getline(sin, aux, ',');
                                room_save = std::stoi(aux);

                                std::cout << room_save << std::endl;
                            }

                            fin1.close();

                            std::cout << "Save 2" << std::endl;

                            std::ofstream fout;
                            std::ifstream fin;
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

                            start = std::chrono::system_clock::now();
                            
                            for(int i = room_save; i < rooms.size() && MAX_HEALTH > 0; i++)
                            {   
                                system("cls");

                                map.printRoom(rooms[i], i, save);

                                end = std::chrono::system_clock::now();

                                if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                {
                                    std::cout << "You ran out of time!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }
                                else if(rooms[i].getIsEnd() == true)
                                {
                                    std::cout << "You won!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }

                            }
                            break;
                        }
                    
                        case 3:
                        {
                            system("cls");
                            
                            fin1.open("save_room_3.csv");

                            while(std::getline(fin1, row))
                            {
                                std::istringstream sin(row);

                                std::getline(sin, aux, ',');
                                room_save = std::stoi(aux);

                                std::cout << room_save << std::endl;
                            }

                            fin1.close();

                            std::cout << "Save 3" << std::endl;

                            std::ofstream fout;
                            std::ifstream fin;
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

                            start = std::chrono::system_clock::now();

                            for(int i = room_save; i < rooms.size() && MAX_HEALTH > 0; i++)
                            {
                                system("cls");

                                map.printRoom(rooms[i], i, save);

                                end = std::chrono::system_clock::now();

                                if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                {
                                    std::cout << "You ran out of time!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }
                                else if(rooms[i].getIsEnd() == true)
                                {
                                    std::cout << "You won!" << std::endl;
                                    std::cout << "The game will close in\n";
                                    Sleep(1000);
                                    std::cout << "3\n";
                                    Sleep(1000);
                                    std::cout << "2\n";
                                    Sleep(1000);
                                    std::cout << "1\n";
                                    Sleep(1000);
                                    std::cout << "0\n";
                                    Sleep(1000);
                                    std::cout << "BYE!!\n";
                                    Sleep(1000);
                                    exit(0);
                                }
                            }
                            break;
                        }

                        default:
                        {
                            std::cout << "Invalid input!" << std::endl;
                            std::cin >> save;
                            break;
                        }
                    }
                }while(save > 0 && save < 4);
                break;
            }
            case 3:
            {
                std::cout << "Credits" << std::endl;
                std::cout << "Made by: " << std::endl;
                std::cout << "Bolohan Stefan-Tudor" << std::endl;
                std::cout << "Ghiorghita Adrian-Dragos" << std::endl;
                std::cout << "Pricopi Robert Alexandru" << std::endl;
                std::cout << "Visan Robert Cristian" << std::endl;
                break;
            }

            case 4:
            {
                std::cout << "HELP:" << std::endl;
                std::cout << "For the command to work the user will have to input an 'enter' after writing it." << std::endl;
                std::cout << "All the andwers if be in lower cases with no punctuation." << std::endl;
                std::cout << "The exit of the room will be printed on the screen for every completed room." << std::endl;
                break;
            }

            case 5:
            {
                std::cout << "Thank you for playing" << std::endl;
                Sleep(1000);
                return 0;
                break;
            }
            
            default:
            {
                std::cout << "Invalid input!" << std::endl;
                std::cin >> input;
                break;
            }
        }
    }while(input > 0 && input < 6);    

    return 0;
}
