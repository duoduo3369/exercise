// PlaneView.cpp : CPlaneView 类的实现
//

#include "stdafx.h"
#include "public.h"
#include <cmath>
#include "PlaneView.h"

using namespace std;
//#include "GameObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CPlaneView

IMPLEMENT_DYNCREATE(CPlaneView, CView)

BEGIN_MESSAGE_MAP(CPlaneView, CView)
    //    ON_WM_LBUTTONDOWN()
    //    ON_WM_RBUTTONDOWN()
    //    ON_WM_KEYDOWN()
    //    ON_WM_TIMER()
    //    ON_WM_DESTROY()
    //ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    //ON_WM_ERASEBKGND()
    ON_WM_ERASEBKGND()
    //    ON_WM_KEYDOWN()
    ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPlaneView 构造/析构

CPlaneView::CPlaneView()
    : pdc(NULL)
    , m_pMemDC(NULL)
    , m_pMemBitmap(NULL)
    , m_pOldBitmap(NULL)
    , count_sepcial(0)
{

}

CPlaneView::~CPlaneView()
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
    {
        delete *it;
    }
}

BOOL CPlaneView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CPlaneView 绘制

void CPlaneView::OnDraw(CDC* pDC)
{

}


// CPlaneView 诊断

#ifdef _DEBUG
void CPlaneView::AssertValid() const
{
    CView::AssertValid();
}

void CPlaneView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CPlaneDoc* CPlaneView::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneDoc)));
    return (CPlaneDoc*)m_pDocument;
}
#endif //_DEBUG



void CPlaneView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
    {
        return;
    }

    CEnemy *enemy =new CEnemy(point);

    pDoc->enemyArray.push_back(enemy);
    CRect enemyRect =  enemy->GetRect();


    CView::OnLButtonDown(nFlags, point);
}
BOOL DrawSpecial(CDC* pDC,CPoint point,int width,int height,BOOL bPause,UINT nIDResource);
void CPlaneView::OnTimer(UINT_PTR nIDEvent)
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if (!pDoc)
    {
        return;
    }
    CRect rect;
    GetClientRect(&rect);
    switch(nIDEvent)
    {
    case TIMER_DRAW:
    {


        CDC MemDC;
        //定义一个位图对象
        CBitmap MemBitmap;
        //建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）
        MemDC.CreateCompatibleDC(pdc);
        //这时还不能绘图，因为没有位图的设备描述表是不能绘图的
        //下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图
        MemBitmap.CreateCompatibleBitmap(pdc,rect.Width(),rect.Height());
        //将位图选入到内存设备描述表
        //只有选入了位图的设备描述表才有地方绘图，画到指定的位图上
        CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
        //先用背景色将位图清除干净，这里我用的是白色作为背景
        //你也可以用自己应该用的颜色
        MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));
        //绘图


        //背景
        pDoc->game.DrawBackGround(&MemDC,FALSE);
        
        
        //文字
        CString life,grade,level;
        life.Format(_T("生命: %3i"),pDoc->myPlane->GetLife());
        grade.Format(_T("分数: %4i"),pDoc->game.GetGrade());
        level.Format(_T("等级: %3i"),pDoc->game.level);
        pDoc->outText[STRING_LIFE].SetString(life);
        pDoc->outText[STRING_GRADE].SetString(grade);
        pDoc->outText[STRING_LEVEL].SetString(level);
        
        pDoc->outText[STRING_LIFE].Draw(&MemDC,FALSE);
        pDoc->outText[STRING_GRADE].Draw(&MemDC,FALSE);
        pDoc->outText[STRING_LEVEL].Draw(&MemDC,FALSE);
        if(!pDoc->myPlane->IsAlive())
        {
            CString gameOver("右键可立即啃桃复活");
            pDoc->outText[STRING_GAME_OVER].SetString(gameOver);
            pDoc->outText[STRING_GAME_OVER].Draw(&MemDC,FALSE);
        }
        if(pDoc->myPlane->IsSuperBombAvilible())
        {
            CString arrow("万箭齐发可用");
            pDoc->outText[STRING_ARROW].SetString(arrow);
            pDoc->outText[STRING_ARROW].Draw(&MemDC,FALSE);

        }
        
         //特殊物体
        for(deque<CTool*>::iterator it = pDoc->toolArray.begin(); it != pDoc->toolArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
        }

        //超级炸弹效果
        if(pDoc->myPlane->IsSuperBombFired())
        {
            DrawSpecial(&MemDC,CPoint(rect.Width()/2-100,rect.Height()/2-145),200,290,TRUE,IDB_ARCHERY_BIG);
        }

        //敌人飞机
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
        }


        //我方飞机
        pDoc->myPlane->Draw(&MemDC,FALSE);

        //导弹
        for(deque<CBomb*>::iterator it = pDoc->bombArray.begin(); it != pDoc->bombArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
        }

        
        //敌机子弹
        for(deque<CBall*>::iterator it = pDoc->ballArray.begin(); it != pDoc->ballArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
        }
        //爆炸

        for(deque<CExplosion*>::iterator it = pDoc->explosionArray.begin(); it != pDoc->explosionArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
            if((*it)->IsDrawDone())
            {
                (*it)->Invalidate();
            }

        }
        
        pdc->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
        MemDC.SelectObject(pOldBit);
        MemBitmap.DeleteObject();
        MemDC.DeleteDC();
        break;
       
    }
    case TIMER_MOVE_10://飞机移动
    {


        //敌方飞机
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            pDoc->game.AI(*(*it),(*pDoc->myPlane));
            (*it)->Move();
        }

        //导弹
        for(deque<CBomb*>::iterator it = pDoc->bombArray.begin(); it != pDoc->bombArray.end(); ++it)
        {
            (*it)->Move();
        }

        //地方子弹
        for(deque<CBall*>::iterator it = pDoc->ballArray.begin(); it != pDoc->ballArray.end(); ++it)
        {
            (*it)->Move();
        }
        //特殊物品
        for(deque<CTool*>::iterator it = pDoc->toolArray.begin(); it != pDoc->toolArray.end(); ++it)
        {
            (*it)->Move();
        }

        //我方飞机
        CPoint point = pDoc->myPlane->GetPoint();
        if(GetKeyState(VK_UP)<0)
        {

            if(point.y - pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_HEIGHT / 2 > 0)
            {
                pDoc->myPlane->SetVerMotion(UP_MOVE);
                pDoc->myPlane->VerMove();
            }
            else
            {
                pDoc->myPlane->SetVerMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_DOWN)<0)
        {
            if(point.y + pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_HEIGHT / 2< rect.bottom)
            {
                pDoc->myPlane->SetVerMotion(DOWN_MOVE);
                pDoc->myPlane->VerMove();
            }
            else
            {
                pDoc->myPlane->SetVerMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_LEFT)<0)
        {
            if(point.x - pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_WIDTH / 2 > 0)
            {
                pDoc->myPlane->SetHorMotion(LEFT_MOVE);
                pDoc->myPlane->HorMove();
            }
            else
            {
                pDoc->myPlane->SetHorMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_RIGHT)<0)
        {
            if(point.x + pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_WIDTH / 2 < rect.right)
            {
                pDoc->myPlane->SetHorMotion(RIGHT_MOVE);
                pDoc->myPlane->HorMove();
            }
            else
            {
                pDoc->myPlane->SetHorMotion(STATIC_MOVE);
            }
        }



        break;
    }
    case TIMER_20:
    {
        //是否升级
        if(pDoc->game.IsLevelUp())
        {
            pDoc->game.LevelUp();           
            pDoc->myPlane->IncreaseLife();
        }
        //敌方飞机AI
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            pDoc->game.AI(*(*it),(*pDoc->myPlane));
        }
        //测试用 加1级 小键盘的'+'和'0'同时按下
        if(GetKeyState(VK_ADD)<0 && GetKeyState(VK_NUMPAD0)<0)
        {
            pDoc->game.LevelUp();
            
        }
        //测试用 加100条生命 小键盘的'+'和'1'同时按下
        if(GetKeyState(VK_ADD)<0 && GetKeyState(VK_NUMPAD1)<0)
        {
            pDoc->myPlane->IncreaseLotsLife();
        }
        //导弹子弹发射
        if(GetKeyState(VK_SPACE)<0)
        {
            if(pDoc->bombArray.size() <= 40 && pDoc->myPlane->IsAlive())
            {

                CBomb *bomb_up_left = new CBomb(pDoc->myPlane->bomb[BOMB_UP_LEFT]);
                CBomb *bomb_up_right = new CBomb(pDoc->myPlane->bomb[BOMB_UP_RIGHT]);
                
                pDoc->bombArray.push_back(bomb_up_left);
                pDoc->bombArray.push_back(bomb_up_right);

                if(pDoc->myPlane->isBombUped)
                //少加两发子弹 多加会卡
                //if(TRUE)
                {
                CBomb *bomb_left = new CBomb(pDoc->myPlane->bomb[BOMB_LEFT]);
                CBomb *bomb_right = new CBomb(pDoc->myPlane->bomb[BOMB_RIGHT]);
                //CBomb *bomb_mid_left = new CBomb(pDoc->myPlane->bomb[BOMB_MID_LEFT]);
                //CBomb *bomb_mid_right = new CBomb(pDoc->myPlane->bomb[BOMB_MID_RIGHT]);
                CBomb *bomb_ball_left = new CBomb(pDoc->myPlane->bomb[BOMB_BALL_LEFT]);
                CBomb *bomb_ball_right = new CBomb(pDoc->myPlane->bomb[BOMB_BALL_RIGHT]);
                pDoc->bombArray.push_back(bomb_left);
                pDoc->bombArray.push_back(bomb_right);
                //pDoc->bombArray.push_back(bomb_mid_left);
                //pDoc->bombArray.push_back(bomb_mid_right);
                pDoc->bombArray.push_back(bomb_ball_left);
                pDoc->bombArray.push_back(bomb_ball_right);

                }

            }
        }

        //生成敌机子弹对象
        CRect enemyRect,myRect;
        if(pDoc->ballArray.size() <= BALL_ARRAY_LIMIT)
        {
            myRect = pDoc->myPlane->GetRect();
            for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); it++)
            {
                enemyRect = (*it)->GetRect();
                if(enemyRect.left > myRect.left - enemyRect.Width() && enemyRect.right < myRect.right + enemyRect.Width())
                {

                    CBall *ball_front = &(*it)->ball[BALL_FRONT];
                    CBall *ball = new CBall(ball_front->GetPoint(),ball_front->GetV(),ball_front->GetMotion());
                    pDoc->ballArray.push_back(ball);
                    if(pDoc->ballArray.size() > BALL_ARRAY_LIMIT)
                    {
                        break;
                    }
                }
            }
        }

        break;
    }

    case TIMER_EXPLORE_50://处理碰撞 碰撞后有爆炸和得分
    {

        GetClientRect(&rect);

        //我机和敌机
        CRect my = pDoc->myPlane->GetRect();
        CRect temp;
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); it++)
        {
            CRect enemy = (*it)->GetRect();
            if(!temp.IntersectRect(enemy,rect))
            {
                continue;
            }
            if(temp.IntersectRect(my,enemy))
            {
                CPoint enemyPoint = (*it)->GetPoint();
                CExplosion* exp = new CExplosion(enemyPoint.x,enemyPoint.y);
                pDoc->explosionArray.push_back(exp);
                (*it)->Invalidate();
                pDoc->myPlane->DecreaseLife();
                pDoc->game.UpGrade(GRADE_ENEMY);
                if(!pDoc->myPlane->IsAlive())
                {
                    pDoc->myPlane->Invalidate();
                }
            }
        }

        //导弹和敌机
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); it++)
        {
            CRect enemy = (*it)->GetRect();
            /*
                        if(pDoc->game.IsGameObjectValidate(enemy,rect))
                        {
               continue;
                        }
                        // */
            for(deque<CBomb*>::iterator it_bomb = pDoc->bombArray.begin(); it_bomb != pDoc->bombArray.end(); ++it_bomb)
            {
                CRect bomb = (*it_bomb)->GetRect();
                ///*
                if(!temp.IntersectRect(bomb,rect))
                {
                    continue;
                }
                //*/
                if(temp.IntersectRect(bomb,enemy))
                {
                    CPoint enemyPoint = (*it)->GetPoint();
                    CExplosion* exp = new CExplosion(enemyPoint.x,enemyPoint.y);
                    pDoc->explosionArray.push_back(exp);
                    (*it)->Invalidate();
                    (*it_bomb)->Invalidate();
                    pDoc->game.UpGrade(GRADE_ENEMY);
                }
            }


        }
        //我机和敌机子弹
        for(deque<CBall*>::iterator it = pDoc->ballArray.begin(); it != pDoc->ballArray.end(); it++)
        {
            CRect ball = (*it)->GetRect();
            if(!temp.IntersectRect(ball,rect))
            {
                continue;
            }
            if(temp.IntersectRect(ball,my))
            {
                CPoint ballPoint = (*it)->GetPoint();
                CExplosion* exp = new CExplosion(ballPoint.x,ballPoint.y);
                pDoc->explosionArray.push_back(exp);
                (*it)->Invalidate();
                pDoc->myPlane->DecreaseLife();
                if(!pDoc->myPlane->IsAlive())
                {
                    pDoc->myPlane->Invalidate();
                }
            }
        }
        //我机子弹和敌机子弹
        for(deque<CBall*>::iterator it_ball = pDoc->ballArray.begin(); it_ball != pDoc->ballArray.end(); it_ball++)
        {
            CRect ball = (*it_ball)->GetRect();
            for(deque<CBomb*>::iterator it_bomb = pDoc->bombArray.begin(); it_bomb != pDoc->bombArray.end(); ++it_bomb)
            {
                CRect bomb = (*it_bomb)->GetRect();
                ///*
                if(!temp.IntersectRect(bomb,ball))
                {
                    continue;
                }
                //*/
                if(temp.IntersectRect(bomb,ball))
                {
                    CPoint ballPoint = (*it_ball)->GetPoint();
                    CExplosion* exp = new CExplosion(ballPoint.x,ballPoint.y);
                    pDoc->explosionArray.push_back(exp);
                    (*it_ball)->Invalidate();
                    (*it_bomb)->Invalidate();
                    pDoc->game.UpGrade(GRADE_BALL);
                }

            }
        }
        //我机与特殊物品
        for(deque<CTool*>::iterator it = pDoc->toolArray.begin(); it != pDoc->toolArray.end(); it++)
        {
            CRect tool = (*it)->GetRect();
            if(!temp.IntersectRect(tool,rect))
            {
                continue;
            }
            if(temp.IntersectRect(my,tool))
            {
                //(*it)->Invalidate();
                (*it)->isVisible = FALSE;
                (*it)->SetActive(TRUE);
                (*it)->Do(*pDoc->myPlane);

            }
        }
        //清屏
        if(GetKeyState(90)<0)
        {
            if(pDoc->myPlane->IsSuperBombAvilible())
            {
                pDoc->myPlane->SetSuperBombFired(TRUE);
                pDoc->myPlane->SetSuperBomb(FALSE);                
                for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); it++)
                {
                    CPoint enemyPoint = (*it)->GetPoint();
                    CExplosion* exp = new CExplosion(enemyPoint.x,enemyPoint.y);
                    pDoc->explosionArray.push_back(exp);
                    pDoc->game.UpGrade(GRADE_ENEMY);
                    (*it)->Invalidate();
                }
                for(deque<CBall*>::iterator it = pDoc->ballArray.begin(); it != pDoc->ballArray.end(); it++)
                {
                    CPoint ballPoint = (*it)->GetPoint();
                    CExplosion* exp = new CExplosion(ballPoint.x,ballPoint.y);
                    pDoc->explosionArray.push_back(exp);
                    pDoc->game.UpGrade(GRADE_BALL);
                    (*it)->Invalidate();
                }
            }
        }
        break;
    }
    case TIMER_NEWENEMY_1000: //生成敌机
    {
        int max_x = RAND_MAX;
        int min_x = 0;  
        int rand_x,rand_y;
        if(pDoc->enemyArray.size() < pDoc->game.GetEnemyLimits())
        {
            rand_x = Util::GetRand(0,rect.Width()+50000);
            rand_y = Util::GetRand(0,10);
            CPoint point(rand_x,rand_y);
            CEnemy *enemy =new CEnemy(point);
            pDoc->enemyArray.push_back(enemy);
            rand_x = Util::GetRand(0,rect.Width());
            rand_y = Util::GetRand(0,7);
            CPoint point_2(rand_x,rand_y);
            CEnemy *enemy_2 =new CEnemy(point_2);
            pDoc->enemyArray.push_back(enemy_2);


            
            rand_x = Util::GetRand(0,rect.Width()+100000);
            rand_y = Util::GetRand(0,3);
            CPoint point_3(rand_x,rand_y);
            CEnemy *enemy_3 =new CEnemy(point_3);
            pDoc->enemyArray.push_back(enemy_3);
            
            
        }
            
        
        break;
    }
    case TIMER_2000:
    {
            //特殊效果显示时间
        pDoc->myPlane->SetSuperBombFired(FALSE);
        break;
    }
    case TIMER_FREE:
    {
        
        unsigned int many = 0;

        //销毁飞出屏幕的敌机

        int gap = 75;

        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            CRect enemyRect = (*it)->GetRect();
            if(pDoc->game.IsGameObjectValidate(enemyRect,rect))
            {
                many++;
            }
            else
            {
                break;
            }
        }

        while(many--)
        {
            if(pDoc->enemyArray.empty())
            {
                break;
            }
            CEnemy* enemy = pDoc->enemyArray.front();
            pDoc->enemyArray.pop_front();
            delete enemy;
        }

        //销毁飞出屏幕的炸弹
        many = 0;
        GetClientRect(&rect);
        for(deque<CBomb*>::iterator it = pDoc->bombArray.begin(); it != pDoc->bombArray.end(); ++it)
        {
            CRect bombRect = (*it)->GetRect();
            if(pDoc->game.IsGameObjectValidate(bombRect,rect))
            {
                many++;
            }
            else
            {
                break;
            }
        }
        while(many--)
        {
            if(pDoc->bombArray.empty())
            {
                break;
            }
            CBomb* bomb = pDoc->bombArray.front();
            pDoc->bombArray.pop_front();
            delete bomb;
        }
//*/
        //销毁飞出屏幕的地方子弹
        many = 0;
        for(deque<CBall*>::iterator it = pDoc->ballArray.begin(); it != pDoc->ballArray.end(); ++it)
        {
            CRect ballRect = (*it)->GetRect();
            if(pDoc->game.IsGameObjectValidate(ballRect,rect))
            {
                many++;
            }
            else
            {
                break;
            }
        }
        while(many--)
        {
            if(pDoc->ballArray.empty())
            {
                break;
            }
            CBall* ball = pDoc->ballArray.front();
            pDoc->ballArray.pop_front();
            delete ball;
        }
        //销毁特殊物品
        many = 0;
        for(deque<CTool*>::iterator it = pDoc->toolArray.begin(); it != pDoc->toolArray.end(); it++)
        {
            CRect tool = (*it)->GetRect();
            if(pDoc->game.IsGameObjectValidate(tool,rect))
            {
                many++;
            }
            else
            {
                break;
            }
        }
        while(many--)
        {
            if(pDoc->toolArray.empty())
            {
                break;
            }
            CTool* tool = pDoc->toolArray.front();
            pDoc->toolArray.pop_front();
            delete tool;
        }
        //销毁爆炸
        many = 0;
        for(deque<CExplosion*>::iterator it = pDoc->explosionArray.begin(); it != pDoc->explosionArray.end(); ++it)
        {
            CRect expRect = (*it)->GetRect();
            if(pDoc->game.IsGameObjectValidate(expRect,rect))
            {
                many++;
            }
            else
            {
                break;
            }
        }
        while(many--)
        {
            if(pDoc->explosionArray.empty())
            {
                break;
            }
            CExplosion* exp = pDoc->explosionArray.front();
            pDoc->explosionArray.pop_front();
            delete exp;
        }

    }
    case TIMER_SP_LIFE_10000://生成特殊物品
    {
        int max_x = RAND_MAX;
        int min_x = 0;
        count_sepcial++;
        count_sepcial = (count_sepcial % 200);
        switch(count_sepcial)
        {
        case 100:
            {
                //撤销掉升级炸弹
                pDoc->myPlane->isBombUped = FALSE;
                break;
            }
        case 20:
        case 90:  
        case 160:
            //生命
        {
            if(pDoc->toolArray.size() < pDoc->game.GetSpecialSize())
            {
                int rand_x = Util::GetRand(0,rect.Width());
                CPoint point(rand_x,10);
                CTool *tool =new CToolLife(point);
                pDoc->toolArray.push_back(tool);
            }
            break;
        }
        //子弹升级
        case 10:
        case 180:
            {
                if(pDoc->toolArray.size() < pDoc->game.GetSpecialSize())
            {
                int rand_x = Util::GetRand(0,rect.Width());
                CPoint point(rand_x,10);
                CTool *tool =new CToolUpBombSize(point);
                pDoc->toolArray.push_back(tool);
            }
                break;
            }
        //我方飞机加速
        case 70:
            {
            if(pDoc->toolArray.size() < pDoc->game.GetSpecialSize())
            {
                int rand_x = Util::GetRand(0,rect.Width());
                CPoint point(rand_x,10);
                CTool *tool =new CToolSpeedUp(point);
                pDoc->toolArray.push_back(tool);
            }
                break;
            }
        //我方飞机减速
        case 170:
            {
            if(pDoc->toolArray.size() < pDoc->game.GetSpecialSize())
            {
                int rand_x = Util::GetRand(0,rect.Width());
                CPoint point(rand_x,10);
                CTool *tool =new CToolSpeedDown(point);
                pDoc->toolArray.push_back(tool);
            }
                break;
            }

        //超级炸弹
        case 40:
        case 101:
        case 140:
        {            
            if(pDoc->toolArray.size() < pDoc->game.GetSpecialSize())
            {
                int rand_x = Util::GetRand(0,rect.Width());
                CPoint point(rand_x,10);
                CTool *tool =new CToolSuperBomb(point);
                pDoc->toolArray.push_back(tool);                
            }
            break;
        }
        
        }
        break;
    }
    
    default:
    {
        break;
    }
    }

    CView::OnTimer(nIDEvent);
}

void CPlaneView::OnDestroy()
{
    CView::OnDestroy();
    KillTimer(TIMER_DRAW);
    KillTimer(TIMER_MOVE_10);
    KillTimer(TIMER_20);
    KillTimer(TIMER_EXPLORE_50);
    KillTimer(TIMER_NEWENEMY_1000);
    KillTimer(TIMER_FREE);
    KillTimer(TIMER_2000);
    KillTimer(TIMER_EXPLORE_5000);
    KillTimer(TIMER_SP_LIFE_10000);
    //KillTimer(TIMER_SP_SUPBOMB_15000);
}

void CPlaneView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
    pdc = new CClientDC(this);
    SetTimer(TIMER_DRAW,9,0);
    SetTimer(TIMER_MOVE_10,11,0);
    SetTimer(TIMER_20,151,0);
    SetTimer(TIMER_2000,2001,0);
    SetTimer(TIMER_EXPLORE_50,51,0);
    SetTimer(TIMER_NEWENEMY_1000,351,0);
    SetTimer(TIMER_FREE,201,0);
    SetTimer(TIMER_EXPLORE_5000,5001,0);
    SetTimer(TIMER_SP_LIFE_10000,10001,0);

    //SetTimer(TIMER_SP_SUPBOMB_15000,499,0);


    //初始化一架敌机
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    CRect rect;
    //GetWindowRect(&rect);
    GetClientRect(&rect);
    GetClientRect(&pDoc->game.GclientRect);

    int rand_x = Util::GetRand(0,rect.Height());
    CPoint pointEnemy(rand_x,10);
    CEnemy *enemy =new CEnemy(pointEnemy);
    pDoc->enemyArray.push_back(enemy);
    CPoint pointMe(rect.Width()/2,rect.Height()-CMyPlane::PLANE_HEIGHT*2);
    pDoc->myPlane = new CMyPlane(pointMe);
    pDoc->outText[STRING_LIFE].SetPos(10,50);
    pDoc->outText[STRING_GRADE].SetPos(10,30);
    pDoc->outText[STRING_LEVEL].SetPos(10,10);
    pDoc->outText[STRING_ARROW].SetPos(280,10);
    pDoc->outText[STRING_GAME_OVER].SetPos(rect.Width()/2-60,rect.Height()/2-30);
    
    count_sepcial = 0;//特殊物品生成有关
    pDoc->backCount = 0;
}

BOOL CPlaneView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

void CPlaneView::OnRButtonDown(UINT nFlags, CPoint point)
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if (!pDoc)
    {
        return;
    }
    CRect rect;
    GetClientRect(&rect);
    pDoc->myPlane->ReInitPlane(rect);
    CView::OnRButtonDown(nFlags, point);
}

BOOL DrawSpecial(CDC* pDC,CPoint point,int width,int height,BOOL bPause,UINT nIDResource)
{
    if(!pDC)
    {
        return FALSE;
    }
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap bmpMem;
    bmpMem.LoadBitmapW(nIDResource);
    CBitmap *pbmpold = memDC.SelectObject(&bmpMem);
    pDC->BitBlt(point.x,point.y,width,height,&memDC,0,0,SRCCOPY);
    //pDC->TransparentBlt(point.x,point.y,width,height,&memDC,0,0,width,height,RGB(0,0,0));
    memDC.SelectObject(pbmpold);

    return TRUE;
}
