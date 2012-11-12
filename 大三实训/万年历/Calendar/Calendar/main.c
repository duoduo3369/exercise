#include <Windows.h>
#include <string.h>
#include "ganzhi.h"
#include "resource.h"
#pragma comment(lib,"WinLib.lib")
void SetDlgMenuID(UINT nMainDlgID,UINT nCalendarDlgID,UINT nMenuID);
void SetButtonID(UINT nCalendarID,UINT nExitID,UINT nBtnChangeID,
                 UINT nBtnClockOn,UINT nBtnClockOff);
INT_PTR ShowMainDlg();

/*
*********************************************************
API�����ο���
GetLocalTime: ��õ�ǰʱ��(�������ꡢ�¡��ա���)
MoveToEx:     �ƶ����ߵ����
LineTo:       ���Ƶ�ĳһ��
SetTextColor: ����Ҫ���Ƶ�������ɫ
TextOut:      ��������
SetBkMode:   ���ñ�����ʾģʽ
wsprintf:    ����ת��Ϊ�ַ��������ַ�����Unicode��
GetClientRect:  ��ȡ���ڴ�С
GetDC:   ��ȡ�ڴ��豸
SetTimer:  ���ö�ʱ��
FillRect:  ������
CreateSolidBrush:  ����ˢ��
RGB:   ����RGB��ɫ
CreateFont:����һ���������Ե�����
�ṹ�����Ͳο���
SYSTEMTIME:   ����ʱ�����ͣ����������ա�ʱ���롢��
*********************************************************
*/

HINSTANCE g_hInst;//�������ϵͳ���ݽ�����"Ӧ�ó���ʵ�����"

//Windows������ں���
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nShowCmd )
{
    g_hInst = hInstance;
    SetDlgMenuID(IDD_DLG_CLOCK,IDD_DLG_CALENDAR,IDR_MENU);
    SetButtonID(ID_CALENDAR,ID_EXIT,ID_40007,ID_40009,ID_40010);
    ShowMainDlg(IDD_DLG_CLOCK);
}



//�����û�Ҫ��ʾ���ꡢ�¡���
unsigned int nCurrentYear=0;
unsigned int nCurrentMonth=0;
unsigned int nCurrentDay=0;


//�ж�ĳ���Ƿ�Ϊ��������
int IsLeapYear(WORD iYear)    //ѧ����Ҫ�޸Ĵ˺���
{
    if(iYear%4 == 0 && iYear%100 != 0)
        return 1;
    if(iYear%100 == 0 && iYear%400 == 0)
        return 1;
    return 0;
}
char* GetShengXiao(int year)
{
    return ShengXiao[(year - 2008) % 12];
}

//��������תũ�����ڵĺ���
void SunToLunar(const stDateTime* pSunDay,stDateTime* pLunarDay)
{
    int i=0;
    int SunDiff=0;
    int SpringDiff=0;

    int nSpringYear=pSunDay->nYear;
    int nSpringMonth=1;
    int nSpringDay=0;

    //���㵱ǰ�������뵱��Ԫ��������
    SunDiff = MonthAdd[pSunDay->nMonth-1] + pSunDay->nDay - 1;
    if(IsLeapYear(pSunDay->nYear) && (pSunDay->nMonth > 2) )//���������Ҵ���2�£������ټ�1
        SunDiff++;

    //���㴺�����ڹ�������Ԫ����������ͨ��������㵱��Ĵ������ڵĹ������ڣ�
    if(((LunarCalendarTable[pSunDay->nYear - 1901] & 0x60)>>5)==1)//�������ڹ���1��
        SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1;
    else//�������ڹ���2��
        SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1+31;

    //SunDiff��SpringDiff�Ĳ���ǵ�ǰ�������봺�ڵ�����

    if(SunDiff>=SpringDiff)//�������ڴ��ں�
    {
        int x = SunDiff - SpringDiff;
        int bLunar = (LunarCalendarTable[nSpringYear - 1901] & 0xF00000)>>20;//�����·�

        i=0;
        nSpringMonth=1;

        for(;;)
        {
            int a = (LunarCalendarTable[pSunDay->nYear-1901] & (0x80000>>i));//�����С��
            if(a==0)
                a=29;
            else
                a=30;
            if(x<a)
                break;
            x =x - a;
            i++;
            nSpringMonth++;
        }
        nSpringDay =x+1;
        //���������
        if(nSpringMonth>bLunar && bLunar>0)
            nSpringMonth--;
    }
    else//�������ڴ���ǰ
    {

        int x = SpringDiff-SunDiff;
        int nShift=0;

        int bLunar = (LunarCalendarTable[nSpringYear - 1901] & 0xF00000)>>20;//�����·�

        i=0;
        nSpringYear--;//��Ҫ��һ���ũ����Ϣ
        nSpringMonth=12;//�����һ���¿�ʼ����

        if (bLunar == 0)//���û������
            nShift = 0x100;
        else
            nShift = 0x80;

        for(;;)
        {
            int a = (LunarCalendarTable[nSpringYear-1901] & (nShift<<i));//�����С��
            if(a==0)
                a=29;
            else
                a=30;

            if(x<a)
            {
                x = a-x;
                break;
            }
            x =x - a;
            i++;
            nSpringMonth--;
        }
        nSpringDay =x+1;

        if(nSpringMonth<bLunar && bLunar>0)
            nSpringMonth++;
    }
    pLunarDay->nYear = nSpringYear;
    pLunarDay->nMonth= nSpringMonth;
    pLunarDay->nDay  = nSpringDay;
}
//���ݹ������ڻ������
int GetDayOfWeek(const stDateTime* pSunDay)
{
    //����̩�չ�ʽ
    //nWeek = [nYear1��4] - 2*nYear1 + nYear2 + [nYear2��4] + [26(nMonth+1)��10] + nDay - 1
    int nWeek=0;
    int nYear1=pSunDay->nYear/100;//���ǰ��λ����
    int nYear2=pSunDay->nYear%100;//��ĺ���λ����
    int nDay=pSunDay->nDay;  //������

    int nMonth=pSunDay->nMonth;//����������������·������1�»�2�£�
    //��Ӧ��Ϊ��һ���13�»�14�£�
    //Ҳ���ǹ�ʽ��nMonth��ȡֵ��Χ�Ǵ�3��14�����Ǵ�1��12

    if(nMonth==1 || nMonth==2)
    {
        nMonth=12+nMonth;
        nYear1=(pSunDay->nYear-1)/100;//���ǰ��λ����
        nYear2=(pSunDay->nYear-1)%100;//��ĺ���λ����
    }

    nWeek = nYear1/4 - 2*nYear1 + nYear2 + nYear2/4 + (26*(nMonth+1))/10 + nDay - 1;
    nWeek = (nWeek + 14) % 7;//��������?

    return nWeek;
}
//���ݹ�����õ�ũ����֧��
char* GetGanZhi(int nYear)
{
    return TianGanDizhi[(nYear-1984)%60];
}
char* GetWeekDay(const stDateTime* pSunDay)
{
    return XingQi[GetDayOfWeek(pSunDay)];
}

//�������ƺ���,ѧ���Լ�ʵ�ָú���
void DrawCalendar(HDC hDC,int nWidth,int nHeight)
{
    HBRUSH hbrush;
    HBRUSH whitebrush,bluebrush,graywhitebrush,graybrush;
    RECT rc,rect,todayrc;
    HPEN hpen;
    HFONT hFont;
    HFONT hFont_big; // �����еĴ�����
    HFONT hFont_small; // �����е�С����
    HFONT hFont_today;// ��ʾ���������
    stDateTime pSunDay;//�洢��������
    stDateTime pLunarDay;
    SYSTEMTIME datetime;// �洢��ǰʱ��
    int nWeek; // ĳ������һ�ܵ����ڼ�
    int iWeek; // ĳ�������µĵڼ��ܣ���һ��Ϊ0�����6�ܣ���Χ0~5
    int days; //������ж�����
    int day;//����
    int xgap,ygap;
    int width,height,i,j;
    int posX,posY; //���ʱ�ĸ����±����
    char stDate[11];
    static TCHAR *DAYS[7] = {TEXT("��"),TEXT("һ"),TEXT("��"),
                             TEXT("��"),TEXT("��"),TEXT("��"),TEXT("��")
                            };



    whitebrush = CreateSolidBrush(RGB(255, 255, 255));
    bluebrush = CreateSolidBrush(RGB(30, 144, 255));
    graywhitebrush = CreateSolidBrush(RGB(248, 248, 255));
    graybrush = CreateSolidBrush(RGB(220, 220, 220));
    hbrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hDC,hbrush);



    width = 228;
    height = (width / 21 * 24);
    rect.left = 3;
    rect.right = rect.left + width;
    rect.top = 67;
    rect.bottom = rect.top + height;
    xgap = (int)((rect.right - rect.left) / 7);
    ygap = (int)((rect.bottom - rect.top) / 6);

    //����������������
    rc.top = 6;
    rc.bottom = rc.top + 60;
    rc.left = rect.left;
    rc.right = rect.right;
    FillRect(hDC,&rc,bluebrush);


    //����׸���
    for(i = 0; i < 6; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(j > 0 && j < 6)
            {
                rc.top = rect.top + i * ygap;
                rc.bottom = rc.top + ygap ;
                rc.left = rect.left + j * xgap;
                rc.right = rc.left + xgap;
                FillRect(hDC,&rc,whitebrush);
            }
        }
    }

    //��������ĻҰ׸���
    rc.top = rect.bottom + 10;
    rc.bottom = rc.top + 60;
    rc.left = rect.left;
    rc.right = rect.right;
    FillRect(hDC,&rc,graywhitebrush);

    //��������ĻҸ���

    rc.top = rc.bottom;
    rc.bottom = rc.top + 90;
    FillRect(hDC,&rc,graybrush);



    //����������
    hpen = CreatePen (PS_SOLID,1,RGB(220, 220, 220)) ;
    SelectObject(hDC,hpen);

    for(i = 0; i <= 6; i++)
    {
        MoveToEx(hDC,rect.left,rect.top+i*ygap,NULL);
        LineTo(hDC,rect.right,rect.top+i*ygap);
    }
    for(i = 0; i < 7; i++)
    {
        MoveToEx(hDC,rect.left+i*xgap+1,rect.top,NULL);
        LineTo(hDC,rect.left+i*xgap+1,rect.bottom);
    }
    height = 16;
    rc.bottom = rect.top;
    rc.left = rect.left;
    rc.right = rect.right+1;
    rc.top = rect.top - height;
    FillRect(hDC,&rc,hbrush);
    SetTextColor(hDC,RGB(255,255,255));




    // ��д ��һ����������
    height -= 4;
    width = height / 2;
    hFont = CreateFont(
                height - 2,      //������߼��߶�
                width,       //�߼�ƽ���ַ����
                0,           //��ˮƽ�ߵĽǶ�
                0,           //���߷�λ�Ƕ�
                FW_REGULAR,  //���Σ�����
                FALSE,       //���Σ�б��
                FALSE,       //���Σ��»���
                FALSE,       //���Σ�����
                GB2312_CHARSET,          //�ַ���
                OUT_DEFAULT_PRECIS,      //�������
                CLIP_DEFAULT_PRECIS,     //���ؾ���
                PROOF_QUALITY,           //���Ʒ��
                FIXED_PITCH | FF_MODERN, //��б��
                "Բ��"                   //����
            );
    SelectObject(hDC,hFont);
    for(i = 0; i < 7; i++)
    {

        rc.left = rect.left + i*xgap;
        rc.right = rc.left + xgap;
        DrawText (hDC,DAYS[i], -1,
                  &rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }




    // ��д����������½��¼�
    height *= 1.1;
    width = height * 0.75;
    hFont_big = CreateFont(
                    height,      //������߼��߶�
                    width,       //�߼�ƽ���ַ����
                    0,           //��ˮƽ�ߵĽǶ�
                    0,           //���߷�λ�Ƕ�
                    FW_REGULAR,  //���Σ�����
                    FALSE,       //���Σ�б��
                    FALSE,       //���Σ��»���
                    FALSE,       //���Σ�����
                    GB2312_CHARSET,          //�ַ���
                    OUT_DEFAULT_PRECIS,      //�������
                    CLIP_DEFAULT_PRECIS,     //���ؾ���
                    PROOF_QUALITY,           //���Ʒ��
                    FIXED_PITCH | FF_MODERN, //��б��
                    "Բ��"                   //����
                );

    //DeleteObject(hBmp);
    SelectObject(hDC,hFont_big);
    SetTextColor(hDC,RGB(0,0,0));
    posX = rect.left+10;
    posY = rect.bottom+20;
    TextOut(hDC,posX,posY,"������¼�",strlen("������¼�"));
    height *= 0.8;
    width = height * 0.75;
    hFont_small = CreateFont(
                      height,      //������߼��߶�
                      width,       //�߼�ƽ���ַ����
                      0,           //��ˮƽ�ߵĽǶ�
                      0,           //���߷�λ�Ƕ�
                      FW_REGULAR,  //���Σ�����
                      FALSE,       //���Σ�б��
                      FALSE,       //���Σ��»���
                      FALSE,       //���Σ�����
                      GB2312_CHARSET,          //�ַ���
                      OUT_DEFAULT_PRECIS,      //�������
                      CLIP_DEFAULT_PRECIS,     //���ؾ���
                      PROOF_QUALITY,           //���Ʒ��
                      FIXED_PITCH | FF_MODERN, //��б��
                      "����"                   //����
                  );
    SelectObject(hDC,hFont_small);
    SetTextColor(hDC,RGB(105, 105, 105));
    if(nCurrentMonth > 9)
    {
        if(nCurrentDay > 9)
        {
            wsprintf(stDate,"%4d-%2d-%2d",nCurrentYear,nCurrentMonth,nCurrentDay);
        }
        else
        {
            wsprintf(stDate,"%4d-%2d-0%d",nCurrentYear,nCurrentMonth,nCurrentDay);
        }
    }
    else
    {
        wsprintf(stDate,"%4d-0%d-0%d",nCurrentYear,nCurrentMonth,nCurrentDay);
    }

    TextOut(hDC,posX,posY+20,stDate,11);

    //д���������ݺ��·�
    SelectObject(hDC,hFont_big);
    SetTextColor(hDC,RGB(255,255,255));
    if(nCurrentMonth > 9)
    {

        wsprintf(stDate,"%4d-%2d",nCurrentYear,nCurrentMonth);

    }
    else
    {
        wsprintf(stDate,"%4d-0%d",nCurrentYear,nCurrentMonth);
    }
    TextOut(hDC,80,25,stDate,7);
    //д������ĸ�֧��

    wsprintf(stDate,"%s",GetGanZhi(nCurrentYear));
    TextOut(hDC,rect.right - 44,15,stDate,4);
    wsprintf(stDate,"%s��",GetShengXiao(nCurrentYear));
    TextOut(hDC,rect.right - 44,30,stDate,4);

    //���������������
    hpen = CreatePen (PS_SOLID,3,RGB(255, 255, 255)) ;
    SelectObject(hDC,hpen);
    for(i = 0; i < 3; i++)
    {
        MoveToEx(hDC,rect.left + 7,20 + i * 8,NULL);
        LineTo(hDC,rect.left + 27,20 + i * 8);
    }

    hFont_today = CreateFont(
                      height,      //������߼��߶�
                      height * 0.80,       //�߼�ƽ���ַ����
                      0,           //��ˮƽ�ߵĽǶ�
                      0,           //���߷�λ�Ƕ�
                      FW_REGULAR,  //���Σ�����
                      FALSE,       //���Σ�б��
                      FALSE,       //���Σ��»���
                      FALSE,       //���Σ�����
                      GB2312_CHARSET,          //�ַ���
                      OUT_DEFAULT_PRECIS,      //�������
                      CLIP_DEFAULT_PRECIS,     //���ؾ���
                      PROOF_QUALITY,           //���Ʒ��
                      FIXED_PITCH | FF_MODERN, //��б��
                      "Բ��"                   //����
                  );


    //��д��������
    day = 1;
    pSunDay.nYear = nCurrentYear;
    pSunDay.nMonth = nCurrentMonth;
    pSunDay.nDay = 1;
    nWeek = GetDayOfWeek(&pSunDay);
    days = MonthTable[nCurrentMonth];
    if(nCurrentMonth == 2 && IsLeapYear(nCurrentYear))
    {
        days = 29;
    }
    iWeek = 0;
    SelectObject(hDC,hFont_big);
    SetTextColor(hDC,RGB(0,0,0));
    GetLocalTime(&datetime);

    //����

    hbrush=CreateSolidBrush(RGB(224, 255, 255));
    SelectObject(hDC,hbrush);

    //��һ��
    rc.top = rect.top + 3;
    rc.bottom = rect.top + ygap;

    for(i = nWeek; i <= 6; i++)
    {
        rc.left = rect.left + i * xgap;
        rc.right = rc.left + xgap;
        if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                && day == datetime.wDay)
        {
            SelectObject(hDC,hFont_today);
            SetTextColor(hDC,RGB(30, 144, 255));

            todayrc.top = rect.top;
            todayrc.bottom = rc.bottom;
            todayrc.left = rc.left+1;
            todayrc.right = rc.right+1;
            FillRect(hDC,&todayrc,hbrush);
            wsprintf(stDate,"����");
            day++;
            DrawText (hDC,stDate, -1,
                      &rc,DT_SINGLELINE | DT_CENTER);
            SetTextColor(hDC,RGB(0,0,0));
            SelectObject(hDC,hFont_big);
        }
        else
        {
            wsprintf(stDate,"%2d",day++);
            DrawText (hDC,stDate, -1,
                      &rc,DT_SINGLELINE | DT_CENTER);

        }


    }
    //�������ʣ�µ���
    iWeek = 1;
    while(day <= days)
    {
        for(i = 0; i < 7; i++)
        {
            if(day > days)
            {
                break;
            }
            rc.top = rect.top + iWeek * ygap + 3;
            rc.bottom = rect.top + (iWeek + 1 ) * ygap;
            rc.left = rect.left + i * xgap;
            rc.right = rc.left + xgap;
            if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                    && day == datetime.wDay)
            {
                todayrc.top = rc.top - 3;
                todayrc.bottom = rc.bottom;
                todayrc.left = rc.left+1;
                todayrc.right = rc.right+1;


                FillRect(hDC,&todayrc,hbrush);
                SelectObject(hDC,hFont_today);
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                day++;
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(0,0,0));
                SelectObject(hDC,hFont_big);
            }
            else
            {
                wsprintf(stDate,"%2d",day++);
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);

            }

        }
        iWeek++;

    }

    //����
    SelectObject(hDC,hFont_small);
    SetTextColor(hDC,RGB(105, 105, 105));
    day = 1;
    rc.top = rect.top + 20;
    rc.bottom = rect.top + ygap;
    for(i = nWeek; i <= 6; i++)
    {
        rc.left = rect.left + i * xgap;
        rc.right = rc.left + xgap;
        pSunDay.nDay = day++;
        SunToLunar(&pSunDay,&pLunarDay);
        //ǡ�ý���
        if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                && day == datetime.wDay)
        {
            //����
            if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //Ԫ��
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"Ԫ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //��Ϧ
            if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"��Ϧ");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //����
            if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //С��
            if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"С��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //Ԫ��
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"Ԫ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //����
            if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //�Ͷ���
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"�Ͷ�");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //�����
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            // ʥ��
            if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"ʥ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            else
            {

                SetTextColor(hDC,RGB(30, 144, 255));
                if(pLunarDay.nDay == 1)
                {
                    if(pLunarDay.nMonth == 0)
                    {
                        wsprintf(stDate,"����");
                    }
                    wsprintf(stDate,"%s��",ChMonthTable[pLunarDay.nMonth]);
                }
                else
                {
                    wsprintf(stDate,"%s",ChDayTable[pLunarDay.nDay]);
                }

                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
            }

        }
        //���ǽ���
        else
        {
            //����
            if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //Ԫ��
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"Ԫ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //��Ϧ
            if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"��Ϧ");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //����
            if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //����
            if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //С��
            if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"С��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //Ԫ��
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"Ԫ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //����
            if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //�Ͷ���
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"�Ͷ�");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //�����
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"����");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            // ʥ��
            if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"ʥ��");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            else
            {
                if(pLunarDay.nDay == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    if(pLunarDay.nMonth == 0)
                    {
                        wsprintf(stDate,"����");
                    }
                    else
                    {
                        wsprintf(stDate,"%s��",ChMonthTable[pLunarDay.nMonth]);
                    }
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                }
                else
                {
                    wsprintf(stDate,"%s",ChDayTable[pLunarDay.nDay]);
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                }


            }
        }

    }
    //�������ʣ�µ���
    iWeek = 1;
    while(day <= days)
    {
        for(i = 0; i < 7; i++)
        {
            if(day > days)
            {
                break;
            }
            rc.top = rect.top + iWeek * ygap + 20;
            rc.bottom = rect.top + (iWeek + 1 ) * ygap;
            rc.left = rect.left + i * xgap;
            rc.right = rc.left + xgap;
            pSunDay.nDay = day++;
            SunToLunar(&pSunDay,&pLunarDay);
            //ǡ�ý���
            if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                    && pSunDay.nDay == datetime.wDay)
            {
                //����
                if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //Ԫ��
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"Ԫ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //��Ϧ
                if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"��Ϧ");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //����
                if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //С��
                if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"С��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //Ԫ��
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"Ԫ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //����
                if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //�Ͷ���
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"�Ͷ�");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //�����
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                // ʥ��
                if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"ʥ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                   SetTextColor(hDC,RGB(105, 105, 105));
                   continue;
                }

                else
                {

                    SetTextColor(hDC,RGB(30, 144, 255));
                    if(pLunarDay.nDay == 1)
                    {
                        if(pLunarDay.nMonth == 0)
                        {
                            wsprintf(stDate,"%s��",ChMonthTable[12]);
                        }
                        wsprintf(stDate,"%s��",ChMonthTable[pLunarDay.nMonth]);
                    }
                    else
                    {
                        wsprintf(stDate,"%s",ChDayTable[pLunarDay.nDay]);
                    }

                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                }

            }
            //���ǽ���
            else
            {
                //����
                if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //Ԫ��
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"Ԫ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //��Ϧ
                if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"��Ϧ");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //����
                if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //����
                if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //С��
                if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"С��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //Ԫ��
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"Ԫ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //����
                if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //�Ͷ���
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"�Ͷ�");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //�����
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"����");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                // ʥ��
                if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"ʥ��");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                   SetTextColor(hDC,RGB(105, 105, 105));
                   continue;
                }

                else
                {


                    if(pLunarDay.nDay == 1 || pLunarDay.nDay == 0)
                    {
                        SetTextColor(hDC,RGB(30, 144, 255));
                        if(pLunarDay.nMonth == 0)
                        {
                            wsprintf(stDate,"����");
                        }
                        else
                        {
                            wsprintf(stDate,"%s��",ChMonthTable[pLunarDay.nMonth]);
                        }
                        DrawText (hDC,stDate, -1,
                                  &rc,DT_SINGLELINE | DT_CENTER);
                        SetTextColor(hDC,RGB(105, 105, 105));
                    }
                    else
                    {
                        wsprintf(stDate,"%s",ChDayTable[pLunarDay.nDay]);
                        DrawText (hDC,stDate, -1,
                                  &rc,DT_SINGLELINE | DT_CENTER);
                    }
                }
            }
        }
        iWeek++;

    }





}

//�¼�������������������ϸ�����ť�󱻵���,ѧԱ�Լ�ʵ�ָú���
//ע�⣺�ú����������ϵͳ�Զ�����DrawCalendar����
//      ��ˣ��������Ϊ���ú�����DrawCalendar������������
void CalendarButtonEvent(UINT nID)     //ѧ����Ҫ�޸Ĵ˺���
{
    SYSTEMTIME datetime;
    switch (nID)
    {
    case IDC_BTN_YEARUP://�����"���"��ť
        nCurrentYear++;
        break;
    case IDC_BTN_YEARDOWN:
        nCurrentYear--;
        break;
    case IDC_BTN_MONTHUP:
        
        
        nCurrentMonth++;
        if(nCurrentMonth>12)
        {
            nCurrentYear++;
            nCurrentMonth %= 12;
        }
        GetLocalTime(&datetime);
        if(nCurrentMonth != datetime.wMonth)
        {
            nCurrentDay = 1;
        }
        else
        {
            nCurrentDay = datetime.wDay;
        }
        break;
    case IDC_BTN_MONTHDOWN:
        nCurrentMonth--;
        if(nCurrentMonth<1)
        {
            nCurrentYear--;
            nCurrentMonth += 12;
        }
        GetLocalTime(&datetime);
        if(nCurrentMonth != datetime.wMonth)
        {
            nCurrentDay = 1;
        }
        else
        {
            nCurrentDay = datetime.wDay;
        }
        break;
    case IDC_BTN_TODAY:
        GetLocalTime(&datetime);
        nCurrentYear = datetime.wYear;
        nCurrentMonth = datetime.wMonth;
        nCurrentDay = datetime.wDay;
        break;
    }

}

void DrawClockText(HDC hDC)
{
    HFONT hFont;

    SYSTEMTIME datetime;
    int i;
    stDateTime sundate,lunardate;
    char stTime[9],stDate[11];
    int xPos,yPos;

    GetLocalTime(&datetime);


    sundate.nDay=datetime.wDay;
    sundate.nMonth = datetime.wMonth;
    sundate.nYear = datetime.wYear;
    SunToLunar(&sundate,&lunardate);

    if(datetime.wHour > 9)
    {
        if(datetime.wMinute > 9)
        {
            if(datetime.wSecond > 9)
            {
                wsprintf(stTime,"%2d:%2d:%2d",datetime.wHour,datetime.wMinute,datetime.wSecond);

            }
            else
            {
                wsprintf(stTime,"%2d:%2d:0%d",datetime.wHour,datetime.wMinute,datetime.wSecond);
            }
        }
        else
        {
            if(datetime.wSecond > 9)
            {
                wsprintf(stTime,"%2d:0%d:%2d",datetime.wHour,datetime.wMinute,datetime.wSecond);

            }
            else
            {
                wsprintf(stTime,"%2d:0%d:0%d",datetime.wHour,datetime.wMinute,datetime.wSecond);
            }
        }
    }
    else
    {
        if(datetime.wMinute > 9)
        {
            if(datetime.wSecond > 9)
            {
                wsprintf(stTime,"0%d:%2d:%2d",datetime.wHour,datetime.wMinute,datetime.wSecond);

            }
            else
            {
                wsprintf(stTime,"0%d:%2d:0%d",datetime.wHour,datetime.wMinute,datetime.wSecond);
            }
        }
        else
        {
            if(datetime.wSecond > 9)
            {
                wsprintf(stTime,"0%d:0%d:%2d",datetime.wHour,datetime.wMinute,datetime.wSecond);

            }
            else
            {
                wsprintf(stTime,"0%d:0%d:0%d",datetime.wHour,datetime.wMinute,datetime.wSecond);
            }
        }

    }


    i = lunardate.nMonth;
    xPos = 40;
    yPos = 30;

    //���ʱ��
    TextOut(hDC,34,70,stTime,8);
    wsprintf(stDate," %s��%s",ChMonthTable[i],ChDayTable[lunardate.nDay]);

    //�����������
    TextOut(hDC,28,50,stDate,9);

    hFont=CreateFont(
              10,      //������߼��߶�
              7.5,      //�߼�ƽ���ַ����
              0,           //��ˮƽ�ߵĽǶ�
              0,           //���߷�λ�Ƕ�
              FW_REGULAR,  //���Σ�����
              FALSE,       //���Σ�б��
              FALSE,       //���Σ��»���
              FALSE,       //���Σ�����
              GB2312_CHARSET,          //�ַ���
              OUT_DEFAULT_PRECIS,      //�������
              CLIP_DEFAULT_PRECIS,     //���ؾ���
              PROOF_QUALITY,           //���Ʒ��
              FIXED_PITCH | FF_MODERN, //��б��
              "Բ��"                   //����
          );
    SelectObject(hDC,hFont);

    //�����֧��
    wsprintf(stDate," %s%s��",GetGanZhi(datetime.wYear),
             GetShengXiao(datetime.wYear));
    TextOut(hDC,xPos-10,yPos+4,stDate,10);

    //�������
    wsprintf(stDate,"����%s",GetWeekDay(&sundate));
    TextOut(hDC,43,90,stDate,6);

    hFont=CreateFont(
              12,      //������߼��߶�
              9,      //�߼�ƽ���ַ����
              300,           //��ˮƽ�ߵĽǶ�
              45,           //���߷�λ�Ƕ�
              FW_REGULAR,  //���Σ�����
              FALSE,       //���Σ�б��
              FALSE,       //���Σ��»���
              FALSE,       //���Σ�����
              GB2312_CHARSET,          //�ַ���
              OUT_DEFAULT_PRECIS,      //�������
              CLIP_DEFAULT_PRECIS,     //���ؾ���
              PROOF_QUALITY,           //���Ʒ��
              FIXED_PITCH | FF_MODERN, //��б��
              "Բ��"                   //����
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%4d",datetime.wYear);
    TextOut(hDC,15,29,stTime,4);
    hFont=CreateFont(
              12,      //������߼��߶�
              9,      //�߼�ƽ���ַ����
              -120,           //��ˮƽ�ߵĽǶ�
              -90,           //���߷�λ�Ƕ�
              FW_REGULAR,  //���Σ�����
              FALSE,       //���Σ�б��
              FALSE,       //���Σ��»���
              FALSE,       //���Σ�����
              GB2312_CHARSET,          //�ַ���
              OUT_DEFAULT_PRECIS,      //�������
              CLIP_DEFAULT_PRECIS,     //���ؾ���
              PROOF_QUALITY,           //���Ʒ��
              FIXED_PITCH | FF_MODERN, //��б��
              "Բ��"                   //����
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%2d",datetime.wMonth);
    TextOut(hDC,65,9,stTime,2);

    hFont=CreateFont(
              12,      //������߼��߶�
              9,      //�߼�ƽ���ַ����
              -360,           //��ˮƽ�ߵĽǶ�
              -90,           //���߷�λ�Ƕ�
              FW_REGULAR,  //���Σ�����
              FALSE,       //���Σ�б��
              FALSE,       //���Σ��»���
              FALSE,       //���Σ�����
              GB2312_CHARSET,          //�ַ���
              OUT_DEFAULT_PRECIS,      //�������
              CLIP_DEFAULT_PRECIS,     //���ؾ���
              PROOF_QUALITY,           //���Ʒ��
              FIXED_PITCH | FF_MODERN, //��б��
              "Բ��"                   //����
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%2d",datetime.wDay);
    TextOut(hDC,91,18,stTime,2);

}

