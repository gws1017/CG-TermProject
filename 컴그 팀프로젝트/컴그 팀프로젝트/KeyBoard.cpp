#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
struct Fruit;

extern GLuint s_program;

extern float CamPosX;
extern float CamPosY;
extern float CamPosZ;

extern float CamXAt;
extern float CamYAt;
extern float CamZAt;

extern float cam_rotate;
extern float cam_revolve;

extern bool fruitTimer;
extern bool treeTimer;
extern bool potswingTimer;
extern bool bMakePoketmon;

extern float treeAngle;
extern int CheckCount;
extern float Red;
extern float Green;
extern float Blue;
extern bool RDraw;

extern bool bCheckColor;
extern CType color;

extern Pokemon_Manager pm;
void Keyboard(unsigned char key, int x, int y)
{
    //디버깅용 메세지
    cout << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamY " << CamPosY << " " << "CamZ " << CamPosZ << " " << endl;
    cout/* << "CamAtX" << CamAtX << " " */ << "CamATY " << CamYAt << " " << "CamATZ " << CamZAt << " " << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamRotate " << cam_rotate << " " << "CamRevolve " << cam_revolve << " " << endl;
    cout << CheckCount << endl;

    cout << endl;
    switch (key)
    {
    case '5':
        pm.Create("balchang", s_program);
        break;
    case '6':
        pm.Create("picachu", s_program);
        break;
    case '7':
        pm.Create("gong", s_program);
        break;
    case '8':
        pm.Create("pang", s_program);
        break;
    case '9':
        pm.Create("coil", s_program);
        break;
    case 'p':
        potswingTimer = !potswingTimer;
        break;
    case 'm':
        treeTimer = !treeTimer;
        fruitTimer = !fruitTimer;
        treeAngle = 0.0f;
        break;
    case 'c':
        CamYAt += 0.5;
        CamPosY += 0.5;
        break;
    case 'C':
        CamYAt -= 0.5;
        CamPosY -= 0.5;
        break;
    case 'z':
        CamZAt += 0.5;
        CamPosZ += 0.5;
        break;
    case 'Z':
        CamZAt -= 0.5;
        CamPosZ -= 0.5;
        break;
    case 'y':
        cam_rotate += 10.0;
        break;
    case 'Y':
        cam_rotate -= 10.0;
        break;
    case 'r':
        cam_revolve += 10.0;
        break;
    case 'R':
        cam_revolve -= 10.0;
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
            bMakePoketmon = false;
            potswingTimer = !potswingTimer;
            bCheckColor = true;
        }
        break;

    }

   

    glutPostRedisplay();
}