# C++ OOP Chess Computing Program


## 1.Requirements and To-Do Checklist

To do:

    • Player vs Player

    • Chess opening explorer (either manually or pgn generated)

    • Player vs Computer (Purpose: search for 'best' move)

        Level 1 - Brute search 1/3ply (very bad)

        Level 2 - Minimax algorithm

Preferably make a user interface for better viewing experience, but will start with terminal


Course specifications: 

    1.1.  Abstract base class for pieces

    1.2.  Derived classes for each piece

    1.3.  Pure virtual functions to get allowed moves

    1.4.  Board class that contains the pieces


    ### Minimum functionality:

    1.5.  Allowed moves for each piece

    1.6.  Output function that prints representation of board

    1.7.  Method to store moves


        1.1  ->
        1.2  -> King, Queen, Bishop, Knight, Rook, Pawn, No Piece
        1.3  ->
        1.4  ->
        1.5  -> Another option during game/can also be done using UI by highlighting squares
                Problems could arise when looking at castling, king moving into check, en passant
                also stale mate -> draw
        1.6  ->
        1.7  -> Saving and loading games will actually be very useful when debugging. Can just load
                into a game at a critical moment where the program crashed previously.
                Saving games can be done using PGN
                Loading in position using FEN

Code design:

    1.8.  Source code organisation (need seperate headers, class files and namespaces)

    1.9.  Use of templates to create generic classes

    1.10. Dynamic memory allocation (and garbage collection) tom improve flexibility 
          (especially for run-time polymorphism)

    1.11. Smart pointers; the use of move semantics

    1.12. error detection/exception handling

    1.13. use of STL (e.g. use of container class)

    1.14. lambda functions

    1.15. a substantial input/output handling interface


        1.8   -> seperate files: main (option selection), pieces, board, opening tree, input/output, computer evaluation/engine
        1.9   -> pieces class then derived class for each piece
        1.10  -> board size can be an array (8x8=64) But perhaps easier to use 10x12 for illegal move checks
                 If time allows look at BitBoards -> more efficient way of board representation 
                    - especially useful when looking at chess engines as they will look through thousands of positions/sec.
        1.11  -> Move semantics for pieces moving I guess during the array. or perhaps when a pawn gets promoted to a piece
                 -> need to look at this in more detail. Perhaps this can be incorporated when a piece gets taken.
        1.12  -> illegal moves
        1.13  ->
        1.14  ->
        1.15  ->


## 2.1 Board game representation (Loading/Saving games)

### Forsyth-Edwards Notation [FEN] -> can start game from any position

file extension .fen 

https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation

Here is the FEN for the starting position:
<pre>
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
</pre>

It is crucial for chess960 as it can represent the starting positions.

### Portable Game Notation

1. devised in 1993 by Steven J.Edwards
2. structured for easy reading and writing by human users and for easy parsing and generation
    by computer programs.

https://en.wikipedia.org/wiki/Portable_Game_Notation

Here is the PGN format of the 29th game of the [[Fischer–Spassky (1992 match)|1992 match]] played in [[Federal Republic of Yugoslavia|Yugoslavia]] between [[Bobby Fischer]] and [[Boris Spassky]]:
<pre>
[Event "F/S Return Match"]
[Site "Belgrade, Serbia JUG"]
[Date "1992.11.04"]
[Round "29"]
[White "Fischer, Robert J."]
[Black "Spassky, Boris V."]
[Result "1/2-1/2"]

1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 {This opening is called the Ruy Lopez.}
4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 d6 8. c3 O-O 9. h3 Nb8 10. d4 Nbd7
11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15. Nb1 h6 16. Bh4 c5 17. dxe5
Nxe4 18. Bxe7 Qxe7 19. exd6 Qf6 20. Nbd2 Nxd6 21. Nc4 Nxc4 22. Bxc4 Nb6
23. Ne5 Rae8 24. Bxf7+ Rxf7 25. Nxf7 Rxe1+ 26. Qxe1 Kxf7 27. Qe3 Qg5 28. Qxg5
hxg5 29. b3 Ke6 30. a3 Kd6 31. axb4 cxb4 32. Ra5 Nd5 33. f3 Bc8 34. Kf2 Bf5
35. Ra7 g6 36. Ra6+ Kc5 37. Ke1 Nf4 38. g3 Nxh3 39. Kd2 Kb5 40. Rd6 Kc5 41. Ra6
Nf2 42. g4 Bd3 43. Re6 1/2-1/2
</pre>


Incorporating PGN loading and saving would be good for the opening tree as almost all games are saved in this format.


## 2.2 Board Game Representation (in house)

Usually want to utilize more than one board representation at different times, for efficiency -> execution efficiency and memory footprint
but we also need to consider the complexity. If it is simpler, it may be easier to debug.

Array piece lists were first used in early programs but the newer approach is bitboards which are found to be more efficient but a more
elaborate approach.

A full description requires: 
1. location of each piece
2. whose turn it is to move
3. 50-move draw rule
4. castling abailability
5. en passant capture possibility
6. (three-fold repetition draw) -> but will need a complete history of the game from the last irreversible action,
can be usually tracked in seperate data structures.

Space list array (8x8) two dimensional or 64 one dimensional 

1.  0 -> empty
2. positive -> white
3. negative -> black
4. with pawn = 1, knight = 2 ...  

Problem with this is checking that each move stays on the board therefore:

10x12 Board array method (Array of length 120) -> much better than a 8x8(=64) array due to the simplicity of finding illegal moves

https://www.chessprogramming.org/10x12_Board

---> Kozdrowicki, Edward & Cooper, Dennis. (1973). COKO III: the Cooper-Koz chess program. Commun. ACM. 16. 411-427. 10.1145/362280.362288. 

Discussed above of an implementationn in Fortran. 


#### Bitboards

64-bit sequence of bits (0 ir 1) -> indicates the absence or presence of samne state of each space on the board. A board can then be
represented using a series of bitboards. 

e.g. Series of bitboards for each piece type, for each side.