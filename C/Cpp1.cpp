#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include <algorithm>
#define MAX 1000
//**************************************** paramster
struct USER   // 定义用户结构体
{
	char id[7];  // 用户编号
	char card[5]; // 卡类型
	long valid;  //有效期/次数
	char carid1[7]; //车牌号1
	char carid2[7]; //车牌号2
	char car1in[13]; //车1入场时间
	char car2in[13]; //车2入场时间
}user[MAX];

//定义月份数组，用于计算天数
int month[13][2]={{0,0},{31,31},{28,29},{31,31},{30,30},{31,31},{30,30},{31,31},{31,31},{30,30},{31,31},{30,30},{31,31}};
//**************************************** function
void showmenu();
void save(int);
void creat();
void display();
void add();
void modify();
void carin();
void carout();
void sort();
//**************************************** main function
int main()
{
	int select,flag,e;
	showmenu();
	printf("请输入您要进行的操作：");
	scanf("%d",&select);
	printf("\n");                          
	do										//指令选择
	{
		if(select>=1&&select<=8)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
			printf("input error.choose again.\n");
		}
	}while(!flag);
	while(flag)                             //指令执行
	{ 
		switch(select)
		{
		case 1:
			printf("创建记录会导致原有记录全部清空，确定继续操作吗(1/0)？");
			scanf("%d",&e);
			if(e==1){
				creat();
				break;
			}
			else
				break;
		case 2:
			add();
			break;
			case 3:
			display();
			break;
		case 4:
			carin();
			break;
		case 5:
			carout();
			break;
		case 6:
			modify();
			break;
		case 7:
			sort();
			break;
		case 8:
			exit(0);                        //exit(0):程序正常运行并退出                     
			break;
		default:break;
		};
		printf("\n");
		printf("是否继续操作?(1/0):");
		scanf("%d",&e);
		if(e==1)
		{
			flag=1;
			system("cls");
			showmenu();
			printf("请输入您要进行的操作： ");
			scanf("%d",&select);
			printf("\n");
		}
		else
			flag=0;
	};
	printf("*****感谢您的使用。*****\n");
	printf("\n");
	return 0;
};
//**************************************** functions 

void showmenu()           //指令菜单
{
	printf( "====== 校园车辆管理系统 ======\n" );
	printf("======\t1、创建记录\t======\n");
	printf("======\t2、添加记录\t======\n");
	printf("======\t3、浏览记录\t======\n");
	printf ("======\t4、车辆进入\t======\n");
	printf ("======\t5、车辆离开\t======\n");
	printf("======\t6、修改记录\t======\n");
	printf ("======\t7、排序显示\t======\n");
	printf ("======\t8、离开系统\t======\n");
	printf ("==============================\n") ;
	printf("如要退出系统，请保存信息！\n");
};

void save(int m){          //保存信息
	int i;
	FILE* fp;
	if((fp=fopen("car.txt","wb"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	for(i=0;i<m;i++)	
		if(fwrite(&user[i],sizeof(struct USER),1,fp)!=1)
			printf("file write error\n");
	fclose(fp);	
}

int load(){                //载入信息
	FILE* fp;
	int i=0;
	if((fp=fopen("car.txt","rb"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	else
	{
		do
		{
			fread(&user[i],sizeof(struct USER),1,fp);
			i++;
		}
		while(feof(fp)==0);
	}
	fclose(fp);
	return(i-1);
};

bool isFull(){ // 判断是否已满
    int m = load();
    if (m == MAX) {return true;}
    return false;
}

void display(){            //展示信息
	int i;
	int m=load();
	for(i=0;i<m;i++)
		printf("\t%s\t,\t%s\t,\t%d\t,\t%s\t,\t%s\t,\t%s\t,\t%s\t\n",user[i].id,user[i].card,user[i].valid,user[i].carid1,user[i].carid2,user[i].car1in,user[i].car2in);
};			

void creat()               //创建新信息数据
{
	int i,j,m,flag,k;
	char uid[7],cid1[7],cid2[7],today[7],va[7],tcard[5];
	long time,v;
	do										//判断输入是否符合要求：位数，数字
	{
		flag=1;
		printf("请输入今日日期(例190212): ");
		scanf("%s",&today);
		if(strlen(today)!=6)
			flag=0;
		for(k=0;today[k]!='\0' && flag;k++)
			if(isdigit(today[k])==0)           // 判断日期格式是否为数字：isdigit
				flag=0;
	}while(!flag);
	time=atol(today);                      //将时间转化为数字形式:atol

	do 
	{
       printf("输入创建用户数(1000以内)：");
       scanf("%d", &m);
    }while(m>1000);

	for(i=0;i<m;i++)
	{
		do                                 //录入用户id
		{
			flag=1;
			do                             //判断用户id是否合理
			{
				flag=1;
				printf("请输入由字母与数字组成的6位用户ID：");
				scanf("%s",&uid);
				if(strlen(uid)!=6)
					flag=0;
				for(k=0;uid[k]!='\0' && flag;k++)
					if(isalnum(uid[k])==0)     //判断用户id是否为字母与数字：isalnum
						flag=0;
			}while(!flag);
			for(j=0;j<i && flag;j++)       //用户id查重
			{
				if((strcmp(user[j].id,uid))==0)
				{
					printf("该用户已存在,请重新输入：");
					flag=0;
				}
			}
		}while(!flag);

		do                                 //录入第一辆车
		{
			flag=1;
			do                             //判断车牌是否合理:不为0；字母与数字组合
			{
				flag=1;
				printf("请输入由字母与数字组成的车牌号：");
				scanf("%s",&cid1);	
				if((strcmp(cid1,"0"))==0)
				{
					printf("用户至少有一辆车!");
					flag=0;
				};
				for(k=0;cid1[k]!='\0' && flag;k++)
				{
					if(isalnum(cid1[k])==0)
						flag=0;
				}
			}while(!flag);
			for(j=0;j<i && flag;j++)       //车牌查重
			{
				if((strcmp(user[j].carid1,cid1))==0 || (strcmp(user[j].carid2,cid1))==0)
				{
					printf("该车已存在！");
			        flag=0;
				}
			}
		}while(!flag);

		do                                 //录入第二辆车,操作同一
		{
			flag=1;
			do 
			{
				flag=1;
				printf("若有第二辆车，请输入由字母与数字组成的车牌号,若没有请输入0：");
				scanf("%s",&cid2);
				for(k=0;cid2[k]!='\0' && flag;k++)
					if(isalnum(cid2[k])==0)
						flag=0;

				if(strcmp(cid1,cid2)==0)
				{
					printf("该车牌号已经输入过了！请重新输入： ");
					flag=0;
				};
			}while(!flag);

			if(strcmp(cid2,"0")!=0)
				for(j=0;j<i;j++)
					if((strcmp(user[j].carid2,cid2))==0 || (strcmp(user[j].carid1,cid2))==0)
					{
						printf("该车已存在!");
						flag=0;
						break;
					}
		}while(!flag);

		if(flag)                          //录入有效期并写入文件
		{
			strcpy(user[i].id,uid);
			strcpy(user[i].carid1,cid1);
			strcpy(user[i].carid2,cid2);

			do                            //有效期录入
			{
				printf("卡类型(year/time):");
				scanf("%s",tcard);

				if((strcmp(tcard,"year"))==0)
				{
					do  
					{
						flag=1;
						printf("请输入有效使用期:");
						scanf("%s",&va);
						if(strlen(va)!=6)
							flag=0;
						for(k=0;va[k]!='\0' && flag;k++)
							if(isdigit(va[k])==0)
								flag=0;
						if(flag)
							v=atol(va);
						if(v<=time)        //有效期与今日时间对比
							flag=0;
					}while(!flag);
					user[i].valid=v;
					strcpy(user[i].card,"year");
					break;
				}
				else if((strcmp(tcard,"time"))==0)
				{
					do
					{
						flag=1;
						printf("请输入有效次数(一次性输入最大使用次数为30):");
						scanf("%s",&va);
						for(k=0;va[k]!='\0' && flag;k++)   //先判断输入是否为数字
							if(isdigit(va[k])==0)
								flag=0;
						
							if(flag)
								v=atoi(va);
								if(v>30 || v<=0)
									flag=0;
					}while(!flag);
					user[i].valid=v;
					strcpy(user[i].card,"time");
					break;
				}
			}while(flag);

			strcpy(user[i].car1in,"车辆未进入");
			strcpy(user[i].car2in,"车辆未进入");
			if((strcmp(user[i].carid2,"0"))==0)
				strcpy(user[i].car2in,"无车辆");
			printf("\n");
		};
	};
	printf("OK!");
	save(m);
};

void add()    //添加信息
{ //add函数的所有添加，验证，容错功能都与creat相同
	FILE* fp;
	int n,i,j,flag,k,count=0;
	int m=load();
	char uid[7],ucid1[7],ucid2[7],t[7],va[7],tcard[5];
	long time,v;

	if (isFull()){printf("用户已满，不能添加！");return;} // 判断是否达到容量上限

	do                         //日期输入
	{
		flag=1;
		printf("请输入今日日期(例190212): ");
		scanf("%s",&t);
		if(strlen(t)!=6)
			flag=0;
		for(k=0;t[k]!='\0' && flag;k++)
			if(isdigit(t[k])==0)
				flag=0;
	}while(!flag);
	time=atol(t);

	fp=fopen("car.txt","a");
	do{
		printf("现在已有%d个用户，最多还可添加%d个用户，要添加几个？",m,1000-m);
		scanf("%d",&n);
	}while(n+m>1000);
	for(i=m;i<(m+n);i++)
	{
		do											//录入用户id并检查是否合理
		{
			do
			{
				flag=1;
				printf("请输入由字母与数字组成的用户ID：");
				scanf("%s",&uid);
				if(strlen(uid)!=6)
					flag=0;
				for(k=0;uid[k]!='\0' && flag;k++)
					if(isalnum(uid[k])==0)
						flag=0;
			}while(!flag);
		    for(j=0;j<i && flag;j++)
			{
				if((strcmp(user[j].id,uid))==0)
				{
					printf("该用户已存在!");
			        flag=0;
				}
			}
		}while(!flag);

		do									// 录入第一辆车
		{
			flag=1;
			do
			{
				flag=1;
				printf("输入由字母与数字组成的车牌号：");
				scanf("%s",&ucid1);	
				if(strcmp(ucid1,"0")==0)
				{
					flag=0;
					printf("用户至少有一辆车!");
				}
				for(k=0;ucid1[k]!='\0' && flag;k++)
					if(isalnum(ucid1[k])==0)
						flag=0;
			}while(!flag);

			for(j=0;j<i && flag;j++)
			{
				if((strcmp(user[j].carid1,ucid1))==0 || (strcmp(user[j].carid2,ucid1))==0)
				{
					printf("该车已存在!");
			        flag=0;
				}
			}
		}while(!flag);

		do                                  //录入第二辆车
		{
			flag=1;
			do
			{
				flag=1;
				printf("若有第二辆车，请输入由字母与数字组成的车牌号,若没有请输入0：");
				scanf("%s",&ucid2);	
				for(k=0;ucid2[k]!='\0' && flag;k++)
					if(isalnum(ucid2[k])==0)
						flag=0;
			
				if(strcmp(ucid1,ucid2)==0)
				{
					printf("该车牌号刚才输入过了! ");
					flag=0;
				};
			}while(!flag);

			if((strcmp(ucid2,"0"))!=0)
				for(j=0;j<i;j++)
				{
					if((strcmp(user[j].carid2,ucid2))==0 || (strcmp(user[j].carid1,ucid2))==0)
					{
						printf("该车已存在！");
						flag=0;
						break;
					}
				}
		}while(!flag);

		if(flag)
		{
			strcpy(user[i].id,uid);
			strcpy(user[i].carid1,ucid1);
			strcpy(user[i].carid2,ucid2);
			do
			{
				printf("卡类型(year/time):");    //输入卡类型
				scanf("%s",tcard);

				if((strcmp(tcard,"year"))==0)  //年卡输入有效期
				{
					do  
					{
						flag=1;
						printf("请输入有效使用期:");
						scanf("%s",&va);
						if(strlen(va)!=6)
							flag=0;
						for(k=0;va[k]!='\0' && flag;k++)
							if(isdigit(va[k])==0)
								flag=0;
						if(flag)
							v=atol(va);
						if(v<=time)        //有效期与今日时间对比
							flag=0;
					}while(!flag);
					user[i].valid=v;
					strcpy(user[i].card,"year");
					break;
				}
				else if((strcmp(tcard,"time"))==0)
				{
					do  //次卡输入有效次数
					{
						flag=1;
						printf("请输入有效次数(一次性输入最大使用次数为30):");
						scanf("%s",&va);
						for(k=0;va[k]!='\0' && flag;k++)
							if(isdigit(va[k])==0)
								flag=0;
							if(flag)
								v=atoi(va);
								if(v>30 || v<=0)
									flag=0;
					}while(!flag);
					user[i].valid=v;
					strcpy(user[i].card,"time");
					break;
				}
			}while(flag);

			strcpy(user[i].car1in,"车辆未进入");
			strcpy(user[i].car2in,"车辆未进入");
			if((strcmp(user[i].carid2,"0"))==0)
				strcpy(user[i].car2in,"无车辆");
			printf("\n");
		};
		count+=1;
	};
	printf("OK!\n");
	m=m+count;
	save(m);   //保存
	fclose(fp);
};

void modify()  //修改信息函数
{ 
	int q,f,loc=-1,i,k,j,ss,x; //loc代表用户序号
	int m=load();
	char id[6],cid[6];
	do
	{
		f=1;
		printf("按用户id修改请选择1，按车牌修改请选择2,放弃修改选择3：");
		scanf("%d",&q);
		if(q>=1&&q<=3)
		{
			f=1;
			break;
		}
		else
		{
			f=0;
			printf("无效的选择!\n");
		}
	}while(!f); 

	switch(q)
	{
	case 1:
		printf("请输入要修改的用户id:");
		scanf("%s",id);
		for(i=0;i<m;i++)
		{
			if(strcmp(user[i].id,id)==0)     // 先检查是否存在该用户id
			{
				loc=i;
			}
		}
		break;
	case 2:
		printf("请输入要修改信息的用户的车牌号:");
		scanf("%s",&cid);
		for(i=0;i<m;i++)
		{
			if(strcmp(user[i].carid1,cid)==0 || strcmp(user[i].carid2,cid)==0)
			{
				loc=i;
			}
		}		
	break;
	default:break;
	}

	int flag=0,c;
	char card[4],t[7],c1id[6],c2id[6],va[6];
	long v=0,td;

	if(loc==-1){
		printf("该用户不存在！");
	}
	else{  // 输出该用户信息，决定是否要修改
		int n;
		printf("该用户信息为：\n");
		printf("\t%s,\t%s,\t%d,\t%s,\t%s,\t%s,\t%s\n",user[loc].id,user[loc].card,user[loc].valid,user[loc].carid1,user[loc].carid2,user[loc].car1in,user[loc].car2in);
		printf("确定修改该用户请选择1，放弃修改请选择0：");
		scanf("%d",&n);
		if(n==1)
		{
			printf("\n1.id 2.卡类型 3.有效日期/有效时间 4.车牌号\n");
			do
			{
				flag=1;
				printf("请输入您要修改的序号：");
				scanf("%d",&c);
				if(c>4 || c<1)
				{
					flag=0;
					printf("无效的选择，请重新选择：");
				}
			}while(!flag);
		}
	}

	if(!flag){return;}

	do
	{
		switch(c)
		{
		case 1:
			do
			{
				flag=1;
				do
				{
					printf("请输入由数字与字母组成的修改后的用户ID：");
					scanf("%s",&id);
					flag=1;
					if(strlen(id)!=6){flag=0;}
					for(k=0;id[k]!='\0' && flag;k++)
						if(isalnum(id[k])==0)
							flag=0;
				}while(!flag);
				for(j=0;j<m;j++)  // 用户id查重
				{
					if((strcmp(user[j].id,id))==0) 
					{
						printf("该id已存在,请重新输入：");
						flag=0;
						break;
					}
				}
			}while(!flag);
			strcpy(user[loc].id,id);
			break;

		case 2:
			printf("请输入修改后的卡类型(year/time)：");
			scanf("%s",card);	
			if((strcmp(card,"time"))==0)
			{
				strcpy(user[loc].card,card);
				do
				{
					flag=1;
					printf("请输入该卡有效次数：");
					scanf("%s",&va);
					for(k=0;va[k]!='\0' && flag;k++) //判断输入是否为数字，并且大于0，小于30
						if(isdigit(va[k])==0)
							flag=0;
					if(flag)
						v=atoi(va);
						if(v>30 || v<=0)
							flag=0;
				}while(!flag);
				user[loc].valid=v;
			}	
			else if((strcmp(card,"year"))==0)
			{
				strcpy(user[loc].card,card);
				do
				{
					flag=1;
					printf("请输入今日日期(例190212): ");
					scanf("%s",&t);
					if(strlen(t)!=6)   // 判断日期是否为6位，并且是数字
						flag=0;
					for(k=0;t[k]!='\0' && flag;k++)
						if(isdigit(t[k])==0)
							flag=0;
				}while(!flag);
				td=atol(t);	
				do
				{
					flag=1;
					printf("请输入有效使用期:");
					scanf("%s",&va);
					if(strlen(va)!=6)
						flag=0;
					for(k=0;va[k]!='\0' && flag;k++)  // 有效期必须大于今日日期
						if(isdigit(va[k])==0)
							flag=0;
					if(flag)
						v=atol(va);
						if(v<=td)
							flag=0;
				}while(!flag);
				user[loc].valid=v;
			};
			break;

		case 3:
			if((strcmp(user[loc].card,"time"))==0)
			{
				do   //修改有效次数
				{
					flag=1;
					printf("请输入该卡有效次数：");
					scanf("%s",&va);
					for(k=0;va[k]!='\0' && flag;k++) 
						if(isdigit(va[k])==0)
							flag=0;
					if(flag)
						v=atoi(va);
						if(v>30 || v<=0)
							flag=0;		
				}while(!flag);
				user[loc].valid=v;
			}
			else if((strcmp(user[loc].card,"year"))==0)
			{
				do   //修改有效日期
				{
					flag=1;
					printf("请输入今日日期(例190212): ");
					scanf("%s",&t);
					if(strlen(t)!=6)
						flag=0;
					for(k=0;t[k]!='\0' && flag;k++)
						if(isdigit(t[k])==0)
							flag=0;
				}while(!flag);
				td=atol(t);	
				do
				{
					flag=1;
					printf("请输入有效使用期:");
					scanf("%s",&va);
					if(strlen(va)!=6)
						flag=0;
					for(k=0;va[k]!='\0' && flag;k++)
						if(isdigit(va[k])==0)
							flag=0;
					if(flag)
						v=atol(va);
						if(v<=td)
							flag=0;
				}while(!flag);
				user[loc].valid=v;		
			};
			break;

		case 4:
			if((strcmp(user[loc].carid1,"0")!=0) && (strcmp(user[loc].carid2 ,"0")!=0)) // 当用户有2辆车
			{
				printf("该用户有2辆车，修改车辆1请按1，修改车辆2请按2，都要修改请按3，放弃修改请按4：");
				scanf("%d",&ss);
				if(ss==1)       //修改车1
				{
					do
					{
						do
						{
							flag=1;
							printf("输入由字母与数字组成的修改后的车牌号：");
							scanf("%s",&c1id);	
							for(k=0;c1id[k]!='\0' && flag;k++)   // 判断车牌号是否合理
								if(isalnum(c1id[k])==0)
									flag=0;
						}while(!flag);
						if(strcmp(c1id,"0")!=0)   // 验证车牌号是否存在
						{
							for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c1id)==0) || (strcmp(user[j].carid2,c1id)==0))
								{
									printf("该车牌号已存在，");
									flag=0;
									break;
								}
							};
						}
					}while(!flag);	
					if(strcmp(c1id,"0")==0)
					{
						strcpy(user[loc].carid1,user[loc].carid2);
					    strcpy(user[loc].carid2,"0");
						strcpy(user[loc].car2in,"无车辆");
					}
					else
						strcpy(user[loc].carid1,c1id);
						printf("修改成功！");
				}
				else if(ss==2)  // 修改车2
				{
					do
					{
						do
						{
							flag=1;
							printf("请输入由字母与数字组成的修改后车辆2的车牌号：");
							scanf("%s",c2id);
							for(k=0;c2id[k]!='\0' && flag;k++)
								if(isalnum(c2id[k])==0)
									flag=0;
						}while(!flag);
						if(strcmp(c2id,"0")!=0)
						{
							for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c2id)==0) || (strcmp(user[j].carid2,c2id)==0))
								{
									printf("该车牌号已存在，");
									flag=0;
									break;
								}
							};
						};
					}while(!flag);
					if(strcmp(c2id,"0")==0)
					{
						strcpy(user[loc].carid2,c2id);
						strcpy(user[loc].car2in,"无车辆");
					};
					strcpy(user[loc].carid2,c2id);
					printf("修改成功！");
				}
				else if(ss==3)  //全修改
				{
					do
					{
						do
						{
							flag=1;
							printf("输入由字母与数字组成的修改后的车牌号1：");
							scanf("%s",&c1id);	
							for(k=0;c1id[k]!='\0' && flag;k++)
								if(isalnum(c1id[k])==0)
									flag=0;
							if(strcmp(c1id,"0")==0)
								flag=0;
						}while(!flag);
						if(strcmp(c1id,"0")!=0)
						{
							for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c1id)==0) || (strcmp(user[j].carid2,c1id)==0))
								{
									printf("该车牌号已存在，");
									flag=0;
									break;
								}
							};
						};
					}while(!flag);				
					strcpy(user[loc].carid1,c1id);
					do
					{
						do
						{
							flag=1;
							printf("请输入由字母与数字组成的修改后车辆2的车牌号：");
							scanf("%s",c2id);
							for(k=0;c2id[k]!='\0' && flag;k++)
								if(isalnum(c2id[k])==0)
									flag=0;
						}while(!flag);

						if(strcmp(c2id,"0")!=0)
						{
							for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c1id)==0) || (strcmp(user[j].carid2,c1id)==0))
								{
									printf("该车牌号已存在，");
									flag=0;
									break;
								}
							}
						}
					}while(!flag);
					if(strcmp(c2id,"0")==0)
					{
						strcpy(user[loc].carid2,c2id);
						strcpy(user[loc].car2in,"无车辆");
					};
					strcpy(user[loc].carid2,c2id);
					printf("修改成功！");
				}
				//else
				//	break;
			}

			else if((strcmp(user[loc].carid1 ,"0")!=0) && (strcmp(user[loc].carid2,"0")==0))   // 若用户仅拥有一辆车
			{
				printf("该用户有一台车，确认修改请按1，添加车辆请按2，取消修改请按0： ");
				scanf("%d",&ss);
				if(ss==1)  // 修改车辆1
				{
					do
					{
						do
						{
							flag=1;
							printf("输入由字母与数字组成的修改后的车牌号：");
							scanf("%s",&c1id);	
							for(k=0;c1id[k]!='\0' && flag;k++)
								if(isalnum(c1id[k])==0)
									flag=0;
							if(strcmp(c1id,"0")==0)
								flag=0;
						}while(!flag);
						for(j=0;j<m;j++)
						{
							if((strcmp(user[j].carid1,c1id)==0) || (strcmp(user[j].carid2,c1id)==0))
							{
								printf("该车牌号已存在，");
								flag=0;
								break;
							}
						}
					}while(!flag);							
					strcpy(user[loc].carid1,c1id);
					printf("修改成功！");
				}
				else if(ss==2)  //添加车辆2
				{
					do
					{
						flag=1;
						do
						{
							printf("输入由字母与数字组成的车牌号：");
							scanf("%s",&c2id);
							for(k=0;c2id[k]!='\0' && flag;k++)
								if(isalnum(c2id[k])==0)
									flag=0;
						}while(!flag);
						for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c2id)==0) || (strcmp(user[j].carid2,c2id)==0))
								{
									printf("该车牌号已存在，");
									flag=0;
									break;
								}
							}
					}while(!flag);
					strcpy(user[loc].carid2,c2id);
					strcpy(user[loc].car2in,"车辆未进入");
					printf("修改成功！");
				}
			}
			break;
		}
		printf("\n");
		printf("确定保存修改的信息（1/0）,如选0，则重新修改？");
		scanf("%d",&flag);
	}while(!flag);

	save(m);
	display();
	printf("\n修改结束请按0，继续修改请按1："); //如果继续修改，清空桌面，重新运行一次
	scanf("%d",&x);
	switch(x)
	{
	case 0:
		system("cls");
		break;
	case 1:
		modify();
		break;
	default:system("cls");break;
	}
}

bool isleap(int year){ // 判断是否为闰年
	 return (year%4==0 && year%100!=0 || year%400==0);
}

//计算停车费用
long fee(long Time_in,long Hour_in,long Time_out,long Hour_out)
{
	//导入进出时间后，将其分解为年，月，日，时，分
    int y1,m1,d1,h1,s1;
    int y2,m2,d2,h2,s2;
    int day=0;
    long hour,p;
    y1=Time_in/10000,m1=Time_in%10000/100,d1=Time_in%100,h1=Hour_in/100,s1=Hour_in%100;
    y2=Time_out/10000,m2=Time_out%10000/100,d2=Time_out%100,h2=Hour_out/100,s2=Hour_out%100;
    while (y1<y2 || m1<m2 || d1<d2){  //计算进出时间相差多少天
        d1++;
        if (d1==month[m1][isleap(y1)]+1){
            m1++;
            d1=1;
        }
        if(m1==13){
            y1++;
            m1=1;
        }
        day++;
    };
    hour=h2-h1;   // 计算小时差
    if(s2-s1>0)
        hour++;
	hour=hour+24*day;
    p=5+3*(hour-1);  // 计算费用
    return p;
};

void carin(){
	FILE* fp;
	int m=load();
	int i,n,j,k=0,flag,tag,loc=-1,f; //tag代表车1还是车2
	bool ft=true;
	char car[6],time[12],tim[6];
	char sto[7];
	long v;
	do
	{
		flag=1;
		printf("请输入车牌号：");     // 确定车牌号
		scanf("%s",car);
		for(i=0;car[i]!='\0' && flag;i++)
		{
			if(isalnum(car[i])==0)
				flag=0;
		}
	}while(!flag);
	strcpy(sto,car);

	for(i=0;i<m;i++)										//检索该车牌的车主，确定进入的车辆是车1还是车2
	{
		if(strcmp(user[i].carid1,sto)==0)
		{
			tag=1;
			loc=i;
			break;
		}
		else if(strcmp(user[i].carid2,sto)==0)
		{
			tag=2;
			loc=i;
			break;
		}
	}

	do
	{
		flag=1;
		printf("请输入入场时间(省略':'精确到分):");  // 输入进入时间
		scanf("%s",time);
		if(strlen(time)!=12)
			flag=0;
		for(i=0;time[i]!='\0' && flag;i++)
		{
			if(isdigit(time[i])==0)
				flag=0;
		}
	}while(!flag);

	if(loc!=-1){ //loc为该用户在数组中的位置
		if(strcmp(user[loc].card,"year")==0)
		{
			strncpy(tim,time+2,6);
			v=atol(tim);
			if(v>=user[loc].valid){ft=false;} 
		};

		if(ft){ // ft是true代表会员没到期
			if(tag==1) //tag代表等待进入的是车主的几号车
			{
				if(strcmp(user[loc].car2in,"vip")==0)
					strcpy(user[loc].car1in,time);
				else if(strcmp(user[loc].car2in,"无车辆")==0 || strcmp(user[loc].car2in,"车辆未进入")==0)
					strcpy(user[loc].car1in,"vip");
			}
			else if(tag==2)
			{
				if(strcmp(user[loc].car1in,"vip")==0)
					strcpy(user[loc].car2in,time);
				else if(strcmp(user[loc].car1in,"无车辆")==0 || strcmp(user[loc].car1in,"车辆未进入")==0)
					strcpy(user[loc].car2in,"vip");
			};
			save(m);
			printf("请进入！");
		}
		else
		{
			for(j=loc;j<m;j++)    //删除过期用户
			{
				strcpy(user[j].id,user[j+1].id);
				user[j].valid=user[j+1].valid;
				strcpy(user[j].card,user[j+1].card);
				strcpy(user[j].carid1,user[j+1].carid1);
				strcpy(user[j].carid2,user[j+1].carid2);
				strcpy(user[j].car1in,user[j+1].car1in);
				strcpy(user[j].car2in,user[j+1].car2in);
			};
			m=m-1;
			save(m);
			loc=-1;
			printf("您的用户卡因逾期未续费，已被注销。请办理临时卡进入.\n");			
		}
	}
	if(!isFull() && loc==-1){
		printf("办理临时卡请选择1，离开请选择0： ");
		scanf("%d",&n);
		if(n==1)
		{  //临时卡只设置车牌号与进入时间，其余全为默认值
			strcpy(user[m].id,"temp");  
			strcpy(user[m].card,"temp");
			strcpy(user[m].carid2,"0");
			strcpy(user[m].car1in,time);
			strcpy(user[m].car2in,"无车辆");
			strcpy(user[m].carid1,sto);
			m=m+1;
			save(m);
			printf("\n添加成功！\n");
			printf("您可以进入！");
		}
		else
			printf("再见！");
	}
	else if(isFull()){printf("用户已满！不能创建临时卡。");}
};

void carout(){
	FILE* fp;
    int m=load();
    int i,j,flag,tag=0,hoursout,hoursin;
    char car[7],time[13],timo[7],timi[7],hourout[5],hourin[5];
    long vo,vi,pay;
    do
	{
        flag=1;
        printf("请输入车牌号：");  // 输入离开的车牌号
        scanf("%s",car);
        for(i=0;car[i]!='\0' && flag;i++)
        {
            if(isalnum(car[i])==0)
                flag=0;
        }
    }while (!flag);

	do
	{
		flag=1;
		printf("请输入出场时间(省略':'精确到分):");		//读入正确时间
		scanf("%s",time);
		if(strlen(time)!=12)
			flag=0;
		for(i=0;time[i]!='\0' && flag;i++)
		{
			if(isdigit(time[i])==0)
				flag=0;
		}
	}while(!flag);

	for(i=0;i<m;i++)										//检索该车牌的车主，并确定是车1还是车2
	{
        if(strcmp(user[i].carid1,car)==0)
        {
            tag=1;
            break;
        }
        else if(strcmp(user[i].carid2,car)==0)
        {
            tag=2;
            break;
        }
    }
	if(!tag)
		flag=0;

	if(flag)
	{
		strncpy(timo,time+2,6);
		strncpy(hourout,time+8,4);
		vo=atol(timo);
		hoursout=atoi(hourout);

		if(strcmp(user[i].card,"year")==0) 
		{// 年卡用户，如果出场时间未到有效截止期。对于vip状态的车，直接设置为车辆未进入；			
			if(tag==1)   // tag代表等待离开的是车主的几号车
			{
				if(strcmp(user[i].car1in,"vip")==0) 
				{
					if(vo<user[i].valid)
					{
						strcpy(user[i].car1in,"车辆未进入");
						printf("祝您一路顺风！");
					}

					else         
					{ // 如果超过截止期，用出场日期到截止期的time差计费，如果另一辆车未进入，直接删除该用户，否则暂时保留

						pay=fee(user[i].valid,0,vo,hoursout);
						if(strcmp(user[i].car2in,"无车辆")==0 || strcmp(user[i].car2in,"车辆未进场")==0)
						{	for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("由于您的用户卡已到期，您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
						else
						{	
							strcpy(user[i].car1in,"车辆未进入");
							printf("由于您的用户卡已到期，您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
					};
				}
				else if(strcmp(user[i].car1in,"vip")!=0)  // 对于非vip状态的用户，直接利用 time差 计费
				{
					strncpy(timi,user[i].car1in+2,6);
					strncpy(hourin,user[i].car1in+8,4);
					vi=atol(timi);
					hoursin=atoi(hourin);
					pay=fee(vi,hoursin,vo,hoursout);

					if(vo<user[i].valid)
					{
						strcpy(user[i].car1in,"车辆未进入");
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
					else   
					{
						if(strcmp(user[i].car2in,"无车辆")==0 || strcmp(user[i].car2in,"车辆未进场")==0)
						{	for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
						else
						{	strcpy(user[i].car1in,"车辆未进入");
							printf("您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
					}
				}
			}

			else if(tag==2)
			{
				if(strcmp(user[i].car2in,"vip")==0)
				{
					if(vo<user[i].valid)
					{
						strcpy(user[i].car2in,"车辆未进入");
						printf("祝您一路顺风！");
					}
					else
					{
						pay=fee(user[i].valid,0,vo,hoursout);
						if(strcmp(user[i].car1in,"无车辆")==0 || strcmp(user[i].car1in,"车辆未进场")==0)
						{	
							for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("由于您的用户卡已到期，您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
						else
						{
							strcpy(user[i].car2in,"车辆未进入");
							printf("由于您的用户卡已到期，您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
					};
				}
				else if(strcmp(user[i].car2in,"vip")!=0)
				{
					strncpy(timi,user[i].car2in+2,6);
					strncpy(hourin,user[i].car2in+8,4);
					vi=atol(timi);
					hoursin=atoi(hourin);
					pay=fee(vi,hoursin,vo,hoursout);

					if(vo<user[i].valid)
					{
						strcpy(user[i].car2in,"车辆未进入");
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
					else
					{
						if(strcmp(user[i].car1in,"无车辆")==0 || strcmp(user[i].car1in,"车辆未进场")==0)
						{	
							for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
						else
						{	strcpy(user[i].car2in,"车辆未进入");
							printf("您需要缴纳的费用为：%ld\n",pay);
							printf("祝您一路顺风！");
						}
					}
				}
			}
		}

		else if(strcmp(user[i].card,"time")==0)  // 次卡未用完，操作同年卡
		{
			if(tag==1)
			{
				if(strcmp(user[i].car1in,"vip")==0)
				{
					if(user[i].valid==1)
					{
						if(strcmp(user[i].car2in,"无车辆")==0 || strcmp(user[i].car2in,"车辆未进场")==0)
						{
							for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("祝您一路顺风！");
						}
						else
						{
							user[i].valid=user[i].valid-1;
							strcpy(user[i].car1in,"车辆未进入");	
							printf("祝您一路顺风！");
						}
					}

					else
					{
						user[i].valid=user[i].valid-1;
						strcpy(user[i].car1in,"车辆未进入");
						printf("祝您一路顺风！");
					}
				}

				else if(strcmp(user[i].car1in,"vip")!=0)
				{
					strncpy(timi,user[i].car1in+2,6);
					strncpy(hourin,user[i].car1in+8,4);
					vi=atol(timi);
					hoursin=atoi(hourin);
					pay=fee(vi,hoursin,vo,hoursout);
					if(user[i].valid==0)
					{
						for(j=i;j<m;j++)    //删除过期用户
						{
							strcpy(user[j].id,user[j+1].id);
							user[j].valid=user[j+1].valid;
							strcpy(user[j].card,user[j+1].card);
							strcpy(user[j].carid1,user[j+1].carid1);
							strcpy(user[j].carid2,user[j+1].carid2);
							strcpy(user[j].car1in,user[j+1].car1in);
							strcpy(user[j].car2in,user[j+1].car2in);
						};
						m=m-1;
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
					else
					{
						strcpy(user[i].car1in,"车辆未进入");
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
				}
			}

			else if(tag==2)
			{
				if(strcmp(user[i].car2in,"vip")==0)
				{
					if(user[i].valid==1)
					{
						if(strcmp(user[i].car1in,"无车辆")==0 || strcmp(user[i].car1in,"车辆未进场")==0)
						{
							for(j=i;j<m;j++)    //删除过期用户
							{
								strcpy(user[j].id,user[j+1].id);
								user[j].valid=user[j+1].valid;
								strcpy(user[j].card,user[j+1].card);
								strcpy(user[j].carid1,user[j+1].carid1);
								strcpy(user[j].carid2,user[j+1].carid2);
								strcpy(user[j].car1in,user[j+1].car1in);
								strcpy(user[j].car2in,user[j+1].car2in);
							};
							m=m-1;
							printf("祝您一路顺风！");
						}
						else
						{
							user[i].valid=user[i].valid-1;
							strcpy(user[i].car2in,"车辆未进入");
							printf("祝您一路顺风！");
						}
					}

					else
					{
						user[i].valid=user[i].valid-1;
						strcpy(user[i].car2in,"车辆未进入");
						printf("祝您一路顺风！");
					}
				}
			
				else if(strcmp(user[i].car2in,"vip")!=0)
				{
					strncpy(timi,user[i].car2in+2,6);
					strncpy(hourin,user[i].car2in+8,4);
					vi=atol(timi);
					hoursin=atoi(hourin);
					pay=fee(vi,hoursin,vo,hoursout);

					if(user[i].valid==0)
					{
						for(j=i;j<m;j++)    //删除过期用户
						{
							strcpy(user[j].id,user[j+1].id);
							user[j].valid=user[j+1].valid;
							strcpy(user[j].card,user[j+1].card);
							strcpy(user[j].carid1,user[j+1].carid1);
							strcpy(user[j].carid2,user[j+1].carid2);
							strcpy(user[j].car1in,user[j+1].car1in);
							strcpy(user[j].car2in,user[j+1].car2in);
						};
						m=m-1;
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
					else
					{
						strcpy(user[i].car2in,"车辆未进入");
						printf("您需要缴纳的费用为：%ld\n",pay);
						printf("祝您一路顺风！");
					}
				}
			}
		}
		else if(strcmp(user[i].card,"temp")==0)
		{
			strncpy(timi,user[i].car1in+2,6);
			strncpy(hourin,user[i].car1in+8,4);
			vi=atol(timi);
			hoursin=atoi(hourin);
			pay=fee(vi,hoursin,vo,hoursout);

			for(j=i;j<m;j++)    //删除过期用户
			{
				strcpy(user[j].id,user[j+1].id);
				user[j].valid=user[j+1].valid;
				strcpy(user[j].card,user[j+1].card);
				strcpy(user[j].carid1,user[j+1].carid1);
				strcpy(user[j].carid2,user[j+1].carid2);
				strcpy(user[j].car1in,user[j+1].car1in);
				strcpy(user[j].car2in,user[j+1].car2in);
			};
			m=m-1;
			printf("您需要缴纳的费用为：%ld\n",pay);
			printf("祝您一路顺风！");
		}
		save(m);
	}
	else
		printf("未查找到该车辆！");
};

bool cmp_id(USER a,USER b){return strcmp(a.id,b.id)<0;}
bool cmp_card(USER a,USER b){return strcmp(a.card,b.card)<0;}
bool cmp_v(USER a,USER b){return a.valid<b.valid;}
bool cmp_car(USER a,USER b){return strcmp(a.carid1,b.carid1)<0;}
bool cmp_in(USER a,USER b){return strcmp(a.car1in,b.car1in)<0;}

void sort(){
	FILE* fp;
	int m=load();
	int i,j,k,s1,s2,flag;
	do
	{
		printf("1.用户ID 2.卡类型 3.有效日期/有效次数 4.车牌号 5.入场时间 6.放弃排序\n");
	    printf("您要对那种字段排序？请输入其对应的代号：");
	    scanf("%d",&s1);
	    if(s1<1 || s1>6)
		{
			printf("输入不合法，请重新输入：");
			scanf("%d",&s1);
			flag=0;
			break;
		}
		else
		{
			flag=1;
			break;
		}
	}while(!flag);

	switch(s1)
	{
	case 1: // 按id排序
		std::sort(user,user+m,cmp_id);
		break;
	case 2: //按卡类型排序
		std::sort(user,user+m,cmp_card);
		break;
	case 3: //按有效期排序
		std::sort(user,user+m,cmp_v);
		break;
	case 4: // 按车牌号排序
		std::sort(user,user+m,cmp_car);
		break;
	case 5: // 按入场时间排序
		std::sort(user,user+m,cmp_in);
		break;
	default:return;
	}
	printf("降序排列选择1，升序排列选择2：");
	scanf("%d",&s2);
	if(s2==1)
	{
		for(i=m-1;i>=0;i--){
			printf("\t%s,\t%s,\t%d,\t%s,\t%s,\t%s,\t%s\n",user[i].id,user[i].card,user[i].valid,user[i].carid1,user[i].carid2,user[i].car1in,user[i].car2in);
		}
	}
	else if(s2==2)
	{
		for(i=0;i<m;i++)
			printf("\t%s,\t%s,\t%d,\t%s,\t%s,\t%s,\t%s\n",user[i].id,user[i].card,user[i].valid,user[i].carid1,user[i].carid2,user[i].car1in,user[i].car2in);
	};
};


