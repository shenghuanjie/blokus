/*
	<<Practice of Programming in C&C++>>
	Sample Program of Team Game -- Blokus  
*/
 
#include <iostream>
#include <string>
#include <cmath>
using namespace std;



int Mypoint=0, Otherpoint=0;
bool startstage=true;
struct 
{
	int x;
	int y;
	int i;
	int d;
}choosepoint;

const int
	Length = 19,
	//游戏棋盘的规模（[0..19]*[0..19]）。
	Piecesize = 4,
	//方块的规模（[0..4]*[0..4]）。
	Piecenum = 20,
	//方块的个数（编号依次为, 1, ... , 20）。

	Blankcolour = 4;
	//游戏棋盘上空白格子的颜色。
int	Mycolour = 5;
	//自己方块的颜色。


const double
	Ironsize[Piecenum + 1] =
	//方块的大小，即每个方块的分值。
		{
			1, 2, 3, 4, 5, 3, 4,
			5, 5, 4, 5, 4, 5, 5,
			5, 5, 5, 4, 5, 5, 5
		};


struct board {
		int
			b[Length + 1][Length + 1];
	};
	//游戏棋盘。其[i][j]分量的值，表示第i行、第j列的格子的颜色。
	//本程序中的其它“坐标”[x][y]，也都表示第x行、第y列。
struct piece {
		int
			p[Piecesize + 1][Piecesize + 1];
	};
	//方块，其分量的值为或，表示该格子是否被占。

const piece
	Iron[Piecenum + 1] =
	//游戏描述中给出的种方块。
		{
			//No.0
			{
				{1, 0, 0, 0, 0,				
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.1
			{
				{1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.2
			{
				{1, 1, 1, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.3
			{
				{1, 1, 1, 1, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.4
			{
				{1, 1, 1, 1, 1,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.5
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.6
			{
				{1, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.7
			{
				{1, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.8
			{
				{1, 1, 0, 0, 0,
				 0, 1, 1, 0, 0,
				 0, 0, 1, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.9
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.10
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.11
			{
				{1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.12
			{
				{1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.13
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.14
			{
				{0, 1, 0, 0, 0,
				 1, 1, 1, 0, 0,
				 0, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.15
			{
				{1, 0, 0, 0, 0,
				 1, 1, 1, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.16
			{
				{1, 1, 1, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.17
			{
				{0, 1, 1, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.18
			{
				{0, 1, 1, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.19
			{
				{0, 1, 1, 0, 0,
				 0, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.20
			{
				{0, 1, 1, 1, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			}
		};


board
	cur;
	//当前的游戏棋盘。
piece
	diamond[Piecenum + 1][8];
	//其[i][d]分量，表示第i种方块经第d种方式旋转后，得到的方块。
bool
	used[Piecenum + 1];
	//其[i]分量表示第i个方块是否已被使用。
int
	fx, fy;
	//第一个方块必须覆盖的格子坐标。
bool
	meetend;
	//是否收到[end]指令。

void turn(int d, piece oir, piece & res);
//方块oir经第d种方式旋转后，得到方块res。
void forge();
//生成diamond数组。
void clean(board & cur);
//初始化游戏棋盘。
void start(board & cur);
//执行[start]指令。

bool putable(board cur, int x, int y, int i, int d);
//判断以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，能否被放置在
//当前棋盘上。
bool putablefirst(int x, int y, int i, int d);
//判断以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，能否作为第一
//个方块，被放置在棋盘上。

void putsingle(board & cur, int x, int y, int p, int i, int d);
//将以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，以颜色p放置在
//棋盘上。
void putothers(board & cur);
//执行[put]指令——根据输入的其他玩家所放置的方块，更新游戏棋盘各个格子的颜色。
void putmine(board & cur);
//依次选择（枚举）方块的种类、旋转方式、位置，直至其能够放置在当前棋盘上为止，并
//输出结果。
void putminefirst(board & cur);
//依次选择（枚举）第一个方块的种类、旋转方式、位置，直至其能够放置在当前棋盘上为
//止，并输出结果。

int ownnumber();//计算自己代号的函数，——(0,0)，——(0,19)，——(19,19)，——(19,0)
void availabledot();//计算目前扩展点的个数
double middle();//计算到中心的距离
void deletesingle(board & cur, int x, int y,int i, int d);//移除方块儿
double getgrade(int x,int y,int i,int d);//计算分数
double extendplace();//计算到出生点的距离
int main()
{
	forge();
	start(cur);
	//初始化游戏棋盘，并生成游戏所需方块。
	putothers(cur);
	putminefirst(cur);
	//放置第一个方块。
	meetend = false;
	for (;;) {
		putothers(cur);
		if (meetend == true)
			break;
		putmine(cur);
	}
	//不断根据输入更新当前游戏棋盘，并输出自己的放置信息，直至接收到[end]指令。
	return 0;
}

void turn(int d, piece oir, piece & res)
//方块oir经第d种旋转方式后，得到方块res。
{
	int
		u, v;

	switch (d) {
		case 0 :
		//原状。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[u            ][v            ];
		break;

		case 1 :
		//向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - v][u            ];
		break;

		case 2 :
		//向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - u][Piecesize - v];
		break;

		case 3 :
		//向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[v            ][Piecesize - u];
		break;

		case 4 :
		//水平翻转。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[u            ][Piecesize - v];
		break;

		case 5 :
		//水平翻转后向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - v][Piecesize - u];
		break;

		case 6 :
		//水平翻转后向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - u][v            ];
		break;

		case 7 :
		//水平翻转后向右度。
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[v            ][u            ];
	}
}

void forge()
//生成diamond数组。
{
	int
		i, d;

	for (i = 0; i <= Piecenum; i++)
	for (d = 0; d <= 7; d++)
		turn(d, Iron[i], diamond[i][d]);
	//将第i种方块（Iron[i]）经第d种旋转方式后得到的方块，记录入diamond数组。
}

void clean(board & cur)
//初始化游戏棋盘。
{
	int
		u, v;

	for (u = 0; u <= Length; u++)
	for (v = 0; v <= Length; v++)
		cur.b[u][v] = Blankcolour;
	//将游戏棋盘初始化为未放置方块的格子的颜色。
}

void start(board & cur)
//执行[start]指令。
{
	string
		command;

	getline(cin, command);
	cin>>fx>>fy;
	cin.get();
	//输入第一个方块必须覆盖的格子。
	Mycolour=ownnumber();
	clean(cur);
	memset(used, 0, sizeof(used));
	//初始化游戏棋盘，并将所有方块置为“未使用过”状态。
}

bool putable(board cur, int x, int y, int i, int d)
//判断以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，能否被放置在
//当前棋盘上。
{
	int
		u, v;
	bool
		corner;
	
	corner = false;
	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++) {
		if (
			(diamond[i][d].p[u][v] == 1) &&
			(
				((x + u) < 0     ) ||
				((y + v) < 0     ) ||
				((x + u) > Length) ||
				((y + v) > Length) ||
				//是否有格子超出游戏棋盘的范围。
				(cur.b[x + u][y + v] != Blankcolour) ||
				(
					((y + v + 1) <= Length) &&
					(cur.b[x + u    ][y + v + 1] == Mycolour)
					//右边。
				) ||
				(
					((x + u + 1) <= Length) &&
					(cur.b[x + u + 1][y + v    ] == Mycolour)
					//下边。
				) ||
				(
					((y + v - 1) >= 0) &&
					(cur.b[x + u    ][y + v - 1] == Mycolour)
					//左边。
				) ||
				(
					((x + u - 1) >= 0) &&
					(cur.b[x + u - 1][y + v	   ] == Mycolour)
					//上边。
				)
				//是否与自己的格子有相邻的边。
			)
		)
			return false;
		if (
			(corner == false) &&
			(diamond[i][d].p[u][v] == 1) &&
			(
				(
					((x + u - 1) >= 0     ) &&
					((y + v + 1) <= Length) &&
					(cur.b[x + u - 1][y + v + 1] == Mycolour)
					//右上角。
				) ||
				(
					((x + u + 1) <= Length) &&
					((y + v + 1) <= Length) &&
					(cur.b[x + u + 1][y + v + 1] == Mycolour)
					//右下角。
				) ||
				(
					((x + u + 1) <= Length) &&
					((y + v - 1) >= 0     ) &&
					(cur.b[x + u + 1][y + v - 1] == Mycolour)
					//左下角。
				) ||
				(
					((x + u - 1) >= 0     ) &&
					((y + v - 1) >= 0     ) &&
					(cur.b[x + u - 1][y + v - 1] == Mycolour)
					//左上角。
				)
			)
			//是否有相连的顶点。
		)
			corner = true;
	}
	if (corner == true)
		return true;
	else
		return false;
	//如果遇到过相连的顶点，则结果为“能”。
}

bool putablefirst(int x, int y, int i, int d)
//判断以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，能否作为第一
//个方块，被放置在棋盘上。
{
	int
		u, v;
	bool
		filled;

	filled = false;
	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++) {
		if (
			(diamond[i][d].p[u][v] == 1) &&
			(
				((x + u) < 0     ) ||
				((y + v) < 0     ) ||
				((x + u) > Length) ||
				((y + v) > Length)
			)
			//是否有格子超出游戏棋盘的范围（第一次放置方块时，不可能与自己的格子
			//有相邻的边，因此无需判断这一点）。
		)
			return false;
		if (
			(diamond[i][d].p[u][v] == 1) &&
			((x + u) == fx) &&
			((y + v) == fy)
			//是否能覆盖格子(fx, fy)。
		)
			filled = true;
	}
	if (filled == true)
		return true;
	else
		return false;
	//如果格子(fx, fy)被覆盖，则结果为“能”。
}

void putsingle(board & cur, int x, int y, int p, int i, int d)
//将以(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，以颜色p放置在
//棋盘上。
{
	int
		u, v;

	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++)
		if (diamond[i][d].p[u][v] == 1)
			cur.b[x + u][y + v] = p;
		//因为(x, y)是左上角坐标，所以该方块的(u, v)位置，对应于游戏棋盘上的
		//(x + u, y + v)位置。
}

void putothers(board & cur)
//执行[put]指令——根据输入的其他玩家所放置的方块，更新游戏棋盘各个格子的颜色。
{
	string
		command;
	int
		n, ni, x, y, p, i, d;

	getline(cin, command);
	if (command == "[end]") {
		meetend = true;
		return;
	}
	//如果遇到[end]指令，则游戏结束，自动退出。

	cin>>n;
	cin.get();
	for (ni = 1; ni <= n; ni++) {
		cin>>x>>y>>p>>i>>d;
		cin.get();
		putsingle(cur, x, y, p, i, d);
		//每输入一个其他玩家所放置的方块，更新棋盘一次。
	}
}

void putmine(board & cur)
//依次选择（枚举）方块的种类、旋转方式、位置，直至其能够放置在当前棋盘上为止，并
//输出结果。
{
	int
		u, v, i, d;
	int Mytemppoint,Othertemppoint;
	double mark=0;double bestmark=-999999;
	availabledot();
	Mytemppoint=Mypoint;
	Othertemppoint=Otherpoint;
	double beforedistance;
	double beforeextend=extendplace();
	if(startstage)beforedistance=middle();
	for (i = 0; i <= Piecenum; i++)
	{
	//枚举方块种类。
	for (d = 0; d <= 7; d++)
	{//枚举旋转方式。
		for (u = (- Piecesize); u <= Length; u++)
		{
	       for (v = (- Piecesize); v <= Length; v++)
	     {
	//枚举方块左上角的格子的坐标。
		if(startstage&&(!used[i])&&putable(cur, u, v, i, d))
		{
			putsingle(cur, u, v, Mycolour, i, d);
			mark=beforedistance-middle();
			mark+=Ironsize[i]*8.0;
			if(mark>bestmark)
			{
				choosepoint.d=d;
				choosepoint.y=v;
				choosepoint.x=u;
				choosepoint.i=i;
				bestmark=mark;
			}
			deletesingle(cur, u, v, i, d);
		}
		else
		{
		if ((!used[i])&&putable(cur, u, v, i, d))
			//如果其未被使用，且可以放置在当前游戏棋盘上。
		{
			putsingle(cur, u, v, Mycolour, i, d);
			Mypoint=Mytemppoint;
			Otherpoint=Othertemppoint;
			mark=getgrade(u,v,i,d);
			mark+=2*(extendplace()-beforeextend);
			if(mark>bestmark)
			{
				choosepoint.d=d;
				choosepoint.y=v;
				choosepoint.x=u;
				choosepoint.i=i;
				bestmark=mark;
			}
			deletesingle(cur, u, v, i, d);
		}
		}
		   }
		}
	}
	}
	putsingle(cur, choosepoint.x, choosepoint.y, Mycolour, choosepoint.i, choosepoint.d);
	
		used[choosepoint.i] = true;


			cout<<choosepoint.x<<' '<<choosepoint.y<<' '<<choosepoint.i<<' '<<choosepoint.d<<endl<<flush;
			//根据该方块的种类、旋转方式、位置，在棋盘上放置该方块并输出结果。
}

void putminefirst(board & cur)
//依次选择（枚举）第一个方块的种类、旋转方式、位置，直至其能够放置在当前棋盘上为
//止，并输出结果。
{
	if (fx == 0 && fy == 0)
	{
		putsingle(cur,0, 0,Mycolour, 8, 7);
		cout << "0 0 8 7" << endl;
		used[8]=true;
    }
	else if (fx == 0 && fy == 19)
	{
		putsingle(cur,0, 15,Mycolour, 8, 1);
		cout << "0 15 8 1"<< endl;
		used[8]=true;
    }
	else if (fx == 19 && fy == 19)
	{
		putsingle(cur,17, 17, Mycolour, 8, 7);
		cout << "17 17 8 7" << endl;
		used[8]=true;
    }
	else if (fx == 19 && fy == 0)
	{
		putsingle(cur,17, -2, Mycolour, 8, 1);
		cout << "17 -2 8 1"<< endl;
		used[8]=true;
    }
}

void deletesingle(board & cur, int x, int y,int i, int d)
//在(x, y)为左上角坐标的第i种方块，经第d种方式旋转后得到的方块，弃置
//棋盘上。
{
	int
		u, v;

	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++)
		if (diamond[i][d].p[u][v] == 1)
			cur.b[x + u][y + v] = Blankcolour;
		//因为(x, y)是左上角坐标，所以该方块的(u, v)位置，对应于游戏棋盘上的
		//(x + u, y + v)位置。
}



int ownnumber()
{
	if(fx==0)
	{
		if(fy==0)
			return 0;
		else 
			return 1;
	}
	else
	{
		if(fy==0)
			return 3;
		else 
			return 2;
	}
}
bool ok(int i,int j,int color)//判断该点是否有邻近的同色点
{
	int left,right,up,down;
	left=(i-1>=0);
	right=(i+1<=Length);
	up=(j-1>=0);
	down=(j+1<=Length);
	
	return (

		(!right||cur.b[i+1][j]!=color)&&
					(!down||cur.b[i][j+1]!=color)&&
					(!left||cur.b[i-1][j]!=color)&&
					(!up||cur.b[i][j-1]!=color)
		
		
		);
}
void availabledot()
{
	Mypoint=0;Otherpoint=0;
	int i,j;
	bool left,right,up,down;
	for(i=0;i<=Length;i++)
	{
		for(j=0;j<=Length;j++)
		{
			left=(i-1>=0);
			right=(i+1<=Length);
			up=(j-1>=0);
			down=(j+1<=Length);
			if(cur.b[i][j]!=Blankcolour)
			{
				if(cur.b[i][j]==Mycolour)
				{
					if(left&&up&&cur.b[i-1][j-1]==Blankcolour&&ok(i-1,j-1,cur.b[i][j]))
					{
					Mypoint++;}
					if(left&&down&&cur.b[i-1][j+1]==Blankcolour&&ok(i-1,j+1,cur.b[i][j]))
					{
					Mypoint++;}
					if(right&&up&&cur.b[i+1][j-1]==Blankcolour&&ok(i+1,j-1,cur.b[i][j]))
					{
					Mypoint++;}
					if(right&&down&&cur.b[i+1][j+1]==Blankcolour&&ok(i+1,j+1,cur.b[i][j]))
					{
					Mypoint++;}
				}
				else
				{
					if(left&&up&&cur.b[i-1][j-1]==Blankcolour&&ok(i-1,j-1,cur.b[i][j]))
					{
					Otherpoint++;}
					if(left&&down&&cur.b[i-1][j+1]==Blankcolour&&ok(i-1,j+1,cur.b[i][j]))
					{
					Otherpoint++;}
					if(right&&up&&cur.b[i+1][j-1]==Blankcolour&&ok(i+1,j-1,cur.b[i][j]))
					{
					Otherpoint++;}
					if(right&&down&&cur.b[i+1][j+1]==Blankcolour&&ok(i+1,j+1,cur.b[i][j]))
					{
					Otherpoint++;}
				}
			}
		}
	}
}

	

double middle()
{
	int i,j;
	double len=999;double temp;
	for(i=0;i<=Length;i++)
	{
		for(j=0;j<=Length;j++)
		{
			if(cur.b[i][j]==Mycolour)
			{
				temp=sqrt((10.0-i)*(10.0-i)+(10.0-j)*(10.0-j));
					if(temp<len)
						len=temp;
			}
		}
	}
	if(len<=2)startstage=false;
	return len;
}
double getgrade(int x,int y,int i,int d)
{
	double Mygrade=Mypoint,Othergrade=Otherpoint;
	Mypoint=Otherpoint=0;
	availabledot();
	double mark=0;
	mark+=Ironsize[i]*8.0;
	mark+=((Mypoint-Mygrade+1)*9+Othergrade-Otherpoint);
	return mark;
}

double extendplace()
{
	double s;double Maxs=-1000;
	int u,v;
	int i,j;
	for(i=0;i<=Length;i++)
	{
		for(j=0;j<=Length;j++)
		{
			if(cur.b[i][j]==Mycolour)
			{
				s=sqrt((double)(fx-i)*(fx-i)+(fy-j)*(fy-j));
				if(s>Maxs)
				{
					u=i;
					v=j;
					Maxs=s;
				}
			}
		}
	}
	return Maxs;
}

