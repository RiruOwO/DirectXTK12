//
// MainScene.cpp
//

#include "..\Base\pch.h"
#include "..\Base\dxtk.h"
#include "SceneFactory.h"

#ifdef _DEBUG
#pragma warning(disable : 4189)
#endif

using namespace SimpleMath;

// Initialize member variables.
MainScene::MainScene()
{

}

// Start is called after the scene is created.
void MainScene::Start()
{
	LoadAssets();
	Initialize();
}

// Load resources.
//void MainScene::LoadAssets()
//{
//	CreateDeviceDependentResources();
//	CreateResources();
//}

// Allocate memory the Direct3D and Direct2D resources.
// These are the resources that depend on the device.
void MainScene::CreateDeviceDependentResources()
{
	auto&& device = DXTK->Device;
	auto&& commandQueue = DXTK->Command.Queue;

	// TODO: Add your device-dependent creation code here.

}

// Create independent resources.
void MainScene::CreateResources()
{
	explode_se_ = DirectXTK::CreateSound(
		DXTK->Audio.Engine, L"Sounds\\Explo1.wav"
	);
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{

}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	// TODO: Add a sound instance reset.
	DXTK->Audio.Engine->Suspend();



	DXTK->Audio.ResetEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.
	DXTK->DescriptorHeaps[0].reset();

}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (InputSystem.Keyboard.wasPressedThisFrame.Enter)
		explode_se_->Play();

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	DXTK->BeginScene();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	auto&& device = DXTK->Device;
	auto&& commandList = DXTK->Command.List;

	// TODO: Add your rendering code here.


	DXTK->EndScene();
}
