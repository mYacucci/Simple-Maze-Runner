#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "point2D.h"
#include "Stack.h"


// Note that this app is not optimized


using namespace std;

enum Direction {DOWN, LEFT, RIGHT, UP};


// prototypes
char getPlayerImage(Direction direction);
void dislpayTheMaze(int maxRows, int maxColumns, char maze[][20]);


int main(int argc, char** argv) {

	const char visited = '+';

	// offsets for moving within the 2D array
	int currentRow = 0;
	int currentColumn = 1;

	Point2D lastKnownPosition;
	Point2D StartingPoint(currentColumn, currentRow);
	Point2D endingPoint(14, 11);


	
	Direction direction = DOWN;
	int numberOfDirectionChanges = 0;

	bool finished = false;

	const int maxRows = 12;
	const int maxColumns = 20;
	char maze[maxRows][maxColumns];

	string filspc;

	Stack<Point2D> stack(300);

	ifstream inputFileStream;

	if(argc != 2) {
		cout << "Unable to open the file " << argv[1] << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	filspc = string(argv[1]);
	inputFileStream.open(filspc);
	if( !inputFileStream) {
		cout << "Unable to locate the file" << argv[1] << endl;
		system("pause");
		return EXIT_FAILURE;
	}


	// read in the maze
	for(int row = 0; row < maxRows; ++ row)
		for( int column = 0; column < maxColumns; ++column)
			inputFileStream  >> maze[row][column];


	// output the maze
	dislpayTheMaze(maxRows, maxColumns, maze);
	
	system("pause");

	

// TODO current problem is stuck in blind canyon
	while(!finished) {

		// sanity test
		// output the maze
		system("cls");
		for(int row = 0; row < maxRows; ++ row){
			for( int column = 0; column < maxColumns; ++column){
				if( maze[row][column] == '_')
					cout << ' ';
				else
					cout << maze[row][column];
			}
			cout << endl;
		}
		maze[currentRow][currentColumn]	= getPlayerImage(direction);				// draw yourself for the first time	
		cout << "Row " << currentRow << " Column " << currentColumn << endl;
		cout << "Direction = " << direction << endl;
		cout << "Number of turns = " << numberOfDirectionChanges << endl << endl;
		
		// pauses the program to show each move of the player
		system("pause");

		
		// move the player
		switch(direction) {
	

			case DOWN:
				// move DOWN if possible else change direction or backtrack
				if(currentRow +1 < maxRows && maze[currentRow +1][currentColumn] == '_'  && maze[currentRow +1][currentColumn] != '.'){
					// ok to move
					numberOfDirectionChanges = 0;										// since you were able to move 
					maze[currentRow][currentColumn]	= '.';								// leave cookie crumb	
					stack.push(Point2D( currentColumn, currentRow));					// remember where you came from
					currentRow++;														// move DOWN
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself	
					
				}
				else {
					direction = LEFT;
					numberOfDirectionChanges++;

					// have you turned a full circle yet
					if (numberOfDirectionChanges >= 4) {
						numberOfDirectionChanges = 0;
						maze[currentRow][currentColumn]	= '.';							// leave cookie crumb	
						lastKnownPosition = stack.top();
						stack.pop();
						currentRow = lastKnownPosition.y;
						currentColumn = lastKnownPosition.x;
					}
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself
				}
				break;

			case LEFT:
				// move LEFT if possible else change direction or backtrack
				if(currentColumn -1  >=  0 && maze[currentRow][currentColumn - 1] == '_'  && maze[currentRow][currentColumn - 1] != '.'){
					// ok to move
					numberOfDirectionChanges = 0;										// since you were able to move 
					maze[currentRow][currentColumn]	= '.';								// leave cookie crumb	
					stack.push(Point2D(currentColumn, currentRow));						// remember where you came from
					currentColumn--;													// move LEFT
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself	
				}
				else {
					direction = RIGHT;
					numberOfDirectionChanges++;

					// have you turned a full circle yet
					if (numberOfDirectionChanges >= 4) {
						numberOfDirectionChanges = 0;
						maze[currentRow][currentColumn]	= '.';							// leave cookie crumb	
						lastKnownPosition = stack.top();
						stack.pop();
						currentRow = lastKnownPosition.y;
						currentColumn = lastKnownPosition.x;
					}
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself
				}
				break;
		
			case RIGHT:
				// move RIGHT if possible else change direction or backtrack
				if(currentColumn + 1  < maxColumns && maze[currentRow ][currentColumn + 1] == '_'  && maze[currentRow][currentColumn + 1] != '.'){
					// ok to move
					numberOfDirectionChanges = 0;										// since you were able to move 
					maze[currentRow][currentColumn]	= '.';								// leave cookie crumb	
					stack.push(Point2D(currentColumn, currentRow));						// remember where you came from
					currentColumn++;													// move RIGHT
					maze[currentRow][currentColumn] = getPlayerImage(direction);		// draw yourself	
				}
				else {
					direction = UP;
					numberOfDirectionChanges++;

					// have you turned a full circle yet
					if (numberOfDirectionChanges >= 4) {
						numberOfDirectionChanges = 0;
						maze[currentRow][currentColumn]	= '.';							// leave cookie crumb	
						lastKnownPosition = stack.top();
						stack.pop();
						currentRow = lastKnownPosition.y;
						currentColumn = lastKnownPosition.x;
					}
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself
				}
				break;

			case UP:
				// move DOWN if possible else change direction or backtrack
				if(currentRow - 1 >= 0 && maze[currentRow - 1][currentColumn] == '_'  && maze[currentRow -1][currentColumn] != '.'){
					// ok to move
					numberOfDirectionChanges = 0;										// since you were able to move 
					maze[currentRow][currentColumn]	= '.';								// leave cookie crumb	
					stack.push(Point2D(currentColumn, currentRow));						// remember where you came from
					currentRow--;														// move UP
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself	

				
				}
				else {
					direction = DOWN;
					numberOfDirectionChanges++;

					// have you turned a full circle yet
					if (numberOfDirectionChanges >= 4) {
						numberOfDirectionChanges = 0;
						maze[currentRow][currentColumn]	= '.';							// leave cookie crumb	
						lastKnownPosition = stack.top();
						stack.pop();
						currentRow = lastKnownPosition.y;
						currentColumn = lastKnownPosition.x;
					}
					maze[currentRow][currentColumn]	= getPlayerImage(direction);		// draw yourself
				}
				break;

			// now that you moved one way or the other, put yourself in the maze
			maze[currentRow][currentColumn]	= getPlayerImage(direction);						// draw yourself
		
			} // end of switch

		// check to see if finished
		if(	currentColumn == 14 && currentRow == 11)
			finished = true;
		else 
			finished = false;
		//finished = endingPoint.equals(Point2D(currentColumn, currentRow));

	}


	//assume here that the maze was solvable
	cout << "You did it!" << endl;
	system("pause");

	return EXIT_SUCCESS;
}


char getPlayerImage(Direction direction) {

	switch (direction) {

	case DOWN:
		return 'v';

	case LEFT:
		return '<';

	case RIGHT:
		return '>';

	case UP:
		return '^';
	}

}

void dislpayTheMaze(int maxRows, int maxColumns, char maze[][20]) {
	for (int row = 0; row < maxRows; ++row) {
		for (int column = 0; column < maxColumns; ++column) {
			if (maze[row][column] == '_')
				cout << ' ';
			else
				cout << maze[row][column];
		}
		cout << endl;
	}
}







