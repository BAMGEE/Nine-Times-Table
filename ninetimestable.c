/***********************************************************************************************
 *  System          : Nine Times Table
 *  Program ID      : ninetimestable.c
 *  Description     : 구구단 출력 프로그램
 *  Author          : Jiyeoning
 ************************************************************************************************/

 /*--<HEADER FILES>------------------------------------------------------------------------------*/
#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>


/*--<VARIABLES>---------------------------------------------------------------------------------*/
char    gsInputArr[100];                      /* 입력값 배열 */
char    gsTimesArr[100][24];                  /* 구구단 배열 */
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
 * Description  : 구구단 출력 프로그램의 main 함수
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
        printf("\n\n1. 다시 입력\n2. 프로그램 종료\n\n입 력 : ");
        scanf("%d", &liAnswer);

        if (liAnswer != 2)
        {
            system("clear");

            /*--------------------------------------------
            * 배열 및 변수 초기화
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

    printf("\n\n프로그램 종료.\n");
    system("clear");

    return 0;
} /* End of main */

/*----------------------------------------------------------------------------------------------
 * Function     : Description
 * Description  : 프로그램명과 입력방법 출력 함수.
 *----------------------------------------------------------------------------------------------*/
void Description()
{
    printf("\n\n[NINE-TIMES-TABLE]\n\n");
    printf("출력을 원하는 구구단의 단수를 아래의 입력방법을 참고해 입력하세요.\n");
    printf("2단부터 9단까지 출력이 가능합니다.\n");
    printf("\n< 입력방법 >\n");
    printf("* 한 개의 숫자 입력 (ex. 2)\n");
    printf("* 콤마(,)를 이용한 입력 (ex. 2,4,5)\n");
    printf("* 물결(~)을 이용한 입력 (ex. 2~5)\n");
    printf("* 콤마(,)와 물결(~)을 이용한 입력 (ex. 2,4~6,9)\n");
    printf("\n\n입 력 : ");
    scanf("%s", gsInputArr);

} /* End of Description */

/*----------------------------------------------------------------------------------------------
 * Function     : InputCheck01
 * Description  : 사용자 입력값이 유효한지 검사.
 *               콤마(,)와 물결(~)이 연속되거나 숫자가 연속되면 에러메시지 출력.
 * Input param  : char gsInputArr[100]
 * Return value : 0(OK), 1(ERR)
 *----------------------------------------------------------------------------------------------*/
int InputCheck01()
{
    int i;

    for (i = 0; i < 100; i++)
    {
        /*--------------------------------------------
        * 입력값 중 0 또는 1이 있을 때
        *--------------------------------------------*/
        if (gsInputArr[i] == 0x30 || gsInputArr[i] == 0x31)
        {
            printf("ERR : 2단부터 9단까지 출력이 가능합니다.\n");
            return 1;
        }
        /*--------------------------------------------
        * 입력값 중 2부터 9 사이의 숫자가 연속될 때
        *--------------------------------------------*/
        else if (gsInputArr[i] >= 0x32 && gsInputArr[i] <= 0x39)
        {
            if (gsInputArr[i + 1] >= 0x32 && gsInputArr[i + 1] <= 0x39)
            {
                printf("ERR : 2단부터 9단까지 출력이 가능합니다.\n");
                return 1;
            }
        }
        /*--------------------------------------------
        * 입력값 중 문자가 반복될 때
        *--------------------------------------------*/
        else if (gsInputArr[i] == 0x2c || gsInputArr[i] == 0x7e)
        {
            if (gsInputArr[i + 1] == 0x2c || gsInputArr[i + 1] == 0x7e)
            {
                printf("ERR : 문자는 한 개씩\n");
                return 1;
            }
        }
    }
    return 0;

} /* End of InputCheck01 */

/*----------------------------------------------------------------------------------------------
 * Function     : InputCheck02
 * Description  : 사용자 입력값을 숫자, 콤마(,), 물결(~)로 구분하여 Calculate 함수로 전달.
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
            * 숫자 다음 물결(~)이 있을 때
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
        * 공백이 연속되면 끝냄
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
 * Description  : 전달받은 인자를 계산해 gsTimesArr 배열에 대입.
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
            * 구구단의 맨 앞 숫자 채우기
            *--------------------------------------------*/
            if (j == 0 || j == 8 || j == 16)
            {
                gsTimesArr[i][j] = n + '0'; /* 숫자를 아스키코드로 변환 */
            }
            /*--------------------------------------------
            * 구구단의 곱셈문자(X) 채우기
            *--------------------------------------------*/
            else if (j == 1 || j == 9 || j == 17)
            {
                gsTimesArr[i][j] = 'X';
            }
            /*--------------------------------------------
            * 구구단의 등호(=) 채우기
            *--------------------------------------------*/
            else if (j == 3 || j == 11 || j == 19)
            {
                gsTimesArr[i][j] = '=';
            }
            /*--------------------------------------------
            * 구구단의 1~9까지 채우기
            *--------------------------------------------*/
            else if (j == 2 || j == 10 || j == 18)
            {
                gsTimesArr[i][j] = (i % 9) + 1 + '0'; /* 숫자를 아스키코드로 변환 */
            }
            /*--------------------------------------------
            * 구구단의 결과값 채우기
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
 * Description  : gsTimesArr 배열을 출력.
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
