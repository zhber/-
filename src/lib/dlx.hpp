/*
 * ��ȷ�������⣺
 *	 ����01����ѡ��һЩ�еļ��ϣ�ʹ�ü�����ÿһ��**ǡ��**һ��1
 *	 �÷� bool ans=dlx.dfs(0) ������dfs�������ù�
 *	 ��������Ҫ dlx.init(n,m)
 * ���󵥵�0��1��link(x,y)
 * ���������dlx.ans[k]��ȡ����,0<=k<dlx.cnt
 */
struct DLX
{
	const static int maxn=740;
	const static int maxm=330;
	const static int maxnode=200010;//���������'1'�ĸ���

	#define FF(i,A,s) for(i=A[s];i!=s;i=A[i])

	int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
	int size,col[maxnode],row[maxnode],s[maxm],H[maxn];
	bool vis[maxm];
	int ans[maxn],cnt;
	void init(int n,int m)
	{
		register int i;
		for(i=0;i<=m;i++)
		{
			L[i]=i-1;
			R[i]=i+1;
			U[i]=D[i]=i;
			s[i]=0;
		}
		for(i=1;i<=n;i++)H[i]=-1;
		L[0]=m;
		R[m]=0;
		size=m+1;
		cnt=-1;
	}
	void link(int r, int c)
	{
		U[size]=c;
		D[size]=D[c];
		U[D[c]]=size;
		D[c]=size;
		if(H[r]<0)H[r]=L[size]=R[size]=size;
		else
		{
			L[size]=H[r];
			R[size]=R[H[r]];
			L[R[H[r]]]=size;
			R[H[r]]=size;
		}
		s[c]++;
		col[size]=c;
		row[size]=r;
		size++;
	}

	void del(int c)
	{
		L[R[c]]=L[c];
		R[L[c]]=R[c];
		register int i,j;
		FF(i,D,c)FF(j,R,i)
			U[D[j]]=U[j],D[U[j]]=D[j],--s[col[j]];
	}
	void add(int c)
	{
		R[L[c]]=L[R[c]]=c;
		register int i,j;
		FF(i,U,c)FF(j,L,i)
			++s[col[U[D[j]]=D[U[j]]=j]];
	}
	bool dfs(int k)
	{
		if(!R[0])
		{
			cnt=~cnt?(k<cnt?k:cnt):k;
			return true;
		}
		if(~cnt&&k>=cnt)return false;
		int c=R[0];
		bool mk=0;
		register int i,j;
		FF(i,R,0) if(s[c]>s[i])c=i;
		del(c);
		FF(i,D,c)
		{
			FF(j,R,i) del(col[j]);
			ans[k]=row[i];
			if(dfs(k+1))return true; /* ֻҪ���һ�� */
			FF(j,L,i)add(col[j]);
		}
		add(c);
		return mk;
	}
	#undef FF
};