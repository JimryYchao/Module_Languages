#include <iostream>
using namespace std;
class Mc
{
private:
	int m_num;
	void Fun()
	{
		cout << m_num << endl;
	}

public:
	Mc(int);
	Mc();
	void Mun(void);
};
//Mc::Mc(){
//	m_num = 100000;
//	Fun();
//}
Mc::Mc(int m_num)
{
	this->m_num = m_num;
	Fun();
}
void Mc::Mun()
{
	m_num = 10000;
	Fun();
}
int main()
{
	Mc m = Mc(10);
	Mc h(10);
	Mc n = Mc();
	Mc f;
	//f.Mun();
}