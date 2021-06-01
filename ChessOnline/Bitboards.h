#pragma once
#include <iostream>
#include <bitset>

typedef unsigned long long  U64;
#define C64(constantU64) constantU64##ULL

U64 notA = 0xfefefefefefefefeULL;
U64 notH = 0x7f7f7f7f7f7f7f7fULL;

void printBitBoard(U64 board) {
	int field = 63;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			if ((1ULL << field) & board)
				std::cout << "X";
			else
				std::cout << "-";
			field -= 1;
		}
		std::cout << std::endl;
	}

	std::bitset<64> x(board);
	std::cout << x << std::endl;
}

U64 fillPawns(bool isWhite)
{
	if (isWhite)
	{
		U64 wPawns = 0ULL;
		for (int i = 8; i <= 15; i++)
		{
			wPawns |= (1ULL << i);
		}

		return wPawns;
	}
	else {
		U64 bPawns = 0ULL;
		for (int i = 48; i <= 55; i++)
		{
			bPawns |= (1ULL << i);
		}

		return bPawns;
	}
}

U64 fillRooks(bool isWhite)
{
	if (isWhite)
	{
		U64 wRooks = 0ULL;
		wRooks |= (1ULL << 7);
		wRooks |= (1ULL << 0);

		return wRooks;
	}
	else {
		U64 bRooks = 0ULL;
		bRooks |= (1ULL << 63);
		bRooks |= (1ULL << 56);

		return bRooks;
	}
}

U64 fillKnights(bool isWhite)
{
	if (isWhite)
	{
		U64 wKnights = 0ULL;
		wKnights |= (1ULL << 1);
		wKnights |= (1ULL << 6);

		return wKnights;
	}
	else {
		U64 bKnights = 0ULL;
		bKnights |= (1ULL << 62);
		bKnights |= (1ULL << 57);

		return bKnights;
	}
}
U64 fillBishops(bool isWhite)
{
	if (isWhite)
	{
		U64 wBishops = 0ULL;
		wBishops |= (1ULL << 2);
		wBishops |= (1ULL << 5);

		return wBishops;
	}
	else {
		U64 bBishops = 0ULL;
		bBishops |= (1ULL << 61);
		bBishops |= (1ULL << 58);

		return bBishops;
	}
}

U64 fillQueens(bool isWhite, bool isWhiteFigure)
{
	U64 wQeen = 0ULL;

	if (isWhite)
	{
		if (isWhiteFigure) {
			wQeen |= (1ULL << 4);
			return wQeen;
		}
		else {
			wQeen |= (1ULL << 60);
			return wQeen;
		}
	}
	else {
		if (isWhiteFigure) {
			wQeen |= (1ULL << 3);
			return wQeen;
		}
		else {
			wQeen |= (1ULL << 59);
			return wQeen;
		}
	}
}

U64 fillKing(bool isWhite, bool isWhiteFigure)
{
	U64 wKing = 0ULL;

	if (isWhite)
	{
		if (isWhiteFigure) {
			wKing |= (1ULL << 3);
			return wKing;
		}
		else {
			wKing |= (1ULL << 59);
			return wKing;
		}
	}
	else {
		if (isWhiteFigure) {
			wKing |= (1ULL << 4);
			return wKing;
		}
		else {
			wKing |= (1ULL << 60);
			return wKing;
		}
	}
}


U64 northRookAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	/*
	flood |= buf = (buf << 8) & empty;
	flood |= buf = (buf << 8) & empty;
	flood |= buf = (buf << 8) & empty;
	flood |= buf = (buf << 8) & empty;
	flood |= buf = (buf << 8) & empty;
	flood |= buf = (buf << 8) & empty;
	flood |= (buf << 8) & empty;
	*/

	while (((buf << 8) & empty)) {
		flood |= buf = (buf << 8) & empty;
	}

	buf = buf << 8;
	flood = flood << 8;
	//printBitBoard(xd);

	//printBitBoard(flood);

	return flood - (buf & white);
}

U64 southRookAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	/*
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	std::cout << "ASDasdsdasdasasassadad" << std::endl;
	printBitBoard(((buf >> 8) & white));
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	flood |= buf = (buf >> 8) & empty;
	printBitBoard(buf);
	flood |= (buf >> 8) & empty;
	printBitBoard(buf);
	*/


	//std::cout << " southRookAttacks " << std::endl;

	//U64 xd = buf;

	while (((buf >> 8) & empty)) {
		flood |= buf = (buf >> 8) & empty;
	}

	buf = buf >> 8;
	flood = flood >> 8;

	return flood - (buf & white);
}

U64 eastRookAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notH;

	/*
	flood |= buf = (buf >> 1) & empty;
	flood |= buf = (buf >> 1) & empty;
	flood |= buf = (buf >> 1) & empty;
	flood |= buf = (buf >> 1) & empty;
	flood |= buf = (buf >> 1) & empty;
	flood |= buf = (buf >> 1) & empty;
	flood |= (buf >> 1) & empty;
	*/
	while (((buf >> 1) & empty)) {
		flood |= buf = (buf >> 1) & empty;
	}

	buf = buf >> 1;

	flood = (flood >> 1) - (buf & white); \

		return flood & notH;
}

U64 westRookAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notA;
	/*
	flood |= buf = (buf << 1) & empty;
	flood |= buf = (buf << 1) & empty;
	flood |= buf = (buf << 1) & empty;
	flood |= buf = (buf << 1) & empty;
	flood |= buf = (buf << 1) & empty;
	flood |= buf = (buf << 1) & empty;
	flood |= (buf << 1) & empty;
	*/
	while (((buf << 1) & empty)) {
		flood |= buf = (buf << 1) & empty;
	}

	buf = buf << 1;

	flood = (flood << 1) - (buf & white);

	return flood & notA;
}

U64 knightAttacks(U64 buf, U64 empty, U64 white) {

	U64 l1 = (buf >> 1) & 0x7f7f7f7f7f7f7f7fULL;
	U64 l2 = (buf >> 2) & 0x3f3f3f3f3f3f3f3fULL;
	U64 r1 = (buf << 1) & 0xfefefefefefefefeULL;
	U64 r2 = (buf << 2) & 0xfcfcfcfcfcfcfcfcULL;
	/*
		U64 myF1 = 0;
	U64 myF2 = 0;
	U64 myF3 = 0;
	U64 myF4 = 0;

	if (l1) myF1 = buf >> 1;
	if (l2) myF2 = buf >> 2;
	if (r1) myF3 = buf << 1;
	if (r2) myF4 = buf << 2;

	if (l1) myF1 = buf >> 1;
	if (l2) myF2 = buf >> 2;
	if (r1) myF3 = buf << 1;
	if (r2) myF4 = buf << 2;

	myF1 = myF1 | myF3;
	myF2 = myF2 | myF4;
	*/
	U64 h1 = l1 | r1;
	U64 h2 = l2 | r2;


	//myF1 = (myF1 << 16) & white | (myF1 >> 16) & white | (myF2 << 8) & white | (myF2 >> 8) & white;

	return (h1 << 16) - ((h1 << 16) & white) | (h1 >> 16) - ((h1 >> 16) & white) | (h2 << 8) - ((h2 << 8) & white) | (h2 >> 8) - ((h2 >> 8) & white);// -myF1;
}

U64 soWebishopAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notH;
	/*
	flood |= buf = (buf >> 9) & empty;
	flood |= buf = (buf >> 9) & empty;
	flood |= buf = (buf >> 9) & empty;
	flood |= buf = (buf >> 9) & empty;
	flood |= buf = (buf >> 9) & empty;
	flood |= buf = (buf >> 9) & empty;
	flood |= (buf >> 9) & empty;
	*/

	while (((buf >> 9) & empty)) {
		flood |= buf = (buf >> 9) & empty;
	}

	buf = buf >> 9;

	flood = (flood >> 9) - (buf & white);

	return flood & notH;
}

U64 noWebishopAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notH;
	/*/
	flood |= buf = (buf << 7) & empty;
	flood |= buf = (buf << 7) & empty;
	flood |= buf = (buf << 7) & empty;
	flood |= buf = (buf << 7) & empty;
	flood |= buf = (buf << 7) & empty;
	flood |= buf = (buf << 7) & empty;
	flood |= (buf << 7) & empty;
	*/

	while (((buf << 7) & empty)) {
		flood |= buf = (buf << 7) & empty;
	}

	buf = buf << 7;

	flood = (flood << 7) - (buf & white);

	return flood & notH;
}
U64 noEabishopAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notA;

	/*/
	flood |= buf = (buf << 9) & empty;
	flood |= buf = (buf << 9) & empty;
	flood |= buf = (buf << 9) & empty;
	flood |= buf = (buf << 9) & empty;
	flood |= buf = (buf << 9) & empty;
	flood |= buf = (buf << 9) & empty;
	flood |= (buf << 9) & empty;
	*/
	while (((buf << 9) & empty)) {
		flood |= buf = (buf << 9) & empty;
	}

	buf = buf << 9;

	flood = (flood << 9) - (buf & white);

	return flood & notA;
}

U64 soEabishopAttacks(U64 buf, U64 empty, U64 white)
{
	U64 flood = buf;
	empty &= notA;
	/*/
	flood |= buf = (buf >> 7) & empty;
	flood |= buf = (buf >> 7) & empty;
	flood |= buf = (buf >> 7) & empty;
	flood |= buf = (buf >> 7) & empty;
	flood |= buf = (buf >> 7) & empty;
	flood |= buf = (buf >> 7) & empty;
	flood |= (buf >> 7) & empty;
	*/
	while (((buf >> 7) & empty)) {
		flood |= buf = (buf >> 7) & empty;
	}

	buf = buf >> 7;

	flood = (flood >> 7) - (buf & white);

	return flood & notA;
}

/////////////////

U64 northKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{

	buf = (buf << 8);
	buf = buf - (buf & white);
	return buf & ~blackAttacked;
}

U64 southKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	buf = (buf >> 8);
	buf = buf - (buf & white);

	return buf & ~blackAttacked;
}

U64 eastKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	empty &= notH;

	buf = (buf >> 1);
	buf = buf - (buf & white);

	return (buf & notH) & ~blackAttacked;
}

U64 westKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	empty &= notA;
	buf = (buf << 1);
	buf = buf - (buf & white);

	return (buf & notA) & ~blackAttacked;
}

U64 soWeKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	U64 flood = buf;
	empty &= notH;

	buf = (buf >> 9);
	buf = buf - (buf & white);

	return (buf & notH) & ~blackAttacked;
}

U64 noWeKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	U64 flood = buf;
	empty &= notH;

	buf = (buf << 7);
	buf = buf - (buf & white);

	return (buf & notH) & ~blackAttacked;
}
U64 noEaKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	U64 flood = buf;
	empty &= notA;

	buf = (buf << 9);
	buf = buf - (buf & white);

	return (buf & notA) & ~blackAttacked;
}

U64 soEaKingAttacks(U64 buf, U64 empty, U64 white, U64 blackAttacked)
{
	U64 flood = buf;
	empty &= notA;

	buf = (buf >> 7);

	buf = buf - (buf & white);

	return (buf & notA) & ~blackAttacked;
}

U64 castlingRightKing(U64 buf, U64 empty, U64 blackAttacked, bool kingMove, bool rightRook, bool isWhite)
{
	if ( !(kingMove || rightRook)) {
		
		if (isWhite)
		{
			U64 buf = ((1ULL << 1) & empty) | ((1ULL << 2) & empty);

			buf = ~buf;
			U64 buf2 = ~(buf | blackAttacked);
			if (((1ULL << 1) & buf2) && ((1ULL << 2) & buf2)) {
				return (1ULL << 1);
			}
		}
		else
		{
			U64 buf = ((1ULL << 1) & empty) | ((1ULL << 2) & empty) | ((1ULL << 3) & empty);

			buf = ~buf;
			U64 buf2 = ~(buf | (((1ULL << 2) & blackAttacked) | ((1ULL << 3) & blackAttacked)));
			if (((1ULL << 1) & buf2) && ((1ULL << 2) & buf2) && ((1ULL << 3) & buf2)) {
				return (1ULL << 2);
			}
		}

	}
	
	return 0ULL;
}

U64 castlingLeftKing(U64 buf, U64 empty, U64 blackAttacked, bool kingMove, bool leftRook, bool isWhite)
{
	if (!(kingMove || leftRook)) {
		if (isWhite)
		{
			U64 buf = ((1ULL << 4) & empty) | ((1ULL << 5) & empty) | ((1ULL << 6) & empty);
			
			buf = ~buf;
			U64 buf2 = ~(buf | (((1ULL << 5) & blackAttacked) | ((1ULL << 4) & blackAttacked)));
			if (((1ULL << 4) & buf2) && ((1ULL << 5) & buf2) && ((1ULL << 6) & buf2)) {
				return (1ULL << 5);
			}
		}
		else
		{
			U64 buf = ((1ULL << 5) & empty) | ((1ULL << 6) & empty);

			buf = ~buf;
			U64 buf2 = ~(buf | blackAttacked);
			if (((1ULL << 5) & buf2) && ((1ULL << 6) & buf2)) {
				return (1ULL << 6);
			}
		}

	}

	return 0ULL;
}

////////

U64 northPawn(U64 buf, U64 empty, U64 white, int pos)
{
	U64 flood = buf;

	if (64 - pos * 8 == 16 && !((buf << 8) & white))
	{
		flood |= (buf << 8) & empty;
	}
	flood = (flood << 8) & empty;
	return flood - (flood & white);
}

U64 sidePawn(U64 buf, U64 empty, U64 white)
{
	U64 flood = 0ULL;
	//std::cout << "BUFFFFFF " << std::endl;
	//printBitBoard(empty);

	flood |= ((buf << 7) & ~empty) & notH;
	//printBitBoard(notH);
	//printBitBoard(flood);
	//	empty &= notH;

	flood |= ((buf << 9) & ~empty) & notA;
	//printBitBoard(flood);

	return flood - (flood & white);
}

U64 northPawnBlack(U64 buf, U64 empty, U64 white, int pos)
{
	U64 flood = buf;

	if (64 - pos * 8 == 56 && !((buf >> 8) & white))
	{
		flood |= (buf >> 8) & empty;
	}
	flood = (flood >> 8) & empty;
	return flood - (flood & white);
}

U64 sidePawnBlack(U64 buf, U64 empty, U64 white)
{
	U64 flood = 0ULL;
	//std::cout << "BUFFFFFF " << std::endl;
	//printBitBoard(empty);

	flood |= ((buf >> 7) & ~empty) & notA;
	//printBitBoard(notH);
	//printBitBoard(flood);
	//	empty &= notH;

	flood |= ((buf >> 9) & ~empty) & notH;
	//printBitBoard(flood);

	return flood - (flood & white);
}
//U64 getLegalMoves(int pos, int value, U64 empty, U64 white, U64 blackTaken, U64 blackAttacked,  bool leftRookMove, bool rightRookMove, bool kingMove)
U64 getLegalMoves(int pos, int value, U64 empty, U64 white, U64 blackAttacked, bool kingMove, bool leftRookMove, bool rightRookMove, bool isWhite)
{
	U64 buf;
	int posBuf;
	posBuf = pos % 8;
	pos /= 8;
	buf = 1ULL << ((64 - pos * 8) - posBuf - 1);

	switch (value)
	{
	case -6:

		return northPawn(buf, empty, white, pos) | sidePawn(buf, empty, white);
		break;

	case -5:
		//U64 empty = 0xffffffffffffffffULL;
		return northRookAttacks(buf, empty, white) | southRookAttacks(buf, empty, white) | eastRookAttacks(buf, empty, white) | westRookAttacks(buf, empty, white);
		break;

	case -4:
		return knightAttacks(buf, empty, white);
		break;
	case -3:

		return soEabishopAttacks(buf, empty, white) | soWebishopAttacks(buf, empty, white) | noEabishopAttacks(buf, empty, white) | noWebishopAttacks(buf, empty, white);
		break;
	case -2:
		return northRookAttacks(buf, empty, white) | southRookAttacks(buf, empty, white) | eastRookAttacks(buf, empty, white) | westRookAttacks(buf, empty, white) |
			soEabishopAttacks(buf, empty, white) | soWebishopAttacks(buf, empty, white) | noEabishopAttacks(buf, empty, white) | noWebishopAttacks(buf, empty, white);
		break;
	case -1:
		//castlingKing(buf, empty, white) |
		return  soEaKingAttacks(buf, empty, white, blackAttacked) | soWeKingAttacks(buf, empty, white, blackAttacked)
			| noEaKingAttacks(buf, empty, white, blackAttacked) | noWeKingAttacks(buf, empty, white, blackAttacked)
			| northKingAttacks(buf, empty, white, blackAttacked) | southKingAttacks(buf, empty, white, blackAttacked)
			| eastKingAttacks(buf, empty, white, blackAttacked) | westKingAttacks(buf, empty, white, blackAttacked)
			| castlingLeftKing(buf, empty, blackAttacked, kingMove, leftRookMove, isWhite) | castlingRightKing(buf, empty, blackAttacked, kingMove, rightRookMove, isWhite);

		break;
	case 6:
		return sidePawnBlack(buf, empty, white);

		break;


	}
}