#include<iostream>
#include<vector>
using namespace std;
class food {
protected:
	double carbohydrate;
	double protein;
	double DF;
	double fat;
public:
	food(double carbohydrate, double protein, double DF, double fat):
		carbohydrate(carbohydrate), protein(protein), DF(DF), fat(fat){}
	virtual double getCarbohydrate() {
		return carbohydrate;
	}
	virtual double getProtein() {
		return protein;
	}
	virtual double getDF() {
		return DF;
	}
	virtual double getFat() {
		return fat;
	}
};

class rice:public food {
public:
	rice():food(16.2, 3.7, 0, 0){}
};

class beef:public food {
public:
	beef():food(1.8, 17.5, 0, 7.2) {}
};

class bro :public food {
public:
	bro() :food(0.2, 0.4, 3.6, 0) {}
};

class oat:public food {
public:
	oat():food(12.3, 5.7, 7.3, 3) {}
};

class duck:public food {
public:
	duck():food(6.9, 9, 0, 9.3) {}
};

class cab:public food {
public:
	cab():food(2.1, 0.8, 4.3, 0) {}
};

class diet {
private:
	vector<food> vFood;
	double rec_carbohydrate;
	double rec_protein;
	double rec_DF;
	double rec_fat;
public:
	diet():rec_carbohydrate(13.3), rec_protein(13.5), rec_DF(3.3), rec_fat(10.3) {}
	diet& operator+= (const food& f) {
		vFood.push_back(f);
		return *this;
	}
	bool if_healthy() {
		double cur_carbohydrate = 0;
		double cur_protein = 0;
		double cur_DF = 0;
		double cur_fat = 0;
		for (vector<food>::iterator it = vFood.begin(); it != vFood.end(); it++) {
			cur_carbohydrate += (*it).getCarbohydrate();
			cur_protein += (*it).getProtein();
			cur_DF += (*it).getDF();
			cur_fat += (*it).getFat();
		}
		if (cur_carbohydrate >= rec_carbohydrate && cur_protein >= rec_protein
			&& cur_DF >= rec_DF && cur_fat <= rec_fat) {
			return true;
		}
		return false;
	}

};


int main() {
	int type;
	diet d;
	for (int i = 0; i < 3; i++) {
		cin >> type;
		if (type <= 0 || type >= 7) {
			cout << -1;
			return 0;
		}
		switch (type) {
		case 1: {
			rice r;
			d += r;
			break;
		}
		case 2: {
			beef b;
			d += b;
			break;
		}
		case 3: {
			bro b;
			d += b;
			break;
		}
		case 4: {
			oat o;
			d += o;
			break;
		}
		case 5: {
			duck du;
			d += du;
			break;
		}
		case 6: {
			cab c;
			d += c;
			break;
		}
		default: {
			cout << -1;
			break;
		}
		}
	}

	if (d.if_healthy()) {
		cout << "healthy";
	}
	else {
		cout << "unhealthy";
	}

	return 0;
}