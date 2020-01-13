#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Hero {
protected:
	int hp;
	int atk;
	string hero_name;
public:
	Hero(int hp, int atk, string hero_name) :hp(hp), atk(atk), hero_name(hero_name) {}
	void startAtk(Hero* opponent) {
		opponent->beingAtked(this->atk);
	}
	virtual void beingAtked(int damage) {};
	virtual void doMagic(){}
	bool isSurvivor() { return hp > 0; }
	string getSurvivorInfo(){
		if (isSurvivor()) {
			return hero_name + " " + to_string(atk) + " " + to_string(hp);
		}
		else {
			return "not a valid survivor";
		}
	}
};

class Warrior :public Hero {
public:
	
	void beingAtked(int damage){
		this->hp = this->hp - damage;
	}
	void doMagic() {
		if (this->hp > 0) {
			this->hp++;
		}
	}
	Warrior() :Hero(12, 2, "Warrior") {}
};

class Magician :public Hero {
private:
	bool powerUsed;
	int remDamage;
public:
	void beingAtked(int damage) {
		hp = hp - damage;
		if (!powerUsed) { remDamage = damage; }
	}

	void doMagic() {
		if (!powerUsed) {
			hp = hp + remDamage;
			powerUsed = true;
		}
	}
	Magician() :Hero(2, 6, "Magician") {
		powerUsed = false;
	}
};

class Leader :public Hero {
public:
	void beingAtked(int damage) {
		this->hp = this->hp - damage;
	}
	void doMagic() {
		if (this->hp > 0) {
			this->atk++;
		}
	}
	Leader() :Hero(6, 6, "Leader") {}
};

class Battle {
private:
	vector<Hero*> player1_heros;
	vector<Hero*> player2_heros;
	int winner;
	int cur_player1_hero;
	int cur_player2_hero;
	bool player1HasNextHero() { return cur_player1_hero < player1_heros.size()-1; }
	bool player2HasNextHero() { return cur_player2_hero < player2_heros.size()-1; }
	Hero* getPlayer1NextHero() {
		return player1_heros[++cur_player1_hero];
	}
	Hero* getPlayer2NextHero() {
		return player2_heros[++cur_player2_hero];
	}
public:
	Battle():winner(0), cur_player1_hero(0), cur_player2_hero(0){}

	void addHero(int player, int type) {
		Hero* tempHero;
		switch (type) {
		case 1:
			tempHero = new Warrior();
			break;
		case 2:
			tempHero = new Magician();
			break;
		case 3:
			tempHero = new Leader();
			break;
		default:
			cout << "input wrong hero type" << endl;
			break;
		}
		if (player == 1) {
			player1_heros.push_back(tempHero);
		}
		else if (player == 2) {
			player2_heros.push_back(tempHero);
		}
		else {
			cout << "wrong player type" << endl;
		}
	}

	void startFight() {
		Hero* h1 = player1_heros[cur_player1_hero];
		Hero* h2 = player2_heros[cur_player2_hero];
		fight(h1, h2);
	}

	void fight(Hero* h1, Hero* h2) {
		h1->startAtk(h2);
		h2->startAtk(h1);
		h1->doMagic();
		h2->doMagic();
		if ((!h1->isSurvivor()) && (!h2->isSurvivor()) && (!player1HasNextHero()) && (!player2HasNextHero())) {
			winner = 3;
			return;
		}


		if (!h1->isSurvivor()) {//h1如果没有活下来，就换下一个
			if (player1HasNextHero()) {//如果h1有下一个，就换下一个
				h1 = getPlayer1NextHero();
			}
			else {//如果没有下一个，宣布player2赢了
				winner = 2;
				return;
			}
		}

		if (!h2->isSurvivor()) {//h2如果没有活下来，就换下一个
			if (player2HasNextHero()) {//如果h2有下一个，就换下一个
				h2 = getPlayer2NextHero();
			}
			else {//如果没有下一个，宣布player1赢了
				winner = 1;
				return;
			}
		}

		fight(h1, h2);
		return;
	}

	void printWinner() {
		if (winner == 1) {
			for (int i = 0; i < player1_heros.size(); i++) {
				if (player1_heros[i]->isSurvivor()) {
					cout << player1_heros[i]->getSurvivorInfo() << endl;
				}
			}
		}
		else if (winner == 2) {
			for (int i = 0; i < player2_heros.size(); i++) {
				if (player2_heros[i]->isSurvivor()) {
					cout << player2_heros[i]->getSurvivorInfo() << endl;
				}
			}
		}
		else if (winner == 3) {
			cout << "All Dead";
		}
		else{
			cout << "not have a winner" << endl;
		}
		
	}
};

int main() {
	int n = 0;
	cin >> n;
	int type = 0;
	Battle battle;
	for (int i = 0; i < n; i++) {
		//添加玩家一的英雄
		cin >> type;
		battle.addHero(1, type);
	}
	for (int i = 0; i < n; i++) {
		//添加玩家二的英雄
		cin >> type;
		battle.addHero(2, type);
	}
	battle.startFight();
	battle.printWinner();
	return 0;
}