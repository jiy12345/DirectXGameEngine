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
창의 색상, 창에서 사용될 메시지 처리함수, 창 위에서의 커서 등 다양한 설정을 할 수 있다.

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
생성된 창 클래스는 이름을 통해 식별되므로, 반드시 <u>앞서 생성된 창 클래스의 이름</u>을 넣어야 한다!

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
- Windows 클래스를 [싱글톤 패턴](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Singleton%20Pattern)으로 구현하여 클래스에 대한 전역적인 접근을 GetInstance 함수를 통해 가능하도록 하였다.
- Windows 클래스에 대한 전역적인 접근점을 Getinstance 함수가 제공해주기 때문에 전역변수가 필요 없어졌고, 따라서 삭제하였다.
### 1 1 추가된 기능
- 생성된 창을 가운데로 전체 화면의 가운데로 옮겨주는 createWindow 함수를 구현하였다.
# v2 쉐이더를 제외한 간단한 렌더링 파이프라인 구성하기
## v2 0 
### 2 0 주요 기능
#### 게임 엔진 파일 분리
- 게임 엔진이라는 상위 개념의 파일을 따로 두어 하위 개념들인 Window, Device가 GameEngine 내부에서 활용되도록 하였다.
#### 렌더링 파이프라인에 필요한 주요 자원들 생성 및 초기화
- Device, Factory, Swapchain, RenderTargetView, Viewport등 화면을 출력하는데 필요한 렌더링 파이프라인의 최소한의 구성요소를 생성, 초기화 하였다.
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
스왑체인의 Present 함수를 호출하여 백버퍼와 프론트 버퍼를 교체하고, 앞서 초기화한 색의 화면이 출력될 수 있도록 하였다.
### 2 0 문제점
### 2 0 클래스 다이어그램
![class diagram2.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/class%20diagrams/ClassDiagram2.0.png)
### 2 0 실행 예시
![result image2.0](https://github.com/jiy12345/DirectXGameEngine/blob/master/images/result%20images/result%20image2.0.png)