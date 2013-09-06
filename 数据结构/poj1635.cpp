#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

string str;

string dfs(int st, int ed)
{
	int cnt = 0 ;
	vector<string> ve;
	for(int i=st; i<=ed; i++)
	{
		if(str[i] == '0')
			cnt ++;
		else
			cnt --;
		if(cnt == 0)
		{
			if(i == st + 1)
				ve.push_back("01");
			else
				ve.push_back("0" + dfs(st+1, i-1) + "1");
			st = i+1;
		}
	}
	sort(ve.begin(), ve.end());
	string ans("");
	for(int i=0; i<ve.size(); i++)
		ans += ve[i];
	return ans;
}

int main()
{
	int cas;
	cin >> cas;
	while(cas --)
	{
		cin >> str;
		string hash1 = dfs(0, str.length()-1);
		cin >> str;
		string hash2 = dfs(0, str.length()-1);
		//cout<<hash1<<" "<<hash2<<endl;
		if(hash1 == hash2)
			printf("same\n");
		else
			printf("different\n");
	}
	return 0;
}

