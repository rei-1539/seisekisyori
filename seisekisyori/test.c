#include<stdio.h>
#include<math.h>

int p, ex, h, subn = 0, subj = 0;//p:管理用フラグ h:
int data[9999][99][99];
int gakunen[9999][99];
char subject[99][99];
int year = 19;

void input()
{
	FILE* fi;
	float student;
	int subject, n, f, stut, stub;
	fi = fopen("data.txt", "a");
	while (1)
	{
		printf("学籍番号> ");
		scanf("%f", &student);
		stut = student / 100;
		stub = fmod(student, 100);
		printf("科目(number)> ");
		scanf("%d", &subject);
		printf("点数> ");
		scanf("%d", &n);
		fprintf(fi, "%d %d %d %d\n", stut, stub, subject, n);
		printf("continue=0 exit=1> ");
		scanf("%d", &f);
		if (f == 1)break;
	}
	fclose(fi);
}

void load()
{
	FILE* fo;
	FILE* fc;
	float student;
	int subje, n, stut, stub;
	int n1, n2, n3;
	for (n1 = 0; n1 < 9999; n1++)
	{
		for (n2 = 0; n2 < 99; n2++)
		{
			for (n3 = 0; n3 < 99; n3++)
			{
				data[n1][n2][n3] = 999;
			}
			gakunen[n1][n2] = 999;
		}

	}
	fo = fopen("data.txt", "r");
	while (1)
	{
		fscanf(fo, "%d %d %d %d", &stut, &stub, &subje, &n);
		data[stut][stub][subje] = n;
		if (fgetc(fo) == EOF)break;
	}
	fclose(fo);
	fc = fopen("config.txt", "r");
	fscanf(fo, "%d %d", &year, &subj);
	for (n = 1; n <= subj; n++)
	{
		fscanf(fo, "%s", subject[n]);
	}
	fclose(fc);
}

int sum(float student)
{
	int n, ans, stut, stub;
	stut = student / 100;
	stub = fmod(student, 100);
	subn = 0;
	n = 0;
	ans = 0;
	while (n <= subj)
	{
		if (data[stut][stub][n] <= 100)
		{
			ans += data[stut][stub][n];
			subn++;
		}
		n++;
	}
	return ans;
}

float average(float student)
{
	int x, n;
	float ans;
	x = sum(student);
	ans = x / subn;
	return ans;
}


int redsub(float student)
{
	int n, ans, stut, stub;
	stut = student / 100;
	stub = fmod(student, 100);
	ans = 0;
	n = 0;
	while (n <= subj)
	{
		if (data[stut][stub][n] < 60)
		{
			ans++;
		}
		n++;
	}
	return ans;
}

int lostsub(float student)
{
	int n, ans, stut, stub;
	stut = student / 100;
	stub = fmod(student, 100);
	ans = 0;
	n = 0;
	while (n <= subj)
	{
		if (data[stut][stub][n] < 30)
		{
			ans++;
		}
		n++;
	}
	return ans;
}

int ryunen(float student)
{
	int n, revel, t;
	t = 0;
	n = lostsub(student);
	if (n != 0) t = 1;
	n = redsub(student);
	revel = fmod(student / 100, 10);
	if (revel < 4)
		if (n >= 3) t = 1;
		else if (revel > 3)
			if (n >= 5)	t = 1;
	return t;

}


void show()
{
	int stut, stub, all, f, n, red, lost, revel, class, sub, ryu, m;
	float ave, student;
	char c, x;
	printf("表示範囲\n1人:0 クラス:1 !beta!学年:2 !beta!在校生:3> ");
	scanf("%d", &f);
	if (f == 0)
	{
		printf("学籍番号> ");
		scanf("%f", &student);
		ave = average(student);
		all = sum(student);
		red = redsub(student);
		lost = lostsub(student);
		ryu = ryunen(student);
		stut = student / 100;
		stub = fmod(student, 100);
		for (n = 1; n <= subj; n++)
		{
			printf(" %s ", subject[n]);
		}
		printf("\n");
		for (n = 1; n <= subj; n++)
		{
			if (data[stut][stub][n] != 999)
			{
				printf("  %d  ", data[stut][stub][n]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
		printf("平均:%.2f 合計点:%d 赤点:%d 失点:%d\n", ave, all, red, lost);
		if (ryu != 0) printf("留年\n");
	}
	else if (f == 1)
	{
		printf("学年> ");
		scanf("%d", &revel);
		printf("M:1 E:2 D:3 S:4 C:5> ");
		scanf("%d", &class);
		stut = 1010 + 10 * year - 10 * revel + class;
		student = stut * 100;
		all = 0;
		red = 0;
		lost = 0;
		sub = 0;
		ryu = 0;
		for (n = 1; n <= subj; n++)
		{
			printf(" %s ", subject[n]);
		}
		printf("\n");

		for (n = 1; n < 99; n++)
		{
			all += sum(student + n);
			sub += subn;
			red += redsub(student + n);
			lost += lostsub(student + n);
			ryu += ryunen(student + n);
			stut = student / 100;
			stub = fmod(student + n, 100);
			if (data[stut][stub][1] != 999)
			{
				for (m = 1; m <= subj; m++)
				{
					if (data[stut][stub][m] != 999)
					{
						printf("  %d  ", data[stut][stub][m]);
					}
					else
					{
						printf("      ");
					}
				}
				printf("\n");
			}
		}
		ave = all / sub;
		printf("平均:%.2f 合計点:%d 赤点:%d 失点:%d 留年:%d人\n", ave, all, red, lost, ryu);
	}
	else if (f == 2)
	{
		printf("!beta!\n学年> ");
		scanf("%d", &revel);
		stut = 1010 + 10 * year - 10 * revel;
		student = stut * 100;
		all = 0;
		red = 0;
		lost = 0;
		sub = 0;
		ryu = 0;
		for (class = 1; class <= 5; class++)
		{
			for (n = 1; n < 99; n++)
			{
				all += sum(student + n);
				sub += subn;
				red += redsub(student + n);
				lost += lostsub(student + n);
				ryu += ryunen(student + n);
			}
		}
		ave = all / sub;
		printf("平均:%.2f 合計点:%d 赤点:%d 失点:%d 留年:%d\n", ave, all, red, lost, ryu);
	}
	else if (f == 3)
	{
		stut = 1010 + 10 * year - 10 * revel;
		student = stut * 100;
		all = 0;
		red = 0;
		lost = 0;
		sub = 0;
		ryu = 0;
		for (revel = 1; revel <= 5; revel++)
		{
			for (class = 1; class <= 5; class++)
			{
				for (n = 1; n < 99; n++)
				{
					all += sum(student + n + revel * 1000 + class * 100);
					sub += subn;
					red += redsub(student + n + revel * 1000 + class * 100);
					lost += lostsub(student + n + revel * 1000 + class * 100);
					ryu += ryunen(student + n + revel * 1000 + class * 100);
				}
			}
		}
		ave = all / sub;
		printf("平均:%.2f 合計点:%d 赤点:%d 失点:%d 留年:%d\n", ave, all, red, lost, ryu);
	}
}


void setting()
{
	int f, n, m;
	FILE* fc;
	fc = fopen("config.txt", "w");
	printf("mode 科目設定:0 年度:1> ");
	scanf("%d", &f);
	while (1)
	{
		if (f == 0)
		{
			printf("追加:1 訂正:2 終了:0> ");
			scanf("%d", &m);
			if (m == 1)
			{
				subj++;
				printf("科目名> ");
				scanf("%s", subject[subj]);
			}
			else if (m == 2)
			{
				printf("科目number>");
				scanf("%d", &n);
				printf("科目名> ");
				scanf("%s", subject[n]);
			}
			else
			{
				break;
			}
		}
		else if (f == 1)
		{
			printf("年度> ");
			scanf("%d", &year);

		}
	}
	fprintf(fc, "%d %d\n", year, subj);
	for (n = 1; n <= subj; n++)
	{
		fprintf(fc, "%s\n", subject[n]);
	}
	fclose(fc);
}

void mainwindow()
{
	while (1)
	{
		int f, n;
		//void UI()
		printf("\nselectmode\n終了:0,入力:1,表示:2,設定:3> ");
		scanf("%d", &f);
		if (f == 0)
		{
			break;
		}
		else if (f == 1)
		{
			input();
		}
		else if (f == 2)
		{
			show();
		}
		else if (f == 3)
		{
			setting();
		}
	}

}


void main()
{
	load();
	mainwindow();
}
