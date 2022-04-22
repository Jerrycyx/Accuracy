#ifndef ACCURACY_H
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int Max_ACC_len=10000;

struct ACC{
	int num[Max_ACC_len+5];
	int len;
	bool neg;
	void clear()
	{
		for(int i=1;i<=Max_ACC_len;i++)
			num[i]=0;
		len=0;
		neg=false;
		return;
	}
	void copy(ACC x)
	{
		for(int i=1;i<=x.len;i++)
			num[i]=x.num[i];
		len=x.len;
		neg=x.neg;
		return;
	}
	void print()
	{
		if(neg==true) printf("-");
		for(int i=len;i>=1;i--)
			printf("%d",num[i]);
		return;
	}
	void get()
	{
		char st[Max_ACC_len+5];
		scanf("%s",st);
		int stlen=strlen(st);
		if(st[0]=='-')
		{
			neg=true;
			for(int i=1;i<stlen;i++)
				num[stlen-i-1]=st[i]-'0';
			len=stlen-1;
		}
		else
		{
			neg=false;
			for(int i=0;i<stlen;i++)
				num[stlen-i]=st[i]-'0';
			len=stlen;
		}
		return;
	}
	void debug()
	{
		printf("	Debug:\n");
		printf("	len=%d\n",len);
		printf("	num={");
		for(int i=len;i>=1;i--)
			printf("%d",num[i]);
		printf("}\n");
		printf("	neg=%d\n",neg);
	}
};

bool ACC_cmp(ACC x,ACC y)
{
	if(x.neg==true&&y.neg==false) return false;
	if(x.neg==false&&y.neg==true) return true;
	
	bool res=true;
	
	if(x.len>y.len) res=true;
	if(x.len<y.len) res=false;
	if(x.len==y.len)
	{
		for(int i=x.len;i>=1;i--)
		{
			if(x.num[i]>y.num[i])
			{
				res=true;
				break;
			}
			if(x.num[i]<y.num[i])
			{
				res=false;
				break;
			}
		}
	}
	return (x.neg==true)?(!res):(res);
}
ACC ACC_max(ACC x,ACC y)
{
	return ACC_cmp(x,y)?x:y;
}
ACC ACC_add_abs(ACC x,ACC y)
{
	int len=max(x.len,y.len);
	for(int i=1;i<=len;i++)
	{
		x.num[i]+=y.num[i];
		x.num[i+1]+=x.num[i]/10;
		x.num[i]%=10;
	}
	if(x.num[x.len+1]>0)
		x.len++;
	x.neg=false;
	return x;
}
ACC ACC_sub_abs(ACC x,ACC y)
{
	int len=max(x.len,y.len);
	for(int i=1;i<=len;i++)
	{
		if(x.num[i]<y.num[i])
		{
			x.num[i+1]-=1;
			x.num[i]+=10;
		}
		x.num[i]-=y.num[i];
	}
	while(x.num[x.len]==0)
		x.len--;
	x.neg=false;
	return x;
}
ACC ACC_sub(ACC x,ACC y)
{
	if(x.neg==false&&y.neg==true)
		return ACC_add_abs(x,y);
	if(x.neg==true&&y.neg==false)
	{
		x=ACC_add_abs(x,y);
		x.neg=true;
		return x;
	}
	if(x.neg==false&&y.neg==false)
	{
		if(ACC_cmp(x,y)==true)
			return ACC_sub_abs(x,y);
		else
		{
			x=ACC_sub_abs(y,x);
			x.neg=true;
			return x;
		}
	}
	if(x.neg==true&&y.neg==true)
	{
		x.neg=false;
		y.neg=false;
		if(ACC_cmp(x,y)==true)
			x=ACC_sub_abs(x,y);
		else
		{
			x=ACC_sub_abs(y,x);
			x.neg=true;
		}
		x.neg=!x.neg;
	}
}
ACC ACC_add(ACC x,ACC y)
{
	if(x.neg==false&&y.neg==false)
		return ACC_add_abs(x,y);
	if(x.neg==true&&y.neg==true)
	{
		x.neg=false;
		y.neg=false;
		x=ACC_add_abs(x,y);
		x.neg=true;
		return x;
	}
	if(x.neg==false&&y.neg==true)
	{
		y.neg=false;
		return ACC_sub(x,y);
	}
	if(x.neg==true&&y.neg==false)
	{
		x.neg=false;
		return ACC_sub(y,x);
	}
}
#endif
