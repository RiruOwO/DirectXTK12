//
// TemplateScene.cpp
//

#include "..\Base\pch.h"
#include "..\Base\dxtk.h"
#include "SceneFactory.h"

#ifdef _DEBUG
#pragma warning(disable : 4189)
#endif

using namespace SimpleMath;

// Initialize member variables.
GameOverScene::GameOverScene()
{

}

// Start is called after the scene is created.
void GameOverScene::Start()
{
	LoadAssets();
	Initialize();
}

// Load resources.
//void GameOverScene::LoadAssets()
//{
//	CreateDeviceDependentResources();
//	CreateResources();
//}

// Allocate memory the Direct3D and Direct2D resources.
// These are the resources that depend on the device.
void GameOverScene::CreateDeviceDependentResources()
{
	auto&& device       = DXTK->Device;
	auto&& commandQueue = DXTK->Command.Queue;

	// TODO: Add your device-dependent creation code here.

}

// Create independent resources.
void GameOverScene::CreateResources()
{

}

// Initialize a variable and audio resources.
void GameOverScene::Initialize()
{

}

// Releasing resources required for termination.
void GameOverScene::Terminate()
{
	// TODO: Add a sound instance reset.
	DXTK->Audio.Engine->Suspend();



	DXTK->Audio.ResetEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.
	DXTK->DescriptorHeaps[0].reset();


}

// Direct3D resource cleanup.
void GameOverScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void GameOverScene::OnRestartSound()
{

}

// Updates the scene.
NextScene GameOverScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.



	return NextScene::Continue;
}

// Draws the scene.
void GameOverScene::Render()
{
	DXTK->BeginScene();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	auto&& device      = DXTK->Device;
	auto&& commandList = DXTK->Command.List;

	// TODO: Add your rendering code here.



	DXTK->EndScene();
}
