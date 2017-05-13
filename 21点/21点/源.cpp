#include<iostream>
#include<string>
#include<time.h>
#include<conio.h>
using namespace std;

#define NUM 1000
int j = 2;//定义为全局变量
int randNum[NUM];//因为rand()函数有一定的缺陷，所以在程序中定义了randNum数组来存放随机数
/*即使使用了种子函数srand(),由于程序运行时间比较短，也不太好设置种子。 因此使用数组来存放随机数*/

class Poker
{
private:
	int poker[53]; //扑克
	int pokerValue[53]; //扑克代表的数值
	string pokerName[53]; //扑克名
	int money; //玩家钱数 
	int cmoney; //庄家钱数
	int bet; //玩家的赌注
	int pokerF[5]; //玩家手中的牌 F:Farmer L:Landlord
	int pokerL[5]; //庄家手中的牌 F:Farmer L:Landlord
	int pokerNumF; //玩家手中的牌数
	int pokerNumL; //庄家手中的牌数
public:
	Poker(); //构造函数，对牌初始化
	void initPoker(); //洗牌,在每轮游戏开始前进行
	string getPokerF(); //用字符串的形式返回玩家的牌
	string getPokerL(); //用字符串的形式返回庄家的牌
	int getSumF(); //返回玩家牌的点数，用以判断是否超过21点
	int getSumL(); //返回庄家牌的点数
	void farmerAsk(); //玩家要牌
	void landlordAsk(); //庄家要牌
	void inputBet(); //玩家输入赌注
	void newGame(); //开始新游戏
	void landlordProcess();
};

Poker::Poker()
{
	int i;
	poker[0] = 0;
	for (i = 1; i <= 13; i++) //|
	{ //|
		poker[i] = i; //|用构造函数对牌初始化
		poker[i + 13] = i; //|
		poker[i + 26] = i; //|
		poker[i + 39] = i; //|
	}//for结束

	pokerValue[0] = 0;
	for (i = 1; i <= 52; i++)
	{
		if (poker[i] <= 10) pokerValue[i] = poker[i];
		else pokerValue[i] = 10;
	}//for结束


	pokerName[0] = "";
	for (i = 0; i<4; i++)
	{
		pokerName[1 + 13 * i] = "A";
		pokerName[2 + 13 * i] = "2";
		pokerName[3 + 13 * i] = "3";
		pokerName[4 + 13 * i] = "4";
		pokerName[5 + 13 * i] = "5";
		pokerName[6 + 13 * i] = "6";
		pokerName[7 + 13 * i] = "7";
		pokerName[8 + 13 * i] = "8";
		pokerName[9 + 13 * i] = "9";
		pokerName[10 + 13 * i] = "10";
		pokerName[11 + 13 * i] = "J";
		pokerName[12 + 13 * i] = "Q";
		pokerName[13 + 13 * i] = "K";
	}//for结束

	money = 200; //玩家开始玩游戏时钱数是200
	cmoney = 1000; //庄家开始玩游戏时钱数是1000
	bet = 0;

	for (i = 0; i<5; i++)
	{
		pokerF[i] = 0; //|对pokerOfFarmer初始化
		pokerL[i] = 0; //|对pokerOfLandlord初始化
	}


	pokerNumF = 0;//玩家手中的牌数初始化为0
	pokerNumL = 0;//庄家手中的牌数初始化为0

	srand((int)time(0));
	for (i = 0; i<NUM; i++)
	{
		randNum[i] = rand() * 51 / 32767 + 1;//产生随机数数组
	}

}//构造函数Poker()结束
void Poker::initPoker()
{
	cout << "新一局游戏开始，开始洗牌>>>>>" << endl;

	pokerF[0] = randNum[j++]; //产生1-52的随机数
	pokerF[1] = randNum[j++]; //产生1-52的随机数
	pokerL[0] = randNum[j++]; //产生1-52的随机数
	pokerL[1] = randNum[j++]; //产生1-52的随机数

	pokerNumF = 2;
	pokerNumL = 2;

	cout << "洗牌完成,你的牌为:" << getPokerF() << endl;
}//void Poker::initPoker()结束

string Poker::getPokerF()//用字符串的形式返回玩家的牌
{
	int i;
	string result = "";

	for (i = 0; i<pokerNumF; i++)
		result = result + pokerName[pokerF[i]] + " ";

	return result;
}//string Poker::getPokerF()结束

string Poker::getPokerL()//用字符串的形式返回庄家的牌
{
	int i;
	string result = "";

	for (i = 0; i<pokerNumL; i++)
		result = result + pokerName[pokerL[i]] + " ";

	return result;
}//string Poker::getPokerL()结束

int Poker::getSumF() //返回玩家的总点数
{
	int result = 0, j = 0;

	for (int i = 0; i<pokerNumF; i++)
		result = result + pokerValue[pokerF[i]];
	if (result < 21){
		for (int i = 0; i < pokerNumF; i++){
			if (pokerValue[pokerF[i]] == 1) j++;
		}
		if (j > 0){
			while (result<=11 && j>0){
				result += 10;
				j--;
			}
		}
	}
	return result;
}

int Poker::getSumL()//返回庄家的总点数
{

	int result = 0, j = 0;

	for (int i = 0; i<pokerNumL; i++)
		result = result + pokerValue[pokerL[i]];
	if (result < 21){
		for (int i = 0; i < pokerNumL; i++){
			if (pokerValue[pokerL[i]] == 1) j++;
		}
		if (j > 0){
			while (result <= 11 && j>0){
				result += 10;
				j--;
			}
		}
	}
	return result;
}

void Poker::farmerAsk()
{
	if (pokerNumF >= 5)
	{
		cout << "你的牌数已够5张，不能再要牌了！" << endl;
		landlordProcess();
	}
	else
	{
		pokerF[pokerNumF++] = randNum[j++]; //产生1-52的随机数
		cout << "你的牌为:" << getPokerF() << endl;
		if (getSumF()>21)
		{
			cout << "你撑死了,你输了" << bet << "元。" << endl;
			money = money - bet;
			cmoney += bet;

			if (money <= 0)
			{
				char key;
				cout << "你已经输光了所有钱！游戏结束..." << endl;
				cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
				cin >> key;
				if (key == '1'){
					money = 200;
					cmoney = 1000;
					newGame();
					return;
				}
				else exit(0);
			}
			inputBet();
			initPoker();
		}
		else if (getSumF() == 21)
		{
			landlordProcess();
		}
	}
}

void Poker::landlordAsk()
{
	if (pokerNumL >= 5)
	{
		if (getSumF()>getSumL())
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "你赢了,你赢了" << bet << "元" << endl;
			money = money + bet;
			cmoney -= bet;
		if (cmoney <= 0)
		{
			char key;
			cout << "恭喜你赢了庄家！游戏结束..." << endl;
			cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
			cin >> key;
			if (key == '1'){
				money = 200;
				cmoney = 1000;
				newGame();
				return;
			}
			else exit(0);
		}
			inputBet();
			initPoker();
		}
		else if (getSumF() == getSumL())
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "平手" << endl;
			inputBet();
			initPoker();
		}
		else if (getSumF()<getSumL())
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "你输了,你输了" << bet << "元" << endl;
			money = money - bet;
			cmoney += bet;
			if (money <= 0)
			{
				char key;
				cout << "你已经输光了所有钱！游戏结束..." << endl;
				cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
				cin >> key;
				if (key == '1'){
					money = 200;
					cmoney = 1000;
					newGame();
					return;
				}
				else exit(0);
			}
			inputBet();
			initPoker();
		}
	}
	else
	{
		pokerL[pokerNumL++] = randNum[j++]; //产生1-52的随机数
		if (getSumL()>21)
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "庄家撑死了,你赢了" << bet << "元" << endl;
			money = money + bet;
			cmoney -= bet;
			if (cmoney <= 0)
			{
				char key;
				cout << "恭喜你赢了庄家！游戏结束..." << endl;
				cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
				cin >> key;
				if (key == '1'){
					money = 200;
					cmoney = 1000;
					newGame();
					return;
				}
				else exit(0);
			}
			inputBet();
			initPoker();
		}
		else landlordProcess();
	}
}
void Poker::inputBet()
{
	cout << "现在你有" << money << "元，庄家有" << cmoney << "元，请输入赌注:";
	do
	{
		cin >> bet;
		if (bet>money)
			cout << "笨蛋，你没那么多钱，少来，重新输入吧:";
	} while (bet>money);

}

void Poker::newGame()
{
	inputBet();
	initPoker();
	cout << "你得到的牌为:" << getPokerF() << endl;
}

void Poker::landlordProcess()
{
	if (getSumL() >= 17)
	{
		if (getSumL()>getSumF())
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "庄家获胜，你输了" << bet << "元" << endl;
			money = money - bet;
			cmoney += bet;
			if (money <= 0)
			{
				char key;
				cout << "你已经输光了所有钱！游戏结束..." << endl;
				cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
				cin >> key;
				if (key == '1'){
					money = 200;
					cmoney = 1000;
					newGame();
					return;
				}
				else exit(0);
			}
			inputBet();
			initPoker();
		}
		else if (getSumF() == getSumL())
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "本次游戏平手" << endl;
			inputBet();
			initPoker();
		}
		else
		{
			cout << "庄家的牌为" << getPokerL() << endl;
			cout << "你赢了,你赢了" << bet << "元" << endl;
			money = money + bet;
			cmoney -= bet;
			if (cmoney <= 0)
			{
				char key;
				cout << "恭喜你赢了庄家！游戏结束..." << endl;
				cout << "1.重新开始 2.退出 >>请输入数字选择操作:";
				cin >> key;
				if (key == '1'){
					money = 200;
					cmoney = 1000;
					newGame();
					return;
				}
				else exit(0);
			}
			inputBet();
			initPoker();
		}
	}
	else
	{
		landlordAsk();
	}
}


int main()
{
	int choose = 1;
	Poker poker;
	cout << "****************************** 欢迎玩二十一点游戏 ******************************" << endl;
	poker.inputBet();
	poker.initPoker(); //洗牌 

	while (choose == 1 || choose == 2 || choose == 3 || choose == 4)
	{
		cout << "1.要牌 2.不要牌 3.重新开始 4.退出 >>请输入数字选择操作:";
		cin >> choose;
		if (choose == 1) poker.farmerAsk();
		else if (choose == 2) poker.landlordProcess();
		else if (choose == 3) poker.newGame();
		else if (choose == 4) exit(0);
	}
	return 0;
}//main函数结束
