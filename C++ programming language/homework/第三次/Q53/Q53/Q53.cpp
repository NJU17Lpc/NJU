#include<iostream>
#include<cmath>
using namespace std;
class GPU {
private:
	int price;
	int hashRate;

public:
	virtual double Caculate() = 0;
	int getPrice() { return this->price; }
	int getHashRate() { return this->hashRate; }
	void setPrice(int p) { this->price = p; }
	void setHashRate(int h) { this->hashRate = h; }
};

class GPUx:public GPU {
protected:
	double electric;

public:
	GPUx(double e):electric(e){}
	double Caculate() {
		int a = getHashRate();
		int b = electric;
		return getHashRate() * 0.02 - electric;
	}
	friend istream& operator>>(istream& in, GPUx& gpu) {
		int price = 0, hashRate = 0;
		in >> price >> hashRate;
		gpu.setPrice(price);
		gpu.setHashRate(hashRate);
		return in;
	}

};

class GPU1 : public GPUx {

public:
	GPU1() : GPUx(16.2) {};
};

class GPU2 : public GPUx {
public:
	GPU2():GPUx(28.8) {};
};

class GPU3 : public GPUx {
public:
	GPU3():GPUx(19.44) {};
};

int main() {
	GPU1 g1;
	GPU2 g2;
	GPU3 g3;

	cin >> g1 >> g2 >> g3;
	double dayImcome = g1.Caculate() + g2.Caculate() + g3.Caculate();
	if (dayImcome <= 0) {
		cout << -1;
	}
	else {
		cout << ceil((g1.getPrice()+g2.getPrice()+g3.getPrice())/dayImcome);
	}
	getchar();
	getchar();
	return 0;
}