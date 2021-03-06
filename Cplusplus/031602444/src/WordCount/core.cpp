#include"core.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<fstream>
#include<string>
#include<map>
using namespace std;

int characters = 0;
int lines = 0;
int words = 0;

struct SortByValue {
	bool operator()(const pair<string, int> & a, const pair<string, int> & b) {
		if (a.second == b.second) {
			return a.first < b.first;
		}
		else return a.second > b.second;
	}
};

void CountCharacters(ifstream& filemm)//统计行数和字符数
{
	char c;
	char lastline = '\0';

	while (filemm.get(c))
	{
		characters++;
		if (lastline != '\n'&&c == '\n')
		{
			lines++;
		}
		if (lastline == '\n' && (c == '\t' || c == ' '))
		{
			lastline = '\n';
		}
		else
		{
			lastline = c;
		}
	}

	if ((c == '\t' || c == ' ') && (lastline == '\t' || lastline == ' '))
	{
		lastline = c;
	}
	//如果文本最后一个字符是换行符或者前一个字符是换行符当前字符是空格要减去一行
	else if (c == '\n' || (lastline = '\n' && (c == '\t' || c == ' ')))
	{
		lines--;
	}

	lines++;

}

void CountWord(ifstream& filemm, map<string, int>& mapp)//统计词数词频
{
	string s;
	vector<int> ans;//存分隔符位置

	while (filemm >> s) //一次读取一个字符串，读取字符串不包括换行和空格和制表符
	{

		ans.clear();

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				ans.push_back(i);
			}
		}

		if (ans.size() == 0)//如果分割符数目等于0，就是只有一个字符串
		{
			//如果从该符号起四个字符都是字母
			if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
			{
				mapp[s]++;
				words++;
			}
			continue;
		}

		//否则就有一个以上的分隔符
		//先判断第一个，因为第一个没有分隔符做开头标记
		if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
		{
			string temp(s.substr(0, ans[0]));//满足前四个字符是字母，截取
			mapp[temp]++;
			words++;
		}

		for (int i = 0; i < ans.size(); i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[ans[i] + 1] >= 97 && s[ans[i] + 1] <= 122) && (s[ans[i] + 2] >= 97 && s[ans[i] + 2] <= 122) &&
				(s[ans[i] + 3] >= 97 && s[ans[i] + 3] <= 122) && (s[ans[i] + 4] >= 97 && s[ans[i] + 4] <= 122))
			{
				string temp(s.substr(ans[i] + 1, ans[i + 1] - ans[i] - 1));
				mapp[temp]++;
				words++;
			}
		}
	}
}

void SortWord(map<string, int>& mapp) //词频排序
{
	vector<pair<string, int>> v(mapp.begin(), mapp.end());
	sort(v.begin(), v.end(), SortByValue());
	int vecflag = 0;
	for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
	{
		cout << "<" << vec->first << ">: " << vec->second << endl;
		vecflag++;
		if (vecflag == 10) break;
	}

}