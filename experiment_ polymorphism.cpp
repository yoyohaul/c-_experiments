#include<iostream>
#include<math.h>
#include <stdlib.h>
using namespace std;
/*用基类指针数组存放指向各种派生类对象的指针，
然后遍历该数组，就能对各个派生类对象做各种操作。*/
class Cshape
{
public:
	virtual float Area() = 0; //纯虚函数 纯虚函数只在声明的时候加上virtual，之后定义的时候是不加virtual
	virtual void PrintInfo() = 0;
};

class CRectangle :public Cshape//共有继承
{
public:
	float w, h;
	virtual float Area();  //虚函数，虚函数的出现是为多态提供服务的
	virtual void PrintInfo();
};
float CRectangle::Area()
{
	return w*h;
}

void CRectangle::PrintInfo()
{
	cout << "Rectangle:" << Area() << endl;
}

class CCircle :public Cshape
{
public:
	float r;
	virtual float Area();
	virtual void PrintInfo();
};

float CCircle::Area()
{
	return 3.14*pow(r,2);
}

void CCircle::PrintInfo()
{
	cout << "Circile:" << Area() << endl;
}
class CTriangle:public Cshape
{
public:
	float a, b, c;
	virtual float Area();
	virtual void PrintInfo();
};
float CTriangle::Area()
{
	float p = a + b + c;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

void CTriangle::PrintInfo()
{
	cout << "Triangle:" << Area() << endl;
}
Cshape *cshape[100]; //指针数组
int compare(const void * src1, const void * src2)
{
	double a1,a2;
	Cshape **p1; //指向指针的指针
	Cshape **p2;
	p1 = (Cshape **)src1; //类型强制转换成指向指针的指针
	p2 = (Cshape **)src2;
	a2 = (*p2)->Area();
	a1 = (*p1)->Area();
	
	if (a1 < a2) return -1;
	else if (a1>a2) return 1;
	else return 0;
}
int main(int argc, char** argv)
{
	int i,n;
	CTriangle *pt;
	CRectangle *pr;
	CCircle *pc;
	char c;
	cout << "please input the number of shapes:" << endl;
	cin >> n;
	int count = 0;
	for ( i = 0; i < n; i++)
	{
		cout << "please input the shape:" << endl;
		cin >> c;
		switch (c)
		{
			case 'R':
				pr = new CRectangle();
				cout << "please input the value" << endl;
				cin >> pr->h >> pr->w;
				cshape[count] = pr;
				count += 1;
				break;
			case 'T':
				pt = new CTriangle();
				cout << "please input the value" << endl;
				cin >> pt->a >> pt->b >> pt->c;
				cshape[count] = pt;
				count += 1;
				break;
			case 'C':
				pc = new CCircle();
				cout << "please input the value" << endl;
				cin >> pc->r;
				cshape[count] = pc;
				count += 1;
				break;
			default:
				break;
		}
	}
	qsort(cshape, n, sizeof(Cshape*),compare); //数组排序语句
	for (i = 0; i < n; i++)
	{
		cshape[i]->PrintInfo(); //多态的实现 
	}
	system("pause");
	return 0;
}