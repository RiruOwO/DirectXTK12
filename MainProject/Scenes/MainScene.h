//
// MainScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Start() override;

	//void LoadAssets() override;
	void CreateDeviceDependentResources() override;
	void CreateResources() override;

	void Initialize() override;
	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	void InitializePlayerPostion();

	DirectXTK::DescriptorHeap descriptor_heap_;

	DirectXTK::Sprite bg_sprite_;
	DirectXTK::Sprite player_sprite_;
	SimpleMath::Vector2 player_position_;

	DirectXTK::Sprite redcar_sprite_;
	SimpleMath::Vector2 redcar_position_;

	DirectXTK::Sprite minivan_sprite_;
	SimpleMath::Vector2 minivan_position_;

	DirectXTK::Sprite collision_sprite_;

	DirectXTK::SpriteFont sprite_font_;
	int score_;
	int rest_;

	DirectXTK::SpriteBatch sprite_batch_;

	// プロトタイプの宣言(戻り値の型名 関数名(引数の型)を伝える
	void InitializeGameData();
	void InitializeRedcar();
	void InitializeMinivan();

	void MovePlayer();
	void ClampPlayerPosition();
	void ProcessClear();
	void RetryPlayer();

	void MoveRedcar();
	void MoveMinivan();

	bool CollisionDetection();

	void DrawBG();
	void DrawPlayer();
	void DrawRedcar();
	void DrawMinivan();
};