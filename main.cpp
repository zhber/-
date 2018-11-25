#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct Sudoku{
    int d[10][10];//���־���
    int col[10][10],row[10][10],block[4][4][10];//ÿ��ÿ��ÿ��ĳ��������û�г��ֹ�
    int ansnum;//�������
    vector<pair<int,int> >pos;//��¼�ɳں�δ��õ�λ��
    #define mem(a) memset(a,0,sizeof a)
    Sudoku()//��ʼ��
    {
    	mem(d);mem(col);mem(row);mem(block);
        pos.clear();ansnum=0;
        char s[15];
        for (int i=1;i<=9;i++)
		{
			scanf("%s",s+1);
			for (int j=1;j<=9;j++)d[i][j]=s[j]-'0';
		}
		for (int i=1;i<=9;i++)
			for (int j=1;j<=9;j++)
				if (d[i][j])col[i][d[i][j]]=row[j][d[i][j]]=block[(i-1)/3+1][(j-1)/3+1][d[i][j]]=1;
    }
    #undef mem
    int findnum(int x,int y)//������λ�õ�ֵ�ܸ�������λ�õ�ǰ���ֵȷ���ͷ������ֵ�����򷵻�0
    {
        int ans=0;
        for (int i=1;i<=9;i++)if (!col[x][i]&&!row[y][i]&&!block[(x-1)/3+1][(y-1)/3+1][i])
        {
            if (ans)return 0;
            else ans=i;
        }
        return ans;
    }
    void print()
    {
        for (int i=1;i<=9;i++)
        {
            for (int j=1;j<=9;j++)
				printf("%d",d[i][j]);
			puts("");
        }
    }
    void dfs(int now)
    {
        if (now==pos.size())
		{
            if (!ansnum)print();
            ansnum++;
            return;
		}
        int nowx=pos[now].first,nowy=pos[now].second;
        for (int i=1;i<=9;i++)if (!col[nowx][i]&&!row[nowy][i]&&!block[(nowx-1)/3+1][(nowy-1)/3+1][i])
		{
			col[nowx][i]=row[nowy][i]=block[(nowx-1)/3+1][(nowy-1)/3+1][i]=1;
            d[nowx][nowy]=i;
            dfs(now+1);
            if(ansnum)return;
			col[nowx][i]=row[nowy][i]=block[(nowx-1)/3+1][(nowy-1)/3+1][i]=0;
            d[nowx][nowy]=0;
		}
    }
    void solve()
    {
    	//�����Щλ����ֱ��ȷ����ֱ��ȷ��������ȷ����֮���������ȷ���µ�λ��
        bool finish=0;
        for (int T=1;T<=81&&!finish;T++)//�ɳ����81��
		{
            finish=1;
            for (int i=1;i<=9&&finish;i++)
				for (int j=1;j<=9&&finish;j++)
					if (!d[i][j]&&findnum(i,j))
					{
                        d[i][j]=findnum(i,j);
                        col[i][d[i][j]]=row[j][d[i][j]]=block[(i-1)/3+1][(j-1)/3+1][d[i][j]]=1;
                        finish=0;
					}
		}
		//�����һЩλ�ò���ȷ�����ͱ���
		for (int i=1;i<=9;i++)
			for (int j=1;j<=9;j++)
				if (!d[i][j])pos.push_back(make_pair(i,j));
        dfs(0);
    }
};
int main(int argc,char** argv)
{
    int T;scanf("%d",&T);
    while (T--)
	{
		Sudoku S;
		S.solve();
	}
}
