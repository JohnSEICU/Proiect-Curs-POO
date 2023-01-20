#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

int MAX_HEALTH = 3;
const int GAME_DURATION_MINUTES = 60;

const std::vector <int> path_begin = 
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

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


std::ostream& operator<<(std::ostream& os, std::vector <std::string> exits)
{
    for(auto i : exits)
        std::cout << i << " ";

    return os;
}


class Map
{
    public:
        bool validMove(std::string move, std::vector<std::string> exits);
        void printRoom(Room room, int i, int save);
        bool answerQuestion(std::string answer, std::string correct_answer, int &health, std::string hint, int &try_count);
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
        std::cout << answer <<  std::endl;
        std::cout << room.getAnswer() << std::endl;
        answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count);
        
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

                if(answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == true)
                {
                    

                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    std::cout << "Exits: ";
                    for(auto j : room.exits)
                        std::cout << j << " ";
                    std::cout << std::endl;

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
                        answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count);
                    } while (answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == false && MAX_HEALTH > 0);
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

                if(answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == true)
                {
                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    std::cout << "Exits: ";
                    for(auto j : room.exits)
                        std::cout << j << " ";
                    std::cout << std::endl;

                    getMove(room.exits, i);
                }
                else
                {   
                    do
                    {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "health: " << MAX_HEALTH << std::endl;
                        std::cout << "Answer: ";
                        std::cin >> answer;
                        answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count);

                    } while (answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == false && MAX_HEALTH > 0);
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

                if(answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == true)
                {
                    std::cout << "Correct answer!" << std::endl;
                    room.is_completed = true;

                    if(room.is_completed == true)
                        fout << "true" << ",";
                    else
                        fout << "false" << ",";

                    std::cout << "Exits: ";
                    for(auto j : room.exits)
                        std::cout << j << " ";
                    std::cout << std::endl;

                    getMove(room.exits, i);
                }
                else
                {   
                    do
                    {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "health: " << MAX_HEALTH << std::endl;
                        std::cout << "Answer: ";
                        std::cin >> answer;
                        answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count);
                    } while (answerQuestion(answer, room.answer, MAX_HEALTH, room.hint, try_count) == false && MAX_HEALTH > 0);
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

        std::cout << "Do you want to exit and save the game? (y/n): ";

        std::cin >> close;
        std::getchar();

        if(close == "y")
        {
            std::cout << "Game saved!" << std::endl;
            saveGame(i, save);
            exit(0);
        }

    } 
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

    for(int k = 0; k < path_begin.size(); k++)
    {
        if(i == path_begin.at(k))
        {
            pos = k;
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


    i = new_room - 1;

    return i;
}

void Map::saveGame(int i, int save) 
{
    std::ofstream fout;
    fout.open("saves.csv", std::ios::app);

    fout << i + 1 << "," << save << std::endl;

    fout.close();

}

int main()
{
    std::cout << "**********************************************************" << std::endl;
    std::cout << "****************   Welcome to the game    ****************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "********************   1.Start Game   ********************" << std::endl;
    std::cout << "*********************   2.Load Game  *********************" << std::endl;
    std::cout << "***********************  3.Credits  **********************" << std::endl;
    std::cout << "*************************  4.Exit  ***********************" << std::endl;
    std::cout << "**********************************************************" << std::endl;
    std::cout << "**********************************************************" << std::endl;


    std::chrono::time_point<std::chrono::system_clock> start, end;

    Map map;

    std::vector<Room> rooms;
    std::string question;
    std::string answer;
    std::string hint;
    std::vector <std::string> exits;
    bool is_completed;
    bool is_end;
    int num, i;
    int room_save;
    int file_save;
    
    std::string aux;
    std::string row;
    std::ifstream fin1;
    int room_count = -1;

    int input;

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
        
                    map.printRoom(rooms[i], i, save);
                    
                    end = std::chrono::system_clock::now();
                    if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                    {
                        std::cout << "You ran out of time!" << std::endl;
                        return 0;
                    }
                    else if(rooms[i].getIsEnd() == true)
                    {
                        std::cout << "You won!" << std::endl;
                        return 0;
                    }

                    num = i;
                }
            }


            case 2:
            {
                int save;

                std::cout << "Start Game" << std::endl;

                fin1.open("saves.csv");

                while(std::getline(fin1, row))
                {
                    std::stringstream sin(row);

                    std::getline(sin, aux, ',');
                    room_save = std::stoi(aux);

                    std::getline(sin, aux, ',');
                    file_save = std::stoi(aux);
                }

                fin1.close();


                do
                {
                    std::cout << "Choose the file you saved your progress: " << std::endl;
                    std::cout << "1. Save 1" << std::endl;
                    std::cout << "2. Save 2" << std::endl;
                    std::cout << "3. Save 3" << std::endl;
                    std::cin >> save;

                    
                    if(save == file_save)
                    {
                        switch (save)
                        {
                            case 1:
                            {
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

                                    map.printRoom(rooms[i], i, file_save);
                                    // std::cout << rooms[i].getIsCompleted() << std::endl;
                                    end = std::chrono::system_clock::now();
                                    if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                    {
                                        std::cout << "You ran out of time!" << std::endl;
                                        return 0;
                                    }
                                    else if(rooms[i].getIsEnd() == true)
                                    {
                                        std::cout << "You won!" << std::endl;
                                        return 0;
                                    }

                                }

                                std::cout << "You ran out of lives!" << std::endl;
                                return 0;

                                break;
                            }

                            case 2:
                            {
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
                                    
                                    map.printRoom(rooms[i], i, file_save);
                                    // std::cout << rooms[i].getIsCompleted() << std::endl;
                                    end = std::chrono::system_clock::now();
                                    if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                    {
                                        std::cout << "You ran out of time!" << std::endl;
                                        return 0;
                                    }
                                    else if(rooms[i].getIsEnd() == true)
                                    {
                                        std::cout << "You won!" << std::endl;
                                        return 0;
                                    }

                                }

                                std::cout << "You ran out of lives!" << std::endl;
                                return 0;

                                break;
                            }
                        
                            case 3:
                            {
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
                                    map.printRoom(rooms[i], i, file_save);
                                    // std::cout << rooms[i].getIsCompleted() << std::endl;
                                    end = std::chrono::system_clock::now();
                                    if(end >= start + std::chrono::minutes(GAME_DURATION_MINUTES))
                                    {
                                        std::cout << "You ran out of time!" << std::endl;
                                        return 0;
                                    }
                                    else if(rooms[i].getIsEnd() == true)
                                    {
                                        std::cout << "You won!" << std::endl;
                                        return 0;
                                    }
                                }

                                std::cout << "You ran out of lives!" << std::endl;
                                return 0;

                                break;
                            }

                            default:
                            {
                                std::cout << "Invalid input!" << std::endl;
                                std::cin >> save;
                                break;
                            }
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
                std::cout << "Thank you for playing" << std::endl;
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
    }while(input > 0 && input < 5);    

    return 0;
}
