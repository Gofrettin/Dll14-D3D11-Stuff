#pragma once
#include <functional>//
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h> // color https://github.com/microsoft/DirectXMath/

#include "shader.h"
#include "rD3D11helpers.h"
/*
#include "rD3D11_VMT_Indices.h"
#include "util.h"
#include "hook.h"
*/
//https://guidedhacking.com/threads/directx11-d3d11-hook-drawing-template.15252/
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//HRESULT __stdcall hkPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);

class rD3D11;

class rD3D11
{
public:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapchain = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11InputLayout* pVertexLayout = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;
	ID3D11Buffer* pConstantBuffer = nullptr;

	HWND hWnd;
	RECT windowRect;

	D3D11_VIEWPORT pViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE]{ 0 };
	D3D11_VIEWPORT myViewport;
	DirectX::XMMATRIX mOrtho;

	//Hook presentHook;

	//hook stuff
	using fnPresent = HRESULT(__stdcall*)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
	void* oPresent;					// Pointer to the original Present function
	fnPresent oPresentTramp;		// Pointer to our trampoline

	//bool DummyDeviceGetPresent();
	//bool HookD3D();
	bool CompileShader(const char* szShader, const char* szEntrypoint, const char* szTarget, ID3D10Blob** pBlob);

	//These are all executed inside InitD3Draw()
	bool GetDeviceContextRenderTarget(IDXGISwapChain* pSwapchain);
	bool CompileShaders();
	bool GetViewport();
	bool SetupOrtho();

	bool InitD3DDraw(IDXGISwapChain* pSwapchain); //call this inside the Present() hook

	//void BeginDraw();
	void DrawLine(float x, float y, float x2, float y2, D3DCOLORVALUE color);
	void DrawLineWH(float x, float y, float width, float height, D3DCOLORVALUE color); //uses 1 vertex + width and height
	void DrawBox(float x, float y, float width, float height, D3DCOLORVALUE color);
	void TestRender();

	/*
	void CleanupD3D();
	void UnHook();

	~rD3D11();
	*/
};