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
	auto&& device       = DXTK->Device;
	auto&& commandQueue = DXTK->Command.Queue;

	descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 3);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	bg_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"eatspease.png", resourceUpload,
		descriptor_heap_, 0
	);
	//エマ
	ema_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"sakurabaEma.png", resourceUpload,
		descriptor_heap_, 1
	);
	//メルル
	mrr_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"hikamimrr.png", resourceUpload,
		descriptor_heap_, 2
	);

	auto&& swapChain = DXTK->SwapChain;
	RenderTargetState rts(swapChain.Format, swapChain.DepthFormat);
	SpriteBatchPipelineStateDescription pd(rts);
	sprite_batch_ = DirectXTK::CreateSpriteBatch(
		device, resourceUpload, pd, &swapChain.Viewport
	);

	auto&& uploadFinished = resourceUpload.End(commandQueue);
	uploadFinished.wait();

}

// Create independent resources.
void MainScene::CreateResources()
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	player_x_ = (DXTK->SwapChain.Width - ema_sprite_.size.x) / 1.0f;
	player_y_ = (DXTK->SwapChain.Height - ema_sprite_.size.y) / 1.0f;
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
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.
	player_x_ += 2.0f;

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	DXTK->BeginScene();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	auto&& device      = DXTK->Device;
	auto&& commandList = DXTK->Command.List;

	ID3D12DescriptorHeap* heaps[] = { descriptor_heap_->Heap() };
	commandList->SetDescriptorHeaps(std::size(heaps), heaps);

	sprite_batch_->Begin(commandList);

	sprite_batch_->Draw(
		bg_sprite_.handle, bg_sprite_.size, Vector2(0.0f, 0.0f));

	sprite_batch_->Draw(
		ema_sprite_.handle, ema_sprite_.size, Vector2(player_x_, 100.0));

	sprite_batch_->Draw(
		mrr_sprite_.handle, mrr_sprite_.size, Vector2(0.0f, 100.0f));

	sprite_batch_->End();



	DXTK->EndScene();
}
