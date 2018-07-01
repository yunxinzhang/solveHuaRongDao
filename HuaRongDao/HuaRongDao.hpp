#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
using namespace std;

enum dirction {
	LEFT, RIGHT, UP, DOWN
};
class Block {
public:
	int dir;
	int x, y;
	int len;
	void move(dirction d) {
		switch (d) {
		case LEFT: ++y; break;
		case RIGHT:--y; break;
		case UP:--x; break;
		case DOWN:++x; break;
		}	
	};
	bool operator<(const Block &p)const {
		if (x < p.x || (x == p.x&&y < p.y))
			return true;
		else
			return false;
	}
	bool operator==(const Block &p)const {
		if (x == p.x&& y == p.y)
			return true;
		else
			return false;
	}
	Block(int x, int y, int len):x(x),y(y) {
		if (len > 0) {
			dir = 1;
			this->len = len;
		}
		else {
			dir = -1;
			this->len = -len;
		}
	}
	Block(){}
};

class Map {
public:
	static set<set<Block>> state;
	set<Block> s;
	int blockNum;
	int row;
	int col;
	Block aim;
	vector<vector<int>> hasBlock;
	int layer;
	//Map * pre;
	string str;
	
	Map() {
		//pre = NULL;
		blockNum = 0;
		str = "";
		layer = 0;
		ifstream fin("map.txt");
		if (!fin) { cout << " read map failed ."; }
		string str; char c;
		fin >> str;
		fin >> row >> col;
		for (int i = 0; i < row; ++i) {
			vector<int> v;
			for (int j = 0; j < col; ++j) {
				v.push_back(0);
			}
			hasBlock.push_back(v);
		}
		for (int i = 0; i < row; ++i) {
			vector<char> vv;
			for (int j = 0; j < col; ++j) {
				fin >> c;
				
				vv.push_back(c);
				if (c == 'x')continue;
				if(c=='@'){
					aim.dir = 1;
					aim.len = 2;
					aim.x = i;
					aim.y = j; 
					s.insert(aim);
					hasBlock[i][j] = ++blockNum;
					hasBlock[i][j + 1] = blockNum;
				}
				else if (c >= 'A' && c <= 'Z') {
					int lenc = c - 'A' + 1;
					++blockNum;
					for (int k = 0; k < lenc; ++k) {
						hasBlock[i][j + k] = blockNum;
					}
					s.insert(Block(i, j, lenc));
				}
				else if (c >= 'a' && c <= 'z') {
					int lenc = c - 'a' + 1;
					
					++blockNum;
					for (int k = 0; k < lenc; ++k) {
						
						hasBlock[i+k][j] = blockNum;
					}
					s.insert(Block(i, j, -lenc));
				}
			}
		}
		state.insert(s);
		fin.close();
	}
	void show() {
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cout << hasBlock[i][j] << "\t";
			}
			cout << endl;
		}
	}
	bool win() {
		for (int i = 1; i < col; ++i) {
			if (aim.y + 1 + i < col && hasBlock[aim.x][aim.y + 1 + i] != false) {
				return false;
			}
		}
		return true;
		//if (aim.y == col - 2)return true;
		//return false;
	}
};
