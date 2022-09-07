# DirectX로 구성한 게임 엔진

- [v1.0](#v1.0)
    - [주요 기능](#주요-기능)
        - [창 생성](#창-생성)
        - [메시지 처리 루프](#메시지-처리-루프)
    - [클래스 다이어그램](#창-띄우기)
    - [문제점](#문제점)
    - [실행 예시](#실행-예시)


## v1.0
[소스 코드](https://github.com/jiy12345/DirectXGameEngine/tree/1.0)
### 주요 기능
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
### 클래스 다이어그램

### 실행 예시