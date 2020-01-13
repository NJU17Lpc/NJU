#include <iostream>
using namespace std;

/*
���͵�virtualizing non-member functions
���ǳ�Ա�������⻯
��Ȼ��Ҫ��CPoint2D��CPoint3D�ֱ���һ��<< >>����
*/

class CPoint2D {
public:
	CPoint2D() {}
	virtual void setParam(istream& in) {
		in >> m_x >> m_y;
	}
	virtual void display(ostream& out) {
		out << m_x << "," << m_y;
	}
protected:
	double m_x;
	double m_y;
};

class CPoint3D :CPoint2D {
public:
	CPoint3D() {}
	virtual void setParam(istream& in) {
		CPoint2D::setParam(in);
		in >> m_z;
	}
	virtual void display(ostream& out) {
		CPoint2D::display(out);
		out << "," << m_z;
	}
protected:
	double m_z;
};

int main() {
	CPoint2D c1;
	CPoint3D c2;
	c1.setParam(cin);
	c2.setParam(cin);

	c1.display(cout);
	cout << endl;
	c2.display(cout);

	return 0;
}