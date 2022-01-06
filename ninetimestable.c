/***********************************************************************************************
 *  System          : Nine Times Table
 *  Program ID      : ninetimestable.c
 *  Description     : ������ ��� ���α׷�
 *  Author          : Jiyeoning
 ************************************************************************************************/

 /*--<HEADER FILES>------------------------------------------------------------------------------*/
#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>


/*--<VARIABLES>---------------------------------------------------------------------------------*/
char    gsInputArr[100];                      /* �Է°� �迭 */
char    gsTimesArr[100][24];                  /* ������ �迭 */
int     giPosX = 0;
int     giPosY = 0;


/*--<FUNCTION PROTOTYPE>------------------------------------------------------------------------*/
void    Description();
int     InputCheck01();
int     InputCheck02();
void    Calculate(int n);
int     PrintTimesTable();


/*----------------------------------------------------------------------------------------------
 * Function     : main
 * Description  : ������ ��� ���α׷��� main �Լ�
 *----------------------------------------------------------------------------------------------*/
int main()
{
    int liCheckNum = 0;
    int liAnswer = 0;
    int i, j;

    system("clear");

    while (liAnswer != 2)
    {
        Description();
        liCheckNum = InputCheck01(); /* 0: OK , 1: ERR */

        if (liCheckNum == 0)
        {
            InputCheck02();
            PrintTimesTable();
        }
        printf("\n\n1. �ٽ� �Է�\n2. ���α׷� ����\n\n�� �� : ");
        scanf("%d", &liAnswer);

        if (liAnswer != 2)
        {
            system("clear");

            /*--------------------------------------------
            * �迭 �� ���� �ʱ�ȭ
            *--------------------------------------------*/
            for (i = 0; i < 100; i++)
            {
                gsInputArr[i] = 0;

                for (j = 0; j < 24; j++)
                {
                    gsTimesArr[i][j] = 0;
                }
            }
            giPosX = 0;
            giPosY = 0;
        }

    }

    printf("\n\n���α׷� ����.\n");
    system("clear");

    return 0;
} /* End of main */

/*----------------------------------------------------------------------------------------------
 * Function     : Description
 * Description  : ���α׷���� �Է¹�� ��� �Լ�.
 *----------------------------------------------------------------------------------------------*/
void Description()
{
    printf("\n\n[NINE-TIMES-TABLE]\n\n");
    printf("����� ���ϴ� �������� �ܼ��� �Ʒ��� �Է¹���� ������ �Է��ϼ���.\n");
    printf("2�ܺ��� 9�ܱ��� ����� �����մϴ�.\n");
    printf("\n< �Է¹�� >\n");
    printf("* �� ���� ���� �Է� (ex. 2)\n");
    printf("* �޸�(,)�� �̿��� �Է� (ex. 2,4,5)\n");
    printf("* ����(~)�� �̿��� �Է� (ex. 2~5)\n");
    printf("* �޸�(,)�� ����(~)�� �̿��� �Է� (ex. 2,4~6,9)\n");
    printf("\n\n�� �� : ");
    scanf("%s", gsInputArr);

} /* End of Description */

/*----------------------------------------------------------------------------------------------
 * Function     : InputCheck01
 * Description  : ����� �Է°��� ��ȿ���� �˻�.
 *               �޸�(,)�� ����(~)�� ���ӵǰų� ���ڰ� ���ӵǸ� �����޽��� ���.
 * Input param  : char gsInputArr[100]
 * Return value : 0(OK), 1(ERR)
 *----------------------------------------------------------------------------------------------*/
int InputCheck01()
{
    int i;

    for (i = 0; i < 100; i++)
    {
        /*--------------------------------------------
        * �Է°� �� 0 �Ǵ� 1�� ���� ��
        *--------------------------------------------*/
        if (gsInputArr[i] == 0x30 || gsInputArr[i] == 0x31)
        {
            printf("ERR : 2�ܺ��� 9�ܱ��� ����� �����մϴ�.\n");
            return 1;
        }
        /*--------------------------------------------
        * �Է°� �� 2���� 9 ������ ���ڰ� ���ӵ� ��
        *--------------------------------------------*/
        else if (gsInputArr[i] >= 0x32 && gsInputArr[i] <= 0x39)
        {
            if (gsInputArr[i + 1] >= 0x32 && gsInputArr[i + 1] <= 0x39)
            {
                printf("ERR : 2�ܺ��� 9�ܱ��� ����� �����մϴ�.\n");
                return 1;
            }
        }
        /*--------------------------------------------
        * �Է°� �� ���ڰ� �ݺ��� ��
        *--------------------------------------------*/
        else if (gsInputArr[i] == 0x2c || gsInputArr[i] == 0x7e)
        {
            if (gsInputArr[i + 1] == 0x2c || gsInputArr[i + 1] == 0x7e)
            {
                printf("ERR : ���ڴ� �� ����\n");
                return 1;
            }
        }
    }
    return 0;

} /* End of InputCheck01 */

/*----------------------------------------------------------------------------------------------
 * Function     : InputCheck02
 * Description  : ����� �Է°��� ����, �޸�(,), ����(~)�� �����Ͽ� Calculate �Լ��� ����.
 *----------------------------------------------------------------------------------------------*/
int InputCheck02()
{
    int liNum01 = 0;
    int liNum02 = 0;
    int i;

    int liInputLen = strlen(gsInputArr);

    for (i = 0; i < liInputLen; i++)
    {
        if (gsInputArr[i] >= 0x32 && gsInputArr[i] <= 0x39)
        {
            /*--------------------------------------------
            * ���� ���� ����(~)�� ���� ��
            *--------------------------------------------*/
            if (gsInputArr[i + 1] == 0x7e)
            {
                liNum01 = atoi(&gsInputArr[i]);
                liNum02 = atoi(&gsInputArr[i + 2]);

                if (gsInputArr[i + 2] == 0)
                {
                    liNum02 = 9;
                }

                if (liNum02 > liNum01)
                {
                    while (liNum01 <= liNum02)
                    {
                        Calculate(liNum01);
                        liNum01++;
                    }
                }
                else
                {
                    while (liNum02 <= liNum01)
                    {
                        Calculate(liNum02);
                        liNum02++;
                    }
                }
                i += 2;
            }
            else
            {
                liNum01 = atoi(&gsInputArr[i]);
                Calculate(liNum01);
            }
        }
        /*--------------------------------------------
        * ������ ���ӵǸ� ����
        *--------------------------------------------*/
        else if (gsInputArr[i] == 0x00 && gsInputArr[i + 1] == 0x00)
        {
            return 0;
        }
    }
    return 0;
} /* End of InputCheck02 */

/*----------------------------------------------------------------------------------------------
 * Function     : Calculate
 * Description  : ���޹��� ���ڸ� ����� gsTimesArr �迭�� ����.
 * Input param  : int i
 *----------------------------------------------------------------------------------------------*/
void Calculate(int n)
{
    int i, j;

    for (i = giPosY; i < (giPosY + 9); i++)
    {
        for (j = giPosX; j < (giPosX + 8); j++)
        {
            /*--------------------------------------------
            * �������� �� �� ���� ä���
            *--------------------------------------------*/
            if (j == 0 || j == 8 || j == 16)
            {
                gsTimesArr[i][j] = n + '0'; /* ���ڸ� �ƽ�Ű�ڵ�� ��ȯ */
            }
            /*--------------------------------------------
            * �������� ��������(X) ä���
            *--------------------------------------------*/
            else if (j == 1 || j == 9 || j == 17)
            {
                gsTimesArr[i][j] = 'X';
            }
            /*--------------------------------------------
            * �������� ��ȣ(=) ä���
            *--------------------------------------------*/
            else if (j == 3 || j == 11 || j == 19)
            {
                gsTimesArr[i][j] = '=';
            }
            /*--------------------------------------------
            * �������� 1~9���� ä���
            *--------------------------------------------*/
            else if (j == 2 || j == 10 || j == 18)
            {
                gsTimesArr[i][j] = (i % 9) + 1 + '0'; /* ���ڸ� �ƽ�Ű�ڵ�� ��ȯ */
            }
            /*--------------------------------------------
            * �������� ����� ä���
            *--------------------------------------------*/
            else if (j == 4 || j == 12 || j == 20)
            {
                gsTimesArr[i][j] = n * ((i % 9) + 1);
            }
            else
            {
                gsTimesArr[i][j] = ' ';
            }
        }
    }

    if (giPosX == 16)
    {
        giPosX = 0;
        giPosY += 9;
    }
    else
    {
        giPosX += 8;
    }

} /* End of Calculate */

/*----------------------------------------------------------------------------------------------
 * Function     : PrintTimesTable
 * Description  : gsTimesArr �迭�� ���.
 *----------------------------------------------------------------------------------------------*/
int PrintTimesTable()
{
    int i, j;

    printf("\n");

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 24; j++)
        {
            if (j == 4 || j == 12 || j == 20)
            {
                if (gsTimesArr[i][j] != 0)
                {
                    printf("%3d", gsTimesArr[i][j]);
                }
                else
                {
                    printf("%3c", gsTimesArr[i][j]);
                }
            }
            else
            {
                printf("%3c", gsTimesArr[i][j]);
            }

            if (j == 23 && (i + 1) % 9 == 0)
            {
                if (gsTimesArr[i + 1][0] == 0x00 && gsTimesArr[i + 2][0] == 0x00)
                {
                    return 0;
                }
                else
                {
                    printf("\n");
                }
            }
        }
        printf("\n");
    }

    return 0;
} /* End of PrintTimesTable */
