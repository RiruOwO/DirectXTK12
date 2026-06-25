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

	descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 1);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	bg_sprite_ = DirectXTK::CreateSpriteSRV(device, L"BG.png", resourceUpload, descriptor_heap_, 0);

	auto&& uploadResourceFinished = resourceUpload.End(commandQueue);
	uploadResourceFinished.wait();

}

// Create independent resources.
void MainScene::CreateResources()
{
	
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	DXTK->SwapChain.Width;
	DXTK->SwapChain.Height;
	player_position_ = Vector2(DXTK->SwapChain.Width / 2.0f, DXTK->SwapChain.Height / 2.0f);
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
