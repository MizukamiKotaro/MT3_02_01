#include <Novice.h>
#include"MyMatrix4x4.h"
#include"MatrixScreenPrintf.h"
#include"MyVector3.h"
#include"VectorScreenPrintf.h"
#include"calc.h"
#include"Grid.h"
#include"Sphere.h"
#include<imgui.h>
#include"Line.h"
#include"Collision.h"
#include"Camera.h"

const char kWindowTitle[] = "学籍番号";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float speed = 0.01f;

	Camera* camera = new Camera();
	camera->Initialize({ 0.0f,1.9f,-6.49f }, { 0.26f,0.0f,0.0f });

	MyMatrix4x4 originMatrix = MyMatrix4x4::MakeAffinMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	
	Sphere s1 = {
		{-1.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{},0.8f
	};

	Sphere s2 = {
		{1.0f,0.0f,1.0f},{1.0f,1.0f,1.0f},{},0.5f
	};
	
	MyMatrix4x4 projectionMatrix = MyMatrix4x4::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	MyMatrix4x4 viewportMatrix = MyMatrix4x4::MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		ImGui::Begin("Window");
		ImGui::Text("R : Reset");
		ImGui::SliderFloat3("s1 Center", &s1.center_.x, -10.0f, 10.0f);
		ImGui::SliderFloat("s1 radius", &s1.radius_, 0.0f, 3.0f);
		ImGui::SliderFloat3("s2 Center", &s2.center_.x, -10.0f, 10.0f);
		ImGui::SliderFloat("s2 radius", &s2.radius_, 0.0f, 3.0f);
		ImGui::End();

		if (keys[DIK_R]) {
			s1 = {
				{-1.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{},0.8f
			};
			s2 = {
				{1.0f,0.0f,1.0f},{1.0f,1.0f,1.0f},{},0.5f
			};
			camera->Initialize({ 0.0f,1.9f,-6.49f }, { 0.26f,0.0f,0.0f });
		}

		camera->Update(keys, preKeys);

		MyMatrix4x4 cameraMatrix = MyMatrix4x4::MakeAffinMatrix(camera->GetScale(), camera->GetRotate(), camera->GetTranslate());
		MyMatrix4x4 viewMatrix = MyMatrix4x4::Inverse(cameraMatrix);
		MyMatrix4x4 viewProjectionMatrix = MyMatrix4x4::Multiply(viewMatrix, projectionMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		


		Grid::DrawGrid(viewProjectionMatrix, viewportMatrix);

		if (Collision::IsCollision(s1, s2)) {
			Sphere::DrawSphere(s1, viewProjectionMatrix, viewportMatrix, 0xFF0000FF);
		}
		else {
			Sphere::DrawSphere(s1, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
		}
		
		Sphere::DrawSphere(s2, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
	
		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
