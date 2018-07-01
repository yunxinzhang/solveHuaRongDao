#include "HuaRongDao.hpp"
#include <queue>
#include <ctime>
set<set<Block>> Map::state;
queue<Map> list;
void showState(set<set<Block>> &state) {
	cout << "#####################" << endl;
	for (auto it : state) {
		for (auto init : it) {
			cout << init.x << "," << init.y << " -> ";
		}
		cout << endl;
	}
}

bool solve() {
	
	int ceng = 0;
		while (list.size() > 0) {
			Map *step = new Map( list.front());
			
			//cout << "start" << endl;
			//cout << "pre" << endl;
			//if (step->pre != NULL)step->pre->show();

			//cout << step->str << endl;
			//step->show();
			//cout << "-----------" << endl;
			//cout <<"layer >>" <<step->layer << endl;;
			list.pop();
			++ceng;
			showState(Map::state);
			cout << ceng << endl;
			//cout <<"size>>"<< Map::state.size() << endl;
			Map::state.insert(step->s);
			if (step->win()) {
				cout << "win" << endl;
				return true;
			}
			for (auto iter : step->s) {
				if (iter.dir == 1) {
					if ((iter.y + iter.len)<step->col&&step->hasBlock[iter.x][iter.y + iter.len] == false) {
						Map *m2 = new Map(*step);
						//m2->pre = step;
						m2->s.erase(iter);
						m2->s.insert(Block(iter.x, iter.y + 1, iter.len));
						m2->hasBlock[iter.x][iter.y + iter.len] = m2->hasBlock[iter.x][iter.y];
						m2->hasBlock[iter.x][iter.y] = 0;
						if (iter.x == step->aim.x && iter.y == step->aim.y) {
							m2->aim.y++;
						}
						m2->layer++;
						m2->str = to_string(iter.x) + "," + to_string(iter.y) + "left";
						if (step->state.find(m2->s) == step->state.end()) {
							list.push(*m2);
							delete m2;
						}
						else {
							delete m2;
						}
						
					}
					if ((iter.y)>0
						&& step->hasBlock[iter.x][iter.y - 1] == false
						) {
						Map *m2 = new Map(*step);
						m2->s.erase(iter);
						m2->s.insert(Block(iter.x, iter.y - 1, iter.len));
						m2->hasBlock[iter.x][iter.y - 1] = m2->hasBlock[iter.x][iter.y];
						m2->hasBlock[iter.x][iter.y + iter.len - 1] = 0;
						if (iter.x == step->aim.x && iter.y == step->aim.y) {
							m2->aim.y--;
						}
						m2->layer++;
						m2->str = to_string(iter.x) + "," + to_string(iter.y) + "right";
						if (step->state.find(m2->s) == step->state.end()) {
							list.push(*m2);
							delete m2;
						}
						else {
							delete m2;
						}
					}
				}
				else if(iter.dir == -1) {
					if ((iter.x + iter.len)<step->row&&
						step->hasBlock[iter.x + iter.len][iter.y] == false
						) {
						Map *m2 = new Map(*step);
						m2->s.erase(iter);
						m2->s.insert(Block(iter.x + 1, iter.y, -iter.len));
						m2->hasBlock[iter.x + iter.len][iter.y] = m2->hasBlock[iter.x][iter.y];
						m2->hasBlock[iter.x][iter.y] = 0;
						if (iter.x == step->aim.x && iter.y == step->aim.y) {
							m2->aim.x++;
						}
						m2->layer++;
						m2->str = to_string(iter.x) + "," + to_string(iter.y) + "down";
						if (step->state.find(m2->s) == step->state.end()) {
							list.push(*m2);
							delete m2;
						}
						else {
							delete m2;
						}
					}
					if ((iter.x)>0
						&& step->hasBlock[iter.x - 1][iter.y] == false
						) {
						Map *m2 = new Map(*step);
						m2->s.erase(iter);
						m2->s.insert(Block(iter.x - 1, iter.y, -iter.len));
						m2->hasBlock[iter.x - 1][iter.y] = m2->hasBlock[iter.x][iter.y];
						m2->hasBlock[iter.x + iter.len - 1][iter.y] = 0;
						if (iter.x == step->aim.x && iter.y == step->aim.y) {
							m2->aim.y--;
						}
						m2->layer++;
						m2->str = to_string(iter.x) + "," + to_string(iter.y) + "up";
						if (step->state.find(m2->s) == step->state.end()) {
							list.push(*m2);
							delete m2;
						}
						else {
							delete m2;
						}
					}
				}
			}
			delete step;
		}
	}
	
	bool solve2() {

		int ceng = 0;
		int ccc = 0;
		clock_t t1=0, t2=0;
		while (list.size() > 0) {
			Map step = list.front();

			//cout << "start" << endl;
			//cout << "pre" << endl;
			//if (step->pre != NULL)step->pre->show();

			//cout << step->str << endl;
			//step->show();
			//cout << "-----------" << endl;
			if (step.layer > ccc) {
				//cout << ceng << "<" << step.layer << endl;
				ccc = step.layer;
				t1 = clock();
				cout << "第" << ccc << "步" << t1 - t2 << endl;
				t2 = t1;
				
			}
		//cout <<"layer >>" <<step.layer << endl;;
			list.pop();
			++ceng;
			//if(Map::state.size()==300)
				//showState(Map::state);
			//cout << ceng << endl;
			//cout <<"size>>"<< Map::state.size() << endl;
			Map::state.insert(step.s);
			if (step.win()) {
				cout << "win" << endl;
				cout << " 移动到底 >>";
				cout << step.str << endl;
				return true;
			}
			for (auto iter : step.s) {
				if (iter.dir == 1) {
					if ((iter.y + iter.len)<step.col&&step.hasBlock[iter.x][iter.y + iter.len] == false) {
						Map m2 = Map(step);
						//m2.pre = NULL;
						m2.s.erase(iter);
						m2.s.insert(Block(iter.x, iter.y + 1, iter.len));
						m2.hasBlock[iter.x][iter.y + iter.len] = m2.hasBlock[iter.x][iter.y];
						m2.hasBlock[iter.x][iter.y] = 0;
						if (iter.x == step.aim.x && iter.y == step.aim.y) {
							m2.aim.y++;
						}
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + "right";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}
					}
					if ((iter.y)>0
						&& step.hasBlock[iter.x][iter.y - 1] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						m2.s.insert(Block(iter.x, iter.y - 1, iter.len));
						m2.hasBlock[iter.x][iter.y - 1] = m2.hasBlock[iter.x][iter.y];
						m2.hasBlock[iter.x][iter.y + iter.len - 1] = 0;
						if (iter.x == step.aim.x && iter.y == step.aim.y) {
							m2.aim.y--;
						}
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + "left";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}
						
					}
				}
				else if (iter.dir == -1) {
					if ((iter.x + iter.len)<step.row&&
						step.hasBlock[iter.x + iter.len][iter.y] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						m2.s.insert(Block(iter.x + 1, iter.y, -iter.len));
						m2.hasBlock[iter.x + iter.len][iter.y] = m2.hasBlock[iter.x][iter.y];
						m2.hasBlock[iter.x][iter.y] = 0;
						if (iter.x == step.aim.x && iter.y == step.aim.y) {
							m2.aim.x++;
						}
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + "down";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}
						
					}
					if ((iter.x)>0
						&& step.hasBlock[iter.x - 1][iter.y] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						m2.s.insert(Block(iter.x - 1, iter.y, -iter.len));
						m2.hasBlock[iter.x - 1][iter.y] = m2.hasBlock[iter.x][iter.y];
						m2.hasBlock[iter.x + iter.len - 1][iter.y] = 0;
						if (iter.x == step.aim.x && iter.y == step.aim.y) {
							m2.aim.y--;
						}
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + "up";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
							
						}
						
					}
				}
			}
		}
	}

// 移动到底，减少深度与分支
	bool solve3() {

		int ceng = 0;
		int ccc = 0;
		clock_t t1 = 0, t2 = 0;
		while (list.size() > 0) {
			Map step = list.front();

			//cout << "start" << endl;
			//cout << "pre" << endl;
			//if (step->pre != NULL)step->pre->show();

			//cout << step->str << endl;
			//step->show();
			//cout << "-----------" << endl;
			if (step.layer > ccc) {
				//cout << ceng << "<" << step.layer << endl;
				ccc = step.layer;
				t1 = clock();
				cout << "第" << ccc << "步" << t1 - t2 << endl;
				t2 = t1;

			}
			//cout <<"layer >>" <<step.layer << endl;;
			list.pop();
			++ceng;
			//if(Map::state.size()==300)
			//showState(Map::state);
			//cout << ceng << endl;
			//cout <<"size>>"<< Map::state.size() << endl;
			Map::state.insert(step.s);
			if (step.win()) {
				cout << "win" << endl;
				cout << step.str << endl;
				return true;
			}
			for (auto iter : step.s) {
				if (iter.dir == 1) {
					if ((iter.y + iter.len)<step.col&&step.hasBlock[iter.x][iter.y + iter.len] == false) {
						Map m2 = Map(step);
						//m2.pre = NULL;
						m2.s.erase(iter);
						if (iter.y + iter.len+ 3 < step.col&&step.hasBlock[iter.x][iter.y + iter.len + 3] == false
							&& step.hasBlock[iter.x][iter.y + iter.len + 2] == false
							&& step.hasBlock[iter.x][iter.y + iter.len + 1] == false
							) {
							m2.s.insert(Block(iter.x, iter.y + 4, iter.len));
							m2.hasBlock[iter.x][iter.y + iter.len] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 2] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 3] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y] = 0;
							m2.hasBlock[iter.x][iter.y + 1] = 0;
							m2.hasBlock[iter.x][iter.y + 2] = 0;
							m2.hasBlock[iter.x][iter.y + 3] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y+4;
							}
						}
						else if (iter.y + iter.len + 2 < step.col&&step.hasBlock[iter.x][iter.y + iter.len + 2] == false
							&& step.hasBlock[iter.x][iter.y + iter.len + 1] == false
							) {
							m2.s.insert(Block(iter.x, iter.y + 3, iter.len));
							m2.hasBlock[iter.x][iter.y + iter.len] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 2] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y] = 0;
							m2.hasBlock[iter.x][iter.y + 1] = 0;
							m2.hasBlock[iter.x][iter.y + 2] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y + 3;
							}
						}
						else if(iter.y + iter.len + 1 < step.col&&step.hasBlock[iter.x][iter.y + iter.len + 1] == false
							) {
							m2.s.insert(Block(iter.x, iter.y + 2, iter.len));
							m2.hasBlock[iter.x][iter.y + iter.len] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len + 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y] = 0;
							m2.hasBlock[iter.x][iter.y + 1] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y + 2;
							}
						}
						else {
							m2.s.insert(Block(iter.x, iter.y + 1, iter.len));
							m2.hasBlock[iter.x][iter.y + iter.len] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y + 1;
							}
						}
						
						
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + " right";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}
					}
					if ((iter.y)>0
						&& step.hasBlock[iter.x][iter.y - 1] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						if (iter.y - 4 >= 0 && step.hasBlock[iter.x][iter.y - 4] == false
							&& step.hasBlock[iter.x][iter.y - 3] == false
							&& step.hasBlock[iter.x][iter.y - 2] == false) {
							m2.s.insert(Block(iter.x, iter.y - 4, iter.len));
							m2.hasBlock[iter.x][iter.y - 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y - 2] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y - 3] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y - 4] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len - 1] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 2] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 3] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 4] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y= m2.aim.y-4;
							}
						}
						else if (iter.y - 3 >= 0 && step.hasBlock[iter.x][iter.y - 3] == false
							&& step.hasBlock[iter.x][iter.y - 2] == false) {
							m2.s.insert(Block(iter.x, iter.y - 3, iter.len));
							m2.hasBlock[iter.x][iter.y - 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y - 2] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y - 3] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len - 1] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 2] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 3] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y - 3;
							}
						}
						else if (iter.y - 2 >= 0 &&step.hasBlock[iter.x][iter.y - 2] == false
							&& step.hasBlock[iter.x][iter.y - 1] == false) {
							m2.s.insert(Block(iter.x, iter.y - 2, iter.len));
							m2.hasBlock[iter.x][iter.y -1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y -2] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len - 1] = 0;
							m2.hasBlock[iter.x][iter.y + iter.len - 2] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y - 2;
							}
						}
						else {
							m2.s.insert(Block(iter.x, iter.y - 1, iter.len));
							m2.hasBlock[iter.x][iter.y - 1] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y + iter.len - 1] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y = m2.aim.y - 1;
							}
						}
						
						
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + " left";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}

					}
				}
				else if (iter.dir == -1) {
					if ((iter.x + iter.len)<step.row&&
						step.hasBlock[iter.x + iter.len][iter.y] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						if (iter.x + iter.len+3 < step.row 
							&& step.hasBlock[iter.x + iter.len + 3][iter.y] == false
							&& step.hasBlock[iter.x + iter.len + 2][iter.y] == false
							&& step.hasBlock[iter.x + iter.len + 1][iter.y] == false) {
							m2.s.insert(Block(iter.x+4, iter.y, -iter.len));
							m2.hasBlock[iter.x + iter.len + 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len + 2][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len + 3][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x  + 1][iter.y] = 0;
							m2.hasBlock[iter.x  + 2][iter.y] = 0;
							m2.hasBlock[iter.x + 3][iter.y] = 0;
							m2.hasBlock[iter.x][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x + 4;
							}
						}else if (iter.x + iter.len + 2 < step.row
							&& step.hasBlock[iter.x + iter.len + 2][iter.y] == false
							&& step.hasBlock[iter.x + iter.len + 1][iter.y] == false) {
							m2.s.insert(Block(iter.x + 3, iter.y, -iter.len));
							m2.hasBlock[iter.x + iter.len + 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len + 2][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x  + 1][iter.y] = 0;
							m2.hasBlock[iter.x  + 2][iter.y] = 0;
							m2.hasBlock[iter.x ][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x + 3;
							}
						}
						else if (iter.x + iter.len + 1 < step.row
							&& step.hasBlock[iter.x + iter.len + 1][iter.y] == false) {
							m2.s.insert(Block(iter.x + 2, iter.y, -iter.len));
							m2.hasBlock[iter.x + iter.len + 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + 1][iter.y] = 0;
							m2.hasBlock[iter.x ][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x + 2;
							}
						}
						else {
							m2.s.insert(Block(iter.x + 1, iter.y, -iter.len));
							m2.hasBlock[iter.x + iter.len][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x++;
							}
						}
						
						
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + " down";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);
						}

					}
					if ((iter.x)>0
						&& step.hasBlock[iter.x - 1][iter.y] == false
						) {
						Map m2 = Map(step);
						m2.s.erase(iter);
						if (iter.x - 4 >= 0
							&& step.hasBlock[iter.x -4][iter.y] == false
							&& step.hasBlock[iter.x -3][iter.y] == false
							&& step.hasBlock[iter.x -2][iter.y] == false) {
							m2.s.insert(Block(iter.x - 4, iter.y, -iter.len));
							m2.hasBlock[iter.x - 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 2][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 3][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 4][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len - 1][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 2][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 3][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 4][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x - 4;
							}
						}else if (iter.x - 3 >= 0
							&& step.hasBlock[iter.x - 3][iter.y] == false
							&& step.hasBlock[iter.x - 2][iter.y] == false) {
							m2.s.insert(Block(iter.x - 3, iter.y, -iter.len));
							m2.hasBlock[iter.x - 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 2][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 3][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len - 1][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 2][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 3][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x - 3;
							}
						}
						else if (iter.x - 2 >= 0
							&& step.hasBlock[iter.x - 2][iter.y] == false) {
							m2.s.insert(Block(iter.x - 2, iter.y, -iter.len));
							m2.hasBlock[iter.x - 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x - 2][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len - 1][iter.y] = 0;
							m2.hasBlock[iter.x + iter.len - 2][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.x = m2.aim.x - 2;
							}
						}
						else {
							m2.s.insert(Block(iter.x - 1, iter.y, -iter.len));
							m2.hasBlock[iter.x - 1][iter.y] = m2.hasBlock[iter.x][iter.y];
							m2.hasBlock[iter.x + iter.len - 1][iter.y] = 0;
							if (iter.x == step.aim.x && iter.y == step.aim.y) {
								m2.aim.y--;
							}
						}
						
						m2.layer++;
						m2.str = m2.str + ";";
						m2.str += to_string(iter.x) + "," + to_string(iter.y) + " up";
						if (step.state.find(m2.s) == step.state.end()) {
							list.push(m2);

						}

					}
				}
			}
		}
	}
int main() {
	Map maze;
	list.push(maze);
	//set<Block> s1, s2;
	//s1.insert(Block(1, 1, 1));
	//cout << (s1.find(Block(1, 1, 1))== s1.end()) << endl;
	solve3();
	//maze.show();
	getchar();
}