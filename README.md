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
### 1 1 해결된 문제
#### [전역변수의 사용](https://github.com/jiy12345/DirectXGameEngine/issues/1)
- Windows 클래스를 [싱글톤 패턴](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Singleton%20Pattern)으로 구현하여 클래스에 대한 전역적인 접근을 GetInstance 함수를 통해 가능하도록 하였습니다.
- Windows 클래스에 대한 전역적인 접근점을 Getinstance 함수가 제공해주기 때문에 전역변수가 필요 없어졌고, 따라서 삭제하였다.
### 1 1 추가된 기능
- 생성된 창을 가운데로 전체 화면의 가운데로 옮겨주는 createWindow 함수를 구현하였습니다.
# v2 쉐이더를 제외한 간단한 렌더링 파이프라인 구성하기
## v2 0 
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
### 2 1 해결된 문제
### 2 1 추가된 기능
- 게임 엔진 프로젝트를 라이브러리화 하여 외부 프로젝트에서 가져와 쓸 수있도록 하였습니다.
- 게임 엔진에 재정의 가능한 함수를 추가하여 해당 함수가 게임의 주요 루프인 run() 함수에서 호출되도록 하였다. 이 라이브러리를 활용하여 게임을 생성할 시 해당 함수들을 재정의 하여 구현하도록 하였습니다.
# v3 게임 엔진에 필요한 부가 기능 추가하기
## v3 0 
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