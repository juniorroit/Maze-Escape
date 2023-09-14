/**********************************************

John Baek

May 31 2022

ICS4U1 Final project

**********************************************/

#include <iostream>
#include <exception>
#include <vector>
using namespace std;


// exception classes to output error messages
class OutOfBoundary: public exception
{
public:
string error()
{
	return "Cannot move outside the map";
}
};

class InvalidCommand: public exception
{
public:
string error()
{
	return "Invalid Command";
}
};

class collision: public exception
{
public:
string error()
{
	return "Avoid touching the wall";
}
};

class ClosedGate: public exception
{
public:
string error()
{
	return "The gate must first be opened with the key of same colour";
}
};

// Base class that will manage the interaction between the player and levels
class Game
{
	protected:
		int x_coor = 3;
		int y_coor = 2;
		vector<vector<string>> vect;
		bool arrived = false;
	public:

		// method to receive the map design of the level and make use of it
		void use_map(vector<vector<string>> a)
		{
			vect = a;
		}

		// method to print out the map to the console and the location of the player
		virtual void print_map()
		{
			vect[y_coor][x_coor] = "p";
			for (int i=0; i<vect.size(); i++)
				{
					for (int j=0; j<vect[0].size(); j++)
						{
							if (vect[i][j] == "p")// colouring p
							{
								cout << "\033[0;34m"; // blue colour
								cout << vect[i][j];	
								cout << "\033[0m";
							}
							else if (vect[i][j] == "f") // colouring f
							{
								cout << "\x1b[31m"; // red colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else
								cout << vect[i][j];
						}
					cout << endl;
				}
		}

		virtual void move(string com)
		{
			try
				{
			// if the player enters w, the player's position will be updated to 1 unit up
			if (com == "w" && !((y_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				y_coor--;
			}
			// if the player enters s, the player's position will be updated to 1 unit down
			else if (com == "s" && !((y_coor+1) == vect.size()-1))
			{
				vect[y_coor][x_coor] = ".";
				y_coor++;
			}
			// if the player enters a, the player's position will be updated to 1 unit to the left
			else if (com == "a" && !((x_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				x_coor--;
			}
			// if the player enters d, the player's position will be updated to 1 unit to the right
			else if (com == "d" && !((x_coor+1) == vect[0].size()-1))
			{
				vect[y_coor][x_coor] = ".";
				x_coor++;
			}
			// if the player does not enter any of the accepted keys, the program will throw an error
			else if (!(com == "w" || com == "s" || com == "a" || com == "d"))
				throw InvalidCommand();
			// if the player tries to move outside of the map, the programm will throw an error
			else					
				throw OutOfBoundary();

			// evaluates whether the player has reached the flag or moved towards the wall
			if (vect[y_coor][x_coor] == "f")
				arrived = true;
				}
			catch (OutOfBoundary& error)
				{
					cout << error.error() << endl;
				}
			catch (InvalidCommand& error)
				{
					cout << error.error() << endl;
				}
		}


		// if the player reaches the flag, this method will return true
		bool win()
		{
			if (arrived)
				return true;
			else
				return false;
		}

		// a method to guide the player through the game
		virtual void manual()
		{
			cout << "=========================================================" << endl;
			cout << "Welcome to \'Maze Escape\'! The goal of this game is to"   << endl; 
			cout << "move your character (indicated as \'p\') by entering the"  << endl;
			cout << "key w,a,s,d to move up, left, down, right respectively"    << endl;
			cout << "until you reach the flag (indicated as \'f\')"             << endl;
			cout << "=========================================================" << endl;
			cout << endl;
		}
};
	
// derived class of Game for level 1
class Level_1: public Game
{
public:
void manual()
{
	cout << "=========================================================" << endl;
	cout << "Move your character until you reach the flag"              << endl;
	cout << "=========================================================" << endl;
}

};

// derived class of Game for level 2
class Level_2: public Game
{
public:
void manual()
{
	cout << "=========================================================" << endl;
	cout << "Touching the wall (indicated as \'‖\' or \'=\') will bring"<< endl;
	cout << "you back to the starting point"                            << endl;
	cout << "=========================================================" << endl;
}

	virtual void move(string com)
		{
			try
				{
			// if the player enters w, the player's position will be updated to 1 unit up
			if (com == "w" && !((y_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				y_coor--;
			}
			// if the player enters s, the player's position will be updated to 1 unit down
			else if (com == "s" && !((y_coor+1) == vect.size()-1))
			{
				vect[y_coor][x_coor] = ".";
				y_coor++;
			}
			// if the player enters a, the player's position will be updated to 1 unit to the left
			else if (com == "a" && !((x_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				x_coor--;
			}
			// if the player enters d, the player's position will be updated to 1 unit to the right
			else if (com == "d" && !((x_coor+1) == vect[0].size()-1))
			{
				vect[y_coor][x_coor] = ".";
				x_coor++;
			}
			// if the player does not enter any of the accepted keys, the program will throw an error
			else if (!(com == "w" || com == "s" || com == "a" || com == "d"))
				throw InvalidCommand();
			// if the player tries to move outside of the map, the programm will throw an error
			else					
				throw OutOfBoundary();

			// evaluates whether the player has reached the flag or moved towards the wall
			if (vect[y_coor][x_coor] == "f")
				arrived = true;
			else if (vect[y_coor][x_coor] == "‖" || vect[y_coor][x_coor] == "=") 
			{
				y_coor = 2;
				x_coor = 3;
				throw collision();
			}
			
				}
			catch (OutOfBoundary& error)
				{
					cout << error.error() << endl;
				}
			catch (InvalidCommand& error)
				{
					cout << error.error() << endl;
				}
			catch (collision& error)
				{
					cout << error.error() << endl;
				}
		}
};

// derived class of Game for level 3
class Level_3: public Game
{
public:

void manual()
{
	cout << "=========================================================" << endl;
	cout << "You cannot go through the gate (indicated as \'%\') until" << endl;
	cout << "you open it with a key (indicated as \'@\'). Gates are in" << endl;
	cout << "different colours indicating that they can only be opened" << endl;
	cout << "with the corresponding colour of the key"                  << endl;
	cout << "=========================================================" << endl;
}
	// a copied method of move() from Game class but with slightly different interactions with the player and the level
	void move(string com) 
		{
			try
				{
			if (com == "w" && !((y_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				y_coor--;
			}
			else if (com == "s" && !((y_coor+1) == vect.size()-1))
			{
				vect[y_coor][x_coor] = ".";
				y_coor++;
			}
			else if (com == "a" && !((x_coor-1) == 0))
			{
				vect[y_coor][x_coor] = ".";
				x_coor--;
			}
			else if (com == "d" && !((x_coor+1) == vect[0].size()-1))
			{
				vect[y_coor][x_coor] = ".";
				x_coor++;
			}
			else if (!(com == "w" || com == "s" || com == "a" || com == "d"))
				throw InvalidCommand();
			else					
				throw OutOfBoundary();

			if (vect[y_coor][x_coor] == "f")
				arrived = true;
			// if the player hits the wall, the keys and gates will be spawned back to original places
			else if (vect[y_coor][x_coor] == "‖" || vect[y_coor][x_coor] == "=") 
			{
				y_coor = 2;
				x_coor = 3;
				vect[3][2] = "%";
				vect[5][5] = "@";
				vect[6][8] = "%";
				vect[8][10] = "@";
				throw collision();
			}
			else if (vect[y_coor][x_coor] == "%")
			{
				y_coor = 2;
				x_coor = 3;
				throw ClosedGate();
			}
			// if the player gets the key, the gate will be opened
			else if (y_coor == 5 && x_coor == 5)
			{
				vect[6][8] = ".";
			}
			// if the player gets the key, the gate will be opened
			else if (y_coor == 8 && x_coor == 10)
			{
				vect[3][2] = ".";
			}
			
				}
			catch (OutOfBoundary& error)
				{
					cout << error.error() << endl;
				}
			catch (InvalidCommand& error)
				{
					cout << error.error() << endl;
				}
			catch (collision& error)
				{
					cout << error.error() << endl;
				}
			catch (ClosedGate& error)
				{
					cout << error.error() << endl;
				}
		}

		// a copied method of print_map() from Game class but with colourings of additional objects in this level
		void print_map()
		{
			vect[y_coor][x_coor] = "p";
			for (int i=0; i<vect.size(); i++)
				{
					for (int j=0; j<vect[0].size(); j++)
						{
							if(i == y_coor && j == x_coor)
							{
								cout << "\033[0;34m"; // blue colour
								cout << vect[i][j];	
								cout << "\033[0m";
							}
							else if (vect[i][j] == "f")
							{
								cout << "\x1b[31m"; // red colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else if (i == 5 && j == 5) // colouring the first @
							{
								cout << "\033[0;32m"; // green colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else if (i == 6 && j == 8) // colouring the first %
							{
								cout << "\033[0;32m"; // green colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else if (i == 8 && j == 10) // colouring the second @
							{
								cout << "\033[0;36m"; // cyan colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else if (i == 3 && j == 2) // colouring the second %
							{
								cout << "\033[0;36m"; // cyan colour
								cout << vect[i][j];
								cout << "\033[0m";
							}
							else
								cout << vect[i][j];
						}
					cout << endl;
				}
		}

		
};

int main()
{
	string command;
// map designs of each level in 2d vector forms
	vector<vector<string>> vect1 = 
{
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
	{"|", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "|"},
	{"|", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "|"},
	{"|", ".", ".", ".", ".", ".", ".", ".", ".", "f", ".", ".", "|"},
	{"|", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "|"},
	{"|", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "|"},
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"}
};

	vector<vector<string>> vect2 = 
{
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
	{"|", ".", "‖", ".", ".", ".", ".", "‖", ".", ".", "‖", ".", "|"},
	{"|", ".", "‖", ".", ".", "‖", ".", "‖", ".", "=", "‖", "f", "|"},
	{"|", ".", ".", ".", ".", "‖", ".", ".", ".", ".", "‖", ".", "|"},
	{"|", "=", "=", "=", ".", "=", "=", "=", ".", "=", "‖", ".", "|"},
	{"|", ".", ".", ".", ".", ".", ".", "‖", ".", ".", ".", ".", "|"},
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"}
};

	vector<vector<string>> vect3 =
{
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
	{"|", ".", "‖", ".", "‖", ".", ".", ".", ".", ".", ".", ".", "|"},
	{"|", "f", "‖", ".", "‖", ".", "‖", ".", "‖", ".", "‖", ".", "|"},
	{"|", ".", "%", ".", ".", ".", "‖", ".", "‖", ".", "‖", ".", "|"},
	{"|", ".", "‖", "=", "=", "=", "‖", ".", "‖", ".", "‖", ".", "|"},
	{"|", ".", "‖", ".", ".", "@", "‖", ".", "‖", "=", "‖", ".", "|"},
	{"|", "=", "‖", ".", "‖", "=", "=", ".", "%", ".", "‖", ".", "|"},
	{"|", ".", "‖", ".", "‖", "=", "=", ".", "‖", ".", "‖", "=", "|"},
	{"|", ".", ".", ".", ".", ".", ".", ".", "‖", ".", "@", ".", "|"},
	{"~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
};


	// array of pointers to store objects of classes of each levels
	Game *level[3];
	Game game;
	Level_1 lvl1;
	Level_2 lvl2;
	Level_3 lvl3;
	level[0] = &lvl1;
	level[1] = &lvl2;
	level[2] = &lvl3;

	// array of pointers to store the map design of each levels
	vector<vector<string>> *map[3];
	map[0] = &vect1;
	map[1] = &vect2;
	map[2] = &vect3;


	game.manual();
	// for loop that will iterate through the array of objects
	for (int i=0; i<3; i++)
		{
			level[i]->manual();
			cout << endl;
			cout << "Level " << i+1 << endl;
			level[i]->use_map(*map[i]);
			level[i]->print_map();
			// while loop will reptitvely prompt the user for the command until the player reaches the flag and win() method returns true
			do
			{
				cout << "Enter: ";
				cin >> command;
				cout << endl;
				level[i]->move(command);
				level[i]->print_map();
				// if the win() method returned true, the program will output a message indicating that the level has been completed
				if (level[i]->win())
				{
					cout << "Level clear!" << endl;
					cout << endl;
				}		
			} while (!level[i]->win());
		}
		cout << "Thank you for playing!" << endl;
		cout << endl;
		cout << "Creator: John Baek\n";

}