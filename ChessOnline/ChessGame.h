#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <process.h>
#include <SFML/Graphics.hpp>
#include <list>
#include "Bitboards.h"
#include "Connect.h"
#include <string.h>


#pragma comment(lib,"ws2_32.lib")

void makeMove(std::string str, bool isRecv, bool moveSprite);
std::string toChessNote(sf::Vector2f p, bool toSend);


struct chess_piece {
	int x, y, value;
	sf::Sprite sprite;
};


int board[8][8];
int size = 105;
int n = -1;
chess_piece pieces[32];

U64 wPawnsBitBoard, copy_wPawnsBitBoard;
U64 bPawnsBitBoard, copy_bPawnsBitBoard;
U64 wRooksBitBoard, copy_wRooksBitBoard;
U64 bRooksBitBoard, copy_bRooksBitBoard;
U64 wKnightsBitBoard, copy_wKnightsBitBoard;
U64 bKnightsBitBoard, copy_bKnightsBitBoard;
U64 wBishopsBitBoard, copy_wBishopsBitBoard;
U64 bBishopsBitBoard, copy_bBishopsBitBoard;
U64 wQueensBitBoard, copy_wQueensBitBoard;
U64 bQueensBitBoard, copy_bQueensBitBoard;
U64 wKingBitBoard, copy_wKingBitBoard;
U64 bKingBitBoard, copy_bKingBitBoard;

U64 myTakenBitBoard, takenBitBoard, blackTakenBitBoard;



bool leftRookMove = false;
bool rightRookMove = false;
bool kingMove = false;
bool isWhiteCastle = false;

void swapBoards(bool copy)
{
	if (copy)
	{
		copy_wPawnsBitBoard = wPawnsBitBoard;
		copy_wRooksBitBoard = wRooksBitBoard;
		copy_wKnightsBitBoard = wKnightsBitBoard;
		copy_wBishopsBitBoard = wBishopsBitBoard;
		copy_wQueensBitBoard = wQueensBitBoard;
		copy_wKingBitBoard = wKingBitBoard;

		copy_bPawnsBitBoard = bPawnsBitBoard;
		copy_bRooksBitBoard = bRooksBitBoard;
		copy_bKnightsBitBoard = bKnightsBitBoard;
		copy_bBishopsBitBoard = bBishopsBitBoard;
		copy_bQueensBitBoard = bQueensBitBoard;
		copy_bKingBitBoard = bKingBitBoard;
	}
	else
	{
		wPawnsBitBoard = copy_wPawnsBitBoard;
		wRooksBitBoard = copy_wRooksBitBoard;
		wKnightsBitBoard = copy_wKnightsBitBoard;
		wBishopsBitBoard = copy_wBishopsBitBoard;
		wQueensBitBoard = copy_wQueensBitBoard;
		wKingBitBoard = copy_wKingBitBoard;

		bPawnsBitBoard = copy_bPawnsBitBoard;
		bRooksBitBoard = copy_bRooksBitBoard;
		bKnightsBitBoard = copy_bKnightsBitBoard;
		bBishopsBitBoard = copy_bBishopsBitBoard;
		bQueensBitBoard = copy_bQueensBitBoard;
		bKingBitBoard = copy_bKingBitBoard;
	}
}


void initBoard(bool isWhite) {
	//std::cout << board << std::endl;
	//std::cout << *board << std::endl;
	//std::cout << &board << std::endl;
	if (isWhite) {
		board[0][0] = 5;
		board[0][1] = 4;
		board[0][2] = 3;
		board[0][3] = 2;
		board[0][4] = 1;
		board[0][5] = 3;
		board[0][6] = 4;
		board[0][7] = 5;

		board[7][0] = -5;
		board[7][1] = -4;
		board[7][2] = -3;
		board[7][3] = -2;
		board[7][4] = -1;
		board[7][5] = -3;
		board[7][6] = -4;
		board[7][7] = -5;
		for (int i = 0; i < 8; i++) {
			board[1][i] = 6;
			board[6][i] = -6;
		}
	}
	else {
		board[0][0] = 5;
		board[0][1] = 4;
		board[0][2] = 3;
		board[0][3] = 1;
		board[0][4] = 2;
		board[0][5] = 3;
		board[0][6] = 4;
		board[0][7] = 5;

		board[7][0] = -5;
		board[7][1] = -4;
		board[7][2] = -3;
		board[7][3] = -1;
		board[7][4] = -2;
		board[7][5] = -3;
		board[7][6] = -4;
		board[7][7] = -5;
		for (int i = 0; i < 8; i++) {
			board[1][i] = 6;
			board[6][i] = -6;
		}
		//	board = buf_board;
	}
}



std::string position = "";


U64 blackAttacked() {
	U64 buf = 0ULL;
	blackTakenBitBoard = bPawnsBitBoard | bRooksBitBoard | bKnightsBitBoard | bBishopsBitBoard | bQueensBitBoard | bKingBitBoard;

	takenBitBoard = wPawnsBitBoard | bPawnsBitBoard | wRooksBitBoard | bRooksBitBoard | wKnightsBitBoard | bKnightsBitBoard | wBishopsBitBoard | bBishopsBitBoard | wQueensBitBoard | bQueensBitBoard | wKingBitBoard | bKingBitBoard;
	int posBuf;
	int pos_bit;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pos_bit = i * 8 + j;

			if (board[i][j] == 6) {
				//buf |= getLegalMoves(pos_bit, board[i][j], ~takenBitBoard, myTakenBitBoard, blackTakenBitBoard, 0ULL, true, true, true);
				buf |= getLegalMoves(pos_bit, board[i][j], ~takenBitBoard, blackTakenBitBoard, 0ULL, true, true, true, isWhiteCastle);
			}
			else if (board[i][j] > 0) {
				//std::cout << "pos " << pos_bit << std::endl;
				//std::cout << i << " " << j << " " << board[i][j] << std::endl;
				//buf |= getLegalMoves(pos_bit, -board[i][j], ~takenBitBoard, myTakenBitBoard, blackTakenBitBoard, 0ULL, true, true, true);
				buf |= getLegalMoves(pos_bit, -board[i][j], ~takenBitBoard, blackTakenBitBoard, 0ULL, true, true, true, isWhiteCastle);


			}

		}
	}

	return buf;
}

std::list<sf::Vector2f> getXY(U64 moves)
{
	std::list<sf::Vector2f> legalList;

	int field = 63;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			if ((1ULL << field) & moves)
				legalList.push_front(sf::Vector2f(i, j));
			field -= 1;
		}
	}

	return legalList;
}

bool isCheck() {
	U64 buf = blackAttacked();

	if ((wKingBitBoard & buf) > 0) return true;
	return false;
}

bool isCheckMate() {
	//std::cout << "isCheckMate()" << std::endl;

	U64 buf;
	int pos_bit;
	std::string strMove;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pos_bit = i * 8 + j;

			if (board[i][j] < 0) {
				//std::cout << "Board[i][j] " << board[i][j] << std::endl;
				U64 enemyTakenBitBoard = bPawnsBitBoard | bRooksBitBoard | bKnightsBitBoard | bBishopsBitBoard | bQueensBitBoard | bKingBitBoard;

				//printBitBoard(enemyTakenBitBoard);
				//printBitBoard(myTakenBitBoard);
				//std::cout << " *************************** " << std::endl;
				//std::cout << "pos " << pos_bit << std::endl;
				//std::cout << i << " " << j << " " << board[i][j] << std::endl;
				//buf |= getLegalMoves(pos_bit, -board[i][j], ~takenBitBoard, myTakenBitBoard, blackTakenBitBoard, 0ULL, true, true, true);
				takenBitBoard = wPawnsBitBoard | bPawnsBitBoard | wRooksBitBoard | bRooksBitBoard | wKnightsBitBoard | bKnightsBitBoard | wBishopsBitBoard | bBishopsBitBoard | wQueensBitBoard | bQueensBitBoard | wKingBitBoard | bKingBitBoard;
				myTakenBitBoard = wPawnsBitBoard | wRooksBitBoard | wKnightsBitBoard | wBishopsBitBoard | wQueensBitBoard | wKingBitBoard;

				blackTakenBitBoard = bPawnsBitBoard | bRooksBitBoard | bKnightsBitBoard | bBishopsBitBoard | bQueensBitBoard | bKingBitBoard;
				buf = getLegalMoves(pos_bit, board[i][j], ~takenBitBoard, myTakenBitBoard, 0ULL, true, true, true, isWhiteCastle);
				//	U64 getLegalMoves(int pos, int value, U64 empty, U64 white, U64 blackAttacked, bool kingMove, bool leftRookMove, bool rightRookMove, bool isWhite)

				//printBitBoard(buf);
				std::list<sf::Vector2f> movesList = getXY(buf);

				for (auto el : movesList) {


					strMove = toChessNote(sf::Vector2f(j * size, i * size), false) + toChessNote(sf::Vector2f(el.y * size, el.x * size), false);
					//std::cout << strMove << std::endl;
					swapBoards(true);
					//printBitBoard(takenBitBoard);
					/*
					for (int z = 0; z < 8; z++)
					{
						for (int x = 0; x < 8; x++)
						{
							std::cout << "\t" << board[z][x];
						}
						std::cout << std::endl;
					}
					*/
					//std::cout << "*******************************************************" << std::endl;
					//std::cout << "el.x " << el.x << " " << el.y << std::endl;
					int odl_value = board[(int)el.x][(int)el.y];
					//std::cout << "Odl_val " << odl_value << std::endl;
					int idx = -1;
					for (int k = 0; k < 32; k++) {
						//std::cout << pieces[k].x << " " << pieces[k].y << std::endl;
						if (pieces[k].x == j && pieces[k].y == i) {
							idx = k;
						}
					}
					if (idx == -1) std::cout << "problemu moj panie222" << std::endl;
					int oldX = pieces[idx].x;
					int oldY = pieces[idx].y;
					//std::cout << "X Y VAl " << pieces[idx].x << " " << pieces[idx].y << " " << pieces[idx].value << std::endl;
					pieces[idx].sprite.setPosition(sf::Vector2f(j * size, i * size));
					makeMove(strMove, false, false);
					//std::cout << "Sprawdzam Mate" << std::endl;

					if (isCheck()) {
						//std::cout << "Jestem matowany" << std::endl;

						swapBoards(false);

						pieces[idx].x = oldX;
						pieces[idx].y = oldY;

						//board[pieces[old_index].y][pieces[old_index].x] = pieces[old_index].value;
						board[pieces[idx].y][pieces[idx].x] = pieces[idx].value;

						board[(int)el.x][(int)el.y] = odl_value;

						pieces[idx].sprite.setPosition(sf::Vector2f(j * size, i * size));

						continue;
					}
					else {
						//std::cout << "nie jestem matownay" << std::endl;

						swapBoards(false);

						pieces[idx].x = oldX;
						pieces[idx].y = oldY;

						board[pieces[idx].y][pieces[idx].x] = pieces[idx].value;

						board[(int)el.x][(int)el.y] = odl_value;
						return false;
					}
				}


			}

		}
	}

	return true;
}

bool contains2(std::list<sf::Vector2f> lista, sf::Vector2f pos) {
	//std::cout << "CONTAINS()++++++++++++++" << std::endl;

	for (auto i : lista) {
		if ((int)(pos.x / 105) == i.y && (int)(pos.y / 105) == i.x) {
			return true;
		}
	}

	return false;

}
sf::Sprite xd;
void load(bool isWhite) {

	int k = 0;
	int y;
	if (!isWhite) {
		board[7][3] = -1;
		board[7][4] = -2;
		board[0][3] = 1;
		board[0][4] = 2;
	}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			if (isWhite) {
				y = n > 0 ? 1 : 0;
			}
			else {
				y = n < 0 ? 1 : 0;
			}
			pieces[k].sprite.setTextureRect(sf::IntRect(333 * x, 333 * y, 333, 333));
			pieces[k].sprite.setScale(0.3f, 0.3f);
			pieces[k].sprite.setPosition(size * j, size * i);
			pieces[k].x = j;
			pieces[k].y = i;
			pieces[k].value = board[i][j];
			k++;
		}

}


std::string toChessNote(sf::Vector2f p, bool toSend)
{
	std::string s = "";

	if (toSend)
	{
		s += char((7 - p.x / size) + 97);
		s += char(7 - (7 - p.y / size) + 49);
	}
	else
	{
		s += char(p.x / size + 97);
		s += char(7 - p.y / size + 49);
	}

	return s;
}

sf::Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return sf::Vector2f(x * size, y * size);
}

void makeMove(std::string str, bool isRecv, bool moveSprite)
{
	sf::Vector2f oldPos = toCoord(str[0], str[1]);
	sf::Vector2f newPos = toCoord(str[2], str[3]);
	//std::cout << "MakeMove()" << std::endl;
	//std::cout << str << std::endl;
	//std::cout << oldPos.x / 105 << " " << oldPos.y / 105 << std::endl;
	//std::cout << newPos.x / 105 << " " << newPos.y / 105 << std::endl;


	int pos_bit = oldPos.y / 105 * 8 + oldPos.x / 105;
	int new_pos_bit = newPos.y / 105 * 8 + newPos.x / 105;
	int old_index = -1, new_index;
	//std::cout << pos_bit << " " << new_pos_bit << std::endl;

	if (isRecv) {
		for (int i = 0; i < 32; i++)
			if (pieces[i].sprite.getPosition() == newPos) {
				U64 buf = (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
				//	printBitBoard(buf);
				if (moveSprite) pieces[i].sprite.setPosition(-100, -100);
				wPawnsBitBoard -= (buf & wPawnsBitBoard);
				//	printBitBoard(wPawnsBitBoard);
				wRooksBitBoard -= (buf & wRooksBitBoard);
				wKnightsBitBoard -= (buf & wKnightsBitBoard);
				wBishopsBitBoard -= (buf & wBishopsBitBoard);
				wQueensBitBoard -= (buf & wQueensBitBoard);
				//	std::cout << "Koniec usuwania" << std::endl;

			}
	}
	else {
		for (int i = 0; i < 32; i++)		//sf::Vector2f(newPos.y, newPos.x)
			if (pieces[i].sprite.getPosition() == newPos) {
				//printBitBoard(wRooksBitBoard);
				U64 buf = (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
				//	printBitBoard(buf);
				if (moveSprite) pieces[i].sprite.setPosition(-100, -100);
				bPawnsBitBoard -= (buf & bPawnsBitBoard);
				//	printBitBoard(wPawnsBitBoard);
				bRooksBitBoard -= (buf & bRooksBitBoard);
				bKnightsBitBoard -= (buf & bKnightsBitBoard);
				bBishopsBitBoard -= (buf & bBishopsBitBoard);
				bQueensBitBoard -= (buf & bQueensBitBoard);
				//	std::cout << "Koniec usuwania" << std::endl;

			}
	}

	for (int i = 0; i < 32; i++) {
		if (pieces[i].sprite.getPosition() == oldPos) {
			board[pieces[i].y][pieces[i].x] = 0;
			if (moveSprite) pieces[i].sprite.setPosition(newPos);
			old_index = i;
		}

	}

	if (old_index == -1) {
		std::cout << "Porblemy moj panie " << std::endl;
		return;
	}
	// wyzerowanie poprzedniej pozycji
	pieces[old_index].x = (int)(newPos.x / 105);
	pieces[old_index].y = (int)(newPos.y / 105);
	board[pieces[old_index].y][pieces[old_index].x] = pieces[old_index].value;



	//std::cout << old_index << " " << pieces[old_index].value << std::endl;
	//printBitBoard((1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1)));
	if (pieces[old_index].value == 6)
	{
		bPawnsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bPawnsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));

		if ((int)(new_pos_bit / 8) == 7 && moveSprite)
		{
			bPawnsBitBoard &= ~(1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
			bQueensBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
			board[(int)(newPos.x / size)][(int)(newPos.y / size)] = 2;
			pieces[old_index].value = 2;
			int bOrW = isWhiteCastle == true ? 1 : 0;
			pieces[old_index].sprite.setTextureRect(sf::IntRect(333 * (abs(-2) - 1), 333 * bOrW, 333, 333));
			pieces[old_index].sprite.setScale(0.3f, 0.3f);
			pieces[old_index].sprite.setPosition(newPos);

		}
	}
	else if (pieces[old_index].value == 5)
	{
		bRooksBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bRooksBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == 4)
	{
		bKnightsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bKnightsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == 3)
	{
		bBishopsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bBishopsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == 2)
	{
		bQueensBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bQueensBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));

	}
	else if (pieces[old_index].value == 1)
	{
		bKingBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		bKingBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
		if (str == "d8b8") makeMove("a8c8", true, true);
		if (str == "d8f8") makeMove("h8e8", true, true);


		if (str == "e8g8") makeMove("h8f8", true, true);
		if (str == "e8c8") makeMove("a8d8", true, true);

	}
	else if (pieces[old_index].value == -6)
	{
		wPawnsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wPawnsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));

		if ((int)(new_pos_bit / 8) == 0 && moveSprite)
		{
			wPawnsBitBoard &= ~(1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
			wQueensBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
			board[(int)(newPos.x / size)][(int)(newPos.y / size)] = -2;
			pieces[old_index].value = -2;
			int bOrW = isWhiteCastle == true ? 0 : 1;
			pieces[old_index].sprite.setTextureRect(sf::IntRect(333 * (abs(-2) - 1), 333 * bOrW, 333, 333));
			pieces[old_index].sprite.setScale(0.3f, 0.3f);
			pieces[old_index].sprite.setPosition(newPos);

		}

	}
	else if (pieces[old_index].value == -5)
	{
		if (pos_bit == 63) rightRookMove = true;
		else if (pos_bit == 55) leftRookMove = true;
		wRooksBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wRooksBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == -4)
	{
		wKnightsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wKnightsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == -3)
	{
		wBishopsBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wBishopsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
	}
	else if (pieces[old_index].value == -2)
	{
		wQueensBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wQueensBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));

	}
	else if (pieces[old_index].value == -1)
	{
		wKingBitBoard |= (1ULL << ((64 - (new_pos_bit / 8) * 8) - (new_pos_bit % 8) - 1));
		wKingBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
		kingMove = true;
		if (str == "e1g1") makeMove("h1f1", false, true);
		if (str == "e1c1") makeMove("a1d1", false, true);

		if (str == "d1b1") makeMove("a1c1", false, true);
		if (str == "d1f1") makeMove("h1e1", false, true);
	}
}

SOCKET connect() {
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2222);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult)
	{
		printf("WSA startup failed");
		return 0;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		printf("Invalid socket");
		return 0;
	}

	iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{
		printf("Connect failed %u", WSAGetLastError());
		return 0;
	}
	return sock;

}

class Connection {
public:
	bool recived = false;
	SOCKET sock;
	std::string note;
};

Connection conn;

unsigned int __stdcall Reciving(void* data)
{
	//Connection* Conn = (Connection*)data;
	//Connection conn = *Conn;

	//SOCKET Client = conn.sock;


	//std::cout << "Odbieram dane" << std::endl;


	char chunk[200];
	while (int sockc = recv(conn.sock, chunk, 200, 0))
	{
		if (sockc == -1) {
			return 0;
		}
		std::cout << "ODEBRALEM " << std::endl;
		printf("%s \t %d\n", chunk, GetCurrentThreadId());
		conn.recived = true;

		conn.note = (std::string)chunk;
	}
	return 0;
}

void resetGame() {
	leftRookMove = false;
	rightRookMove = false;
	kingMove = false;
	isWhiteCastle = false;
	n = -1;
	position = "";

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = 0;
		}
		std::cout << std::endl;
	}
	std::cout << "*******************************************************" << std::endl;

}


int game(bool online)
{
	bool isMove = true;
	bool isWhite = true;
	HANDLE sockHandle = NULL;
	resetGame();

	if (online)
	{
		isMove = false;
		isWhite = false;
		SOCKET sock = connect();
		if (sock == 0) {
			std::cout << "Bład połączenia";
			return 0;
		}

		conn.sock = sock;
		char chunk[200];
		recv(conn.sock, chunk, 200, 0);
		if (strcmp(chunk, "white") == 0) {
			std::cout << "jestem bialy" << std::endl;
			isMove = true;
			isWhite = true;
		}
		else std::cout << "jestem czarny" << std::endl;

		sockHandle = (HANDLE)_beginthreadex(0, 0, Reciving, (void*)&conn, 0, 0);
	}
	else
	{
		TCHAR proces[] = TEXT("stockfish.exe");
		ConnectToEngine(proces);
	}

	wPawnsBitBoard = fillPawns(true);
	bPawnsBitBoard = fillPawns(false);
	wRooksBitBoard = fillRooks(true);
	bRooksBitBoard = fillRooks(false);
	wKnightsBitBoard = fillKnights(true);
	bKnightsBitBoard = fillKnights(false);
	wBishopsBitBoard = fillBishops(true);
	bBishopsBitBoard = fillBishops(false);
	wQueensBitBoard = fillQueens(isWhite, true);
	bQueensBitBoard = fillQueens(isWhite, false);
	wKingBitBoard = fillKing(isWhite, true);
	bKingBitBoard = fillKing(isWhite, false);


	isWhiteCastle = isWhite;
	initBoard(isWhite);

	myTakenBitBoard = wPawnsBitBoard | wRooksBitBoard | wKnightsBitBoard | wBishopsBitBoard | wQueensBitBoard | wKingBitBoard;

	Sleep(1111);
	//printBitBoard(myTakenBitBoard);

	sf::Sprite winSprite, loseSprite;

	sf::RectangleShape winloseRec(sf::Vector2f(400, 400));
	winloseRec.setPosition(840 / 2 - 100 - 80, 840 / 2 - 100);
	winloseRec.setFillColor(sf::Color(0, 0, 0, 200));

	winSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
	winSprite.setPosition(840 / 2 - 100 - 80, 840 / 2 - 100);

	loseSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
	loseSprite.setPosition(840 / 2 - 100 - 80, 840 / 2 - 100);
	
	sf::Texture winTexture, loseTexture;
	winTexture.loadFromFile("win.png");
	loseTexture.loadFromFile("lose.png");


	winSprite.setTexture(winTexture);
	loseSprite.setTexture(loseTexture);



	//printBitBoard(wPawnsBitBoard);
	//printBitBoard(bPawnsBitBoard);
	//printBitBoard(wRooksBitBoard);
	//printBitBoard(bRooksBitBoard);
	//printBitBoard(wKnightsBitBoard);
	//printBitBoard(bKnightsBitBoard);
	//printBitBoard(wBishopsBitBoard);
	//printBitBoard(bBishopsBitBoard);
	//printBitBoard(wQueensBitBoard);
	//printBitBoard(bQueensBitBoard);
	//printBitBoard(wKingBitBoard);
	//printBitBoard(bKingBitBoard);


	//printBitBoard((((1ULL << 50) & wPawnsBitBoard) >> 7) | ((1ULL << 50) & wPawnsBitBoard));


	sf::RenderWindow window(sf::VideoMode(840, 840), "Chess Online");



	sf::Texture tFigures, tBoard;
	tFigures.loadFromFile("figures2.png");
	tBoard.loadFromFile("board2.png");

	sf::Sprite sBoard(tBoard);
	sBoard.scale(1.4f, 1.4f);

	for (int i = 0; i < 32; i++) pieces[i].sprite.setTexture(tFigures);

	load(isWhite);

	sf::Event event;

	float dx = 0, dy = 0;

	sf::RectangleShape rectangle(sf::Vector2f(105, 105));

	std::list<sf::RectangleShape> highlightMovesList;
	std::list<sf::Vector2f> movesList;
	sf::Vector2f oldPos;
	bool moveDone = false;
	int pos_bit;
	bool legit_move;

	while (window.isOpen()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				CloseHandle(sockHandle);
				closesocket(conn.sock);
				window.close();
			}


			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
					for (int i = 0; i < 32; i++)
						if (pieces[i].sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
							if (pieces[i].value < 0 && isWhite)
							{
								isMove = true;
								legit_move = true;
								n = i;
								dx = mousePos.x - pieces[i].sprite.getPosition().x;
								dy = mousePos.y - pieces[i].sprite.getPosition().y;
								oldPos = pieces[i].sprite.getPosition();

								//board[pieces[i].y][pieces[i].x] = 0;
								pos_bit = pieces[i].y * 8 + pieces[i].x;

								//U64 empty = ~(wPawnsBitBoard | bPawnsBitBoard);
								takenBitBoard = wPawnsBitBoard | bPawnsBitBoard | wRooksBitBoard | bRooksBitBoard | wKnightsBitBoard | bKnightsBitBoard | wBishopsBitBoard | bBishopsBitBoard | wQueensBitBoard | bQueensBitBoard | wKingBitBoard | bKingBitBoard;
								myTakenBitBoard = wPawnsBitBoard | wRooksBitBoard | wKnightsBitBoard | wBishopsBitBoard | wQueensBitBoard | wKingBitBoard;

								blackTakenBitBoard = bPawnsBitBoard | bRooksBitBoard | bKnightsBitBoard | bBishopsBitBoard | bQueensBitBoard | bKingBitBoard;

								U64 empty = ~takenBitBoard;

								U64 moveBoard;
								if (pieces[i].value >= -6 && pieces[i].value <= -1)
								{
									//	U64 getLegalMoves(int pos, int value, U64 empty, U64 white, U64 blackTaken, U64 blackAttacked, bool leftRookMove, bool rightRookMove, bool kingMove)

										//moveBoard = getLegalMoves(pos_bit, pieces[i].value, empty, myTakenBitBoard, blackTakenBitBoard, blackAttacked(),  leftRookMove, rightRookMove, kingMove);
									moveBoard = getLegalMoves(pos_bit, pieces[i].value, empty, myTakenBitBoard, blackAttacked(), kingMove, leftRookMove, rightRookMove, isWhiteCastle);
									//wPawnsBitBoard &= ~(1ULL << ((64 - (pos_bit / 8) * 8) - (pos_bit % 8) - 1));
									movesList = getXY(moveBoard);

								}
								else movesList.clear();


								for (auto i : movesList) {
									//std::cout << i.x << " " << i.y << std::endl;
									rectangle.setPosition(sf::Vector2f(i.y * size, i.x * size)); // i ustawiamy mu pozycję
									rectangle.setFillColor(sf::Color(255, 0, 0, 125));
									highlightMovesList.push_back(rectangle);
								}
							}


			if (event.type == sf::Event::MouseButtonReleased && isWhite && isMove)
			{
				//std::cout << "White " << isWhite << " value " << pieces[n].value << std::endl;
				if (event.key.code == sf::Mouse::Left)
				{
					isMove = false; //bufor czy dpobrze sie rusza oraz ryspowanie kwadratow
					sf::Vector2f curPos = pieces[n].sprite.getPosition() + sf::Vector2f(size / 2, size / 2);
					sf::Vector2f newPos = sf::Vector2f(size * int(curPos.x / size), size * int(curPos.y / size));

					//sf::Vector2f oldPos2 = oldPos + sf::Vector2f(size / 2, size / 2);
					//oldPos2 = sf::Vector2f(size * int(oldPos2.x / size), size * int(oldPos2.y / size));
					std::string strToMove = toChessNote(oldPos, false) + toChessNote(newPos, false);;

					if (!contains2(movesList, newPos)) {
						pieces[n].sprite.setPosition(oldPos);
						//board[pieces[n].y][pieces[n].x] = pieces[n].value;
						highlightMovesList.clear();
						movesList.clear();
						continue;
					}
					//std::cout << "Contains2" << std::endl;

					int new_pos_bit = (int)(newPos.y / 105) * 8 + (int)(newPos.x / 105);

					//std::cout << "Wchodze w IFa isCheck" << std::endl;

					if (isCheck()) {

					



						swapBoards(true);

						strToMove = toChessNote(oldPos, false) + toChessNote(newPos, false);


						int odl_value = board[(int)(newPos.y / 105)][(int)(newPos.x / 105)];
						int oldX = pieces[n].x;
						int oldY = pieces[n].y;

						pieces[n].sprite.setPosition(oldPos);
						makeMove(strToMove, false, false);
						//std::cout << "Wchodze w 2222222 IFa isCheck" << std::endl;

						if (isCheck()) {
							swapBoards(false);

							pieces[n].x = oldX;
							pieces[n].y = oldY;

							//board[pieces[old_index].y][pieces[old_index].x] = pieces[old_index].value;
							board[pieces[n].y][pieces[n].x] = pieces[n].value;

							board[(int)(newPos.y / 105)][(int)(newPos.x / 105)] = odl_value;

							pieces[n].sprite.setPosition(oldPos);
							highlightMovesList.clear();
							movesList.clear();

							continue;
						}
						else {
							swapBoards(false);

							pieces[n].x = oldX;
							pieces[n].y = oldY;

							board[pieces[n].y][pieces[n].x] = pieces[n].value;

							board[(int)(newPos.y / 105)][(int)(newPos.x / 105)] = odl_value;
						}
					}


					//std::cout << "NIema check" << std::endl;
					//std::cout << "Sprawdzam pinna" << std::endl;

					bool isPinned = true;
					if (isPinned && (strToMove != "e1g1") && (strToMove != "e1c1") && (strToMove != "d1b1") && (strToMove != "d1f1")) {

						//std::cout << (strToMove != "e1g1") << std::endl;
						//std::cout << (strToMove != "d1b1") << std::endl;

						swapBoards(true);



						//strToMove = toChessNote(oldPos, false) + toChessNote(newPos, false);

						int odl_value = board[(int)(newPos.y / 105)][(int)(newPos.x / 105)];
						int oldX = pieces[n].x;
						int oldY = pieces[n].y;

						pieces[n].sprite.setPosition(oldPos);
						makeMove(strToMove, false, false);

						//std::cout << "Wchodze w 2222222 IFa isCheck" << std::endl;

						if (isCheck()) {
							swapBoards(false);

							pieces[n].x = oldX;
							pieces[n].y = oldY;

							board[pieces[n].y][pieces[n].x] = pieces[n].value;

							board[(int)(newPos.y / 105)][(int)(newPos.x / 105)] = odl_value;

							pieces[n].sprite.setPosition(oldPos);
							highlightMovesList.clear();
							movesList.clear();

							continue;
						}
						else {

							swapBoards(false);

							pieces[n].x = oldX;
							pieces[n].y = oldY;

							board[pieces[n].y][pieces[n].x] = pieces[n].value;

							board[(int)(newPos.y / 105)][(int)(newPos.x / 105)] = odl_value;
						}
					}
					//std::cout << "NIema pinna" << std::endl;

					/*
					for (int i = 0; i < 32; i++)
					{
						if (newPos == pieces[i].sprite.getPosition())
						{
							if ((isWhite && pieces[i].value > 0) || (!isWhite && pieces[i].value < 0))
							{
								pieces[i].sprite.setPosition(-200, -200);
								//conn.
								break;
							}
						}
					}
					*/

					/*
					if (pieces[n].x != (int)(newPos.x / 105) || pieces[n].y != (int)(newPos.y / 105))
					{
						std::string str = toChessNote(oldPos, isWhite) + toChessNote(newPos, isWhite);
						isWhite = pieces[n].value > 0 ? true : false;
						std::cout << str << std::endl;

						char send_me[5];
						strcpy(send_me, str.c_str());

						send(conn.sock, send_me, sizeof(send_me), 0);

						position += str + " ";

						moveDone = true;
					}
					*/
					std::string strToSend = toChessNote(oldPos, true) + toChessNote(newPos, true);
					strToMove = toChessNote(oldPos, false) + toChessNote(newPos, false);
					isWhite = !isWhite;// pieces[n].value > 0 ? true : false;//chyba moze byc inaczej po prostu obocenie wartosci
					//std::cout << str << std::endl;

					char send_me[5];
					strcpy(send_me, strToSend.c_str());
					//std::cout << "wysylam " << send_me << std::endl;
					send(conn.sock, send_me, sizeof(send_me), 0);
					position += strToMove + " ";

					pieces[n].sprite.setPosition(oldPos);
					makeMove(strToMove, false, true);

					if (!online) {
						moveDone = true;
						isWhite = false;
					}

					highlightMovesList.clear();
					movesList.clear();


					// DEBUG BOARD 
					/*
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							std::cout << "\t" << board[i][j];
						}
						std::cout << std::endl;
					}
					std::cout << "*******************************************************" << std::endl;
					*/

					myTakenBitBoard = wPawnsBitBoard | wRooksBitBoard | wKnightsBitBoard | wBishopsBitBoard | wQueensBitBoard | wKingBitBoard;

					//printBitBoard(myTakenBitBoard);
				}
			}


		}




		window.clear();
		window.draw(sBoard);

		if (isMove)
		{
			pieces[n].sprite.setPosition(mousePos.x - dx, mousePos.y - dy);
			for (auto rec : highlightMovesList) window.draw(rec);
		}

		for (int i = 0; i < 32; i++) window.draw(pieces[i].sprite);
		window.display();

		if(!online)
		{
			if (moveDone)
			{

				//std::cout << position << std::endl;

				std::string enemyMove = getNextMove(position);
				if (enemyMove == "error")
				{
					std::cout << "ERROR" << std::endl;
				}


				makeMove(enemyMove, true, true);
				position += enemyMove + " ";

				moveDone = false;
				isWhite = true;


				}
		}
		else
		{
			if (conn.recived) {
				//std::cout << "Recived222" << std::endl;
				//std::cout << conn.note << std::endl;
				isWhite = true;
				conn.recived = false;
				if (conn.note == "win")
				{
					std::cout << "Wygrales" << std::endl;
					CloseHandle(sockHandle);
					closesocket(conn.sock);
					Sleep(1000);
					window.draw(winloseRec);
					window.draw(winSprite);
					window.display();
					Sleep(5555);
					break;
				}
				makeMove(conn.note, true, true);
				takenBitBoard = wPawnsBitBoard | bPawnsBitBoard | wRooksBitBoard | bRooksBitBoard | wKnightsBitBoard | bKnightsBitBoard | wBishopsBitBoard | bBishopsBitBoard | wQueensBitBoard | bQueensBitBoard | wKingBitBoard | bKingBitBoard;
				if(isCheck())
					if (isCheckMate()) {
						std::cout << "GG WP~!!!!!!!!!!!!!!!!!!" << std::endl;
						char send_me[5];
						std::string str = "win";
						strcpy(send_me, str.c_str());
						//std::cout << "wysylam " << send_me << std::endl;
						send(conn.sock, send_me, sizeof(send_me), 0);
						CloseHandle(sockHandle);
						closesocket(conn.sock);

						Sleep(1000);
						window.draw(winloseRec);
						window.draw(loseSprite);
						window.display();
						//std::cout << "wyswietlam " << send_me << std::endl;
						Sleep(5555);
						break;
					}

				//printBitBoard(takenBitBoard);

				//isCheck();
			}
		}
	}

	return 0;
}
