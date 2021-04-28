#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include <algorithm>
#define MAX 1000
//**************************************** paramster
struct USER   // �����û��ṹ��
{
	char id[7];  // �û����
	char card[5]; // ������
	long valid;  //��Ч��/����
	char carid1[7]; //���ƺ�1
	char carid2[7]; //���ƺ�2
	char car1in[13]; //��1�볡ʱ��
	char car2in[13]; //��2�볡ʱ��
}user[MAX];

//�����·����飬���ڼ�������
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
	printf("��������Ҫ���еĲ�����");
	scanf("%d",&select);
	printf("\n");                          
	do										//ָ��ѡ��
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
	while(flag)                             //ָ��ִ��
	{ 
		switch(select)
		{
		case 1:
			printf("������¼�ᵼ��ԭ�м�¼ȫ����գ�ȷ������������(1/0)��");
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
			exit(0);                        //exit(0):�����������в��˳�                     
			break;
		default:break;
		};
		printf("\n");
		printf("�Ƿ��������?(1/0):");
		scanf("%d",&e);
		if(e==1)
		{
			flag=1;
			system("cls");
			showmenu();
			printf("��������Ҫ���еĲ����� ");
			scanf("%d",&select);
			printf("\n");
		}
		else
			flag=0;
	};
	printf("*****��л����ʹ�á�*****\n");
	printf("\n");
	return 0;
};
//**************************************** functions 

void showmenu()           //ָ��˵�
{
	printf( "====== У԰��������ϵͳ ======\n" );
	printf("======\t1��������¼\t======\n");
	printf("======\t2����Ӽ�¼\t======\n");
	printf("======\t3�������¼\t======\n");
	printf ("======\t4����������\t======\n");
	printf ("======\t5�������뿪\t======\n");
	printf("======\t6���޸ļ�¼\t======\n");
	printf ("======\t7��������ʾ\t======\n");
	printf ("======\t8���뿪ϵͳ\t======\n");
	printf ("==============================\n") ;
	printf("��Ҫ�˳�ϵͳ���뱣����Ϣ��\n");
};

void save(int m){          //������Ϣ
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

int load(){                //������Ϣ
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

bool isFull(){ // �ж��Ƿ�����
    int m = load();
    if (m == MAX) {return true;}
    return false;
}

void display(){            //չʾ��Ϣ
	int i;
	int m=load();
	for(i=0;i<m;i++)
		printf("\t%s\t,\t%s\t,\t%d\t,\t%s\t,\t%s\t,\t%s\t,\t%s\t\n",user[i].id,user[i].card,user[i].valid,user[i].carid1,user[i].carid2,user[i].car1in,user[i].car2in);
};			

void creat()               //��������Ϣ����
{
	int i,j,m,flag,k;
	char uid[7],cid1[7],cid2[7],today[7],va[7],tcard[5];
	long time,v;
	do										//�ж������Ƿ����Ҫ��λ��������
	{
		flag=1;
		printf("�������������(��190212): ");
		scanf("%s",&today);
		if(strlen(today)!=6)
			flag=0;
		for(k=0;today[k]!='\0' && flag;k++)
			if(isdigit(today[k])==0)           // �ж����ڸ�ʽ�Ƿ�Ϊ���֣�isdigit
				flag=0;
	}while(!flag);
	time=atol(today);                      //��ʱ��ת��Ϊ������ʽ:atol

	do 
	{
       printf("���봴���û���(1000����)��");
       scanf("%d", &m);
    }while(m>1000);

	for(i=0;i<m;i++)
	{
		do                                 //¼���û�id
		{
			flag=1;
			do                             //�ж��û�id�Ƿ����
			{
				flag=1;
				printf("����������ĸ��������ɵ�6λ�û�ID��");
				scanf("%s",&uid);
				if(strlen(uid)!=6)
					flag=0;
				for(k=0;uid[k]!='\0' && flag;k++)
					if(isalnum(uid[k])==0)     //�ж��û�id�Ƿ�Ϊ��ĸ�����֣�isalnum
						flag=0;
			}while(!flag);
			for(j=0;j<i && flag;j++)       //�û�id����
			{
				if((strcmp(user[j].id,uid))==0)
				{
					printf("���û��Ѵ���,���������룺");
					flag=0;
				}
			}
		}while(!flag);

		do                                 //¼���һ����
		{
			flag=1;
			do                             //�жϳ����Ƿ����:��Ϊ0����ĸ���������
			{
				flag=1;
				printf("����������ĸ��������ɵĳ��ƺţ�");
				scanf("%s",&cid1);	
				if((strcmp(cid1,"0"))==0)
				{
					printf("�û�������һ����!");
					flag=0;
				};
				for(k=0;cid1[k]!='\0' && flag;k++)
				{
					if(isalnum(cid1[k])==0)
						flag=0;
				}
			}while(!flag);
			for(j=0;j<i && flag;j++)       //���Ʋ���
			{
				if((strcmp(user[j].carid1,cid1))==0 || (strcmp(user[j].carid2,cid1))==0)
				{
					printf("�ó��Ѵ��ڣ�");
			        flag=0;
				}
			}
		}while(!flag);

		do                                 //¼��ڶ�����,����ͬһ
		{
			flag=1;
			do 
			{
				flag=1;
				printf("���еڶ�����������������ĸ��������ɵĳ��ƺ�,��û��������0��");
				scanf("%s",&cid2);
				for(k=0;cid2[k]!='\0' && flag;k++)
					if(isalnum(cid2[k])==0)
						flag=0;

				if(strcmp(cid1,cid2)==0)
				{
					printf("�ó��ƺ��Ѿ�������ˣ����������룺 ");
					flag=0;
				};
			}while(!flag);

			if(strcmp(cid2,"0")!=0)
				for(j=0;j<i;j++)
					if((strcmp(user[j].carid2,cid2))==0 || (strcmp(user[j].carid1,cid2))==0)
					{
						printf("�ó��Ѵ���!");
						flag=0;
						break;
					}
		}while(!flag);

		if(flag)                          //¼����Ч�ڲ�д���ļ�
		{
			strcpy(user[i].id,uid);
			strcpy(user[i].carid1,cid1);
			strcpy(user[i].carid2,cid2);

			do                            //��Ч��¼��
			{
				printf("������(year/time):");
				scanf("%s",tcard);

				if((strcmp(tcard,"year"))==0)
				{
					do  
					{
						flag=1;
						printf("��������Чʹ����:");
						scanf("%s",&va);
						if(strlen(va)!=6)
							flag=0;
						for(k=0;va[k]!='\0' && flag;k++)
							if(isdigit(va[k])==0)
								flag=0;
						if(flag)
							v=atol(va);
						if(v<=time)        //��Ч�������ʱ��Ա�
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
						printf("��������Ч����(һ�����������ʹ�ô���Ϊ30):");
						scanf("%s",&va);
						for(k=0;va[k]!='\0' && flag;k++)   //���ж������Ƿ�Ϊ����
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

			strcpy(user[i].car1in,"����δ����");
			strcpy(user[i].car2in,"����δ����");
			if((strcmp(user[i].carid2,"0"))==0)
				strcpy(user[i].car2in,"�޳���");
			printf("\n");
		};
	};
	printf("OK!");
	save(m);
};

void add()    //�����Ϣ
{ //add������������ӣ���֤���ݴ��ܶ���creat��ͬ
	FILE* fp;
	int n,i,j,flag,k,count=0;
	int m=load();
	char uid[7],ucid1[7],ucid2[7],t[7],va[7],tcard[5];
	long time,v;

	if (isFull()){printf("�û�������������ӣ�");return;} // �ж��Ƿ�ﵽ��������

	do                         //��������
	{
		flag=1;
		printf("�������������(��190212): ");
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
		printf("��������%d���û�����໹�����%d���û���Ҫ��Ӽ�����",m,1000-m);
		scanf("%d",&n);
	}while(n+m>1000);
	for(i=m;i<(m+n);i++)
	{
		do											//¼���û�id������Ƿ����
		{
			do
			{
				flag=1;
				printf("����������ĸ��������ɵ��û�ID��");
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
					printf("���û��Ѵ���!");
			        flag=0;
				}
			}
		}while(!flag);

		do									// ¼���һ����
		{
			flag=1;
			do
			{
				flag=1;
				printf("��������ĸ��������ɵĳ��ƺţ�");
				scanf("%s",&ucid1);	
				if(strcmp(ucid1,"0")==0)
				{
					flag=0;
					printf("�û�������һ����!");
				}
				for(k=0;ucid1[k]!='\0' && flag;k++)
					if(isalnum(ucid1[k])==0)
						flag=0;
			}while(!flag);

			for(j=0;j<i && flag;j++)
			{
				if((strcmp(user[j].carid1,ucid1))==0 || (strcmp(user[j].carid2,ucid1))==0)
				{
					printf("�ó��Ѵ���!");
			        flag=0;
				}
			}
		}while(!flag);

		do                                  //¼��ڶ�����
		{
			flag=1;
			do
			{
				flag=1;
				printf("���еڶ�����������������ĸ��������ɵĳ��ƺ�,��û��������0��");
				scanf("%s",&ucid2);	
				for(k=0;ucid2[k]!='\0' && flag;k++)
					if(isalnum(ucid2[k])==0)
						flag=0;
			
				if(strcmp(ucid1,ucid2)==0)
				{
					printf("�ó��ƺŸղ��������! ");
					flag=0;
				};
			}while(!flag);

			if((strcmp(ucid2,"0"))!=0)
				for(j=0;j<i;j++)
				{
					if((strcmp(user[j].carid2,ucid2))==0 || (strcmp(user[j].carid1,ucid2))==0)
					{
						printf("�ó��Ѵ��ڣ�");
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
				printf("������(year/time):");    //���뿨����
				scanf("%s",tcard);

				if((strcmp(tcard,"year"))==0)  //�꿨������Ч��
				{
					do  
					{
						flag=1;
						printf("��������Чʹ����:");
						scanf("%s",&va);
						if(strlen(va)!=6)
							flag=0;
						for(k=0;va[k]!='\0' && flag;k++)
							if(isdigit(va[k])==0)
								flag=0;
						if(flag)
							v=atol(va);
						if(v<=time)        //��Ч�������ʱ��Ա�
							flag=0;
					}while(!flag);
					user[i].valid=v;
					strcpy(user[i].card,"year");
					break;
				}
				else if((strcmp(tcard,"time"))==0)
				{
					do  //�ο�������Ч����
					{
						flag=1;
						printf("��������Ч����(һ�����������ʹ�ô���Ϊ30):");
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

			strcpy(user[i].car1in,"����δ����");
			strcpy(user[i].car2in,"����δ����");
			if((strcmp(user[i].carid2,"0"))==0)
				strcpy(user[i].car2in,"�޳���");
			printf("\n");
		};
		count+=1;
	};
	printf("OK!\n");
	m=m+count;
	save(m);   //����
	fclose(fp);
};

void modify()  //�޸���Ϣ����
{ 
	int q,f,loc=-1,i,k,j,ss,x; //loc�����û����
	int m=load();
	char id[6],cid[6];
	do
	{
		f=1;
		printf("���û�id�޸���ѡ��1���������޸���ѡ��2,�����޸�ѡ��3��");
		scanf("%d",&q);
		if(q>=1&&q<=3)
		{
			f=1;
			break;
		}
		else
		{
			f=0;
			printf("��Ч��ѡ��!\n");
		}
	}while(!f); 

	switch(q)
	{
	case 1:
		printf("������Ҫ�޸ĵ��û�id:");
		scanf("%s",id);
		for(i=0;i<m;i++)
		{
			if(strcmp(user[i].id,id)==0)     // �ȼ���Ƿ���ڸ��û�id
			{
				loc=i;
			}
		}
		break;
	case 2:
		printf("������Ҫ�޸���Ϣ���û��ĳ��ƺ�:");
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
		printf("���û������ڣ�");
	}
	else{  // ������û���Ϣ�������Ƿ�Ҫ�޸�
		int n;
		printf("���û���ϢΪ��\n");
		printf("\t%s,\t%s,\t%d,\t%s,\t%s,\t%s,\t%s\n",user[loc].id,user[loc].card,user[loc].valid,user[loc].carid1,user[loc].carid2,user[loc].car1in,user[loc].car2in);
		printf("ȷ���޸ĸ��û���ѡ��1�������޸���ѡ��0��");
		scanf("%d",&n);
		if(n==1)
		{
			printf("\n1.id 2.������ 3.��Ч����/��Чʱ�� 4.���ƺ�\n");
			do
			{
				flag=1;
				printf("��������Ҫ�޸ĵ���ţ�");
				scanf("%d",&c);
				if(c>4 || c<1)
				{
					flag=0;
					printf("��Ч��ѡ��������ѡ��");
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
					printf("����������������ĸ��ɵ��޸ĺ���û�ID��");
					scanf("%s",&id);
					flag=1;
					if(strlen(id)!=6){flag=0;}
					for(k=0;id[k]!='\0' && flag;k++)
						if(isalnum(id[k])==0)
							flag=0;
				}while(!flag);
				for(j=0;j<m;j++)  // �û�id����
				{
					if((strcmp(user[j].id,id))==0) 
					{
						printf("��id�Ѵ���,���������룺");
						flag=0;
						break;
					}
				}
			}while(!flag);
			strcpy(user[loc].id,id);
			break;

		case 2:
			printf("�������޸ĺ�Ŀ�����(year/time)��");
			scanf("%s",card);	
			if((strcmp(card,"time"))==0)
			{
				strcpy(user[loc].card,card);
				do
				{
					flag=1;
					printf("������ÿ���Ч������");
					scanf("%s",&va);
					for(k=0;va[k]!='\0' && flag;k++) //�ж������Ƿ�Ϊ���֣����Ҵ���0��С��30
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
					printf("�������������(��190212): ");
					scanf("%s",&t);
					if(strlen(t)!=6)   // �ж������Ƿ�Ϊ6λ������������
						flag=0;
					for(k=0;t[k]!='\0' && flag;k++)
						if(isdigit(t[k])==0)
							flag=0;
				}while(!flag);
				td=atol(t);	
				do
				{
					flag=1;
					printf("��������Чʹ����:");
					scanf("%s",&va);
					if(strlen(va)!=6)
						flag=0;
					for(k=0;va[k]!='\0' && flag;k++)  // ��Ч�ڱ�����ڽ�������
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
				do   //�޸���Ч����
				{
					flag=1;
					printf("������ÿ���Ч������");
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
				do   //�޸���Ч����
				{
					flag=1;
					printf("�������������(��190212): ");
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
					printf("��������Чʹ����:");
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
			if((strcmp(user[loc].carid1,"0")!=0) && (strcmp(user[loc].carid2 ,"0")!=0)) // ���û���2����
			{
				printf("���û���2�������޸ĳ���1�밴1���޸ĳ���2�밴2����Ҫ�޸��밴3�������޸��밴4��");
				scanf("%d",&ss);
				if(ss==1)       //�޸ĳ�1
				{
					do
					{
						do
						{
							flag=1;
							printf("��������ĸ��������ɵ��޸ĺ�ĳ��ƺţ�");
							scanf("%s",&c1id);	
							for(k=0;c1id[k]!='\0' && flag;k++)   // �жϳ��ƺ��Ƿ����
								if(isalnum(c1id[k])==0)
									flag=0;
						}while(!flag);
						if(strcmp(c1id,"0")!=0)   // ��֤���ƺ��Ƿ����
						{
							for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c1id)==0) || (strcmp(user[j].carid2,c1id)==0))
								{
									printf("�ó��ƺ��Ѵ��ڣ�");
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
						strcpy(user[loc].car2in,"�޳���");
					}
					else
						strcpy(user[loc].carid1,c1id);
						printf("�޸ĳɹ���");
				}
				else if(ss==2)  // �޸ĳ�2
				{
					do
					{
						do
						{
							flag=1;
							printf("����������ĸ��������ɵ��޸ĺ���2�ĳ��ƺţ�");
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
									printf("�ó��ƺ��Ѵ��ڣ�");
									flag=0;
									break;
								}
							};
						};
					}while(!flag);
					if(strcmp(c2id,"0")==0)
					{
						strcpy(user[loc].carid2,c2id);
						strcpy(user[loc].car2in,"�޳���");
					};
					strcpy(user[loc].carid2,c2id);
					printf("�޸ĳɹ���");
				}
				else if(ss==3)  //ȫ�޸�
				{
					do
					{
						do
						{
							flag=1;
							printf("��������ĸ��������ɵ��޸ĺ�ĳ��ƺ�1��");
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
									printf("�ó��ƺ��Ѵ��ڣ�");
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
							printf("����������ĸ��������ɵ��޸ĺ���2�ĳ��ƺţ�");
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
									printf("�ó��ƺ��Ѵ��ڣ�");
									flag=0;
									break;
								}
							}
						}
					}while(!flag);
					if(strcmp(c2id,"0")==0)
					{
						strcpy(user[loc].carid2,c2id);
						strcpy(user[loc].car2in,"�޳���");
					};
					strcpy(user[loc].carid2,c2id);
					printf("�޸ĳɹ���");
				}
				//else
				//	break;
			}

			else if((strcmp(user[loc].carid1 ,"0")!=0) && (strcmp(user[loc].carid2,"0")==0))   // ���û���ӵ��һ����
			{
				printf("���û���һ̨����ȷ���޸��밴1����ӳ����밴2��ȡ���޸��밴0�� ");
				scanf("%d",&ss);
				if(ss==1)  // �޸ĳ���1
				{
					do
					{
						do
						{
							flag=1;
							printf("��������ĸ��������ɵ��޸ĺ�ĳ��ƺţ�");
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
								printf("�ó��ƺ��Ѵ��ڣ�");
								flag=0;
								break;
							}
						}
					}while(!flag);							
					strcpy(user[loc].carid1,c1id);
					printf("�޸ĳɹ���");
				}
				else if(ss==2)  //��ӳ���2
				{
					do
					{
						flag=1;
						do
						{
							printf("��������ĸ��������ɵĳ��ƺţ�");
							scanf("%s",&c2id);
							for(k=0;c2id[k]!='\0' && flag;k++)
								if(isalnum(c2id[k])==0)
									flag=0;
						}while(!flag);
						for(j=0;j<m;j++)
							{
								if((strcmp(user[j].carid1,c2id)==0) || (strcmp(user[j].carid2,c2id)==0))
								{
									printf("�ó��ƺ��Ѵ��ڣ�");
									flag=0;
									break;
								}
							}
					}while(!flag);
					strcpy(user[loc].carid2,c2id);
					strcpy(user[loc].car2in,"����δ����");
					printf("�޸ĳɹ���");
				}
			}
			break;
		}
		printf("\n");
		printf("ȷ�������޸ĵ���Ϣ��1/0��,��ѡ0���������޸ģ�");
		scanf("%d",&flag);
	}while(!flag);

	save(m);
	display();
	printf("\n�޸Ľ����밴0�������޸��밴1��"); //��������޸ģ�������棬��������һ��
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

bool isleap(int year){ // �ж��Ƿ�Ϊ����
	 return (year%4==0 && year%100!=0 || year%400==0);
}

//����ͣ������
long fee(long Time_in,long Hour_in,long Time_out,long Hour_out)
{
	//�������ʱ��󣬽���ֽ�Ϊ�꣬�£��գ�ʱ����
    int y1,m1,d1,h1,s1;
    int y2,m2,d2,h2,s2;
    int day=0;
    long hour,p;
    y1=Time_in/10000,m1=Time_in%10000/100,d1=Time_in%100,h1=Hour_in/100,s1=Hour_in%100;
    y2=Time_out/10000,m2=Time_out%10000/100,d2=Time_out%100,h2=Hour_out/100,s2=Hour_out%100;
    while (y1<y2 || m1<m2 || d1<d2){  //�������ʱ����������
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
    hour=h2-h1;   // ����Сʱ��
    if(s2-s1>0)
        hour++;
	hour=hour+24*day;
    p=5+3*(hour-1);  // �������
    return p;
};

void carin(){
	FILE* fp;
	int m=load();
	int i,n,j,k=0,flag,tag,loc=-1,f; //tag����1���ǳ�2
	bool ft=true;
	char car[6],time[12],tim[6];
	char sto[7];
	long v;
	do
	{
		flag=1;
		printf("�����복�ƺţ�");     // ȷ�����ƺ�
		scanf("%s",car);
		for(i=0;car[i]!='\0' && flag;i++)
		{
			if(isalnum(car[i])==0)
				flag=0;
		}
	}while(!flag);
	strcpy(sto,car);

	for(i=0;i<m;i++)										//�����ó��Ƶĳ�����ȷ������ĳ����ǳ�1���ǳ�2
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
		printf("�������볡ʱ��(ʡ��':'��ȷ����):");  // �������ʱ��
		scanf("%s",time);
		if(strlen(time)!=12)
			flag=0;
		for(i=0;time[i]!='\0' && flag;i++)
		{
			if(isdigit(time[i])==0)
				flag=0;
		}
	}while(!flag);

	if(loc!=-1){ //locΪ���û��������е�λ��
		if(strcmp(user[loc].card,"year")==0)
		{
			strncpy(tim,time+2,6);
			v=atol(tim);
			if(v>=user[loc].valid){ft=false;} 
		};

		if(ft){ // ft��true�����Աû����
			if(tag==1) //tag����ȴ�������ǳ����ļ��ų�
			{
				if(strcmp(user[loc].car2in,"vip")==0)
					strcpy(user[loc].car1in,time);
				else if(strcmp(user[loc].car2in,"�޳���")==0 || strcmp(user[loc].car2in,"����δ����")==0)
					strcpy(user[loc].car1in,"vip");
			}
			else if(tag==2)
			{
				if(strcmp(user[loc].car1in,"vip")==0)
					strcpy(user[loc].car2in,time);
				else if(strcmp(user[loc].car1in,"�޳���")==0 || strcmp(user[loc].car1in,"����δ����")==0)
					strcpy(user[loc].car2in,"vip");
			};
			save(m);
			printf("����룡");
		}
		else
		{
			for(j=loc;j<m;j++)    //ɾ�������û�
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
			printf("�����û���������δ���ѣ��ѱ�ע�����������ʱ������.\n");			
		}
	}
	if(!isFull() && loc==-1){
		printf("������ʱ����ѡ��1���뿪��ѡ��0�� ");
		scanf("%d",&n);
		if(n==1)
		{  //��ʱ��ֻ���ó��ƺ������ʱ�䣬����ȫΪĬ��ֵ
			strcpy(user[m].id,"temp");  
			strcpy(user[m].card,"temp");
			strcpy(user[m].carid2,"0");
			strcpy(user[m].car1in,time);
			strcpy(user[m].car2in,"�޳���");
			strcpy(user[m].carid1,sto);
			m=m+1;
			save(m);
			printf("\n��ӳɹ���\n");
			printf("�����Խ��룡");
		}
		else
			printf("�ټ���");
	}
	else if(isFull()){printf("�û����������ܴ�����ʱ����");}
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
        printf("�����복�ƺţ�");  // �����뿪�ĳ��ƺ�
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
		printf("���������ʱ��(ʡ��':'��ȷ����):");		//������ȷʱ��
		scanf("%s",time);
		if(strlen(time)!=12)
			flag=0;
		for(i=0;time[i]!='\0' && flag;i++)
		{
			if(isdigit(time[i])==0)
				flag=0;
		}
	}while(!flag);

	for(i=0;i<m;i++)										//�����ó��Ƶĳ�������ȷ���ǳ�1���ǳ�2
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
		{// �꿨�û����������ʱ��δ����Ч��ֹ�ڡ�����vip״̬�ĳ���ֱ������Ϊ����δ���룻			
			if(tag==1)   // tag����ȴ��뿪���ǳ����ļ��ų�
			{
				if(strcmp(user[i].car1in,"vip")==0) 
				{
					if(vo<user[i].valid)
					{
						strcpy(user[i].car1in,"����δ����");
						printf("ף��һ·˳�磡");
					}

					else         
					{ // ���������ֹ�ڣ��ó������ڵ���ֹ�ڵ�time��Ʒѣ������һ����δ���룬ֱ��ɾ�����û���������ʱ����

						pay=fee(user[i].valid,0,vo,hoursout);
						if(strcmp(user[i].car2in,"�޳���")==0 || strcmp(user[i].car2in,"����δ����")==0)
						{	for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("���������û����ѵ��ڣ�����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
						else
						{	
							strcpy(user[i].car1in,"����δ����");
							printf("���������û����ѵ��ڣ�����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
					};
				}
				else if(strcmp(user[i].car1in,"vip")!=0)  // ���ڷ�vip״̬���û���ֱ������ time�� �Ʒ�
				{
					strncpy(timi,user[i].car1in+2,6);
					strncpy(hourin,user[i].car1in+8,4);
					vi=atol(timi);
					hoursin=atoi(hourin);
					pay=fee(vi,hoursin,vo,hoursout);

					if(vo<user[i].valid)
					{
						strcpy(user[i].car1in,"����δ����");
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
					}
					else   
					{
						if(strcmp(user[i].car2in,"�޳���")==0 || strcmp(user[i].car2in,"����δ����")==0)
						{	for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
						else
						{	strcpy(user[i].car1in,"����δ����");
							printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
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
						strcpy(user[i].car2in,"����δ����");
						printf("ף��һ·˳�磡");
					}
					else
					{
						pay=fee(user[i].valid,0,vo,hoursout);
						if(strcmp(user[i].car1in,"�޳���")==0 || strcmp(user[i].car1in,"����δ����")==0)
						{	
							for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("���������û����ѵ��ڣ�����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
						else
						{
							strcpy(user[i].car2in,"����δ����");
							printf("���������û����ѵ��ڣ�����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
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
						strcpy(user[i].car2in,"����δ����");
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
					}
					else
					{
						if(strcmp(user[i].car1in,"�޳���")==0 || strcmp(user[i].car1in,"����δ����")==0)
						{	
							for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
						else
						{	strcpy(user[i].car2in,"����δ����");
							printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
							printf("ף��һ·˳�磡");
						}
					}
				}
			}
		}

		else if(strcmp(user[i].card,"time")==0)  // �ο�δ���꣬����ͬ�꿨
		{
			if(tag==1)
			{
				if(strcmp(user[i].car1in,"vip")==0)
				{
					if(user[i].valid==1)
					{
						if(strcmp(user[i].car2in,"�޳���")==0 || strcmp(user[i].car2in,"����δ����")==0)
						{
							for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("ף��һ·˳�磡");
						}
						else
						{
							user[i].valid=user[i].valid-1;
							strcpy(user[i].car1in,"����δ����");	
							printf("ף��һ·˳�磡");
						}
					}

					else
					{
						user[i].valid=user[i].valid-1;
						strcpy(user[i].car1in,"����δ����");
						printf("ף��һ·˳�磡");
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
						for(j=i;j<m;j++)    //ɾ�������û�
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
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
					}
					else
					{
						strcpy(user[i].car1in,"����δ����");
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
					}
				}
			}

			else if(tag==2)
			{
				if(strcmp(user[i].car2in,"vip")==0)
				{
					if(user[i].valid==1)
					{
						if(strcmp(user[i].car1in,"�޳���")==0 || strcmp(user[i].car1in,"����δ����")==0)
						{
							for(j=i;j<m;j++)    //ɾ�������û�
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
							printf("ף��һ·˳�磡");
						}
						else
						{
							user[i].valid=user[i].valid-1;
							strcpy(user[i].car2in,"����δ����");
							printf("ף��һ·˳�磡");
						}
					}

					else
					{
						user[i].valid=user[i].valid-1;
						strcpy(user[i].car2in,"����δ����");
						printf("ף��һ·˳�磡");
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
						for(j=i;j<m;j++)    //ɾ�������û�
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
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
					}
					else
					{
						strcpy(user[i].car2in,"����δ����");
						printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
						printf("ף��һ·˳�磡");
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

			for(j=i;j<m;j++)    //ɾ�������û�
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
			printf("����Ҫ���ɵķ���Ϊ��%ld\n",pay);
			printf("ף��һ·˳�磡");
		}
		save(m);
	}
	else
		printf("δ���ҵ��ó�����");
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
		printf("1.�û�ID 2.������ 3.��Ч����/��Ч���� 4.���ƺ� 5.�볡ʱ�� 6.��������\n");
	    printf("��Ҫ�������ֶ��������������Ӧ�Ĵ��ţ�");
	    scanf("%d",&s1);
	    if(s1<1 || s1>6)
		{
			printf("���벻�Ϸ������������룺");
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
	case 1: // ��id����
		std::sort(user,user+m,cmp_id);
		break;
	case 2: //������������
		std::sort(user,user+m,cmp_card);
		break;
	case 3: //����Ч������
		std::sort(user,user+m,cmp_v);
		break;
	case 4: // �����ƺ�����
		std::sort(user,user+m,cmp_car);
		break;
	case 5: // ���볡ʱ������
		std::sort(user,user+m,cmp_in);
		break;
	default:return;
	}
	printf("��������ѡ��1����������ѡ��2��");
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


