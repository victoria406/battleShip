#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int boardSize = 5;
char board[boardSize][boardSize];

void printBoard(){
	cout << "  1 2 3 4 5\n";
	for (int i = 0; i < boardSize; i++){
		cout << char('A' + i) << " ";
		for (int j =0; j < boardSize; j ++){
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

void initBoard(){
	for(int i = 0; i < boardSize; ++i)
		for (int j = 0; j < boardSize; ++j)
			board[i][j] = '.';
}

int main(){
	cout << "[DEBUG] Starting...\n";
	HANDLE hSerial;
	hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

	if(hSerial == INVALID_HANDLE_VALUE){
		cerr << "Error opening serial port\n";
		return 1;
	}

	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)){
			cerr << "Failed to get serial params\n";
			return 1;
	}

	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams)){
		cerr << "Failed to set serial port state\n";
		return 1;
	}

	cout << "Connected to Arduino Battleship! \n";
	initBoard();

	while (true){
		printBoard();
		string input;
		cout << "Enter target (ex B3, cap sens) or Q to quit: ";
		cin >> input;
	if (input == "Q" || input == "q") break;

	if (input.size() != 2 || input[0] < 'A' || input[0] > 'E' || input[1] < '1' || input[1] > '5'){
		cout << "Invalid input. Format is A1 to E5.\n";
		continue;
	}

	DWORD bytesWritten, bytesRead;
	char buffer[1];

	WriteFile(hSerial, &input[0], 1, &bytesWritten, NULL);
	Sleep(10);
	WriteFile(hSerial, &input[1], 1, &bytesWritten, NULL);

	char response[32] = {0}; // woah strange syntax, reading more about this
	ReadFile(hSerial, response, sizeof(response) - 1, &bytesWritten, NULL);
	string result(response);

	int row = input[0] - 'A';
	int col = input[1] - '1';

	if (result.find("hit") != string::npos){
		board[row][col] = 'H';
		cout << ">> HIT.\n";
	} else if (result.find("miss") != string::npos){
		board[row][col] = 'X';
		cout << "MISS.\n";
	} else{
		cout << "Bad responss: " << result << "\n";
	}

	cout << "\n";
	}
	CloseHandle(hSerial);
	return 0;
}
