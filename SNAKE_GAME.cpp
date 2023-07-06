//SNAKE GAME
/*in snake game we have a snake head, snake tail,
we control the snake head by moving up, down
left, right, if the snake eats fruit tail length
increase and if the snake head hit the walls then the game overs*/
#include <iostream>
#include <cstdlib>
#include <conio.h>//library for functions such as getting character from console window
#include<windows.h>//for sleep function to slow down the game
using namespace std;
bool gameover;//global variable
const int width = 40;//variables for map dimensions
const int height = 20;//variable for map dimensions
int x, y, fruitx, fruity, score;//variables for head position and fruit position
int tailx[100], taily[100];//first array for x coordinate of tail and y for y coodinate of tail
int nTail;//specify length of tail
enum edirection{ STOP = 0, UP, DOWN, LEFT, RIGHT};//track the direction of snake
//enum: data type to create set of constants for use with var and properties
edirection dir;//variable for direection
void setup()//function for setup
{
    gameover = false;
    dir = STOP;//snake will not move until we move it
    x = width / 2;//position of snake head middle
    y = height / 2;//position of snake head middle
    fruitx = rand() % width;//position of fruit...random from 0 to width-1
    fruity = rand() % height;//position of fruit...random from 0 to height-1
    score = 0;
}
void draw()
{
    system("cls");//to clear the console window
    for (int i = 0; i < width + 2; i++)//display top border of map
    {
        cout << "-";
    }
    cout << endl;//move to next line
    for (int i = 0; i < height; i++)//i is height and j is width
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)//if j is equal to zero then wall to left is printed
                cout << "|"; // walls
            if (i == y && j == x)//print snake head,if i that is height is equal to y coordinate and j equal to x coordinate
                cout << "O"; // snake head
           
            else if (i == fruity && j == fruitx)//print the fruit
                cout << "*"; // change it to change the fruit
            else
            {
                bool print = false;//variable keep track whether we print the tail segment or not
                for(int k=0;k<nTail;k++){//print the tail
                    if(tailx[k]==j && taily[k]==i)//if tailx is equal to current x coordianate and taily is equal to current y coordianate
                    {
                       
                        cout<<"o";
                        print = true;//if printed then true and prints tail segment
                    }
                }
                if(!print)//if not printed tail segment then print blank
                cout << " ";
            }
            if (j == width - 1)//print wall on right side
                cout << "|";
        }
        cout << endl;//exits the j loop and move to next row then
    }
    for (int i = 0; i < width + 2; i++)//display bottom wall
        cout << "-";
    cout << endl;
    cout<<"SCORE : "<<score<<endl;//print score
}
void input()
{
    if (_kbhit())//boolean return true if key is pressed else return 0
    {
        switch (_getch())//return ascii value of character we pressed
        {
        case 'w'://press w
            dir = UP;//then direction of snake head up
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x'://for terminating game
            gameover = true;
            break;
        }
    }
}
void logic()
{
    int prevX = tailx[0];//previous x coordinate of tail
    int prevY = taily[0];//previous y coordinate of tail
    int prev2X, prev2Y;//
    tailx[0]=x;//set first element to follow head
    taily[0]=y;//set first element to follow head
    for(int i=1;i<nTail;i++){//i will be 1 because above we do have tailx,y[0]
        prev2X = tailx[i];//remembers current position of segment
        prev2Y = taily[i];//remembers current position of segment
        tailx[i]=prevX;//change it to previous coordinates
        taily[i]=prevY;//~~/
        prevX = prev2X;//update prevx and prev2x
        prevY = prev2Y;//update prevy and prev2y
    }
    switch (dir)//switch direction for moving the snake head
    {
    case UP:
        y--;//when we go up decrease y coordinate
        break;
    case LEFT:
        x--;//when we go left decrease x coordinate
        break;
    case RIGHT:
        x++;//when we go right increase x coordinate
        break;
    case DOWN:
        y++;//when we go down increase y coordinate
        break;
    default:
        break;
    }
    if(x>width || x<0 || y>height || y<0)//x and y coordinate of snake head greater then walls then game terminate
        gameover=true;
    for(int i=0;i<nTail;i++){//loop through all tail segments
        if(tailx[i]==x && taily[i]==y){//if tailx segment equal to head x coordinate and taily coordinate equal to heads y coordinate
            gameover=true;//then game over if tail and head collide
        }
    }
    if(x==fruitx && y==fruity) //if snake head coordinates x, y equals fruit coordinates, friutx, fruity then tail increases and score increases
    //also enables to eat the fruit in other words
    {
       
        score+=10;//increase score by 10
        fruitx=rand() % width;//randomly place the fruit somewhere on the map
        fruity= rand() % height;
        nTail++;//increase the tail length by 1
    }
}
int main()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
_sleep(70);//slows down our game
    }
    return 0;
}