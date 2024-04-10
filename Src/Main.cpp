#include "DxLib.h"
#include "Common.h"
#include "Scene/Play/play.h"
#include "Scene/Title/title.h"


//�ݒ�t���[�����[�g
#define FRAME_RATE (60)

//�P�t���[���̎���(�~���b)
#define FRAME_TIME (1000/FRAME_RATE)

//�t���[�����[�g���
struct FrameRateInfo {
	int currentTime;//���݂̎���
	int lastFrameTime;//�O��̃t���[�����s���̎���
	int count;//�t���[���J�E���g�p
	int calcFpsTime;//FPS���v�Z��������
	float fps;//�v������FPS
};
//�t���[�����[�g���ϐ�
FrameRateInfo frameRateInfo;

//FPS�v�Z
void CalcFps();

//FPS�\��
void DrawCalc();


//�ŏ��̃V�[��
SCENE scene=SCENE_INIT_PLAY;


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(false);

	//DX���C�u�����̏�����
	if(DxLib_Init() == -1)
	{
		return -1;
	}

	//�E�B���h�E�T�C�Y��ύX
	SetGraphMode(1280, 720, 32);

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);


	Input::Init();
	
	//=====================================
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1);

		frameRateInfo.currentTime = GetNowCount();

		if (frameRateInfo.calcFpsTime == 0.0f) {
			frameRateInfo.fps = (float)FRAME_RATE;
		}


		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME) {

			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			Input::Step();

			//�V�[���J��
			switch (scene) {

			case SCENE_INIT_TITLE:
				
				InitTitle();

				break;

			case SCENE_LOOP_TITLE:

				StepTitle();

				DrawTitle();

				break;

			case SCENE_FIN_TITLE:

				FinTitle();

				break;

			case SCENE_INIT_PLAY:
					
				InitPlay();

				break;

			case SCENE_LOOP_PLAY:
					
				StepPlay();

				DrawPlay();

				break;

			case SCENE_FIN_PLAY:

				FinPlay();

				break;
			}
			
			CalcFps();
			DrawCalc();
			
			
			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}
	}
	//�Ō�ɂP�񂾂���鏈���������ɏ���
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}


void CalcFps() {
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;


	if (difTime > 1000) {
		float frameCount = (float)(frameRateInfo.count * 1000.0f);


		frameRateInfo.fps = frameCount / difTime;

		frameRateInfo.count = 0;
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

void DrawCalc() {
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1190, 700, color, "FPS[%.2f]", frameRateInfo.fps);
}
