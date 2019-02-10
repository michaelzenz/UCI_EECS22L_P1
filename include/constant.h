
//hard code for different objects and situation
#define HUMAN 0
#define COMPUTER 1

#define PLAYER1 0
#define PLAYER2 1

#define WHITE 1
#define BLACK -1

//hard code for different kinds of pieces
#define BLANK 0
#define PAWN 1
#define PAWN_W 1
#define PAWN_B -1
#define KNIGHT 2
#define KNIGHT_W 2
#define KNIGHT_B -2
#define CASTLE 3
#define CASTLE_W 3
#define CASTLE_B -3
#define BISHOP 4
#define BISHOP_W 4
#define BISHOP_B -4
#define QUEEN 5
#define QUEEN_W 5
#define QUEEN_B -5
#define KING 6
#define KING_W 6
#define KING_B -6

//code for special moves
#define NOSPECIAL 0
#define ENPASSANT 1
#define CASTLING 2
#define PROMOTION 3

//the size of char array that should be used when 
//calling stack_ and convertion between move and string functions
#define STR_NODE_SIZE 80

#define CUR_PLAYER_LOSE 1
#define CUR_PLAYER_WIN 2
#define QUIT 3
