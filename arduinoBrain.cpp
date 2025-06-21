/*
 * This is the five by five board with a couple of ships. 
 * We are going to wait for coordinate input sent over via serial, maybe A2
 * Check if it is a hit or miss
 * Send back a response
 * 
 * Do i need to close the serial at the end. since we are physically plugged in? and is it a socket?
 *
 * . = empty, S = ship, H = hit, X = empty
 */

String incomingData = "";
char int boardSize = 5;
char board[boardSize][boardSize] ={
	{'.','.','.','.','.'},
	{'.','.','.','S','.'}, // B,4
	{'.','.','S','.','.'}, // C,3
	{'.','.','.','.','.'},
	{'.','.','.','.','.'},
};

void setup(){
	Serial.begin(9600);
	while (!Serial);
	Serial.println("Arduino command ship is ready!");
};

void loop(){
	if (Serial.available()){
		char rowChar = Serial.read();
		while(!Serial.available()); // awaiting column
		char colChar = Serial.read();
		
		int row = rowChar - 'A';
		int column = colChar - '1';
		
		// should it be board size - 1 since we start at 0-4?
		if (row >= 0 && row < boardSize && col >=0 && col < boardSize){
			if (board[row][col] == "S"){
				board[row][col] = 'H';
				Serial.println("hit");
			} else {
				// if it is already X, should we handle it differently for memory constraints
				board[row][col] = 'X'; // empty
				Serial.println("miss");
			}
		} else {
			Serial.println("Invalid, please enter coords for 5x5 board");
		}
	}
}
