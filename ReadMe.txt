// ======================= GLOBAL FUNCTION EXPLANATION ============================= //

Function name 'isValidSequence' works as follows

I takes an array of AbstractHex game references. If it finds a valid sequence between those games
it return true otherwise it returns false

ex:

	arr[0]
		A B C D E
	1 . . . x .
	2 . . . . .
	3 . . . . .
	4 . . . . .
	5 . . . . .

	arr[0]
		A B C D E
	1 . . . x .
	2 o . . . .
	3 . . . . .
	4 . . . . .
	5 . . . . .

	arr[0]
		A B C D E
	1 . . . x .
	2 o . . . .
	3 . . x . .
	4 . . . . .
	5 . . . . .

	arr[0]
		A B C D E
	1 . . . x .
	2 o . . . o
	3 . . x . .
	4 . . . . .
	5 . . . . .


	Result would be 'true' for this examples

ex2:
	arr[0]
		A B C D E
	1 x . . x .
	2 . . o . .
	3 . . . . .
	4 o . . . .
	5 . . . . .

	arr[0]
		A B C D E
	1 x . . x .
	2 o o o . .
	3 x . . . .
	4 o . . . .
	5 . . . . .

	Result would be 'false' because there is not a valid sequence




// ========================= SCORING ALGORITHM ==================================== //

My score algorithm uses a backtracking algorithm.

It starts from top left to bottom right and tries to find the most valuable chain.


For x:
	If there is a neighbour in the right side +2 points
	If there is a neighbour at the top or the bottom +1 point

For o:
	If there is a neighbour in the right or the left side +1 point
	If there is a neighbour at the bottom +2 point

ex1:

For a board like this

expected score is 5

	A B C D E
1	x x . . .
2	. . . . .
3	. x . . .
4	. x x x .
5	. . . . .

It starts from A1

A1 -> returns 2 points
A2 -> returns 0
B3 -> returns 5 *
B4 -> returns 4
C4 -> returns 2
D5 -> returns 0


ex:2

For a board like this

	A B C D E
1	. o o . .
2	. . o . .
3	o . . . .
4	o o o o .
5	. . . o .

expected score is 7

It starts from A1

B1 -> returns 3 points
C1 -> returns 2
C2 -> returns 5
A3 -> returns 7 *
A4 -> returns 5
B4 -> returns 4
C4 -> returns 3
D4 -> returns 3
D5 -> returns 0
