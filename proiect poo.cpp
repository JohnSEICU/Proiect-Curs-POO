//map (partialy done)
//healthbar (undone)
//rooms (undone)
//intrebari grila (undone)
//file reading
// '*' marked tasks will be focused after finishing the project and will generate a more complex algorithm;

#include <iostream.h>

using namespace std;

int boundary(int position) //preventing the user to go out of map
{

}


//availability of the move

//move function

//death funtion *

int main()
{
    int map[5][5]; // map shower
    int position; //in the format "RowCollumn"

    for(int i = 1 ; i <= 5; i++)
    {
        for(int j = 1 ; j <= 5 ; j++)
        {
            map[i][j] = 0;
        }
    }

    //start is 1:1

    //flooring(3 floors - 1 each course)

    int health = 3;

    if(health == 0)
    {
        //death message + restart option
    }

    while(true) //for testing
    {
        //questions+asnwers -> map_update -> if wrong answer drop healh
    }

    return 0;
}
