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
	descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 3);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	bg_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"Scroll\\TestBG.png", resourceUpload,
		descriptor_heap_, 0
	);
	player_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"player.png", resourceUpload,
		descriptor_heap_, 1
	);
	enemy_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"enemy.png", resourceUpload,
		descriptor_heap_, 2
	);

	auto&& swapChain = DXTK->SwapChain;
	RenderTargetState rts(swapChain.Format, swapChain.DepthFormat);
	SpriteBatchPipelineStateDescription pd(rts, &CommonStates::NonPremultiplied);
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
	bg_position_ = Vector2(0.0f, 0.0f);
	player_position_ = Vector2(0.0f, 0.0f);
	enemy_position_ = Vector2(1280.0f - 128.0f, 720.0f - 128.0f);
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

	Vector2 direction(0.0f, 0.0f);
	if (InputSystem.Keyboard.isPressed.Right)
		direction.x += 1.0f;
	if (InputSystem.Keyboard.isPressed.Left)
		direction.x -= 1.0f;
	if (InputSystem.Keyboard.isPressed.Down)
		direction.y += 1.0f;
	if (InputSystem.Keyboard.isPressed.Up)
		direction.y -= 1.0f;

	direction.Normalize();
	player_position_ += direction * 5.0f;
	player_position_.x = std::clamp(player_position_.x, 0.0f, 1280.0f - 128.0f);
	player_position_.y = std::clamp(player_position_.y, 0.0f, 720.0f - 128.0f);

	// 背景スクロール
	bg_position_.x -= 1.0f;

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	DXTK->BeginScene();
	DXTK->ClearRenderTarget(Colors::Black);

	auto&& device = DXTK->Device;
	auto&& commandList = DXTK->Command.List;

	// TODO: Add your rendering code here.
	ID3D12DescriptorHeap* heaps[] = { descriptor_heap_->Heap() };
	commandList->SetDescriptorHeaps(std::size(heaps), heaps);

	sprite_batch_->Begin(commandList);

	sprite_batch_->Draw(
		bg_sprite_.handle, bg_sprite_.size, bg_position_
	);
	sprite_batch_->Draw(
		player_sprite_.handle, player_sprite_.size,
		player_position_
	);
	sprite_batch_->Draw(
		enemy_sprite_.handle, enemy_sprite_.size,
		enemy_position_
	);

	sprite_batch_->End();

	DXTK->EndScene();
}
