// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

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
		TEXT("Window"),	// заголовок окна
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

int Guess()
{
	TCHAR buffer[200];
	srand(time(NULL));
	int num, msgboxID;
	num = rand() % 100 + 1;
	srand(time(NULL));
	wsprintf(buffer, TEXT("Your number is..%d"), num);
		msgboxID = MessageBox(
		0,
		buffer,
		TEXT("Game"),
		MB_YESNO | MB_ICONQUESTION
	);
	return msgboxID;
}

int PlayAgain()
{
	int msgboxID = MessageBox(
		0,
		TEXT("Want to continue?"),
		TEXT("Game"),
		MB_YESNO | MB_ICONQUESTION
	);
	return msgboxID;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{



	switch (uMessage)
	{
	case WM_CREATE:
		{
			MessageBox(
				0,
				TEXT("Guess a number from 1 to 100"),
				TEXT("Game"),
				MB_OK | MB_ICONINFORMATION
			);

		
			int rez, play;
			int count = 0;
			TCHAR buff[20];
			bool check = true;

			do {
				rez = Guess();
				switch (rez)
				{
				case IDNO:
					count++;
					break;
				case IDYES:
					wsprintf(buff, TEXT("Attemps: %d"), count);
					MessageBox(
						0,
						buff,
						TEXT("Game"),
						MB_OK | MB_ICONINFORMATION
					);

					play = PlayAgain();

					switch (play)
					{
						case IDNO:
							check = false;
							break;

						case IDYES:
							count = 0;
							break;
					}


					break;
				default:
					break;
				}

			} while (check);
			

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
