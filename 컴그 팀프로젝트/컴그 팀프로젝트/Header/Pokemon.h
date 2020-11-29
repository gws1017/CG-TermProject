#pragma once
#include "header.h"


class Pokemon {

	GLuint vao, vbo[3], ebo;

	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	int width, height, nrChannels;
	unsigned int texture;

	
	char* Filename, *Texturename; //파일이름, 텍스처파일이름
	char* name; //포켓몬 이름
	int nsize; //포켓몬 이름 길이
	float p_height; //포켓몬 키
	int Act_Type; //임의로 행동을 부여하기위한 변수
	glm::vec3 pos; //포켓몬 현재 위치

	//모델 변환행렬
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 PKM = glm::mat4(1.0f); //포켓몬 초기세팅 행렬

	glm::mat4 PT = glm::mat4(1.0f);

	//모델 애니메이션
	glm::mat4 JMP = glm::mat4(1.0f); //점프 행렬
	float jmpy = 0.0f;  //점프 이동량
	int delta_jy = 1;  //점프 변화량
	int jumptimer = 0; //재 점프대기시간

	glm::mat4 SW = glm::mat4(1.0f);  //스윙 행렬
	glm::mat4 SWR = glm::mat4(1.0f); //스윙 회전
	glm::mat4 SWT = glm::mat4(1.0f);  //스윙 축이동
	glm::mat4 SWT2 = glm::mat4(1.0f); //스윙 축이동 원위치
	float SWRa = 0.0f; // 스윙각도 변수
	float sw_speed = 1.0f; // 스윙 속도
	int delta_SWT = 1, delta_SW = 1; // 스윙변화량 제어 변수

	glm::mat4 ROT = glm::mat4(1.0f); // 회전(뱅글뱅글) 행렬

	glm::mat4 FLO = glm::mat4(1.0f); // 둥둥 떠다니는 행렬
	int delta_fy = 1; // 둥둥 변화량
	float floy = 0.0f; // 둥둥 이동량

public:

	// 생성자 포켓몬 생성시 이름을 적어주세요
	Pokemon(const char* n); 
	//소멸자
	~Pokemon();

	int Get_Act_Type();
	int Get_PosX();
	int Get_PosZ();
	float Get_p_height();
	

	void Set_Pos(float x, float y, float z);

	void Init(const GLuint s_program);

	//포켓몬 이름에따라 변수를 초기화 해주는 함수
	void Has_Pokemon();

	//포켓몬 위치 재지정
	void Position();

	void Draw(const unsigned int modelLocation);

	void Update_Pos();

	//포켓몬 애니메이션

	//점프1
	void Jump();
	// 점프2 
	void Jump2();
	//스윙 
	void Swing();
	//빙글빙글 
	void Rotate();
	//둥둥 
	void Float(float _h);
	//토네이도
	void Tornado();

};

