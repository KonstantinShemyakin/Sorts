#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "TXLib.h"

using namespace std;

void rotate(float x1,float y1,float &x2,float &y2, float angle)
{
    float dx=x2;
    float dy=y2;
    x2=x1+(dx-x1)*cos(angle*M_PI/180)-(dy-y1)*sin(angle*M_PI/180);
    y2=y1+(dx-x1)*sin(angle*M_PI/180)+(dy-y1)*cos(angle*M_PI/180);
}

void DrawArrow(int x1, int y1, int x2, int y2)
{
    txSetFillColor(TX_RED);
    txSetColor(TX_BLACK, 3);
    POINT Arrow[7] = {{(x1 + x2)/2, y2}, {x2, y1 + ((y2 - y1)*3)/4}, {x1 + ((x2 - x1)*3)/4, y1 + ((y2 - y1)*3)/4}, {x1 + ((x2 - x1)*3)/4, y1}, {x1 + (x2 - x1)/4, y1}, {x1 + (x2 - x1)/4, y1 + ((y2 - y1)*3)/4}, {x1, y1 + ((y2 - y1)*3)/4}};
    txPolygon(Arrow, 7);
}

void DrawBattery(int x1, int y1, int x2, int y2)
{
    txSetFillColor(TX_RED);
    txSetColor(TX_BLACK, 3);
    txRectangle(x1, y1, x2, y2);
    txSetColor(TX_YELLOW, 3);
    txSetFillColor(TX_YELLOW);
    POINT Lightning[6] = {{(x1 + x2)/2, y1}, {x2, y1 + ((y2 - y1)*5)/8}, {(x1 + x2)/2, y1 + ((y2 - y1)*5)/8}, {(x1 + x2)/2, y2}, {x1, y1 + ((y2 - y1)*3)/8}, {(x1 + x2)/2, y1 + ((y2 - y1)*3)/8}};
    txPolygon(Lightning, 6);
}

class Box
{
private:
    int data;
    int x, y;
    bool exist;
public:
    void Draw(int size_b);

    void SetBox(int x_new, int y_new, int data_new);

    void Move(int x_dif, int y_dif);

    void Delete();

    int GetX();

    int GetY();

    int GetData();

    bool GetState();
};

bool Box::GetState()
{
    return exist;
}

int Box::GetX()
{
    return x;
}

int Box::GetY()
{
    return y;
}

void Box::Move(int x_dif, int y_dif)
{
    x+=x_dif;
    y+=y_dif;
}

void Box::SetBox(int x_new, int y_new, int data_new = 0)
{
    x = x_new;
    y = y_new;
    data = data_new;
    exist = true;
}

void Box::Draw(int size_b)
{
    if(exist)
    {
        txSetColor(TX_YELLOW, 5);
        txSetFillColor(TX_BROWN);
        txRectangle(x - size_b/2, y - size_b/2, x + size_b/2, y + size_b/2);
        txSetFillColor(TX_RED);
        txSetColor(TX_RED);
        float ball_size = size_b/5 - 1.5;
        float ball_x = ball_size/2 + 4.25, ball_y = ball_size/2 + 4.25;
        int used_data = data;
        while(used_data > 0)
        {
            if(used_data/5 >= 1)
            {
                used_data-=5;
                for(int i = 0; i < 5; i++)
                {
                    txCircle(x - size_b/2 + ball_x, y + size_b/2 - ball_y, ball_size/2);
                    ball_x+=ball_size;
                }
                ball_x = ball_size/2 + 4;
                ball_y+= ball_size;
            }
            else
            {
                for(int i = 0; i < used_data; i++)
                {
                    txCircle(x - size_b/2 + ball_x, y + size_b/2 - ball_y, ball_size/2);
                    ball_x+=ball_size;
                }
                used_data = 0;
            }
        }
    }
}

void Box::Delete()
{
    exist = false;
}

int Box::GetData()
{
    return data;
}

class SortHuman
{
private:
    int x, y;
    double x_gr, y_gr;
    double x_hn, y_hn;
    bool walk;
    bool hand;
    int chosen_box;
    Box* picked;
    int frame;
    float bl_size;
    int box_count;
    int angle_gr;
    int angle_hn;
    int speed;
    Box* Boxes;
public:
    SortHuman();

    void Spawn(int x_new, int y_new);

    void SetBlSiz(int new_size);

    void Draw();

    void DrawHand();

    void DrawGrap();

    void DrawSit();

    void DrawBox();

    void SetBoxCount(int new_box);

    float GetBlSize();

    void WatchOn(int num, bool hand_new);

    void MoveGrHn(double x_dif, double y_dif, bool grap);

    void Grab(int num);

    void ChangeUg(int ang_new, bool grab);

    void MoveBoxTo(int num);

    void Move(int x_dif, int y_dif);

    void MoveBox(int num, int x_dif);

    bool GetBoxState(int num);

    int GetX();

    double GetGrabX(bool grab);

    double GetGrabY(bool grab);

    int GetBoxCount();

    int GetAngle(bool grab);

    int GetBoxX(int num);

    int GetBoxData(int num);

    void SetBox(int num, float x_new, float y_new, int data);

    void DeleteBox(int num);

    void RandomBoxes();

    void ChangeFrame();

    int GetSpeed();

    void SetSpeed(int speed_new);
};

int SortHuman::GetSpeed()
{
    return speed;
}

void SortHuman::SetSpeed(int speed_new)
{
    speed = speed_new;
}

void SortHuman::ChangeFrame()
{
    frame+=1;
    if(frame == 5)
    {
        frame = 0;
    }
}

void SortHuman::DeleteBox(int num)
{
    Boxes[num].Delete();
}

int SortHuman::GetBoxData(int num)
{
    return Boxes[num].GetData();
}

void SortHuman::SetBox(int num, float x_new, float y_new, int data)
{
    Boxes[num].SetBox(x_new, y_new, data);
}

int SortHuman::GetBoxX(int num)
{
    return Boxes[num].GetX();
}

int SortHuman::GetAngle(bool grab)
{
    if(grab)
    {
        return angle_gr;
    }
    else
    {
        return angle_hn;
    }
}

int SortHuman::GetBoxCount()
{
    return box_count;
}

void SortHuman::MoveBox(int num, int x_dif)
{
    Boxes[num].Move(x_dif, 0);
}

bool SortHuman::GetBoxState(int num)
{
    return Boxes[num].GetState();
}

double SortHuman::GetGrabX(bool grab)
{
    if(grab)
    {
        return x_gr;
    }
    else
    {
        return x_hn;
    }
}

double SortHuman::GetGrabY(bool grab)
{
    if(grab)
    {
        return y_gr;
    }
    else
    {
        return y_hn;
    }
}

void SortHuman::ChangeUg(int ang_new, bool grab)
{
    if(grab)
    {
        angle_gr+=ang_new;
    }
    else
    {
        angle_hn+=ang_new;
    }
}

float SortHuman::GetBlSize()
{
    return bl_size;
}

void SortHuman::MoveGrHn(double x_dif, double y_dif, bool grap)
{
    if(grap)
    {
        x_gr+=x_dif;
        y_gr+=y_dif;
        if(picked != NULL)
        {
            (*picked).Move(x_dif, y_dif);
        }
    }
    else
    {
        x_hn+=x_dif;
        y_hn+=y_dif;
    }
}

void SortHuman::Grab(int num)
{
    picked = new Box;
    (*picked) = Boxes[num];
    Boxes[num].Delete();
}

void SortHuman::MoveBoxTo(int num)
{
    Boxes[num] = (*picked);
    Boxes[num].SetBox(num*bl_size + bl_size/2 + 3, 500 - bl_size/2, (*picked).GetData());
    delete []picked;
    picked = NULL;
}

void SortHuman::WatchOn(int num, bool hand_new)
{
    chosen_box = num;
    hand = hand_new;
}

int SortHuman::GetX()
{
    return x;
}

void SortHuman::Move(int x_dif, int y_dif)
{
    x+=x_dif;
    y+=y_dif;
}

SortHuman::SortHuman()
{
    speed = 1;
    frame = 0;
    chosen_box = -1;
    picked = NULL;
    Boxes = NULL;
    hand = false;
    walk = false;
    bl_size = 0;
    angle_gr = 45;
    angle_hn = 45;
    x_gr = 270;
    y_gr = 100;
    x_hn = 500;
    y_hn = 100;
    x = -50;
    y = 460;
}

void SortHuman::Spawn(int x_new, int y_new)
{
    x = x_new;
    y = y_new - 50;
}

void SortHuman::SetBlSiz(int new_size)
{
    bl_size = new_size;
}

void SortHuman::SetBoxCount(int new_box)
{
    delete []Boxes;
    box_count = new_box;
    bl_size = 700/box_count;
    Boxes = new Box[box_count];
    for(int i = 0; i < box_count; i++)
    {
        Boxes[i].SetBox(i*bl_size + bl_size/2 + 3, 500 - bl_size/2, rand()%26);
    }
}

void SortHuman::DrawHand()
{
    txSetColor(TX_GRAY, 6);
    txSetFillColor(TX_GRAY);
    float x_hand = x_hn, y_hand = y_hn + 30;
    rotate(x_hn, y_hn, x_hand, y_hand, angle_hn);
    txLine(x_hn, y_hn, x_hand, y_hand);
    x_hand = x_hn;
    y_hand = y_hn + 30;
    rotate(x_hn, y_hn, x_hand, y_hand, angle_hn - 90);
    txLine(x_hn, y_hn, x_hand, y_hand);
    txSetColor(TX_BLACK, 2);
    txRectangle(x_hn - 5, y_hn, x_hn + 5, y_hn - 500);
    txRectangle(x_hn - 10, 100, x_hn + 10, 0);
}

void SortHuman::DrawBox()
{
    for(int i = 0; i < box_count; i++)
    {
        if(i == chosen_box)
        {
            DrawArrow(chosen_box*bl_size + bl_size/2 - 2, 475 - bl_size, chosen_box*bl_size + bl_size/2 + 8, 495 - bl_size);
        }
        Boxes[i].Draw(bl_size);
    }
}

void SortHuman::DrawGrap()
{
    if(picked != NULL)
    {
        (*picked).Draw(bl_size);
    }
    txSetColor(TX_DARKGRAY, 6);
    txSetFillColor(TX_GRAY);
    float x_grap = x_gr, y_grap = y_gr + 30;
    rotate(x_gr, y_gr, x_grap, y_grap, angle_gr);
    txLine(x_gr, y_gr, x_grap, y_grap);
    x_grap = x_gr;
    y_grap = y_gr + 30;
    rotate(x_gr, y_gr, x_grap, y_grap, (-1)*angle_gr);
    txLine(x_gr, y_gr, x_grap, y_grap);
    txLine(x_gr, y_gr, x_gr, y_grap);
    txSetColor(TX_BLACK, 2);
    txRectangle(x_gr - 5, y_gr, x_gr + 5, y_gr - 500);
    txTriangle(x_gr, 85, x_gr - 25, 120, x_gr + 25, 120);
    txRectangle(x_gr - 10, 100, x_gr + 10, 0);
}

void SortHuman::Draw()
{
    float x_help, y_help;
    txSetColor(TX_BLACK, 6);
    switch(frame)
    {
    case 0:
        x_help = x;
        y_help = y + 45;
        rotate(x, y, x_help, y_help, (-1)*asin(5/1625)*M_PI/180);
        txLine(x, y, x_help, y_help);
        x_help = x;
        y_help = y + 45;
        rotate(x, y, x_help, y_help, asin(5/1625)*M_PI/180);
        txLine(x, y, x_help, y_help);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
}

void SortHuman::DrawSit()
{
    ///Background
    txSetFillColor(TX_LIGHTGRAY);
    txSetColor(TX_BLACK);
    txRectangle(120, 0, 700, 290);
    POINT Wall_Left[4] = {{0, 0}, {120, 0}, {120, 290}, {0, 500}};
    txPolygon(Wall_Left, 4);
    POINT Floor[4] = {{120, 290}, {700, 290}, {700, 500}, {0, 500}};
    txPolygon(Floor, 4);
    txSetFillColor(TX_BROWN);
    txRectangle(150, 170, 210, 290);
    txSetFillColor(TX_BLACK);
    txCircle(200, 240, 4);
    ///
    ///Chair
    txSetColor(TX_BROWN, 5);
    txSetFillColor(TX_BROWN);
    txLine(337.5, 300, 337.5, 275);
    txLine(362.5, 300, 362.5, 275);
    txLine(343.75, 295, 343.75, 270);
    txLine(368.75, 295, 368.75, 270);
    txLine(337.5, 275, 362.5, 275);
    txLine(337.5, 275, 343.75, 270);
    txLine(368.75, 270, 343.75, 270);
    txLine(368.75, 270, 362.5, 275);
    txLine(343.75, 270, 343.75, 250);
    txLine(368.75, 270, 368.75, 250);
    txRectangle(343.75, 245, 369.75, 255);
    ///
    ///Human
    float angle = asin((chosen_box*bl_size + bl_size/2 - 355)/sqrt(pow(chosen_box*bl_size + bl_size/2 - 355, 2)+pow(240 - Boxes[chosen_box].GetY(), 2)));
    txSetColor(TX_BLACK, 6);
    txSetFillColor(TX_BLACK);
    txLine(355, 270, 355, 240);
    txLine(355, 270, 342.5, 280);
    txLine(342.5, 280, 342.5, 300);
    txLine(355, 270, 357, 278.5);
    txLine(357, 278.5, 357, 300);
    float x_head = 355, y_head = 250;//ehal greka cherez reku vidit greka v reke rak synul greka ryky v reky rak za ryky greky tsap
    if(chosen_box >= 0)
    {
        rotate(355, 240, x_head, y_head, (-1)*angle*180/M_PI);
    }
    else
    {
        y_head-=10;
    }
    txSetColor(TX_BLACK);
    txSetFillColor(TX_BLACK);
    txCircle(x_head, y_head, 13);
    txSetColor(TX_BLACK, 6);
    if(hand)
    {
        x_head = 355;
        y_head = 285;
        rotate(355, 255, x_head, y_head, (-1)*angle*180/M_PI);
        txLine(355, 255, x_head, y_head);
    }
    else
    {
        txLine(355, 255, 345, 263);
        txLine(345, 263, 346.5, 280);
    }
    txLine(355, 255, 360, 265);
    txLine(360, 265, 356, 279);
    ///
    ///Eyes
    float x_eyes = 355, y_eyes = 255;
    float x_eye, y_eye;
    txSetFillColor(TX_WHITE);
    txSetColor(TX_WHITE);
    if(chosen_box >= 0)
    {
        rotate(355, 240, x_eyes, y_eyes, (-1)*angle*180/M_PI);
        txCircle(x_eyes - 5, y_eyes, 3);
        txCircle(x_eyes + 5, y_eyes, 3);
        txSetFillColor(TX_BLACK);
        txSetColor(TX_BLACK);
        x_eye = x_eyes - 5;
        y_eye = y_eyes + 2;
        rotate(x_eye, y_eyes, x_eye, y_eye, (-1)*angle*180/M_PI);
        txCircle(x_eye , y_eye, 2);
        x_eye = x_eyes + 5;
        y_eye = y_eyes + 2;
        rotate(x_eye, y_eyes, x_eye, y_eye, (-1)*angle*180/M_PI);
        txCircle(x_eye , y_eye, 2);
    }
    else
    {
        txCircle(x_eyes - 5, y_eyes - 16, 3);
        txCircle(x_eyes + 5, y_eyes - 16, 3);
        txSetFillColor(TX_BLACK);
        txSetColor(TX_BLACK);
        txCircle(x_eyes - 5, y_eyes - 16, 2);
        txCircle(x_eyes + 5, y_eyes - 16, 2);
    }
    ///
}

void update(int tim = 1)
{
    txSleep(tim);
    txSetFillColor(TX_WHITE);
    txClear();
}

void DrawScene(SortHuman &Main_h)
{
    Main_h.DrawSit();
    Main_h.DrawBox();
    Main_h.DrawGrap();
    Main_h.DrawHand();
}

void GrabBox(SortHuman &Main_h, int num)
{
    int bl_size = Main_h.GetBlSize();
    int vel;
    int del_box;
    for(int i = 0; i < Main_h.GetBoxCount(); i++)
    {
        if(!Main_h.GetBoxState(i))
        {
            del_box = i;
            break;
        }
    }
    if(num*bl_size + bl_size/2 - Main_h.GetGrabX(true) >= 0)
    {
        vel = Main_h.GetSpeed();
    }
    else
    {
        vel = (-1)*Main_h.GetSpeed();
    }
    while(!(abs(Main_h.GetGrabX(true) - (num*bl_size + bl_size/2 + 3)) <= abs(vel)/2))
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(vel, 0, true);
        update();
    }
    Main_h.MoveGrHn(num*bl_size + bl_size/2 + 3 - Main_h.GetGrabX(true), 0, true);
    DrawScene(Main_h);
    update();
    while(!((Main_h.GetGrabY(true) <= 500)&&(Main_h.GetGrabY(true) >= 500 - (bl_size + 2*abs(vel)))))
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(0, abs(vel), true);
        update();
    }
    for(int i = 0; i < 25; i++)
    {
        Main_h.ChangeUg(-1, true);
        DrawScene(Main_h);
        update();
    }
    Main_h.Grab(num);
    while(Main_h.GetGrabY(true) != 100)
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(0, (-1)*abs(vel), true);
        update();
    }
}

void PutBox(SortHuman &Main_h, int num)
{
    int bl_size = Main_h.GetBlSize();
    int vel;
    if(num*bl_size + bl_size/2 + 3 - Main_h.GetGrabX(true) >= 0)
    {
        vel = Main_h.GetSpeed();
    }
    else
    {
        vel = (-1)*Main_h.GetSpeed();
    }
    while(!(abs(Main_h.GetGrabX(true) - (num*bl_size + bl_size/2 + 3)) <= abs(vel)/2))
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(vel, 0, true);
        update();
    }
    Main_h.MoveGrHn((num*bl_size + bl_size/2 + 3) - Main_h.GetGrabX(true), 0, true);
    DrawScene(Main_h);
    update();
    while(!((Main_h.GetGrabY(true) <= 500 - (bl_size - 2))&&(Main_h.GetGrabY(true) >= 500 - (bl_size + abs(vel)*2))))
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(0, abs(vel), true);
        update();
    }
    for(int i = 0; i < 25; i++)
    {
        Main_h.ChangeUg(1, true);
        DrawScene(Main_h);
        update();
    }
    Main_h.MoveBoxTo(num);
    while(Main_h.GetGrabY(true) != 100)
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn(0, (-1)*abs(vel), true);
        update();
    }
    /*while(Main_h.GetGrabX(true) != 270)
    {
        DrawScene(Main_h);
        Main_h.MoveGrHn((-1)*vel, 0, true);
        update();
    }*/
}

void MoveBoxes(SortHuman &Main_h, int num)
{
    int bl_size = Main_h.GetBlSize();
    int vel;
    int del_box;
    for(int i = 0; i < Main_h.GetBoxCount(); i++)
    {
        if(!Main_h.GetBoxState(i))
        {
            del_box = i;
            break;
        }
    }
    if(del_box < num)
    {
        if((num + 1)*bl_size - Main_h.GetGrabX(false) >= 0)
        {
            vel = Main_h.GetSpeed();
        }
        else
        {
            vel = (-1)*Main_h.GetSpeed();
        }
        while(!(abs(Main_h.GetGrabX(false) - ((num + 1)*bl_size + 3)) <= abs(vel)/2))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(vel, 0, false);
            update();
        }
        Main_h.MoveGrHn(((num + 1)*bl_size + 3) - Main_h.GetGrabX(false), 0, false);
        DrawScene(Main_h);
        update();
        while(!(Main_h.GetAngle(false) == 90))
        {
            DrawScene(Main_h);
            Main_h.ChangeUg(3, false);
            update();
        }
        while(!((Main_h.GetGrabY(false) <= 500 - (bl_size - abs(vel)/2))&&(Main_h.GetGrabY(false) >= 500 - (bl_size + abs(vel)/2))))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(0, abs(vel), false);
            update();
        }
        while(!((Main_h.GetBoxX(del_box + 1) <= Main_h.GetBoxX(del_box) + abs(vel)/2)&&(Main_h.GetBoxX(del_box + 1) >= Main_h.GetBoxX(del_box) - abs(vel)/2)))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn((-1)*abs(vel), 0, false);
            for(int i = num; i > del_box; i--)
            {
                Main_h.MoveBox(i, (-1)*abs(vel));
            }
            update();
        }
        for(int i = del_box; i < num; i++)
        {
            Main_h.SetBox(i, i*Main_h.GetBlSize() + Main_h.GetBlSize()/2, 500 - Main_h.GetBlSize()/2, Main_h.GetBoxData(i + 1));
        }
        Main_h.DeleteBox(num);
        while(Main_h.GetGrabY(false) != 100)
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(0, (-1)*abs(vel), false);
            update();
        }
    }
    else
    {
        if(num*bl_size + 3 - Main_h.GetGrabX(false) >= 0)
        {
            vel = Main_h.GetSpeed();
        }
        else
        {
            vel = (-1)*Main_h.GetSpeed();
        }
        while(!(abs(Main_h.GetGrabX(false) - (num*bl_size + 3)) <= abs(vel)/2))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(vel, 0, false);
            update();
        }
        Main_h.MoveGrHn((num*bl_size + 3) - Main_h.GetGrabX(false), 0, false);
        DrawScene(Main_h);
        update();
        while(!(Main_h.GetAngle(false) == 0))
        {
            DrawScene(Main_h);
            Main_h.ChangeUg(-1, false);
            update();
        }
        while(!((Main_h.GetGrabY(false) <= 500 - (bl_size - abs(vel)/2))&&(Main_h.GetGrabY(false) >= 500 - (bl_size + abs(vel)/2))))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(0, abs(vel), false);
            update();
        }
        while(!((Main_h.GetBoxX(del_box - 1) <= Main_h.GetBoxX(del_box) + abs(vel)/2)&&(Main_h.GetBoxX(del_box - 1) >= Main_h.GetBoxX(del_box) - abs(vel)/2)))
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(abs(vel), 0, false);
            for(int i = num; i < del_box; i++)
            {
                Main_h.MoveBox(i, abs(vel));
            }
            update();
        }
        for(int i = del_box; i > num; i--)
        {
            Main_h.SetBox(i, i*Main_h.GetBlSize() + Main_h.GetBlSize()/2, 500 - Main_h.GetBlSize()/2, Main_h.GetBoxData(i - 1));
        }
        Main_h.DeleteBox(num);
        while(Main_h.GetGrabY(false) != 100)
        {
            DrawScene(Main_h);
            Main_h.MoveGrHn(0, (-1)*abs(vel), false);
            update();
        }
    }
}

void SwapBoxes(SortHuman &Main_h, int num1, int num2)
{
    if(abs(num1 - num2) == 1)
    {
        Main_h.WatchOn(num1, true);
        GrabBox(Main_h, num1);
        Main_h.WatchOn(num2, true);
        MoveBoxes(Main_h, num2);
        PutBox(Main_h, num2);
    }
    else if(num1 != num2)
    {
        Main_h.WatchOn(num1, true);
        GrabBox(Main_h, num1);
        Main_h.WatchOn(num2, true);
        MoveBoxes(Main_h, num2);
        PutBox(Main_h, num2);
        if(num1 > num2)
        {
            Main_h.WatchOn(num2 + 1, true);
            GrabBox(Main_h, num2 + 1);
            Main_h.WatchOn(num1, true);
            MoveBoxes(Main_h, num1);
            PutBox(Main_h, num1);
        }
        else
        {
            Main_h.WatchOn(num2 - 1, true);
            GrabBox(Main_h, num2 - 1);
            Main_h.WatchOn(num1, true);
            MoveBoxes(Main_h, num1);
            PutBox(Main_h, num1);
        }
    }
}
///////////////Bubble Sort
void BubbleSort(SortHuman &Main_h, int speed)
{
	bool swa = false;
	int range = Main_h.GetBoxCount();
	DrawScene(Main_h);
	update(3000);
	for(int i = 0; i < range; i++)
	{
		for(int i = 0; i < range - 1; i++)
		{
			Main_h.WatchOn(i, false);
			DrawScene(Main_h);
            update(300 - (10.714*speed));
			Main_h.WatchOn(i+1, false);
			DrawScene(Main_h);
            update(300 - (10.714*speed));
			Main_h.WatchOn(i, false);
			DrawScene(Main_h);
            update(300 - (10.714*speed));
			if(Main_h.GetBoxData(i) > Main_h.GetBoxData(i+1))
			{
				SwapBoxes(Main_h, i, i+1);
				swa = true;
			}
			DrawScene(Main_h);
            update();
		}
		if(swa == false)
		{
			break;
		}
		swa = false;
	}
	Main_h.WatchOn(-1, false);
	DrawScene(Main_h);
}
///////////////
///////////////Insert Sort

int IndexFind(SortHuman &Main_h, int number, int speed, int step = 1, int start = 0)
{
    for(int i = start; i < number; i+=step)
    {
        Main_h.WatchOn(i, false);
        DrawScene(Main_h);
        update(300 - (10.714*speed));
        Main_h.WatchOn(number, false);
        DrawScene(Main_h);
        update(300 - (10.714*speed));
        if(Main_h.GetBoxData(i) > Main_h.GetBoxData(number))
        {
            return i;
        }
    }
    return -1;
}

void InsertSort(SortHuman &Main_h, int speed, int step = 1, int start = 0)
{
	int index, elem_cur;
	int range = Main_h.GetBoxCount();
	DrawScene(Main_h);
    update(3000);
	for(int i = start + step; i < range; i+=step)
	{
		if(i + step > range)
        {
            break;
        }
		index = IndexFind(Main_h, i, speed, step, start);
		if (index == -1)
		{
			continue;
		}
		else
		{
			Main_h.WatchOn(i, true);
			GrabBox(Main_h, i);
			Main_h.WatchOn(index, true);
			MoveBoxes(Main_h, index);
			PutBox(Main_h, index);
		}
	}
}

///////////////
///////////////Merge

void ConArr(SortHuman &Main_h, int range_1_from, int range_1_to, int range_2_from, int range_2_to, int speed)
{
    int i = range_1_from, j = range_2_from, k = 0;
	DrawScene(Main_h);
	update();
	int arr_complete[range_2_to - range_1_from + 1];
	while((i <= range_1_to)&&(j <= range_2_to))
    {
        Main_h.WatchOn(i, false);
        DrawScene(Main_h);
        update(300 - (speed*10.71));
        Main_h.WatchOn(j, false);
        DrawScene(Main_h);
        update(300 - (speed*10.71));
        if(Main_h.GetBoxData(i) < Main_h.GetBoxData(j))
        {
            arr_complete[k] = i;
            i++;
        }
        else
        {
            arr_complete[k] = i;
            j++;
        }
        k++;
    }
    if(i == range_1_to + 1)
    {
        while(j <= range_2_to)
        {
            arr_complete[k] = j;
            j++;
            k++;
        }
    }
    else if (j == range_2_to + 1)
    {
        while(i < range_1_to)
        {
            arr_complete[k] = i;
            i++;
            k++;
        }
    }
    k = 0;
    for(int ind = range_1_from; ind <= range_2_to; i++)
    {
        DrawScene(Main_h);
        update();
        if(ind != arr_complete[k])
        {
            GrabBox(Main_h, arr_complete[k]);
            MoveBoxes(Main_h, ind);
            PutBox(Main_h, ind);
            for(int m = ind; m <= arr_complete[k]; m++)
            {
                arr_complete[k]++;
            }
        }
    }
}

void MergeSort(SortHuman &Main_h, int range_from, int range_to, int speed)
{
        int *range_1_from = new int;
        int *range_1_to = new int;
        int *range_2_from = new int;
        int *range_2_to = new int;
        (*range_1_from) = range_from;
        (*range_2_to) = range_to;
        (*range_1_to) = (range_to + range_from)/2;
        (*range_2_from) = (*range_1_to) + 1;
        DrawScene(Main_h);
        update();
        if((*range_1_to) - (*range_1_from) >= 2)
        {
            MergeSort(Main_h, (*range_1_from), (*range_1_to), speed);
        }
        if((*range_2_to) - (*range_2_from) >= 2)
        {
            MergeSort(Main_h, (*range_2_from), (*range_2_to), speed);
        }
        if((*range_1_to) - (*range_1_from) == 1)
        {
            Main_h.WatchOn((*range_1_from), false);
            DrawScene(Main_h);
            update(300 - (speed*10.71));
            Main_h.WatchOn((*range_1_to), false);
            DrawScene(Main_h);
            update(300 - (speed*10.71));
            if(Main_h.GetBoxData(*range_1_from) > Main_h.GetBoxData(*range_1_to))
            {
                SwapBoxes(Main_h, (*range_1_from), (*range_1_to));
            }
        }
        if((*range_2_to) - (*range_2_from) == 1)
        {
            Main_h.WatchOn((*range_2_from), false);
            DrawScene(Main_h);
            update(300 - (speed*10.71));
            Main_h.WatchOn((*range_2_to), false);
            DrawScene(Main_h);
            update(300 - (speed*10.71));
            if(Main_h.GetBoxData(*range_2_from) > Main_h.GetBoxData(*range_2_to))
            {
                SwapBoxes(Main_h, (*range_2_from), (*range_2_to));
            }
        }
        ConArr(Main_h, (*range_1_from), (*range_1_to), (*range_2_from), (*range_2_to), speed);
        delete []range_1_from;
        delete []range_1_to;
        delete []range_2_from;
        delete []range_2_to;
}

///////////////
///////////////Shaker

void ShakerSort(SortHuman &Main_h, int speed)
{
	bool swa = false;
	DrawScene(Main_h);
	update(3000);
	for(int i = 0; i < ceil(Main_h.GetBoxCount()/2); i++)
	{
		for(int k = i, j = Main_h.GetBoxCount() - 2 - i; k < Main_h.GetBoxCount() - 1 - i; k++, j--)
		{
			Main_h.WatchOn(k, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			Main_h.WatchOn(k + 1, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			Main_h.WatchOn(k, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			if(Main_h.GetBoxData(k) > Main_h.GetBoxData(k + 1))
			{
				SwapBoxes(Main_h, k, k+1);
				swa = true;
			}
			Main_h.WatchOn(j, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			Main_h.WatchOn(j + 1, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			Main_h.WatchOn(j, false);
			DrawScene(Main_h);
			update(300 - (speed*10.71));
			if(Main_h.GetBoxData(j) > Main_h.GetBoxData(j + 1))
			{
				SwapBoxes(Main_h, j, j+1);
				swa = true;
			}
		}
		if(swa == false)
		{
			break;
		}
		swa = false;
	}
}

///////////////
///////////////

///////////////
///////////////

///////////////

void DrawMenu(int speed, int box_count)
{
    txSetColor(TX_BLACK, 2);
    for(int i = 0; i < 7; i++)
    {
        txSetFillColor(TX_BLACK);
        txRectangle(i*100 + 12.5, txGetExtentY(), i*100 + 87.5, txGetExtentY() - 100);
        txSetFillColor(TX_BROWN);
        if(((txMouseX() <= i*100 + 87.5)&&(txMouseX() >= i*100 + 12.5))&&((txMouseY() <= txGetExtentY())&&(txMouseY() >= txGetExtentY() - 100)))
        {
            POINT DrawDoor[4] = {{i*100 + 12.5, txGetExtentY()}, {i*100 + 12.5, txGetExtentY() - 100}, {i*100 + 70, txGetExtentY() - 85}, {i*100 + 70, txGetExtentY() - 15}};
            txPolygon(DrawDoor, 4);
            txSetFillColor(TX_BLACK);
            txCircle(i*100 + 65, txGetExtentY() - 45, 4);
        }
        else
        {
            txRectangle(i*100 + 12.5, txGetExtentY(), i*100 + 87.5, txGetExtentY() - 100);
            txSetFillColor(TX_BLACK);
            txCircle(i*100 + 80.5, txGetExtentY() - 50, 5);
        }
        switch(i)
        {
        case 0:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Bubble");
            break;
        case 1:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Insert");
            break;
        case 2:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Shella");
            break;
        case 3:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Shaker");
            break;
        case 4:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Fast");
            break;
        case 5:
            txSelectFont("Times New Roman", 30);
            txDrawText(i*100 + 12.5, txGetExtentY() - 100, i*100 + 87.5, txGetExtentY() - 130, "Merge");
            break;
        }
    }
    txSetFillColor(TX_WHITE);
    txRectangle(50, 100, 100, 150);
    txRectangle(600, 100, 650, 150);
    txRectangle(100, 150, 600, 100);
    txSetFillColor(TX_BLACK);
    txTriangle(55, 125, 90, 140, 90, 110);
    txTriangle(645, 125, 610, 140, 610, 110);
    txSetColor(TX_YELLOW, 7);
    txSetFillColor(TX_BROWN);
    for(int i = 0; i < box_count; i++)
    {
        txRectangle(i*50 + 100, 100, (i+1)*50 + 100, 150);
    }
    txSetColor(TX_BLACK, 2);
    txSetFillColor(TX_WHITE);
    txRectangle(50, 200, 100, 250);
    txRectangle(600, 200, 650, 250);
    txRectangle(100, 250, 600, 200);
    txSetFillColor(TX_BLACK);
    txTriangle(55, 225, 90, 240, 90, 210);
    txTriangle(645, 225, 610, 240, 610, 210);
    for(int i = 0; i < speed; i++)
    {
        DrawBattery(i*35.714 + 100, 200, (i+1)*35.714 + 100, 250);
    }
}

int MenuInterface(int &box_count, int& speed, bool &tap)
{
    int index = -1;
    for(int i = 0; i < 7; i++)
    {
        if((((txMouseX() <= i*100 + 87.5)&&(txMouseX() >= i*100 + 12.5))&&((txMouseY() <= txGetExtentY())&&(txMouseY() >= txGetExtentY() - 100)))&&(txMouseButtons() == 1))
        {
            index = i;
            break;
        }
    }

    RECT button_boxplus = {600, 100, 650, 150};
    RECT button_boxmin = {50, 100, 100, 150};

    if((box_count < 10)&&(In(txMousePos(), button_boxplus))&&(txMouseButtons() == 1)&&(!tap))
    {
        box_count+=1;
        tap = true;
    }
    if((box_count > 4)&&(In(txMousePos(), button_boxmin))&&(txMouseButtons() == 1)&&(!tap))
    {
        box_count-=1;
        tap = true;
    }

    RECT button_speedplus = {600, 200, 650, 250};
    RECT button_speedmin = {50, 200, 100, 250};

    if((speed < 14)&&(In(txMousePos(), button_speedplus))&&(txMouseButtons() == 1)&&(!tap))
    {
        speed+=1;
        tap = true;
    }
    if((speed > 2)&&(In(txMousePos(), button_speedmin))&&(txMouseButtons() == 1)&&(!tap))
    {
        speed-=1;
        tap = true;
    }

    if(txMouseButtons() == 0)
    {
        tap = false;
    }

    return index;
}

int Menu(SortHuman &Main_h, int &box_count, int &speed, bool &tap)
{
    DrawMenu(speed, box_count);
    switch(MenuInterface(box_count, speed, tap))
    {
    case 0:
        Main_h.SetBoxCount(box_count);
        Main_h.SetSpeed(speed);
        Main_h.WatchOn(-1, false);
        BubbleSort(Main_h, speed);
        Main_h.WatchOn(-1, false);
        DrawScene(Main_h);
        update(5000);
        break;
    case 1:
        Main_h.SetBoxCount(box_count);
        Main_h.SetSpeed(speed);
        Main_h.WatchOn(-1, false);
        InsertSort(Main_h, speed);
        Main_h.WatchOn(-1, false);
        DrawScene(Main_h);
        update(5000);
        break;
    case 3:
        Main_h.SetBoxCount(box_count);
        Main_h.SetSpeed(speed);
        Main_h.WatchOn(-1, false);
        ShakerSort(Main_h, speed);
        Main_h.WatchOn(-1, false);
        DrawScene(Main_h);
        update(5000);
        break;
    case 5:
        Main_h.SetBoxCount(box_count);
        Main_h.SetSpeed(speed);
        Main_h.WatchOn(-1, false);
        MergeSort(Main_h, 0, box_count - 1,speed);
        Main_h.WatchOn(-1, false);
        DrawScene(Main_h);
        update(5000);
        break;
    }
}

int main()//Max speed = 14, Box Count = 10
{
    int box_count = 4;
    int speed = 2;
    bool tap = false;
    srand(time(0));
    txBegin();
    txCreateWindow(700, 500);
    txTextCursor(false);
    update();
    SortHuman MainInter;
    MainInter.SetSpeed(14);
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        Menu(MainInter, box_count, speed, tap);
        update(10);
    }
    txEnd();
    txDisableAutoPause();
}
