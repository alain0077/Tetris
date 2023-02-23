#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "SceneMgr.h"
#include "Keyboard.h"

/*!
* @brief DX���C�u������Q�[���̏�������
*/
bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);						//�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(TRUE);		//�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
	SetOutApplicationLogValidFlag(FALSE);		//���O�o�͂��Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//�t���X�N���[�����ɏc������ێ�����
	SetWindowText("Shooting Game");				//�E�B���h�E�^�C�g����t����
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɕύX
	SetWindowSizeExtendRate(2.5);				//�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;					//�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
	SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);		//�Q�[����ʂ̉𑜓x��ݒ肷��
	if (DxLib_Init()) {							//DX���C�u��������������
		return false;							//�ُ�I�������瑦���ɂ�߂�
	}
	SetDrawScreen(DX_SCREEN_BACK);				//����ʏ�����ݒ肷��
	return true;
}

/*!
* @brief DX���C�u������Q�[���̏I������
*/
void SystemMain::finalize() const
{

	DxLib_End();
}

/*!
* @brief ���C������
*/
void SystemMain::main() const
{
	SceneMgr sceneMgr;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (sceneMgr.update()) {
			// �X�V�������L�q
			Keyboard::getIns()->update();   //�L�[�{�[�h�̍X�V
		}
		else {
			break;
		}
	}
}