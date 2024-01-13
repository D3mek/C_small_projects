void connect_four();

void initialize_board(int rows, int cols, char board[rows][cols]);

void print_board(int rows, int cols, const char board[rows][cols]);

int is_valid_move(int rows, int cols, const char board[rows][cols], int col);

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece);

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece);

int is_board_full(int rows, int cols, const char board[rows][cols]);
