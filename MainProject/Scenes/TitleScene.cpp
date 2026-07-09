//
// TitleScene.cpp
//

#include "..\Base\pch.h"
#include "..\Base\dxtk.h"
#include "SceneFactory.h"

#ifdef _DEBUG
#pragma warning(disable : 4189)
#endif

using namespace SimpleMath;

// Initialize member variables.
TitleScene::TitleScene()
{

}

// Start is called after the scene is created.
void TitleScene::Start()
{
	LoadAssets();
	Initialize();
}

// Load resources.
//void TemplateScene::LoadAssets()
//{
//	CreateDeviceDependentResources();
//	CreateResources();
//}

// Allocate memory the Direct3D and Direct2D resources.
// These are the resources that depend on the device.
void TitleScene::CreateDeviceDependentResources()
{
	auto&& device       = DXTK->Device;
	auto&& commandQueue = DXTK->Command.Queue;

	// TODO: Add your device-dependent creation code here.
	descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 1);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	title_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"Title.png", resourceUpload,
		descriptor_heap_, 0
	);

	RenderTargetState rtState(DXTK->SwapChain.Format, DXTK->SwapChain.DepthFormat);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	auto&& viewport = DXTK->SwapChain.Viewport;
	sprite_batch_ = DirectXTK::CreateSpriteBatch(
		device, resourceUpload, pd, &viewport
	);

	auto&& uploadResourcesFinished = resourceUpload.End(commandQueue);
	uploadResourcesFinished.wait();
}

// Create independent resources.
void TitleScene::CreateResources()
{

}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{

}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	// TODO: Add a sound instance reset.
	DXTK->Audio.Engine->Suspend();



	DXTK->Audio.ResetEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.
	DXTK->DescriptorHeaps[0].reset();


}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{

}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.
	if (InputSystem.Keyboard.wasPressedThisFrame.Enter)
		return NextScene::MainScene;

	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
	DXTK->BeginScene();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	auto&& device      = DXTK->Device;
	auto&& commandList = DXTK->Command.List;

	// TODO: Add your rendering code here.
	auto&& heap = descriptor_heap_->Heap();
	commandList->SetDescriptorHeaps(1, &heap);

	sprite_batch_->Begin(commandList);

	sprite_batch_->Draw(
		title_sprite_.handle, title_sprite_.size, Vector2(0.0f, 0.0f)
	);

	sprite_batch_->End();

	DXTK->EndScene();
}
