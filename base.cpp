#include<iostream>
#include<cstring>
#include<string>
#include<ctime>
#include<random>
#include<cmath>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int date=0;
int gameEnd=0;
class character {
public:
	int intellegence;//����
	int strength;//����
	int income;//����
	int money;//��Ǯ
	int move;//�ж���
	int luck;//����ֵ
	character() :intellegence(50), income(50), strength(50), money(0), move(0),luck(0) {};
} player;


class card {
public:
	int number;
	string name;
	string description;
	int weight;

	//��������
	int dintellegence;
	int dstrength;
	int dincome;
	int dmoney;
	int dmove;
	card():	weight(-100){};
	card(int nu,string na,string des,int we,int dint,int dst,int dinc,int dmon,int dmov):number(nu),name(na),description(des),weight(we),dintellegence(dint),dstrength(dst),dincome(dinc),dmoney(dmon),dmove(dmov){};
};

class news {
public:
	int number;
	string name;
	string description;

	//��������
	int dintellegence;
	int dstrength;
	int dincome;
	int dmoney;
	int dmove;
	news(int nu,string na,string des,int dint,int dst,int dinc,int dmon,int dmov):number(nu),name(na),description(des),dintellegence(dint),dstrength(dst),dincome(dinc),dmoney(dmon),dmove(dmov){};
};
void gameStart();
void day();//����һ����¼�
void dayStart();//һ��Ŀ�ʼ����
void setLuck();//�趨��������ֵ
void putCard();//ÿһ�쿪ʼʱ���������뿨��
void randomEvent();//����¼�
void drawACard();//����
void drawTenCard();//ʮ��
void chooseCard(int cardNumber);//���ѡ��
void dayEnd();//һ��Ľ�������
bool judgeEnd();//�ж���Ϸ��������

card cardLibrary[500];
vector<news> newsPool;
vector<int> cardPool;//����
void gameStart(){
	//��ȡ������Ϣ
	freopen("card.txt","r",stdin);
	int num;
	while (cin>>num){
		if (num==999) break;
		string name,description;
		int weight,dintellegence,dstrength,dincome,dmoney,dmove;
		cin>>name>>description>>weight>>dintellegence>>dstrength>>dincome>>dmoney>>dmove;
		cardLibrary[num]=card(num,name,description,weight,dintellegence,dstrength,dincome,dmoney,dmove);
	}
	fclose(stdin);
	cin.clear();
	//��ȡ����¼���Ϣ
	freopen("news.txt","r",stdin);
	while (cin>>num){
		if (num==999) break;
		string name,description;
		int dintellegence,dstrength,dincome,dmoney,dmove;
		cin>>name>>description>>dintellegence>>dstrength>>dincome>>dmoney>>dmove;
		newsPool.push_back(news(num,name,description,dintellegence,dstrength,dincome,dmoney,dmove));
	}
	fclose(stdin);
	cin.clear();
	//�ض�������������
	freopen("CON", "r", stdin); 
}
void day() {
	dayStart();
	setLuck();
	putCard();
	randomEvent();
	if (judgeEnd()) return;
	int n;
	while (player.move > 0) {
		cout << "income:" << player.income << endl;
		cout << "intellegence:" << player.intellegence << endl;
		cout << "strength:" << player.strength << endl;
		cout << "money:" << player.money << endl;
		cout << "move:" << player.move << endl;
		if (judgeEnd()) return;
		cout << "1.���� 10.ʮ��(1000��Ǯ) 0.��һ��"<<endl;
		cin >> n;//TODO:��Ϊ������ѡ�񵥳�/ʮ��/������һ��
		if (n == 1) drawACard();
		if (n == 10) {
			if (player.money>=1000) drawTenCard();
			else  cout<<"Ǯ����!"<<endl;
		}
		if (n == 0) break;
		if (judgeEnd()) return;
	}
}

void dayStart() {
	date++;
	cout<<"DAY"<<date<<":"<<endl;
	player.money += player.income * 10;
	player.move = max(player.strength/15, 1);
	//TODO:ת������
}
int luckPool[10] = { 0,1,1,2,2,2,2,3,3,4 };
void setLuck() {
	player.luck = luckPool[rand() % 10];
	cout<<"�������ƣ�";
	switch (player.luck) {
	case 0:cout << "����" << endl; break;
	case 1:cout << "��" << endl; break;
	case 2:cout << "��ƽ" << endl; break;
	case 3:cout << "��" << endl; break;
	case 4:cout << "��" << endl; break;
	}
	player.luck+=player.intellegence/25;
	//TODO:��ǩ����
}
void putCard(){
	cardPool.clear();
	for (int i=0;i<500;i++){
		for (int j=0;j<cardLibrary[i].weight+player.luck;j++)
			cardPool.push_back(i);
	}
}


void randomEvent() {
	int pos = rand() % newsPool.size();
	news today_event= newsPool[pos];
	newsPool.erase(newsPool.begin() + pos);//�����ų���ɾȥ�¼�����֤ͬһ�ֲ��ٴ���
	cout << today_event.name << endl;
	cout << today_event.description << endl;
	player.income += today_event.dincome;
	player.intellegence += today_event.dintellegence;
	player.strength += today_event.dstrength;
	player.money += today_event.dmoney;
	player.move += today_event.dmove;
	if (today_event.dincome != 0) cout << "income+" << today_event.dincome << endl;
	if (today_event.dintellegence != 0) cout << "intellegence+" << today_event.dintellegence << endl;
	if (today_event.dstrength != 0) cout << "strength+" << today_event.dstrength << endl;
	if (today_event.dmoney != 0) cout << "money+" << today_event.dmoney << endl;
	if (today_event.dmove != 0) cout << "move+" << today_event.dmove << endl;
}



void chosenCard(int cardNumber){
	card& chosenCard = cardLibrary[cardNumber];
	cout << chosenCard.name << endl;
	cout << chosenCard.description << endl;
	player.income += chosenCard.dincome;
	player.intellegence += chosenCard.dintellegence;
	player.strength += chosenCard.dstrength;
	player.money += chosenCard.dmoney;
	player.move += chosenCard.dmove;
	if (chosenCard.dincome != 0) cout << "income+" << chosenCard.dincome << endl;
	if (chosenCard.dintellegence != 0) cout << "intellegence+" << chosenCard.dintellegence << endl;
	if (chosenCard.dstrength != 0) cout << "strength+" << chosenCard.dstrength << endl;
	if (chosenCard.dmoney != 0) cout << "money+" << chosenCard.dmoney << endl;
	if (chosenCard.dmove != 0) cout << "move+" << chosenCard.dmove << endl;
	player.move--;
}
void drawACard() {
	int cardNum = cardPool[rand() % cardPool.size()];
	chosenCard(cardNum);
}
void drawTenCard() {
	player.money-=1000;
	vector<int> cardNum;
	for (int i=0;i<10;i++)
		cardNum.push_back(cardPool[rand() % cardPool.size()]);	
	while (player.move > 0) {
		for (int i = 0; i < cardNum.size(); i++)
			cout <<i+1<< cardLibrary[cardNum[i]].name << endl;
		cout<<0<<"����Ҫ��"<<endl;
		int num;
		cin >> num;
		if (num == 0) break;
		chosenCard(cardNum[num-1]);
		cardNum.erase(cardNum.begin()+num-1);
	}
}
bool judgeEnd(){
	gameEnd=1;
	if (player.intellegence>=100){
		cout<<"�����"<<endl;
		return true;
	}
	if (player.intellegence<=0){
		cout<<"�󱿵�"<<endl;
		return true;
	}
	if (player.income>=100){
		cout<<"vivo50"<<endl;
		return true;
	}
	if (player.income<=0){
		cout<<"���ֻ�ܳ���"<<endl;
		return true;
	}
	if (player.strength>=100){
		cout<<"��"<<endl;
		return true;
	}
	if (player.strength<=0){
		cout<<"��"<<endl;
		return true;
	}
	if (date>20){
		cout<<"̫����"<<endl;
		return true;
	}
	gameEnd=0;
	return false;
}

int main() {
	srand(unsigned(time(0)));
	
	cout << "���"<<endl;
	gameStart();
	while (!gameEnd){
		day();
	}
	cout<<"game over";
}
