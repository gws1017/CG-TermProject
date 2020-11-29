#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
#include "Header/Fruit.h"
#include "Header/Camera.h"
#include "Header/Pot.h"

extern GLuint s_program;

extern unsigned int viewLocation;
extern Camera cm;

extern bool fruitTimer;
extern bool treeTimer;
extern bool bMakePoketmon;

extern float treeAngle;
extern int CheckCount;
extern float Red;
extern float Green;
extern float Blue;
extern bool RDraw;

extern bool bCheckColor;
extern CType color;

extern Pot p;
extern Pokemon_Manager pm;
void Keyboard(unsigned char key, int x, int y)
{
    //디버깅용 메세지
    cout << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamY " << cm.CamPosY << " " << "CamZ " << cm.CamPosZ << " " << endl;
    cout/* << "CamAtX" << CamAtX << " " */ << "CamATY " << cm.CamYAt << " " << "CamATZ " << cm.CamZAt << " " << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamRotate " << cm.cam_rotate << " " << "CamRevolve " << cm.cam_revolve << " " << endl;
    cout << CheckCount << endl;

    cout << endl;
    switch (key)
    {
    case 'm':
        treeTimer = !treeTimer;
        fruitTimer = !fruitTimer;
        //treeAngle = 0.0f;
        break;
    case 'e'://위
        cm.CamYAt += 0.5;
        cm.CamPosY += 0.5;
        break;
    case 'E'://아래
        cm.CamYAt -= 0.5;
        cm.CamPosY -= 0.5;
        break;
    case 's'://뒤
        cm.CamZAt += 0.5;
        cm.CamPosZ += 0.5;
        break;
    case 'w'://앞
        cm.CamZAt -= 0.5;
        cm.CamPosZ -= 0.5;
        break;
    case'a'://왼
        cm.CamXAt -= 0.5;
        cm.CamPosX -= 0.5;
        break;
    case'd'://오
        cm.CamXAt += 0.5;
        cm.CamPosX += 0.5;
        break;
    case 'y':
        cm.cam_rotate += 10.0;
        break;
    case 'Y':
        cm.cam_rotate -= 10.0;
        break;
    case 'r':
        cm.cam_revolve += 10.0;
        break;
    case 'R':
        cm.cam_revolve -= 10.0;
        break;
    case'+':
        bMakePoketmon = true;//솥 조합시스템 시작
        
        break;
    case '1'://빨간열매 생성
        if (bMakePoketmon)
        {
            RDraw = true;
            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 1.0f;
                Green = 0.0f;
                Blue = 0.0f;
                color = CType::RED;
            }
        }
        break;
    case '2'://초록 열매 생성
        if (bMakePoketmon)
        {
            RDraw = true;

            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 0.0f;
                Green = 1.0f;
                Blue = 0.0f;
                color = CType::GREEN;
            }
        }
        break;
    case'3'://파란 열매 생성
        if (bMakePoketmon)
        {
            RDraw = true;
            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 0.0f;
                Green = 0.0f;
                Blue = 1.0f;
                color = CType::BLUE;
            }
        }
        break;
    case'-'://열매빼기(임시)
        
        RDraw = false;
        if (CheckCount >0)
        {   
            CheckCount--;
            
            Red = 0.0f;
            Green = 0.0f;
            Blue = 0.0f;
            color = CType::NONE;
        }
        break;

    case'o'://열매 배치 확정키
        if (CheckCount >= 8)
        {
            cm.CamPosY = 3.5f;
            cm.CamPosZ = 16.0f;
            cm.CamYAt = 3.0f;
            cm.CamZAt = 6.5f;
            bMakePoketmon = false;
            p.potswingTimer = !p.potswingTimer;
            bCheckColor = true;
        }
        break;

    }

    

    glutPostRedisplay();
}