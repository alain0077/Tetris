#include "SceneMgr.h"
#include "TitleScene.h"
#include "InstructScene.h"
#include "GameScene.h"
#include "ResultScene.h"

using namespace std;

SceneMgr::SceneMgr()
{
	Parameter parameter;
	_sceneStack.push(make_shared<TitleScene>(this, parameter)); //�^�C�g����ʃV�[���������push
}
/*!
@brief �X�^�b�N�̃g�b�v�̃V�[���̏���������
*/
bool SceneMgr::update()
{
	//�X�^�b�N�̃g�b�v�̃V�[�����X�V
	if (!_sceneStack.top()->update()) return false;

	//�X�^�b�N�̃g�b�v�̃V�[����`��
	_sceneStack.top()->draw();
	
	return true;
}

/*!
@brief �V�[���ύX(�e�V�[������R�[���o�b�N�����)
@param scene �ύX����V�[����enum
@param parameter �O�̃V�[����������p���p�����[�^
@param stackClear ���݂̃V�[���̃X�^�b�N���N���A���邩
*/
void SceneMgr::onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear)
{
	if (stackClear) {
		while (!_sceneStack.empty()) {
			_sceneStack.pop();
		}
	}
	switch (scene) {
	case Title:
		_sceneStack.push(make_shared<TitleScene>(this, parameter));
		break;
	case Game:
		_sceneStack.push(make_shared<GameScene>(this, parameter));
		break;
	case Instruct:
		_sceneStack.push(make_shared<InstructScene>(this, parameter));
		break;
	case Result:
		_sceneStack.push(make_shared<ResultScene>(this, parameter));
		break;
	default:
		// �G���[����
		break;
	}
}