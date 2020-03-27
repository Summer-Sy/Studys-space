#include <stdio.h>
#include <mysql.h>

int* getLimit(int* a,int count);
int* draw(int* stati,int count);
int main()
{
    MYSQL mysql;        //mysql���ݿ�����
    mysql_init(&mysql); //��ʼ�����ݿ�����

    MYSQL_RES *res;     //ָ���ѯ�����ָ��
    MYSQL_ROW row;      //���з��ص�select�������һ�м�¼
    MYSQL_FIELD *field; //ָ���ֶνṹ���ָ��

    int rowCount;       //select������ص�����
    int colCount;       //���ص�������
    int i,j;
    int choose1,choose2;
    int year,mon,day;
    char str1[20],yearc[10],monc[10],dayc[10];
    char select_query[100];
    int stat[3];
    printf("-------------------------������Ϣ��ѯϵͳ-------------------------\n\n");
    if(mysql_real_connect(&mysql, "localhost", "root",
	                     "123456", "experiment2", 3306, NULL, 0))
    {
        mysql_query(&mysql, "set names gbk");
        printf("1.��ѯĳ��ĳ�������״��\n2.ͳ����Ϣ\n��ѡ��");
        while(scanf("%d", &choose1))
        {
            switch(choose1)
            {
                case 1:
                    printf("1.����ID���� \n2.������������\n��ѡ��");
                    while(scanf("%d", &choose2))
                    {
                        switch(choose2)
                        {
                            case 1:
                                printf("������ID:\n");
                                memset(select_query, 0 ,sizeof(select_query));

                                scanf("%s", str1);
                                printf("������date��\n");
                                scanf("%d %d %d",&year,&mon,&day);
                                printf("\n");
                                snprintf(monc,sizeof(monc),"%d",mon);
                                snprintf(dayc,sizeof(dayc),"%d",day);

                                strcat(select_query,
								        "select * from basic,data where basic.ID = data.ID and basic.ID = '");
                                strcat(select_query,str1);
                                strcat(select_query,"' and data.date = '2020-");
                                strcat(select_query,monc);
                                strcat(select_query,"-");
                                strcat(select_query,dayc);
                                strcat(select_query,"'");
                                //printf("%s\n", select_query);

                                if(mysql_query(&mysql, select_query)==0)
                                {
                                    res = mysql_store_result(&mysql);
                                    rowCount = mysql_num_rows(res);
                                    colCount = mysql_num_fields(res);
                                    
									//��ʾ����
                                    field = mysql_fetch_field(res);
                                    for (i = 0; i<6; i++)
                                        printf("%15s", field[i].name);
                                    for(i = 7; i<10; i++)
                                        printf("%15s", field[i].name);
                                    printf("\n");

                                    //������ʾ����
                                    row = mysql_fetch_row(res);
                                    for(j = 0; j < 6; j++)
                                    {
                                        printf("%15s", row[j]);
                                    }
                                    for(j = 7; j < colCount; j++)
                                        printf("%15s", row[j]);
                                    printf("\n");
                                }
                                else
                                    printf("select fail");
                                break;

                            case 2:
                                printf("����������:\n");
                                memset(select_query, 0 ,sizeof(select_query));

                                scanf("%s", str1);
                                printf("������date��\n");
                                scanf("%d %d %d",&year,&mon,&day);
                                snprintf(monc,sizeof(monc),"%d",mon);
                                snprintf(dayc,sizeof(dayc),"%d",day);

                                strcat(select_query,
								    "select * from basic,data where basic.ID = data.ID and basic.name = '");
                                strcat(select_query,str1);
                                strcat(select_query,"' and data.date = '2020-");
                                strcat(select_query,monc);
                                strcat(select_query,"-");
                                strcat(select_query,dayc);
                                strcat(select_query,"'");
                                //printf("%s\n", select_query);

                                if(mysql_query(&mysql, select_query)==0)
                                {
                                    res = mysql_store_result(&mysql);
                                    rowCount = mysql_num_rows(res);
                                    colCount = mysql_num_fields(res);
                                    field = mysql_fetch_field(res);
                                    for (i = 0; i<6; i++)
                                        printf("%15s", field[i].name);
                                    for(i = 7; i<10; i++)
                                        printf("%15s", field[i].name);
                                    printf("\n");

                                    row = mysql_fetch_row(res);
                                    for(j = 0; j < 6; j++)
                                    {
                                        printf("%15s", row[j]);
                                    }
                                    for(j = 7; j < colCount; j++)
                                        printf("%15s", row[j]);
                                    printf("\n");
                                }
                                else
                                    printf("select fail");
                                break;
                        	default:
                                printf("��������������ѡ��");
                        }
                    }
                    break;

                case 2:
                    memset(select_query, 0 ,sizeof(select_query));
                    printf("��������Ҫͳ�Ƶ�ʱ�䣺\n");

                    scanf("%d %d %d",&year,&mon,&day);
                    snprintf(monc,sizeof(monc),"%d",mon);
                    snprintf(dayc,sizeof(dayc),"%d",day);

                    strcat(select_query,
						"select * from data where �Ƿ�ȷ�� = '��' and date = '2020-");
                    strcat(select_query,monc);
                    strcat(select_query,"-");
                    strcat(select_query,dayc);
                    strcat(select_query,"'");
                    //printf("%s",select_query);

                    if(mysql_query(&mysql,select_query)==0)
                    {
                        res = mysql_store_result(&mysql);
                        stat[0] = mysql_num_rows(res);
                        printf("ȷ�ﲡ��:%d\n", stat[0]);
                    }
                    else
                        printf("stat[0] of selection fail");

                    memset(select_query, 0 ,sizeof(select_query));
                    strcat(select_query,
					    "select * from data where �Ƿ����� = '��' and date = '2020-");
                    strcat(select_query,monc);
                    strcat(select_query,"-");
                    strcat(select_query,dayc);
                    strcat(select_query,"'");
                    // printf("%s",select_query);

                    if(mysql_query(&mysql,select_query)==0)
                    {
                        res = mysql_store_result(&mysql);
                        stat[1] = mysql_num_rows(res);
                        printf("���Ʋ���:%d\n", stat[1]);
                    }
                    else
                        printf("stat[1] of selection fail");

                    memset(select_query, 0 ,sizeof(select_query));
                    strcat(select_query,
					    "select * from data where �Ƿ�Ӵ� = '��' and date = '2020-");
                    strcat(select_query,monc);
                    strcat(select_query,"-");
                    strcat(select_query,dayc);
                    strcat(select_query,"'");
                    // printf("%s",select_query);

                    if(mysql_query(&mysql,select_query)==0)
                    {
                        res = mysql_store_result(&mysql);
                        stat[2] = mysql_num_rows(res);
                        printf("�Ӵ�����:%d\n", stat[2]);
                    }
                    else
                        printf("stat[2] of selection fail");

                    //��ͼ
                    int count = sizeof(stat)/sizeof(stat[0]);
                    draw(stat,count);
                    break;
                    
            	default:
                	printf("��������������ѡ��: ");
                break;
            }
        }
        mysql_close(&mysql);
    }
    else
        printf("fail!");

}
//���ͳ����Ϣ�е���Сֵ
int* getLimit(int* a,int count)
{
    static int limit[2]={0};
    for(int i=0;i<count;i++)
    {
    	limit[1] = limit[1]>a[i] ? limit[1] : a[i];
        limit[0] = limit[0]<a[i] ? limit[0] : a[i];
    }
    return limit;
}

//��ͼ����
int* draw(int* stati,int count)
{
    int * pLimit = getLimit(stati,count);
    int min = pLimit[0]-1;
    int max = pLimit[1];
    printf("\n");
    puts("^");
    printf("|\n");

    for(int i=max+1;i>-100;i=i-100)
    {
        if(i<=0){
            printf("+");
            for(int j=0;j<15*count;j++)
                printf("-");
            puts(">");
        }
        else
        {
            if(i>0){
                printf("|");
                for(int j=0;j<count;j++)
                {
                    if(stati[j]>=i)
                        printf("     ####     ");
                    else if(stati[j]+99 >= i-1)
                        printf("     %d      ",stati[j]);
                    else
                        printf("              ");
                }
                printf(" \n");
            }
        }
    }
    printf("\n");
    printf("    ȷ�ﲡ��      ���Ʋ���      �Ӵ�����");
}
