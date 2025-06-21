const int boardSize = 5;              // <-- ‘char int’ was invalid
char board[boardSize][boardSize] = {
  {'.','.','.','.','.'},
  {'.','.','.','S','.'},  // B4
  {'.','.','S','.','.'},  // C3
  {'.','.','.','.','.'},
  {'.','.','.','.','.'}
};

void setup() {
  Serial.begin(9600);
  while (!Serial);       // wait for PC
  Serial.println("Arduino command ship is ready!");
  Serial.println("READY");
}

void loop() {
  if (Serial.available() >= 2) {      // make sure we have both bytes
    char rowChar = Serial.read();
    char colChar = Serial.read();

    int row = rowChar - 'A';
    int col = colChar - '1';

    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
      if (board[row][col] == 'S') {
        board[row][col] = 'H';
        Serial.println("hit");
      } else {
        board[row][col] = 'X';
        Serial.println("miss");
      }
    } else {
      Serial.println("Invalid");
    }
  }
}
