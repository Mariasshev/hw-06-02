// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include <string>

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */



INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


	/*  2. Регистрация класса окна  */

	if (!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход

	/*  3. Создание окна  */

	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("CV text"),	// заголовок окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
			кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения


	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна


	/* 5. Запуск цикла обработки сообщений  */

	// получение очередного сообщения из очереди сообщений
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);	// трансляция сообщения
		DispatchMessage(&Msg);	// диспетчеризация сообщений
	}
	return Msg.wParam;
}


// Оконная процедура вызывается операционной системой и получает в качестве 
// параметров сообщения из очереди сообщений данного приложения	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	const TCHAR str1[] = TEXT("Hello, my name is Matt Zimmer and I'm looking for a software engineer position at your company Acme");
	const TCHAR str2[] = TEXT("Dedicated Sales Manager with 9+ years of experience implementing strategies and exceeding sales goals in competitive environments. Lauded for my ability to recruit and supervise sales staff. Fluent and articulate communicator with a talent for creating co-operative and trusting relationships with clients and colleagues. Obtained a Master's Degree in Business Administration in 2014. Seeking a sales management position with opportunities to oversee sales policies, objectives, and initiatives.");
	const TCHAR str3[] = TEXT("Manage merchandise displays and highlight new inventory, resulting in meeting 105% of sales targets for 3 consecutive month. ﻿﻿Collaborated effectively with merchants and wholesalers to deliver excellent customer experiences. ﻿﻿Effectively maintained the company's CRM system (Salesforce)");
	const int symb = (strlen(str1) + strlen(str2) + strlen(str3)) / 3;
	TCHAR buffer[100];
	wsprintf(buffer, _TEXT("%d words in this CV"), symb);


	switch (uMessage)
	{
	case WM_CREATE:
		{
			MessageBox(
				0,
				str1,
				TEXT("CV"),
				MB_OK | MB_ICONINFORMATION
			);

			MessageBox(
				0,
				str2,
				TEXT("CV"),
				MB_OK | MB_ICONINFORMATION
			);

			MessageBox(
				0,
				str3, 
				buffer,
				MB_OK | MB_ICONINFORMATION
			);

		}

		return 0;
	
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0);	// посылка сообщения WM_QUIT
		break;
	default:
		// все сообщения, которые не обрабатываются в данной оконной 
		// функции направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
