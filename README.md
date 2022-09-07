# DirectX�� ������ ���� ����

- [v1.0](#v1.0)
    - [�ֿ� ���](#�ֿ�-���)
        - [â ����](#â-����)
        - [�޽��� ó�� ����](#�޽���-ó��-����)
    - [Ŭ���� ���̾�׷�](#â-����)
    - [������](#������)
    - [���� ����](#����-����)


## v1.0
[�ҽ� �ڵ�](https://github.com/jiy12345/DirectXGameEngine/tree/1.0)
### �ֿ� ���
#### â ����
- ������ â�� ���� ������ ������ ���� <u>â Ŭ���� ����</u>
```C++
ATOM JWindow::registerWNDClass()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hInstance;
	wcex.hbrBackground = CreateSolidBrush(RGB(7, 77, 7));
	wcex.lpszClassName = L"â";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_UPARROW);
	return RegisterClassEx(&wcex);
}
```
â�� ����, â���� ���� �޽��� ó���Լ�, â �������� Ŀ�� �� �پ��� ������ �� �� �ִ�.

- ������ â Ŭ������ Ȱ���Ͽ� <u>â ����</u>
```C++
	HWND hWnd = CreateWindowW(
		L"â",
		szTitle,
		m_csStyle,
		0, 0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr, nullptr,
		m_hInstance, nullptr);
```
������ â Ŭ������ �̸��� ���� �ĺ��ǹǷ�, �ݵ�� <u>�ռ� ������ â Ŭ������ �̸�</u>�� �־�� �Ѵ�!

#### �޽��� ó�� ����
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
- �޽��� ó�� �߿� �ٸ� �޽����� ó���� �����ϵ��� PeekMessage()�Լ� ��� (����: [������ ��� ���α׷��� �޽��� ó�� ���� ��: GetMessage vs PeekMessage](https://blog.naver.com/jiy12345/222649736315))
- �޽����� ������ �ʾ��� ��� frame, render �Լ��� ȣ���ϵ��� �Ͽ�, frame, render �Լ��� �����ϸ� ������ ������ �� �ֵ��� ��
### Ŭ���� ���̾�׷�

### ���� ����