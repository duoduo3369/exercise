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
API函数参考：
GetLocalTime: 获得当前时间(公历：年、月、日、周)
MoveToEx:     移动划线的起点
LineTo:       绘制到某一点
SetTextColor: 设置要绘制的文字颜色
TextOut:      绘制文字
SetBkMode:   设置背景显示模式
wsprintf:    整数转换为字符串，宽字符，用Unicode码
GetClientRect:  获取窗口大小
GetDC:   获取内存设备
SetTimer:  设置定时器
FillRect:  填充矩形
CreateSolidBrush:  创建刷子
RGB:   设置RGB颜色
CreateFont:创建一种有特殊性的字体
结构体类型参考：
SYSTEMTIME:   描述时间类型，包括年月日、时分秒、周
*********************************************************
*/

HINSTANCE g_hInst;//保存操作系统传递进来的"应用程序实例句柄"

//Windows程序入口函数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nShowCmd )
{
    g_hInst = hInstance;
    SetDlgMenuID(IDD_DLG_CLOCK,IDD_DLG_CALENDAR,IDR_MENU);
    SetButtonID(ID_CALENDAR,ID_EXIT,ID_40007,ID_40009,ID_40010);
    ShowMainDlg(IDD_DLG_CLOCK);
}



//定义用户要显示的年、月、日
unsigned int nCurrentYear=0;
unsigned int nCurrentMonth=0;
unsigned int nCurrentDay=0;


//判断某年是否为公历闰年
int IsLeapYear(WORD iYear)    //学生需要修改此函数
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

//公历日期转农历日期的函数
void SunToLunar(const stDateTime* pSunDay,stDateTime* pLunarDay)
{
    int i=0;
    int SunDiff=0;
    int SpringDiff=0;

    int nSpringYear=pSunDay->nYear;
    int nSpringMonth=1;
    int nSpringDay=0;

    //计算当前公历日离当年元旦的天数
    SunDiff = MonthAdd[pSunDay->nMonth-1] + pSunDay->nDay - 1;
    if(IsLeapYear(pSunDay->nYear) && (pSunDay->nMonth > 2) )//若是瑞年且大于2月，天数再加1
        SunDiff++;

    //计算春节所在公历日离元旦的天数：通过查表，计算当年的春节所在的公历日期，
    if(((LunarCalendarTable[pSunDay->nYear - 1901] & 0x60)>>5)==1)//若春节在公历1月
        SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1;
    else//若春节在公历2月
        SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1+31;

    //SunDiff和SpringDiff的差就是当前公历日离春节的天数

    if(SunDiff>=SpringDiff)//公历日在春节后
    {
        int x = SunDiff - SpringDiff;
        int bLunar = (LunarCalendarTable[nSpringYear - 1901] & 0xF00000)>>20;//闰月月份

        i=0;
        nSpringMonth=1;

        for(;;)
        {
            int a = (LunarCalendarTable[pSunDay->nYear-1901] & (0x80000>>i));//计算大小月
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
        //如果有闰月
        if(nSpringMonth>bLunar && bLunar>0)
            nSpringMonth--;
    }
    else//公历日在春节前
    {

        int x = SpringDiff-SunDiff;
        int nShift=0;

        int bLunar = (LunarCalendarTable[nSpringYear - 1901] & 0xF00000)>>20;//闰月月份

        i=0;
        nSpringYear--;//需要上一年的农历信息
        nSpringMonth=12;//从最后一个月开始计算

        if (bLunar == 0)//如果没有润月
            nShift = 0x100;
        else
            nShift = 0x80;

        for(;;)
        {
            int a = (LunarCalendarTable[nSpringYear-1901] & (nShift<<i));//计算大小月
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
//根据公历日期获得星期
int GetDayOfWeek(const stDateTime* pSunDay)
{
    //根据泰勒公式
    //nWeek = [nYear1÷4] - 2*nYear1 + nYear2 + [nYear2÷4] + [26(nMonth+1)÷10] + nDay - 1
    int nWeek=0;
    int nYear1=pSunDay->nYear/100;//年的前两位数字
    int nYear2=pSunDay->nYear%100;//年的后两位数字
    int nDay=pSunDay->nDay;  //公立日

    int nMonth=pSunDay->nMonth;//公立月数，所求的月份如果是1月或2月，
    //则应视为上一年的13月或14月，
    //也就是公式中nMonth的取值范围是从3到14而不是从1到12

    if(nMonth==1 || nMonth==2)
    {
        nMonth=12+nMonth;
        nYear1=(pSunDay->nYear-1)/100;//年的前两位数字
        nYear2=(pSunDay->nYear-1)%100;//年的后两位数字
    }

    nWeek = nYear1/4 - 2*nYear1 + nYear2 + nYear2/4 + (26*(nMonth+1))/10 + nDay - 1;
    nWeek = (nWeek + 14) % 7;//有问题吗?

    return nWeek;
}
//根据公立年得到农历干支年
char* GetGanZhi(int nYear)
{
    return TianGanDizhi[(nYear-1984)%60];
}
char* GetWeekDay(const stDateTime* pSunDay)
{
    return XingQi[GetDayOfWeek(pSunDay)];
}

//日历绘制函数,学生自己实现该函数
void DrawCalendar(HDC hDC,int nWidth,int nHeight)
{
    HBRUSH hbrush;
    HBRUSH whitebrush,bluebrush,graywhitebrush,graybrush;
    RECT rc,rect,todayrc;
    HPEN hpen;
    HFONT hFont;
    HFONT hFont_big; // 日历中的大字体
    HFONT hFont_small; // 日历中的小字体
    HFONT hFont_today;// 显示今天的字体
    stDateTime pSunDay;//存储公历日期
    stDateTime pLunarDay;
    SYSTEMTIME datetime;// 存储当前时间
    int nWeek; // 某天是这一周的星期几
    int iWeek; // 某天是这月的第几周，第一周为0，最多6周，范围0~5
    int days; //这个月有多少天
    int day;//几号
    int xgap,ygap;
    int width,height,i,j;
    int posX,posY; //输出时的辅助下标变量
    char stDate[11];
    static TCHAR *DAYS[7] = {TEXT("日"),TEXT("一"),TEXT("二"),
                             TEXT("三"),TEXT("四"),TEXT("五"),TEXT("六")
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

    //描出最上面的蓝格子
    rc.top = 6;
    rc.bottom = rc.top + 60;
    rc.left = rect.left;
    rc.right = rect.right;
    FillRect(hDC,&rc,bluebrush);


    //描出白格子
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

    //画出下面的灰白格子
    rc.top = rect.bottom + 10;
    rc.bottom = rc.top + 60;
    rc.left = rect.left;
    rc.right = rect.right;
    FillRect(hDC,&rc,graywhitebrush);

    //画出下面的灰格子

    rc.top = rc.bottom;
    rc.bottom = rc.top + 90;
    FillRect(hDC,&rc,graybrush);



    //画出表盘线
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




    // 填写 日一二三四五六
    height -= 4;
    width = height / 2;
    hFont = CreateFont(
                height - 2,      //字体的逻辑高度
                width,       //逻辑平均字符宽度
                0,           //与水平线的角度
                0,           //基线方位角度
                FW_REGULAR,  //字形：常规
                FALSE,       //字形：斜体
                FALSE,       //字形：下划线
                FALSE,       //字形：粗体
                GB2312_CHARSET,          //字符集
                OUT_DEFAULT_PRECIS,      //输出精度
                CLIP_DEFAULT_PRECIS,     //剪截精度
                PROOF_QUALITY,           //输出品质
                FIXED_PITCH | FF_MODERN, //倾斜度
                "圆体"                   //字体
            );
    SelectObject(hDC,hFont);
    for(i = 0; i < 7; i++)
    {

        rc.left = rect.left + i*xgap;
        rc.right = rc.left + xgap;
        DrawText (hDC,DAYS[i], -1,
                  &rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }




    // 填写日历下面的新建事件
    height *= 1.1;
    width = height * 0.75;
    hFont_big = CreateFont(
                    height,      //字体的逻辑高度
                    width,       //逻辑平均字符宽度
                    0,           //与水平线的角度
                    0,           //基线方位角度
                    FW_REGULAR,  //字形：常规
                    FALSE,       //字形：斜体
                    FALSE,       //字形：下划线
                    FALSE,       //字形：粗体
                    GB2312_CHARSET,          //字符集
                    OUT_DEFAULT_PRECIS,      //输出精度
                    CLIP_DEFAULT_PRECIS,     //剪截精度
                    PROOF_QUALITY,           //输出品质
                    FIXED_PITCH | FF_MODERN, //倾斜度
                    "圆体"                   //字体
                );

    //DeleteObject(hBmp);
    SelectObject(hDC,hFont_big);
    SetTextColor(hDC,RGB(0,0,0));
    posX = rect.left+10;
    posY = rect.bottom+20;
    TextOut(hDC,posX,posY,"添加新事件",strlen("添加新事件"));
    height *= 0.8;
    width = height * 0.75;
    hFont_small = CreateFont(
                      height,      //字体的逻辑高度
                      width,       //逻辑平均字符宽度
                      0,           //与水平线的角度
                      0,           //基线方位角度
                      FW_REGULAR,  //字形：常规
                      FALSE,       //字形：斜体
                      FALSE,       //字形：下划线
                      FALSE,       //字形：粗体
                      GB2312_CHARSET,          //字符集
                      OUT_DEFAULT_PRECIS,      //输出精度
                      CLIP_DEFAULT_PRECIS,     //剪截精度
                      PROOF_QUALITY,           //输出品质
                      FIXED_PITCH | FF_MODERN, //倾斜度
                      "黑体"                   //字体
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

    //写最上面的年份和月份
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
    //写最上面的干支年

    wsprintf(stDate,"%s",GetGanZhi(nCurrentYear));
    TextOut(hDC,rect.right - 44,15,stDate,4);
    wsprintf(stDate,"%s年",GetShengXiao(nCurrentYear));
    TextOut(hDC,rect.right - 44,30,stDate,4);

    //画最上面的三条线
    hpen = CreatePen (PS_SOLID,3,RGB(255, 255, 255)) ;
    SelectObject(hDC,hpen);
    for(i = 0; i < 3; i++)
    {
        MoveToEx(hDC,rect.left + 7,20 + i * 8,NULL);
        LineTo(hDC,rect.left + 27,20 + i * 8);
    }

    hFont_today = CreateFont(
                      height,      //字体的逻辑高度
                      height * 0.80,       //逻辑平均字符宽度
                      0,           //与水平线的角度
                      0,           //基线方位角度
                      FW_REGULAR,  //字形：常规
                      FALSE,       //字形：斜体
                      FALSE,       //字形：下划线
                      FALSE,       //字形：粗体
                      GB2312_CHARSET,          //字符集
                      OUT_DEFAULT_PRECIS,      //输出精度
                      CLIP_DEFAULT_PRECIS,     //剪截精度
                      PROOF_QUALITY,           //输出品质
                      FIXED_PITCH | FF_MODERN, //倾斜度
                      "圆体"                   //字体
                  );


    //填写日历日期
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

    //阳历

    hbrush=CreateSolidBrush(RGB(224, 255, 255));
    SelectObject(hDC,hbrush);

    //第一行
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
            wsprintf(stDate,"今天");
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
    //这个月中剩下的行
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
                wsprintf(stDate,"今天");
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

    //阴历
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
        //恰好今天
        if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                && day == datetime.wDay)
        {
            //春节
            if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"春节");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //元宵
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"元宵");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //端午
            if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"端午");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //七夕
            if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"七夕");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //中秋
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"中秋");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //重阳
            if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"重阳");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //腊八
            if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"腊八");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //小年
            if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"小年");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //元旦
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"元旦");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //清明
            if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"清明");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //劳动节
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"劳动");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //国庆节
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"国庆");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            // 圣诞
            if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"圣诞");
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
                        wsprintf(stDate,"腊月");
                    }
                    wsprintf(stDate,"%s月",ChMonthTable[pLunarDay.nMonth]);
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
        //不是今天
        else
        {
            //春节
            if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"春节");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //元宵
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"元宵");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //端午
            if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"端午");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //七夕
            if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"七夕");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //中秋
            if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"中秋");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //重阳
            if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"重阳");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //腊八
            if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"腊八");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //小年
            if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"小年");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            //元旦
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"元旦");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //清明
            if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"清明");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //劳动节
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"劳动");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }

            //国庆节
            if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"国庆");
                DrawText (hDC,stDate, -1,
                          &rc,DT_SINGLELINE | DT_CENTER);
                SetTextColor(hDC,RGB(105, 105, 105));
                continue;
            }
            // 圣诞
            if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
            {
                SetTextColor(hDC,RGB(30, 144, 255));
                wsprintf(stDate,"圣诞");
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
                        wsprintf(stDate,"腊月");
                    }
                    else
                    {
                        wsprintf(stDate,"%s月",ChMonthTable[pLunarDay.nMonth]);
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
    //这个月中剩下的行
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
            //恰好今天
            if(nCurrentYear == datetime.wYear && nCurrentMonth == datetime.wMonth
                    && pSunDay.nDay == datetime.wDay)
            {
                //春节
                if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"春节");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //元宵
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"元宵");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //端午
                if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"端午");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //七夕
                if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"七夕");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //中秋
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"中秋");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //重阳
                if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"重阳");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //腊八
                if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"腊八");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //小年
                if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"小年");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //元旦
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"元旦");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //清明
                if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"清明");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //劳动节
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"劳动");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //国庆节
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"国庆");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                // 圣诞
                if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"圣诞");
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
                            wsprintf(stDate,"%s月",ChMonthTable[12]);
                        }
                        wsprintf(stDate,"%s月",ChMonthTable[pLunarDay.nMonth]);
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
            //不是今天
            else
            {
                //春节
                if(pLunarDay.nDay == 1 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"春节");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //元宵
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"元宵");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //端午
                if(pLunarDay.nDay == 5 && pLunarDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"端午");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //七夕
                if(pLunarDay.nDay == 7 && pLunarDay.nMonth == 7)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"七夕");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //中秋
                if(pLunarDay.nDay == 15 && pLunarDay.nMonth == 8)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"中秋");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //重阳
                if(pLunarDay.nDay == 9 && pLunarDay.nMonth == 9)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"重阳");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //腊八
                if(pLunarDay.nDay == 8 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"腊八");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //小年
                if(pLunarDay.nDay == 23 && pLunarDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"小年");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                //元旦
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 1)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"元旦");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //清明
                if(pSunDay.nDay == 5 && pSunDay.nMonth == 4)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"清明");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //劳动节
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 5)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"劳动");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }

                //国庆节
                if(pSunDay.nDay == 1 && pSunDay.nMonth == 10)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"国庆");
                    DrawText (hDC,stDate, -1,
                              &rc,DT_SINGLELINE | DT_CENTER);
                    SetTextColor(hDC,RGB(105, 105, 105));
                    continue;
                }
                // 圣诞
                if(pSunDay.nDay == 12 && pSunDay.nMonth == 12)
                {
                    SetTextColor(hDC,RGB(30, 144, 255));
                    wsprintf(stDate,"圣诞");
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
                            wsprintf(stDate,"腊月");
                        }
                        else
                        {
                            wsprintf(stDate,"%s月",ChMonthTable[pLunarDay.nMonth]);
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

//事件函数：点击日历界面上各个按钮后被调用,学员自己实现该函数
//注意：该函数调用完后，系统自动调用DrawCalendar函数
//      因此，可以理解为，该函数和DrawCalendar函数是联动的
void CalendarButtonEvent(UINT nID)     //学生需要修改此函数
{
    SYSTEMTIME datetime;
    switch (nID)
    {
    case IDC_BTN_YEARUP://点击了"年↑"按钮
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

    //输出时间
    TextOut(hDC,34,70,stTime,8);
    wsprintf(stDate," %s月%s",ChMonthTable[i],ChDayTable[lunardate.nDay]);

    //输出阴历日期
    TextOut(hDC,28,50,stDate,9);

    hFont=CreateFont(
              10,      //字体的逻辑高度
              7.5,      //逻辑平均字符宽度
              0,           //与水平线的角度
              0,           //基线方位角度
              FW_REGULAR,  //字形：常规
              FALSE,       //字形：斜体
              FALSE,       //字形：下划线
              FALSE,       //字形：粗体
              GB2312_CHARSET,          //字符集
              OUT_DEFAULT_PRECIS,      //输出精度
              CLIP_DEFAULT_PRECIS,     //剪截精度
              PROOF_QUALITY,           //输出品质
              FIXED_PITCH | FF_MODERN, //倾斜度
              "圆体"                   //字体
          );
    SelectObject(hDC,hFont);

    //输出干支年
    wsprintf(stDate," %s%s年",GetGanZhi(datetime.wYear),
             GetShengXiao(datetime.wYear));
    TextOut(hDC,xPos-10,yPos+4,stDate,10);

    //输出星期
    wsprintf(stDate,"星期%s",GetWeekDay(&sundate));
    TextOut(hDC,43,90,stDate,6);

    hFont=CreateFont(
              12,      //字体的逻辑高度
              9,      //逻辑平均字符宽度
              300,           //与水平线的角度
              45,           //基线方位角度
              FW_REGULAR,  //字形：常规
              FALSE,       //字形：斜体
              FALSE,       //字形：下划线
              FALSE,       //字形：粗体
              GB2312_CHARSET,          //字符集
              OUT_DEFAULT_PRECIS,      //输出精度
              CLIP_DEFAULT_PRECIS,     //剪截精度
              PROOF_QUALITY,           //输出品质
              FIXED_PITCH | FF_MODERN, //倾斜度
              "圆体"                   //字体
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%4d",datetime.wYear);
    TextOut(hDC,15,29,stTime,4);
    hFont=CreateFont(
              12,      //字体的逻辑高度
              9,      //逻辑平均字符宽度
              -120,           //与水平线的角度
              -90,           //基线方位角度
              FW_REGULAR,  //字形：常规
              FALSE,       //字形：斜体
              FALSE,       //字形：下划线
              FALSE,       //字形：粗体
              GB2312_CHARSET,          //字符集
              OUT_DEFAULT_PRECIS,      //输出精度
              CLIP_DEFAULT_PRECIS,     //剪截精度
              PROOF_QUALITY,           //输出品质
              FIXED_PITCH | FF_MODERN, //倾斜度
              "圆体"                   //字体
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%2d",datetime.wMonth);
    TextOut(hDC,65,9,stTime,2);

    hFont=CreateFont(
              12,      //字体的逻辑高度
              9,      //逻辑平均字符宽度
              -360,           //与水平线的角度
              -90,           //基线方位角度
              FW_REGULAR,  //字形：常规
              FALSE,       //字形：斜体
              FALSE,       //字形：下划线
              FALSE,       //字形：粗体
              GB2312_CHARSET,          //字符集
              OUT_DEFAULT_PRECIS,      //输出精度
              CLIP_DEFAULT_PRECIS,     //剪截精度
              PROOF_QUALITY,           //输出品质
              FIXED_PITCH | FF_MODERN, //倾斜度
              "圆体"                   //字体
          );
    SelectObject(hDC,hFont);
    wsprintf(stTime,"%2d",datetime.wDay);
    TextOut(hDC,91,18,stTime,2);

}

