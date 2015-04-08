//
// Game.h
//

#pragma once

#include "pch.h"

#include "StepTimer.h"
#include "SpriteFont.h"
#include "Audio.h"
#include "vce.h"

using namespace DirectX;


// A basic game implementation that creates a D3D11 device and
// provides a game loop
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();
    void Present();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged();
	void OnKeydown(int keycode);

    // Properites
    void GetDefaultSize( size_t& width, size_t& height ) const;

    // networking
    static const int CHANNEL_ID = 12345;
    void incrementPong() { m_pong_recv_count++; };
    static const int PACKET_TYPE = 3456;
    void channelJoined() { m_channel_joined = true; }
    void incrementChannelcastNotify() { m_channelcast_notify_count++; }
    
private:

    void Update(DX::StepTimer const& timer);

    void CreateDevice();
    void CreateResources();
    
    void OnDeviceLost();

    // Application state
    HWND                                            m_window;

    // Direct3D Objects
    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    // Rendering resources
    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_depthStencil;

    // Game state
    DX::StepTimer                                   m_timer;
	int m_framecnt;

	// Show status logs
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

	AudioEngine *m_audioEngine;
	SoundEffect *m_soundEffect;

    // network
    conn_t m_rtConn;
    int m_pong_recv_count;
    bool m_channel_joined;
    int m_channelcast_notify_count;
    
};
