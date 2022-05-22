#include <iostream>
using namespace std;
/********************Printer Example*****************************/
class Printer
{
public:
	static void printText(string s) { cout << s << endl; count++; }
	static Printer* getInstance()
	{
		return singlePrinter;
	}
	static int getUseTimes()
	{
		return count;
	}

private:
	static int count;
	static Printer* singlePrinter;
	Printer() {}
	Printer(const Printer& p) {}
};

Printer* Printer::singlePrinter = new Printer;

/**********************ChairMan Example*******************************/
class ChairMan
{
private:
	static ChairMan* singleMan;
	ChairMan() 
	{
		cout << "ChairMan" << endl;
	}

	ChairMan(const ChairMan& c)
	{
	}

public:

	static	ChairMan* getInstance()
	{
		return singleMan;
	}
	 
};

ChairMan* ChairMan::singleMan = new ChairMan;
int Printer::count = 0;
void test()
{
	ChairMan* cm1 = ChairMan::getInstance();
	ChairMan* cm2 = ChairMan::getInstance();
	if (cm1 == cm2)
	{
		cout << "CM1 == CM2" << endl;
	}

	Printer* p1 = Printer::getInstance();
	p1->printText("HAHAHAHAAHAH");
}
int main()
{
	cout << "Main" << endl;
	test();
    system("pause");
    return 0;
}