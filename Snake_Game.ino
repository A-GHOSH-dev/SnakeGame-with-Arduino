#include "LedControl.h" 

// The pins
struct Pin {
  static const short joystickX = A2;   //  X axis pin joystick      //There are four type modifiers in C++.1. short(We can use short for small integers (in the range −32,767 to +32,767))2.long3.signed4.unsigned
  static const short joystickY = A3;   // Y axis pin joystick 
  static const short joystickVCC = 15; //5v ??
  static const short joystickGND = 14; //gnd??

  static const short potentiometer = A5; // potentiometer for snake speed control

  static const short CLK = 10;   // clock for LED matrix
  static const short CS  = 11;  // chip-select for LED matrix
  static const short DIN = 12; // data-in for LED matrix
};

// LED matrix brightness 0-15
const short intensity = 8;//6

// message scrolling speed
const short messageSpeed = 22;//5

// initial snake length 
const short initialSnakeLength = 2;//3 


void setup() {
  Serial.begin(115200); 
/*The serial communication is a simple scheme that uses the UART (Universal Asynchronous Receiver/Transmitter) on the Microcontroller. It uses,
5V for logic 1 (high)
0V for logic 0 (low)
For a 3.3V board, it uses
3V for logic 1 (high)
0V for logic 0 (low)
Every message sent on the UART is in the form of 8 bits  
The Serial.begin( ) is a part of the serial object in the Arduino. It tells the serial object to perform initialization steps to send and receive data on the Rx and Tx (pins 1 and 0).
The serial.begin( ) sets the baud rate for serial data communication. The baud rate signifies the data rate in bits per second.

The default baud rate in Arduino is 9600 bps (bits per second). We can specify other baud rates as well, such as 4800, 14400, 38400, 28800, etc.

The Serial.begin( ) is declared in two formats, which are shown below:

begin( speed )
begin( speed, config)*/
  //Serial.begin(9600);
  
  initializing();         // initialization of the pins & LED matrix
  checktheJoystick(); 
  theSnakeMsg(); // scrolls the snake message 
}


void loop() {
  makeFood();    // when no food is there, we have to make a food appear
  scanJoystick();    // watches joystick movements & blinks with food
  WorkingOnMySnake();  // calculates snake parameters
  gamePlay();
}


/*LedControl let you control many 7 segment displays or many LEDs using one or more MAX7219 or MAX7221 chips.
Basic Usage
LedControl mydisplay = LedControl(DIN_pin, CLK_pin, LOAD_pin, number_of_chips);
Create an instance of LedControl using a name of your choice. The 3 pins where you connected the MAX7219 signals need to be given. The number of chips is also needed. Normally if you need more than one chip, it's easiest to chain them together (DOUT to DIN) and use only a single object to control them all. You could also connect each chip to 3 separate pins and create a separate object for each.

Setup
mydisplay.shutdown(chip, false);
Turn the chip on or off. Use "false" to turn the chip on, "true" to shut it down. The chips default to shutdown mode, so you must turn them on before using them. If you have multiple chips, this must be done for each chip.

mydisplay.setIntensity(chip, intensity);
Set the intensity on a chip. 15 is the maximum brightness. If you have multiple chips, this must be done for each chip.

Display Functions
mydisplay.setDigit(chip, digit_position, number, dot);
Sets a 7 segment display to "number". The chip and position of the digit on that chip must be given. "dot" is usually false. Using "true" will turn on the dot associated with that digit.

mydisplay.setLed(chip, row, column, state);
Turn a single LED on or off. Three inputs, "chip", "row" and "column" select the exact LED, and "state" must be true to turn the LED on, or false to turn it off.

Example Program
#include <LedControl.h>

// inputs: DIN pin, CLK pin, LOAD pin. number of chips
LedControl mydisplay = LedControl(45, 44, 43, 1);

void setup() {
  mydisplay.shutdown(0, false);  // turns on display
  mydisplay.setIntensity(0, 15); // 15 = brightest
  mydisplay.setDigit(0, 0, 9, false);
  mydisplay.setDigit(0, 1, 8, false);
  mydisplay.setDigit(0, 2, 7, false);
  mydisplay.setDigit(0, 3, 6, false);
  mydisplay.setDigit(0, 4, 5, true);
  mydisplay.setDigit(0, 5, 4, false);
  mydisplay.setDigit(0, 6, 3, false);
  mydisplay.setDigit(0, 7, 2, false);
}

void loop() {
}*/


LedControl matrix(Pin::DIN, Pin::CLK, Pin::CS, 1);

//In C++, classes and structs are blueprints that are used to create the instance of a class. Structs are used for lightweight objects such as Rectangle, color, Point, etc.Unlike class, structs in C++ are value type than reference type. It is useful if you have data that is not intended to be modified after creation of struct.
/*struct Student  
{  
    char name[20];  
     int id;  
     int age;  
}  
In the above case, Student is a structure contains three variables name, id, and age. When the structure is declared, no memory is allocated. When the variable of a structure is created, then the memory is allocated. 
How to access the variable of Structure:
The variable of the structure can be accessed by simply using the instance of the structure followed by the dot (.) operator and then the field of the structure.

For example:

s.id = 4;  
In the above statement, we are accessing the id field of the structure Student by using the dot(.) operator and assigns the value 4 to the id field.

Let's see another example of struct where we are using the constructor to initialize data and method to calculate the area of rectangle.

#include <iostream>    
using namespace std;    
 struct Rectangle    {      
   int width, height;      
  Rectangle(int w, int h)      
    {      
        width = w;      
        height = h;      
    }      
  void areaOfRectangle() {       
    cout<<"Area of Rectangle is: "<<(width*height); }      
 };      
int main(void) {    
    struct Rectangle rec=Rectangle(4,6);    
    rec.areaOfRectangle();    
   return 0;    
}    
Output:

Area of Rectangle is: 24



#include<iostream>
using namespace std;

struct Person
{
  int citizenship;
  int age;
};

void func(struct Person p);

int main()
{
  struct Person p;

  p.citizenship = 1;
  p.age = 27;

  func(p);
  return 0;
}
void func(struct Person p)
{
  cout << " Person citizenship: " << p.citizenship<<endl;
  cout << " Person age: " << p.age;
}

OUTPUT

Person Citizenship: 1
Person age: 27


Code Explanation:

1. Include the iostream header file into our file. We will then use its functions without getting errors.
2. Include the std namespace in our program to use its classes. We will not need to call the namespace to use its classes.
3. Create a struct named Person.
4. Start of the body of the struct Person.
5. Create a member of struct Person. The member is named citizenship and is of type integer.
6. Create a member of struct Person. The member is named age and is of type integer.
7. End of the body of struct Person.
8. Create a function that takes the instance of struct Person, p, as the argument.
9. Call the main function. The { marks the beginning of the body of main() function.
10.Create an instance of struct Person and giving it the name p.
11. Access the struct member variable citizenship using the instance of the struct, p, and assigning it the value 1.
12. Access the struct member variable age using the instance of the struct, p, and assigning it the value 27.
13. Call the function and passing to it the instance of the struct Person, p, as the argument.
14. The function must return a value upon successful execution.
15. End of the body of the main() function.
16. Create the body of the function.
17. The start of the body of the function.
18. Access the struct member citizenship value and printing it on the console alongside other text.
19. Access the struct member age value and printing it on the console alongside other text.
20. End of the function body.
*/


struct Point {
  int row = 0, col = 0;
  Point(int row = 0, int col = 0): row(row), col(col) {}
};

/*Define a function outside a class
The scope resolution operator can be used to define a function outside a class. A program that demonstrates this is given as follows.

Example
#include<iostream>
using namespace std;
class Example {
   int num;
   public:
   Example() {
      num = 10;
   }
   void display();
};
void Example::display() {
   cout << "The value of num is: "<<num;;
}
int main() {
   Example obj;
   obj.display();
   return 0;
}
Output
The output of the above program is as follows.

The value of num is: 10
Access a global variable when there is also a local variable with the same name
The scope resolution operator can be used to access a global variable when there is also a local variable with the same name. A program that demonstrates this is given as follows.

Example
#include<iostream>
using namespace std;
int num = 7;
int main() {
   int num = 3;
   cout << "Value of local variable num is: " << num;
   cout << "\nValue of global variable num is: " << ::num;
   return 0;
}
Output
The output of the above program is as follows.

Value of local variable num is: 3
Value of global variable num is: 7
*/



struct Coordinate {
  int x = 0, y = 0;
  Coordinate(int x = 0, int y = 0): x(x), y(y) {}
};

bool win = false;
bool gameOver = false;

// snake head is generated randomly
Point snake;

// food is not anywhere yet
Point food(-1, -1);

// construct with default values
Coordinate joystickHome(500, 500);

// snake conditions
int snakeLength = initialSnakeLength; 
int snakeSpeed = 1; // this will actually be set by the potentiometer in hardware
int snakeDirection = 0; // when it is 0/null, the snake does not move
// direction constants
const short up     = 1;
const short right  = 2;
const short down   = 3; 
const short left   = 4; 



/*The value on every analog channel can vary from 0 to 1023. When connected to analog ports, VRx to A0 and VRy to A1 respectively, they should transmit the values as shown in the image below.
x:0;y:115 left
x:1023;y:115 right
x:115;y1023 up
x:511;y:0 down
*/




// threshold where movement of the joystick will be accepted
const int joystickThreshold = 160;

// steepness of the potentiometer (-1 = linear, 1 = natural, bigger = steeper (better is 0...1))
const float logarithmity = 0.4;

// snake body parts code
int gameboard[8][8] = {};

// if there is no food, generate one, also check for victory
void makeFood() {
  if (food.row == -1 || food.col == -1) {
    
    if (snakeLength >= 64) {
      win = true;
      return; // the food maker is stopped from preparing more food
    }

    // make the food 
    do {
      food.col = random(8);
      food.row = random(8);
    } while (gameboard[food.row][food.col] > 0);
  }
}


// coordinating the joystick movement
void scanJoystick() {
  int previousDirection = snakeDirection; 
  long timeInterval = millis(); //millis() Returns the number of milliseconds passed since the Arduino board began running the current program. unsigned long


  while (millis() < timeInterval + snakeSpeed) {
    // speed of snake is to be calculated exponentially
    float raw = mapf(analogRead(Pin::potentiometer), 0, 1023, 0, 1); //analogRead - Arduino AnalogRead function is used to measure the voltage between 0 to 5 volts and converts it into a digital value between 0 to 1023. 
    snakeSpeed = mapf(pow(raw, 3.5), 0, 1, 10, 1000); // change the speed exponentially------??
    if (snakeSpeed == 0) snakeSpeed = 1; 

    // snakeDirection with joystick control
    analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold ? snakeDirection = up    : 0;
    analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold ? snakeDirection = down  : 0;
    analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold ? snakeDirection = left  : 0;
    analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold ? snakeDirection = right : 0;


/*Conditional ternary operator ( ? )
The conditional operator evaluates an expression, returning one value if that expression evaluates to true, and a different one if the expression evaluates as false. Its syntax is:

condition ? result1 : result2

If condition is true, the entire expression evaluates to result1, and otherwise to result2.

7==5 ? 4 : 3     // evaluates to 3, since 7 is not equal to 5.
7==5+2 ? 4 : 3   // evaluates to 4, since 7 is equal to 5+2.
5>3 ? a : b      // evaluates to the value of a, since 5 is greater than 3.
a>b ? a : b      // evaluates to whichever is greater, a or b.  

For example:
// conditional operator
#include <iostream>
using namespace std;

int main ()
{
  int a,b,c;

  a=2;
  b=7;
  c = (a>b) ? a : b;

  cout << c << '\n';
}
OUTPUT
7

In this example, a was 2, and b was 7, so the expression being evaluated (a>b) was not true, thus the first value specified after the question mark was discarded in favor of the second value (the one after the colon) which was b (with a value of 7).
*/


/*Dot (.) operator is known as "Class Member Access Operator" in C++ programming language, it is used to access public members of a class. Public members contain data members (variables) and member functions (class methods) of a class.

Syntax:

object_name.member_name;
Consider the given class declaration

class sample
{
  private:
    int a;
  public:
    int b;
    void init(int a)
    {this->a = a;}
    void display()
    {cout<<"a: "<<a<<endl;}
};
In this class declaration, following are the class members that can be accessed through the "Class Member Access Operator":

Public data member: b

Public member functions: init(), display()

Here is the complete program

#include <iostream>
using namespace std;

class sample
{
  private:
    int a;
  public:
    int b;
    void init(int a)
    {this->a = a;}
    void display()
    {cout<<"a: "<<a<<endl;}
};

int main()
{
  //object declaration
  sample sam;
  //value assignment to a and back
  sam.init(100);
  sam.b=200;
  
  //printing the values
  sam.display();
  cout<<"b: "<<sam.b<<endl;
  
  return 0;     
}
Output

a: 100
b: 200
Consider the following statements in main() function

sam.init(100); - This statement will assign 100 to the private data member a through this public member function.
sam.b=200; - This statement will assign 200 to the public data member b.

a.b is only used if b is a member of the object (or reference[1] to an object) a. So for a.b, a will always be an actual object (or a reference to an object) of a class.
a→b is essentially a shorthand notation for (*a).b, ie, if a is a pointer to an object, then a→b is accessing the property b of the object that a points to. 
*/



    // if user's first joystick movement is left then right(180 degrees) then the snake continues to move in original direction
    snakeDirection + 2 == previousDirection && previousDirection != 0 ? snakeDirection = previousDirection : 0;
    snakeDirection - 2 == previousDirection && previousDirection != 0 ? snakeDirection = previousDirection : 0;

    // intelligently blink with the food
    matrix.setLed(0, food.row, food.col, millis() % 100 < 50 ? 1 : 0);//----------??
  }
}


// logic of snake
void WorkingOnMySnake() {
  switch (snakeDirection) {
    case up:
      snake.row--;//when user is clicking on up, then the snake is moving up, hence row decreases from bottom to top
      appearFromSideEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case right:
      snake.col++;//when user is clicking on right, then the snake is moving right, hence column increases from left to right
      appearFromSideEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case down:
      snake.row++;//when user is clicking on down, then the snake is moving down, hence row increases from top to bottom
      appearFromSideEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case left:
      snake.col--;//when user is clicking on left, then the snake is moving left, hence column decreasing from right to left
      appearFromSideEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    default: 
    // if the snake is not moving, exit
      return;
  }

  // next snake hitting previous snake, causing GameOver
  if (gameboard[snake.row][snake.col] > 1 && snakeDirection != 0) {  //if at a single led matrix, more than 1 led is approaching and snake has a direction and is moving, then GameOver as next snake hits previous snake body
    gameOver = true;
    return;
  }

  // Eat the food  // again place the food at a random place
  if (snake.row == food.row && snake.col == food.col) {
    food.row = -1; 
    food.col = -1;
    snakeLength++;// when the snake haves the food, its length increases by 1

    // ++ of snake game (when snake length increases)
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] > 0 ) {
          gameboard[row][col]++;
        }
      }
    }
  }

  // we add a new element with snake body
  gameboard[snake.row][snake.col] = snakeLength + 1; 

  // -- of snake body elements
  //if body element is 0
  //turn that led off
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (gameboard[row][col] > 0 ) {
        gameboard[row][col]--;
      }
      matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 0 : 1);   //displaying the leds
    }
  }
}


// when from one side, or edge, the snake goes out, then it appears from the otherside edge
void appearFromSideEdge() {
  snake.col < 0 ? snake.col += 8 : 0;
  snake.col > 7 ? snake.col -= 8 : 0;
  snake.row < 0 ? snake.row += 8 : 0;
  snake.row > 7 ? snake.row -= 8 : 0;
}


void gamePlay() {
  if (gameOver || win) {
    stopSnakePlay();
    showScoreMessage(snakeLength - initialSnakeLength); //Our scoring system will be that the points will be the : final snake length - the initial snake length
    if (gameOver) showGameOverMessage(); //when snake hits previous snake body, gameover, show gameover message
    else if (win) showWinMessage();//When won game, showing winning message

    // again restart the game
    win = false;
    gameOver = false;
    snake.row = random(8);
    snake.col = random(8);
    food.row = -1;
    food.col = -1;
    snakeLength = initialSnakeLength;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard[0][0]) * 8 * 8);/*In C++, memset is a function that is used to fill the blocks of memory. 
    It first converts the value of ‘c’ into an unsigned character and then copies that character to the first ‘n’ characters in the object pointed out by dest[] 
    (fills the first ‘n’ blocks of dest[] with the same character ‘c’). The size ‘n’ mentioned in the memset should be smaller or equals to the size of the object pointed
    by dest[] otherwise it is undefined. If the object is non copyable, then also the behavior of the function is undefined. 
    */
    matrix.clearDisplay(0);
  }
}


void stopSnakePlay() {
  // switch off the food LED
  matrix.setLed(0, food.row, food.col, 0);

  delay(800);

  // just flashing of the led matrix 5 times
  for (int i = 0; i < 5; i++) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 1 : 0);
      }
    }
    delay(20);
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 0 : 1);
      }
    }

    delay(50);
  }
  delay(600);
  for (int i = 1; i <= snakeLength; i++) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] == i) {
          matrix.setLed(0, row, col, 0);
          delay(100);
        }
      }
    }
  }
}


// calibrate the joystick home for 10 times
void checktheJoystick() {
  Coordinate values;
  for (int i = 0; i < 10; i++) {
    values.x += analogRead(Pin::joystickX);
    values.y += analogRead(Pin::joystickY);
  }

  joystickHome.x = values.x / 10;
  joystickHome.y = values.y / 10;
}


void initializing() {
  pinMode(Pin::joystickVCC, OUTPUT);
  digitalWrite(Pin::joystickVCC, HIGH);

  pinMode(Pin::joystickGND, OUTPUT);
  digitalWrite(Pin::joystickGND, LOW);

  matrix.shutdown(0, false);
  matrix.setIntensity(0, intensity);
  matrix.clearDisplay(0);

  randomSeed(analogRead(A5));
  snake.row = random(8);
  snake.col = random(8);
}

//The messages// bits
const PROGMEM bool snakeMessage[8][56] = {  /*Store data in flash (program) memory instead of SRAM. There’s a description of the various types of memory available on an Arduino board.
The PROGMEM keyword is a variable modifier, it should be used only with the datatypes defined in pgmspace.h. It tells the compiler "put this information into flash memory", instead of into SRAM, where it would normally go.*/
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const PROGMEM bool gameOverMessage[8][90] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const PROGMEM bool scoreMessage[8][58] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const PROGMEM bool digits[][8][8] = {
  {
    {0, 0, 0, 0, 0, 0, 0, 0},  //0
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},  //1
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},//2
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},//3
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},//4
    {0, 0, 1, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},//5
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},//6
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},//7
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},//8
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},//9
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  }
};


// scrolls the snake message 
void theSnakeMsg() {
  [&] {
    for (int d = 0; d < sizeof(snakeMessage[0]) - 7; d++) {
      for (int col = 0; col < 8; col++) {
        delay(messageSpeed);
        for (int row = 0; row < 8; row++) {
          matrix.setLed(0, row, col, pgm_read_byte(&(snakeMessage[row][col + d]))); // this reads the byte from the PROGMEM and displays it on the screen
        }
      }

      
      if (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold
              || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
              || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
              || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {
        return; 
      }
    }
  }();// if the joystick is moved, exit the message at that time

  matrix.clearDisplay(0);

  // wait for joystick co come back
  while (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold
          || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
          || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
          || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {}

}


// scrolls the game over message 
void showGameOverMessage() {
  [&] {
    for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {
      for (int col = 0; col < 8; col++) {
        delay(messageSpeed);
        for (int row = 0; row < 8; row++) {
          // this reads the byte from the PROGMEM and displays it on the screen
          matrix.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d])));
        }
      }

      
      if (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold   // if the joystick is moved, exit the message
              || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
              || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
              || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {
        return; 
      }
    }
  }();

  matrix.clearDisplay(0);

  // wait for joystick co come back
  while (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold
          || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
          || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
          || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {}

}


// scrolls the win message 
void showWinMessage() {
  // not implemented yet 
}


// scrolls the score message with numbers 
void showScoreMessage(int score) {
  if (score < 0 || score > 99) return; //score cannot be less than 0 or greater than 99

  // score digits
  int second = score % 10;
  int first = (score / 10) % 10;

  [&] {
    for (int d = 0; d < sizeof(scoreMessage[0]) + 2 * sizeof(digits[0][0]); d++) {
      for (int col = 0; col < 8; col++) {
        delay(messageSpeed);
        for (int row = 0; row < 8; row++) {
          if (d <= sizeof(scoreMessage[0]) - 8) {
            matrix.setLed(0, row, col, pgm_read_byte(&(scoreMessage[row][col + d])));
          }

          int c = col + d - sizeof(scoreMessage[0]) + 6; // move 6 px in front of the previous message

          // if the score is < 10, remove first digit zero
          if (score < 10) c += 8;

          if (c >= 0 && c < 8) {
            if (first > 0) matrix.setLed(0, row, col, pgm_read_byte(&(digits[first][row][c]))); 
          } else {
            c -= 8;
            if (c >= 0 && c < 8) {
              matrix.setLed(0, row, col, pgm_read_byte(&(digits[second][row][c]))); // show when score is greater than or equal to 10
            }
          }
        }
      }

 // if the joystick is moved, exit the message
      if (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold
              || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
              || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
              || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {
        return; 
      }
    }
  }();

  matrix.clearDisplay(0);

  //  // wait for joystick to come back
  //  while (analogRead(Pin::joystickY) < joystickHome.y - joystickThreshold
  //          || analogRead(Pin::joystickY) > joystickHome.y + joystickThreshold
  //          || analogRead(Pin::joystickX) < joystickHome.x - joystickThreshold
  //          || analogRead(Pin::joystickX) > joystickHome.x + joystickThreshold) {}

}


// the map, floats have to be set
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
