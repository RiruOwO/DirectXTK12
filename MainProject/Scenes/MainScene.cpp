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

	// TODO: Add your device-dependent creation code here.
	descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 6);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	bg_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"BG.png", resourceUpload,
		descriptor_heap_, 0
	);
	player_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"Player.tif", resourceUpload,
		descriptor_heap_, 1
	);
	redcar_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"RedCar.tif", resourceUpload,
		descriptor_heap_, 2
	);
	minivan_sprite_ = DirectXTK::CreateSpriteSRV(
		device, L"Minivan.tif", resourceUpload,
		descriptor_heap_, 3
	);
	
	// 当たり判定確認用
	collision_sprite_ = DirectXTK::CreateDefaultSpriteSRV(
		device, resourceUpload,
		descriptor_heap_, 4
	);

	sprite_font_ = DirectXTK::CreateSpriteFont(
		device, L"MSGothic.spritefont", resourceUpload,
		descriptor_heap_, 5
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
void MainScene::CreateResources()
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	InitializePlayerPostion();

	redcar_position_ = Vector2(-88.0f, 240.0f);
	minivan_position_ = Vector2(1280.0f, 314.0f);

	score_ = 0;
	rest_ = 2;
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
	// プレイヤーの移動
	Vector2 direction = Vector2(0.0f, 0.0f);
	if (InputSystem.Keyboard.isPressed.Right)
		direction += Vector2(1.0f, 0.0f);
	if (InputSystem.Keyboard.isPressed.Left)
		direction += Vector2(-1.0f, 0.0f);
	if (InputSystem.Keyboard.isPressed.Down)
		direction += Vector2(0.0f, 1.0f);
	if (InputSystem.Keyboard.isPressed.Up)
		direction += Vector2(0.0f, -1.0f);
	direction.Normalize();
	player_position_ += 200.0f * direction * deltaTime;

	// 画面の左右から出られない
	player_position_.x = std::clamp(
		player_position_.x,
		DXTK->SwapChain.Viewport.TopLeftX,
		DXTK->SwapChain.Viewport.Width - player_sprite_.size.x
	);

	// 画面の下から出られない
	player_position_.y = std::min(player_position_.y, DXTK->SwapChain.Viewport.Height - player_sprite_.size.y);

	// クリア判定
	if (player_position_.y <= 0.0f) {
		// スコアを加算する
		++score_;
		// プレイヤーの座標をスタート地点にする
		InitializePlayerPostion();
	}

	// 赤い車
	redcar_position_.x += 400.0f * deltaTime;
	if (redcar_position_.x >= 1280.0f) {
		redcar_position_.x = -88.0f;
	}

	// ミニバン
	minivan_position_.x += -200.0f * deltaTime;
	if (minivan_position_.x <= -float(minivan_sprite_.size.x)) {
		minivan_position_.x = 1280.0f;
	}

	// プレイヤーの衝突領域
	Rectangle player_collision;
	player_collision.x      = player_position_.x;
	player_collision.y      = player_position_.y;
	player_collision.width  = player_sprite_.size.x;
	player_collision.height = player_sprite_.size.y;

	// 赤い車の衝突領域
	Rectangle redcar_collision;
	redcar_collision.x = redcar_position_.x;
	redcar_collision.y = redcar_position_.y;
	redcar_collision.width = redcar_sprite_.size.x;
	redcar_collision.height = redcar_sprite_.size.y;

	if (player_collision.Intersects(redcar_collision)) {
		--rest_;
		if(rest_ < 0)
			return NextScene::GameOverScene;

		InitializePlayerPostion();
	}

	// ミニバンの衝突領域
	Rectangle minivan_collision;
	minivan_collision.x = minivan_position_.x;
	minivan_collision.y = minivan_position_.y;
	minivan_collision.width = minivan_sprite_.size.x;
	minivan_collision.height = minivan_sprite_.size.y;

	if (player_collision.Intersects(minivan_collision)) {
		--rest_;
		if (rest_ < 0)
			return NextScene::GameOverScene;

		InitializePlayerPostion();
	}

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
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
		bg_sprite_.handle, bg_sprite_.size, Vector2(0.0f, 0.0f)
	);

	sprite_batch_->Draw(
		player_sprite_.handle, player_sprite_.size, player_position_
	);

	sprite_batch_->Draw(
		redcar_sprite_.handle, redcar_sprite_.size, redcar_position_
	);
	sprite_batch_->Draw(
		minivan_sprite_.handle, minivan_sprite_.size,
		minivan_position_, nullptr, Colors::White,
		0.0f, g_XMZero, 1.0f, SpriteEffects_FlipHorizontally
	);

	// 当たり判定の表示
	Rectangle player_collision;
	player_collision.x = player_position_.x;
	player_collision.y = player_position_.y;
	player_collision.width = player_sprite_.size.x;
	player_collision.height = player_sprite_.size.y;
	XMVECTORF32 collision_color = {{{ 0.0f, 1.0f, 1.0f, 0.25f }}};	// 左からRGBA(0.0f～1.0f)
	sprite_batch_->Draw(
		collision_sprite_.handle, collision_sprite_.size,
		player_collision, nullptr, collision_color
	);

	// スコア
	sprite_font_->DrawString(
		sprite_batch_.get(), L"1-UP", Vector2(256.0f, 0.0f), Colors::White
	);

	std::wstring score_string = std::to_wstring(score_);
	Vector2 score_origin = sprite_font_->MeasureString(score_string.c_str());
	score_origin.y = 0.0f;
	sprite_font_->DrawString(
		sprite_batch_.get(), score_string.c_str(), Vector2(312.0f, 32.0f), Colors::Red,
		0.0f, score_origin
	);

	// 残機
	sprite_font_->DrawString(
		sprite_batch_.get(), L"REST", Vector2(1024.0f, 0.0f), Colors::White
	);

	std::wstring rest_string = std::to_wstring(rest_);
	Vector2 rest_origin = sprite_font_->MeasureString(rest_string.c_str());
	rest_origin.y = 0.0f;
	sprite_font_->DrawString(
		sprite_batch_.get(), rest_string.c_str(), Vector2(1080.0f, 32.0f), Colors::Red,
		0.0f, rest_origin
	);

	sprite_batch_->End();

	DXTK->EndScene();
}

void MainScene::InitializePlayerPostion()
{
	player_position_ = Vector2(
		(DXTK->SwapChain.Viewport.Width - player_sprite_.size.x) / 2.0f,
		DXTK->SwapChain.Viewport.Height - player_sprite_.size.y
	);
}