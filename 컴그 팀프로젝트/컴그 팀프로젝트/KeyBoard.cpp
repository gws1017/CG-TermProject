#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"

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

extern float treeAngle;

extern Pokemon_Manager pm;

void Keyboard(unsigned char key, int x, int y)
{
    //디버깅용 메세지
    cout << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamY " << CamPosY << " " << "CamZ " << CamPosZ << " " << endl;
    cout/* << "CamAtX" << CamAtX << " " */ << "CamATY " << CamYAt << " " << "CamATZ " << CamZAt << " " << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamRotate " << cam_rotate << " " << "CamRevolve " << cam_revolve << " " << endl;
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
    }

   

    glutPostRedisplay();
}