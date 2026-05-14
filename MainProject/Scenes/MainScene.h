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

	DirectXTK::DescriptorHeap descriptor_heap_;
	DirectXTK::Sprite bg_sprite_;
	DirectXTK::Sprite ema_sprite_;
	DirectXTK::Sprite mrr_sprite_;
	DirectXTK::SpriteBatch sprite_batch_;

	float player_x_, player_y_;

};