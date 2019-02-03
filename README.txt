
++++++++++++++++++++++++++++++++++++++++++++++++++
Team 11: King Me!
++++++++++++++++++++++++++++++++++++++++++++++++++
By Aria Javanmard	Armando Rodriguez	Keenan Lau	Marshall Payatt		Michael Zeng  
University of California Irvine

Alpha Version
Feb 1, 2019

Copyright © 2019 by Marshall Payatt, Keenan Lau, Zhifang Zeng, Armando Rodriguez, Aria Javanmard
All rights reserved. This book and program or any portion thereof may not be reproduced or used in any manner whatsoever without the express written permission of the publisher except for the use of brief quotations in a book review

Background image used: https://www.udemy.com/learn-chess/

++++++++++++++++++++++++++++++++++++++++++++++++++
Gameplay
++++++++++++++++++++++++++++++++++++++++++++++++++

In the alpha release, only AI vs AI is playable. Launching the program will open the Chess Board GUI, and two AI players will begin automatically without any user input. The program closes if one AI player wins. In future versions we will have safeguards against stalemates but the current version will continue plating until the user closes the program.


++++++++++++++++++++++++++++++++++++++++++++++++++
Error Messages
++++++++++++++++++++++++++++++++++++++++++++++++++

Illegal Move: Appears when a player attempts a move that is not permitted by the rules of chess. See Glossary on page 3 for more information.

Illegal Selection: Appears when a player selects a piece that does not belong to the current player or is unoccupied.

King in Check: Appears when a player makes a move that does not resolve check. See the entry for King in the Glossary on page 5 for more information

Error: a catch-all for unforeseen errors in the game program.


++++++++++++++++++++++++++++++++++++++++++++++++++
Installation
++++++++++++++++++++++++++++++++++++++++++++++++++

#To install this program in commandline:
Change into the directory by running: 
    cd chess
Compile code by running:
    mkdir build
    cd build
    cmake ..
    make
Run the program running
    cd ..
    ./bin/chess


#To install this program using easy script:
Change into the directory by running: 
    cd chess
To compile run this command:
    bash SuperSimpleIntstallAndRun.sh

++++++++++++++++++++++++++++++++++++++++++++++++++
Glossary
++++++++++++++++++++++++++++++++++++++++++++++++++

Terminology

Capture  -  When a piece is taken by another from the opposite player, it is removed from the board.

Check  -  When a King is threatened by an opponent’s pieces. The player’s next move must protect the king in some way.

CheckMate  -  When the King is put in check, but the player has no means of protecting it from being captured on the opponent's next turn. When you are out of moves in this situation, you lose.


Pieces

Pawn  -  A piece that is able to move forward two spaces on its first move and only one space forward on subsequent turns. It cannot advance forward if blocked by the enemy or friendly pieces. It is only able to capture in the forward diagonal directions. If it makes it to the enemies end of the board, it can be promoted to another kind of piece except for King or Pawn. 

Rook  -  A piece that can move and capture vertically and horizontally unless obstructed by another piece.

Bishop  -  A piece that can move and capture diagonally unless obstructed by another piece.

Knight  -  A piece that can move in an ‘L’ shape of two spaces in one of the cardinal directions, then one in a perpendicular direction to its original heading. It can jump over other pieces and can capture enemy pieces on the space it lands. It cannot land on a space occupied by a friendly piece.

Queen  -  A piece that can move both horizontally, vertically and diagonally like both the Rook or Bishop. Along these directions, she can capture as well as move as long as she is unobstructed.

King  -  The King is the most valuable piece. It can move and capture within one space horizontally, vertically as well as diagonally. It cannot move to a space that would put it in check, which would be considered an illegal move. The game is lost if the king is put into checkmate, where the player cannot make a move that would save it.


Advanced Moves

Castling  -  An advanced move that can be used when a king is separated from a Rook of its own color by two or three empty spaces in the horizontal direction. You are allowed to move both the King and Rook at the same time by moving the king two spaces in the direction of the Rook as well moving the Rook to space next to the king's new position on the opposite side of the Rook’s original position.
Castling is only permissible if all of the following conditions hold:
	The king and rook involved in castling must not have previously moved
	There are no pieces between the king and the rook
	The king may not currently be in check, nor may the king pass through or end up in a square that is under attack by an enemy piece, although the rook is permitted to be under attack and to pass over an attacked square.
	The king and the rook must be on the same row.

En Passant  -  An advanced move that allows a pawn to capture a pawn under very specific conditions. It can occur when a pawn is moved for the first time two spaces to avoid being captured on the space directly in front of it by an opposing pawn that is two spaces in front and one space to either side. The enemy pawn is only able to pull off this move immediately on the next turn. If the enemy pawn is allowed to move diagonally behind the first pawn and can capture the first pawn from behind.


