// GPL v3
// Yongda ZHU
// zzyzvivy@gmail.com

// This code was written during my undergraduate study as a part of my homework.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#define BOARDSIZE 8				 //棋盘大小
#define RND (rnd = Schrage(rnd)) //获取下一个随机数

using namespace std;

int MAINBOARD[BOARDSIZE][BOARDSIZE] = {0}; //主棋盘 0空 1黑 2白
int WEIGBOARD[BOARDSIZE][BOARDSIZE] = {1}; //权重表 实时更新
int vsperstep = 200000;

/* 用Schrage方法生成随机数*/
double Schrage(double seed)
{
	int q = 127773, r = 2836;
	double a = 16807;
	double m = 2147483647;
	double rnd;
	rnd = a * ((int)(seed * m) % q) - r * (int)(seed * m / q);
	// seed*m可退回除以m前的整数随机数
	rnd = rnd > 0 ? rnd : rnd + m; //若小于0，加上m
	rnd /= m;					   //变成0-1上的随机数
	return rnd;					   //子程序结束
}

/*五子棋胜负判断*/
int Count5(int a[BOARDSIZE][BOARDSIZE])
{
	int tmp;
	int result = 0; //1 black win, 2 white win
	for (int i = 0; i < BOARDSIZE - 4; i++)
	{
		for (int j = 0; j < BOARDSIZE - 4; j++)
		{
			tmp = a[i][j];
			if (tmp == 0)
				continue;
			if (((a[i + 1][j] == tmp) && (a[i + 2][j] == tmp) && (a[i + 3][j] == tmp) && (a[i + 4][j] == tmp)) || ((a[i][j + 1] == tmp) && (a[i][j + 2] == tmp) && (a[i][j + 3] == tmp) && (a[i][j + 4] == tmp)) || ((a[i + 1][j + 1] == tmp) && (a[i + 2][j + 2] == tmp) && (a[i + 3][j + 3] == tmp) && (a[i + 4][j + 4] == tmp)))
			{
				result = tmp;
				return result;
			}
		}
	}
	for (int i = BOARDSIZE - 1; i > 3; i--)
	{
		for (int j = 0; j < BOARDSIZE - 4; j++)
		{
			tmp = a[i][j];
			if (tmp == 0)
				continue;
			if ((a[i - 1][j + 1] == tmp) && (a[i - 2][j + 2] == tmp) && (a[i - 3][j + 3] == tmp) && (a[i - 4][j + 4] == tmp))
			{
				result = tmp;
				return result;
			}
		}
	}
	return result;
}

int FinalWin(int a[BOARDSIZE][BOARDSIZE])
{
	return Count5(a);
}

/*打印棋盘*/
void BoardPrint(int a[BOARDSIZE][BOARDSIZE])
{
	cout << endl
		 << "*****************************************\n"
		 << endl;
	cout << "\t";
	for (int i = 0; i < BOARDSIZE; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	cout << "\t\t";
	for (int k = 0; k < BOARDSIZE; k++)
	{
		cout << "\t";
	}
	cout << endl;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (a[i][j] == 0)
				cout << "＋"; //空点打印+
			else if (a[i][j] == 1)
				cout << "●"; //黑色实心圆点
			else if (a[i][j] == 2)
				cout << "○"; //白子空心圆点
			else
				cout << " □ "; //其他情况
			printf("\t");
		}
		cout << endl;
		cout << "\t\t";
		for (int k = 0; k < BOARDSIZE; k++)
		{
			cout << "\t";
		}
		cout << endl;
		cout << endl;
	}
	cout << "*****************************************\n"
		 << endl;
}

int lawfulpoint(int p, int q, int m, int n, int k, int a[BOARDSIZE][BOARDSIZE]) //p，q为随机点，m，n为beeaten的点，k为对手颜色
{
	int s;
	int b[BOARDSIZE][BOARDSIZE] = {0};
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			b[i][j] = a[i][j];

	if (a[p][q] != 0)
		return 0; //有点

	return 1;
}

int lawfulpoint(int p, int q, int k, int a[BOARDSIZE][BOARDSIZE]) //p，q为随机点，m，n为beeaten的点，k为对手颜色
{
	int s;
	int b[BOARDSIZE][BOARDSIZE] = {0};
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			b[i][j] = a[i][j];

	if (a[p][q] != 0)
		return 0; //有点

	return 1;
}

int main()
{
	// system("color F0");
	/*随机数生成部分*/
	double rnd;																//随机数
	rnd = (double)clock() / CLOCKS_PER_SEC - (int)clock() / CLOCKS_PER_SEC; //调用系统时间作随机种子
	RND;																	//获取随机数

	/*用户界面*/
	char UserChoice = 'B'; //用户选择黑白
	int currentcolor = 1;  //当前要下的颜色
	int GGColor = 0;	   //GammaGo颜色，也就是电脑执掌的颜色
	int x, y;			   //用户输入坐标

	int inputflg = 1; //输入是否合法
	cout << "五子棋" << endl;
	cout << "2020 ydzhuastro" << endl;

	cout << "（提示:游戏中可输入-2 -2放弃比赛。）\n你想作为黑棋(B)还是白棋(w):";
	cin >> UserChoice;

	if (UserChoice == 'B' || UserChoice == 'b')
	{
		cout << "请输入第一个黑色棋子的位置<行 列>:";
		cin >> x >> y;
		GGColor = 2;
	}
	else
	{
		x = y = BOARDSIZE / 2;
		GGColor = 1;
	}
	cout << "所以电脑的走棋顺序是 " << GGColor << endl;
	MAINBOARD[x][y] = 1; //黑子先走
	int endflg = 0;		 //终局标志
	int winflg = 0;		 //获胜标志 0 1 2
	for (int mainloop = 0;; mainloop++)
	{
		BoardPrint(MAINBOARD);
		//主循环 真实走棋
		currentcolor = currentcolor ^ 3;
		cout << "第" << mainloop + 1 << "手，" << endl;
		if (currentcolor == 1)
			cout << "黑子当局:" << endl;
		else
			cout << "白子当局:" << endl;
		if (currentcolor != GGColor)
		{
			inputflg = 0;
			while (!inputflg)
			{
				cout << "请落子<行 列> :";
				cin >> x >> y;
				if (x == -2 && y == -2)
				{
					cout << "你选择放弃。" << endl;
					exit(1);
				}
				inputflg = lawfulpoint(x, y, currentcolor ^ 3, MAINBOARD);
			}
			MAINBOARD[x][y] = currentcolor;
		}
		else
		{
			//初始化权重表
			for (int i = 0; i < BOARDSIZE; i++)
			{
				for (int j = 0; j < BOARDSIZE; j++)
				{
					WEIGBOARD[i][j] = 1;
					if (MAINBOARD[i][j] != 0)
					{
						WEIGBOARD[i][j] = -1;
					}
				}
			}
#pragma omp parallel for
			for (int localloop = 0; localloop < vsperstep; localloop++)
			{
				//模拟多次走棋
				int mx = -1, my = -1;		//尝试当前步位置
				int tempx = -1, tempy = -1; //循环时的位置

				int localinputflg;
				//复制主棋盘
				int TEMPBOARD[BOARDSIZE][BOARDSIZE] = {0};
				int localwinflg, localendflg;
				int localcount;
				for (int i = 0; i < BOARDSIZE; i++)
				{
					for (int j = 0; j < BOARDSIZE; j++)
					{
						TEMPBOARD[i][j] = MAINBOARD[i][j];
					}
				}
				//获得尝试位置
				localinputflg = 0;
				localcount = 0;
				while (!localinputflg)
				{
					localcount++;
					tempx = (int)(RND * BOARDSIZE);
					tempy = (int)(RND * BOARDSIZE);
					localinputflg = lawfulpoint(tempx, tempy, currentcolor ^ 3, TEMPBOARD);
					if (localinputflg)
					{
						break;
					}
					if (localcount > BOARDSIZE * BOARDSIZE)
					{
						//cout<<"***TOO many try!"<<endl;
						break;
					}
				}
				mx = tempx;
				my = tempy;
				TEMPBOARD[mx][my] = currentcolor;

				localendflg = 1;
				for (int i = 0; i < BOARDSIZE; i++)
				{
					for (int j = 0; j < BOARDSIZE; j++)
					{
						if (lawfulpoint(i, j, currentcolor, TEMPBOARD))
							localendflg = 0;
					}
				}
				//开始走棋
				int subtmpcolor = currentcolor;
				while (!localendflg)
				{
					//单次走棋
					subtmpcolor = subtmpcolor ^ 3;
					//获得尝试位置
					localcount = 0;
					localinputflg = 0;
					while (!localinputflg)
					{
						localcount++;
						tempx = (int)(RND * BOARDSIZE);
						tempy = (int)(RND * BOARDSIZE);
						localinputflg = lawfulpoint(tempx, tempy, subtmpcolor /*^3*/, TEMPBOARD);
						if (localinputflg)
							break;
						if (localcount > BOARDSIZE * BOARDSIZE)
						{
							//cout << "+++Too many try!" << endl;
							break;
						}
					}
					TEMPBOARD[tempx][tempy] = subtmpcolor;

					localendflg = 1;
					for (int i = 0; i < BOARDSIZE; i++)
					{
						for (int j = 0; j < BOARDSIZE; j++)
						{
							if (lawfulpoint(i, j, subtmpcolor ^ 3, TEMPBOARD))
								localendflg = 0;
						}
					}
					if (localendflg)
						break;
					if (Count5(TEMPBOARD))
						break;
				}
				localwinflg = FinalWin(TEMPBOARD);

				if (localwinflg == GGColor)
					WEIGBOARD[mx][my] += 1;
			}

			//找到权重最大的点
			int maxx = -1, maxy = -1, maxw = 0;
			for (int i = 0; i < BOARDSIZE; i++)
			{
				for (int j = 0; j < BOARDSIZE; j++)
				{
					if (WEIGBOARD[i][j] > maxw)
					{
						maxw = WEIGBOARD[i][j];
						maxx = i;
						maxy = j;
					}
				}
			}
			cout << "电脑选择落子于" << maxx << "行" << maxy << "列。" << endl;
			MAINBOARD[maxx][maxy] = currentcolor;
		}

		endflg = 1;
		for (int i = 0; i < BOARDSIZE; i++)
		{
			for (int j = 0; j < BOARDSIZE; j++)
			{
				if (lawfulpoint(i, j, currentcolor, MAINBOARD))
					endflg = 0;
			}
		}
		if (endflg || FinalWin(MAINBOARD))
			break;
	}
	winflg = FinalWin(MAINBOARD);
	if (winflg == 0)
	{
		cout << "平局!" << endl;
	}
	if (winflg == 1)
	{
		cout << "黑子胜!" << endl;
	}
	else if (winflg == 2)
	{
		cout << "白子胜!" << endl;
	}
	BoardPrint(MAINBOARD);
	// system("pause");

	return 0;
}
