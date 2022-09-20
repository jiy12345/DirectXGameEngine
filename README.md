# DirectX로 구성한 게임 엔진

- [v1 창 띄우기](#v1-창-띄우기)
  - [v1.0](#v1-0) 
    - [주요 기능](#1-0-주요-기능)
      - [창 생성](#창-생성)
      - [메시지 처리 루프](#메시지-처리-루프)
    - [문제점](#1-0-문제점)
      - [전역변수의 사용](#전역변수의-사용)
    - [클래스 다이어그램](#1-0-클래스-다이어그램)
    - [실행 예시](#1-0-실행-예시)
  - [v1.1](#v1-1)
	- [해결된 문제](#1-1-해결된-문제)
      - [전역변수의 사용](#전역변수의-사용)
    - [추가된 기능](#1-1-추가된-기능)
- [v2 쉐이더를 제외한 간단한 렌더링 파이프라인 구성하기](#v2-쉐이더를-제외한-간단한-렌더링-파이프라인-구성하기)
  - [v2.0](#v2-0) 
    - [주요 기능](#2-0-주요-기능)
      - [게임 엔진 파일 분리](#게임-엔진-파일-분리)
      - [렌더링 파이프라인에 필요한 주요 자원들 생성 및 초기화](#렌더링-파이프라인에-필요한-주요-자원들-생성-및-초기화)
      - [렌더 타겟을 특정 색으로 초기화 하여 출력](#렌더-타겟을-특정-색으로-초기화-하여-출력)
    - [문제점](#2-0-문제점)
    - [클래스 다이어그램](#2-0-클래스-다이어그램)
    - [실행 예시](#2-0-실행-예시)
  - [v2.1](#v2-1)
	- [해결된 문제](#2-1-해결된-문제)
    - [추가된 기능](#2-1-추가된-기능)
- [v3 게임 엔진에 필요한 부가 기능 추가하기](#v3-게임-엔진에-필요한-부가-기능-추가하기)
  - [v3.0](#v3-0) 
    - [주요 기능](#3-0-주요-기능)
      - [타이머-JTimer](#타이머-JTimer)
      - [입력 처리-JInput](#입력-처리-JInput)
      - [문자 출력-JWriter](#문자-출력-JWriter)
    - [문제점](#3-0-문제점)
    - [클래스 다이어그램](#3-0-클래스-다이어그램)
    - [실행 예시](#3-0-실행-예시)
- [v4 쉐이더 구성하여 도형 그릴 수 있도록 하기](#v4-쉐이더-구성하여-도형-그릴-수-있도록-하기)
  - [v4.0](#v4-0) 
    - [주요 기능](#4-0-주요-기능)
      - [HLSL 코드로 쉐이더 구성하기](#HLSL-코드로-쉐이더-구성하기)
      - [생성된 정점 쉐이더를 활용하여 Input Layout 생성하기](#생성된-정점-쉐이더를-활용하여-Input-Layout-생성하기)
      - [쉐이더에 넘겨줄 Vertex Buffer, Index Buffer 생성하기](#쉐이더에-넘겨줄-Vertex-Buffer,-Index-Buffer-생성하기)
      - [생성된 쉐이더들을 렌더링 파이프라인에 연결하여 도형 출력하기](#생성된-쉐이더들을-렌더링-파이프라인에-연결하여-도형-출력하기)
    - [문제점](#3-0-문제점)
      - [확장성 부족](#확장성-부족)
      - [쉐이더 코드의 중복 로드 가능성](#쉐이더-코드의-중복-로드-가능성)
    - [클래스 다이어그램](#3-0-클래스-다이어그램)
    - [실행 예시](#3-0-실행-예시)

# v1 창 띄우기
## v1 0
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/1.0)
### 1 0 주요 기능
#### 창 생성
- 생성될 창의 여러 설정값 지정을 위한 <u>창 클래스 생성</u>
```C++
ATOM JWindow::registerWNDClass()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hInstance;
	wcex.hbrBackground = CreateSolidBrush(RGB(7, 77, 7));
	wcex.lpszClassName = L"창";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_UPARROW);
	return RegisterClassEx(&wcex);
}
```
창의 색상, 창에서 사용될 메시지 처리함수, 창 위에서의 커서 등 다양한 설정을 할 수 있습니다.

- 생성된 창 클래스를 활용하여 <u>창 생성</u>
```C++
	HWND hWnd = CreateWindowW(
		L"창",
		szTitle,
		m_csStyle,
		0, 0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr, nullptr,
		m_hInstance, nullptr);
```
생성된 창 클래스는 이름을 통해 식별되므로, 반드시 <u>앞서 생성된 창 클래스의 이름</u>을 넣어야 합니다!

#### 메시지 처리 루프
```C++
	MSG msg = { 0, };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else
		{
			frame();
			render();
		}
	}
```
- 메시지 처리 중에 다른 메시지의 처리가 가능하도록 PeekMessage()함수 사용 (참고: [윈도우 기반 프로그램의 메시지 처리 과정 비교: GetMessage vs PeekMessage](https://blog.naver.com/jiy12345/222649736315))
- 메시지가 들어오지 않았을 경우 frame, render 함수를 호출하도록 하여, frame, render 함수를 구현하면 게임이 구성될 수 있도록 함
### 1 0 문제점
#### [전역변수의 사용](https://github.com/jiy12345/DirectXGameEngine/issues/1)
### 1 0 클래스 다이어그램
![class diagram1.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/class%20diagrams/ClassDiagram1.0.png)
### 1 0 실행 예시
![result image1.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/result%20images/result%20image1.0.png)

## v1 1
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/1.1)
### 1 1 해결된 문제
#### [전역변수의 사용](https://github.com/jiy12345/DirectXGameEngine/issues/1)
- Windows 클래스를 [싱글톤 패턴](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Singleton%20Pattern)으로 구현하여 클래스에 대한 전역적인 접근을 GetInstance 함수를 통해 가능하도록 하였습니다.
- Windows 클래스에 대한 전역적인 접근점을 Getinstance 함수가 제공해주기 때문에 전역변수가 필요 없어졌고, 따라서 삭제하였다.
### 1 1 추가된 기능
- 생성된 창을 가운데로 전체 화면의 가운데로 옮겨주는 createWindow 함수를 구현하였습니다.
# v2 쉐이더를 제외한 간단한 렌더링 파이프라인 구성하기
## v2 0 
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/2.0)
### 2 0 주요 기능
#### 게임 엔진 파일 분리
- 게임 엔진이라는 상위 개념의 파일을 따로 두어 하위 개념들인 Window, Device가 GameEngine 내부에서 활용되도록 하였습니다.
#### 렌더링 파이프라인에 필요한 주요 자원들 생성 및 초기화
- Device, Factory, Swapchain, RenderTargetView, Viewport등 화면을 출력하는데 필요한 렌더링 파이프라인의 최소한의 구성요소를 생성, 초기화 하였습니다.
#### 렌더 타겟을 특정 색으로 초기화 하여 출력
```C++
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
```
위와 같은 코드를 통해 렌더 타겟 뷰를 렌더링 파이프라인에 연결하고, 렌더 타겟 뷰를 설정한 색으로 초기화하였고, 
```C++
I_Device.m_pSwapChain->Present(0, 0);
```
스왑체인의 Present 함수를 호출하여 백버퍼와 프론트 버퍼를 교체하고, 앞서 초기화한 색의 화면이 출력될 수 있도록 하였습니다.
### 2 0 문제점
### 2 0 클래스 다이어그램
![class diagram2.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/class%20diagrams/ClassDiagram2.0.png)
### 2 0 실행 예시
![result image2.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/result%20images/result%20image2.0.png)  
렌더 타겟을 초기화할 때 설정된 색으로 화면이 출력되고 있는 것을 확인할 수 있습니다.
## v2 1
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/2.1)
### 2 1 해결된 문제
### 2 1 추가된 기능
- 게임 엔진 프로젝트를 라이브러리화 하여 외부 프로젝트에서 가져와 쓸 수있도록 하였습니다.
- 게임 엔진에 재정의 가능한 함수를 추가하여 해당 함수가 게임의 주요 루프인 run() 함수에서 호출되도록 하였다. 이 라이브러리를 활용하여 게임을 생성할 시 해당 함수들을 재정의 하여 구현하도록 하였습니다.
# v3 게임 엔진에 필요한 부가 기능 추가하기
## v3 0 
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/3.0)
### 3 0 주요 기능
#### 타이머-JTimer
- 활용된 라이브러리  
```C++
#pragma comment(lib, "winmm.lib")
```
  
- 타이머가 필요한 이유  
 게임의 어떤 한 객체가 어떤 속도로 움직인다고 할 때, 그 속도를 게임상에 표현하기 위해서는 반드시 시간 개념이 필요합니다. 
아무리 빠르게 연산하는 게임이라고 해도, 한 프레임과 다음 프레임의 출력간에는 시간 차이가 존재할 수밖에 없습니다. 
또한 연산량등의 상황이 매번 달라지므로, 그 시간차는 매번 달라지게 됩니다. 따라서 어떤 객체의 한 프레임당 변위는 속도에 이전 프레임과의 시간차를 곱한 값이 되어야 합니다.  
이러한 기능 외에도 FPS(Frame Per Second: 초당 프레임), 켰을 때부터의 시간 등 다양한 기능을 위해 시간을 측정하는 기능이 필요합니다. 
  
- 현재 구현된 주요 기능  
##### 이전 프레임과의 시간차 구하기
```C++
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_dwBeforeTime = dwCurrentTime;
```
위 코드는 매 프레임마다 현재 시간을 기존 라이브러리에 있는 timeGetTime() 함수로 구하고, 현재 시간을 활용해 이전 프레임과의 시간차를 구하여 멤버 변수에 그 시간 차 값을 받아놓는 부분이다. 
위의 코드를 통해 JTimer 클래스는 매 프레임마다 이전 프레임과의 시간차 값을 제공해줄 수 있다.  
##### FPS(Frame Per Second: 초당 프레임) 구하기
```C++
    m_iFPSCounter++;
    m_fFPSTimer += m_fElapseTimer;
    if (m_fFPSTimer >= 1.0f) {
        m_iFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_fFPSTimer = m_fFPSTimer - 1.0f;
    }
```
위와 같은 코드를 통해 초당 출력되고 있는 프레임의 수를 세고, 그 값을 JTimer 클래스의 멤버 변수로 유지하여 다른 필요한 곳에서 활용할 수 있도록 합니다.
#### 입력 처리-JInput  
- 현재 구현된 주요 기능  
##### 현재 눌려있는 키 상태 저장하기
```C++
    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
        {
            if (m_dwKeyState[iKey] == KEY_FREE ||
                m_dwKeyState[iKey] == KEY_UP)
                m_dwKeyState[iKey] = KEY_PUSH;
            else
                m_dwKeyState[iKey] = KEY_HOLD;
        }
        else
        {
            if (m_dwKeyState[iKey] == KEY_PUSH ||
                m_dwKeyState[iKey] == KEY_HOLD)
                m_dwKeyState[iKey] = KEY_UP;
            else
                m_dwKeyState[iKey] = KEY_FREE;
        }
    }
```
위 코드를 통해 JInput 클래스는 각 키가 눌려있는 상태를 저장하고,
```C++
DWORD  JInput::GetKey(DWORD dwKey)
{
    return m_dwKeyState[dwKey];
}
```
위의 함수를 통해 외부에서 요청하였을 때 각 키의 상태를 반환합니다.
```C++
enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
```
각 키의 상태는 위의 열거형 상수를 통해 구분됩니다. KEY_FREE는 눌려있지 않은 상태를, KEY_UP은 눌려져 있는 상태였다가 뗄 때의 상태를, 
KEY_PUSH는 누를 때의 상태를, KEY_HOLD는 누르고 있을 때의 상태를 나타냅니다.
##### 커서의 현재 위치 구하기
```C++
    ::GetCursorPos(&m_ptPos);
    ::ScreenToClient(I_Window.m_hWnd, &m_ptPos);
```
위 코드를 통해 현재 클라이언트(메뉴바, 타이틀 바 등을 제외한 순수 출력되는 화면)상에서의 위치를 매 프레임마다 유지하여, 다른 클래스에서 커서의 현재 위치를 요청하였을 때 반환할 수 있도록 합니다.
#### 문자 출력-JWriter
- 활용된 라이브러리  
```C++
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
```
- dwrite 라이브러리의 단점  
 dwrite 라이브러리는 단순히 봤을 때는 비교적 짧은 코드로 간단히 문자를 화면에 출력해주는 편리한 라이브러리로 보일 수 있습니다.
그러나 dwrite 라이브러리에는 치명적인 문제가 존재합니다. 바로 속도가 매우 느리다는 것입니다.
dwrite 라이브러리는 d2d1라이브러리를 통해 2d 렌더링 파이프라인을 따로 구성하고, 그 구성한 파이프라인을 통해 문자를 '그려'주고 있는 것입니다. 
이처럼 매우 속도가 느리므로, 게임상에 글씨를 출력하는데는 활용되지 않습니다.  
 현 프로젝트에서는 화면에 FPS값을 띄워주는 데 활용됩니다.

### 3 0 문제점
### 3 0 클래스 다이어그램
![class diagram3.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/class%20diagrams/ClassDiagram3.0.png)
### 3 0 실행 예시
![result image3.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/result%20images/result%20image3.0.png)  
프로젝트의 실행 시작 시점부터 현재까지의 시간과 FPS가 출력되는 것을 확인할 수 있습니다.
# v4 쉐이더 구성하여 도형 그릴 수 있도록 하기
## v4 0 
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/4.0)
### 4 0 주요 기능
#### HLSL 코드로 쉐이더 구성하기
- hlsl 코드란?
 HLSL은 DirectX에서 프로그래밍 가능한 쉐이더와 함께 사용하는 C와 유사한 고수준 쉐이더 언어입니다.
프로그래머는 hlsl 코드를 통해 렌더링 파이프라인에 필요한 정점 쉐이더, 픽셀 쉐이더에 대한 코드를 작성할 수 있습니다. 
각각의 hlsl 코드는 다음과 같은 과정을 거쳐 렌더링 파이프라인에서 활용될 수 있는 쉐이더를 구성하게 됩니다.
1. hlsl 코드를 hlsl 컴파일러로 컴파일하여 이진 코드 형태로 받아옵니다.  
  
 hlsl 코드는 C와 유사한 프로그래밍 언어이기는 하지만 엄연히 다른 언어이므로, 다른 컴파일러가 필요합니다.
 따라서 D3DCompileFromFile() 함수를 통해 hlsl 컴파일러로 컴파일해야 합니다.
```C++
    hr = D3DCompileFromFile(
        filename.c_str(), // hlsl 코드 파일의 파일명
        NULL,
        NULL,
        "VS", // 쉐이더를 나타낼 함수의 함수명
        "vs_5_0", // 쉐이더의 종류와 버전명
        0,
        0,
        &m_pVSCode, // hlsl 코드를 컴파일한 결과물인 이진 코드의 주소를 받아올 변수
        &pErrorCode);
```
위의 함수를 실행하면 함수 내부에서 hlsl코드의 컴파일러에 의해 컴파일된 결과가 m_pVSCode 변수에 저장됩니다.  
  
2. 이진 코드를 활용하여 쉐이더 생성하기  
   
컴파일된 이진 코드를 가지고 Create ... Buffer() 함수를 호출하면 렌더링 파이프라인에 결합 가능한 쉐이더가 완성됩니다.
```C++
    hr = I_Device.m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS // 생성된 정점 쉐이더가 저장될 변수
);
```
위와 같은 코드가 바로 앞서 컴파일한 이진 코드를 활용하여 쉐이더를 생성하는 코드입니다.

#### 생성된 정점 쉐이더를 활용하여 Input Layout 생성하기
- Input Layout이란?  
 렌더링 파이프라인에서 특정 객체를 그리기 위해서는 정점의 위치, 색상등의 정보들이 쉐이더에 전달되어 그래픽 카드에서 처리되어야 합니다.
 그런데 그러한 데이터가 그래픽 카드에 전달되는 순간 우리가 C코드로 작성할때는 명확했던 각 데이터간의 경계를 알 수 없게 됩니다. 
 따라서 각 데이터가 어떤 데이터인지 식별하기 위한 일종의 '데이터 사용 설명서'를 그래픽 카드에게 넘겨주어야 하고, 그게 바로 Input Layout입니다.

1. Vertex Shader에 넘겨줄 데이터의 형태 결정하기
```C++
    // Vertex Shader에 넘어갈 데이터의 형태
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
```
 위 코드는 Vertex Shader에 넘겨줄 데이터의 형태를 알려준다고 볼 수 있으며, 위 코드는 3가지의 데이터를 넘기고 있는 것으로 이해할 수 있습니다.
 각각의 한줄은 [D3D11_INPUT_ELEMENT_DESC](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_input_element_desc) 하나를 의미하며, 각각의 D3D11_INPUT_ELEMENT_DESC
 하나는 각 데이터의 이름, 각 데이터가 포함한 데이터들의 기본 크기 등 각 데이터를 식별하는데 필요한 정보를
 가지고 있습니다. 각각의 원소가 의미하는 바를 조금 더 자세히 알고 싶다면 다음의 링크를 참조 바랍니다.
  
[D3D11_INPUT_ELEMENT_DESC](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_input_element_desc)
   
2. 데이터의 형태에 따른 Input Layout 생성하기  
```C++
    // 요소의 개수 계산
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    
    // InputLayout을 생성하는 함수 호출
    hr = I_Device.m_pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
```
위의 코드는 앞서 생성한 D3D11_INPUT_ELEMENT_DESC들을 바탕으로 Input Layout을 설정하는 코드입니다.

#### 쉐이더에 넘겨줄 Vertex Buffer, Index Buffer 생성하기
- Vertex Buffer, Index Buffer란?  
 아래의 글을 참고 바랍니다.  

 [Input Assembler(IA) 단계에서는 어떤 작업이 이루어질까?](https://blog.naver.com/jiy12345/222701037912)
1. Vertex Buffer, Index Buffer가 될 데이터 작성하기
```C++
void    JShader::setVertexData() {
    m_VertexList.resize(4);
    m_VertexList[0].p = { -0.5f, 0.5f, 0.0f };
    m_VertexList[1].p = { +0.5f, 0.5f,  0.0f };
    m_VertexList[2].p = { -0.5f, -0.5f, 0.0f };
    m_VertexList[3].p = { 0.5f, -0.5f, 0.0f };

    m_VertexList[0].c = { 1.0f, 0.0f, 1.0f, 1.0f };
    m_VertexList[1].c = { 0.0f, 1.0f, 1.0f, 1.0f };
    m_VertexList[2].c = { 1.0f, 1.0f, 0.0f, 1.0f };
    m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 1.0f };

    m_VertexList[0].t = { 0.0f, 0.0f };
    m_VertexList[1].t = { 1.0f, 0.0f };
    m_VertexList[2].t = { 0.0f, 1.0f };
    m_VertexList[3].t = { 1.0f, 1.0f };
}
void    JShader::setIndexData() {
    m_IndexList.resize(6);
    m_IndexList[0] = 0;
    m_IndexList[1] = 1;
    m_IndexList[2] = 2;
    m_IndexList[3] = 2;
    m_IndexList[4] = 1;
    m_IndexList[5] = 3;
}
```
2. 작성한 데이터를 버퍼 형태로 변경
```C++
HRESULT JShader::createVertexBuffer() {
    // 버퍼 데이터 작성해주는 함수
    setVertexData();

    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
    // GPU/CPU에서 읽기, 쓰기 가능 여부 설정
    bd.Usage = D3D11_USAGE_DEFAULT; // DEFAULT는 GPU에서만 읽기 쓰기 가능
    // 어떤 버퍼인지 설정
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_VertexList.at(0);
    return I_Device.m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼에 대한 설정값 전달
        &sd, // 작성한 데이터
        &m_pVertexBuffer); // 생성된 버퍼를 넘겨받을 변수 작성
}
HRESULT JShader::createIndexBuffer() {
    setIndexData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_IndexList.at(0);
    return I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pIndexBuffer);;
}
```

#### 생성한 부품들을 렌더링 파이프라인에 연결하여 도형 출력하기
 앞서 한 동작들이 전체 기계에 필요한 각각의 부품을 제작하는 과정이었다면, 이 과정은 제작한 모든 부품을 렌더링 파이프라인이라는
 기계에 장착하는 과정입니다.  
1. 각각의 부품들 렌더링 파이프라인에 연결하기
```C++
    // Input Layout 연결
    I_Device.m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    // Vertex Shader 연결
    I_Device.m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    // Pixer Shader 연결
    I_Device.m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    
    // 실제 정점 정보를 가진 버퍼 연결
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    I_Device.m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);
    I_Device.m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer,
        DXGI_FORMAT_R32_UINT, 0);
```
 위 코드는 앞서 생성한 모든 부품들을 렌더링 파이프라인에 연결하는 코드입니다.

### 4 0 문제점
#### 확장성 부족
[해당 이슈](https://github.com/jiy12345/DirectXGameEngine/issues/10)
#### 쉐이더 코드의 중복 로드 가능성
[해당 이슈](https://github.com/jiy12345/DirectXGameEngine/issues/11)
### 4 0 클래스 다이어그램
 앞서 언급한 여러 문제점들 때문에 JShader 클래스를 아직 라이브러리에 통합하지 않았고, 따라서 엔진 라이브러리 상의 변화는 없다.
### 4 0 실행 예시