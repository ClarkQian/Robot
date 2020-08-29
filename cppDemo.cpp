
#include<iostream>
#include<windows.h>
 
using namespace std;
 

//about the cursor
int main(){
	POINT p; 
	while(1){
		GetCursorPos(&p);//获取鼠标坐标 
		SetCursorPos(p.x+3,p.y);//更改鼠标坐标 
		Sleep(10);//控制移动时间间隔 
	}
	
	return 0;
}

//more about it
#include<windows.h>
int main()
{
Sleep(3000);//留3秒用于我们把鼠标移到文档上
for(int i=1;i<567;i++)
{
//模拟右键按下弹起
mouse_event(MOUSEEVENTF_RIGHTDOWN,0, 0, 0, 0);
mouse_event(MOUSEEVENTF_RIGHTUP,0, 0, 0, 0);
//模拟按下'E'键
keybd_event('E',(BYTE)0, 0 ,0);
keybd_event('E', (BYTE)0, KEYEVENTF_KEYUP,0);
Sleep(50);
//模拟按下回车，对应确定保存
keybd_event(VK_RETURN, 0, 0 ,0);
keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP,0);
Sleep(100);//等待保存
//模拟按下ctrl+PageDown键，对应翻页
keybd_event(VK_CONTROL, (BYTE)0, 0 ,0);
keybd_event(VK_NEXT,(BYTE)0, 0 ,0);
keybd_event(VK_NEXT, (BYTE)0, KEYEVENTF_KEYUP,0);
keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP,0);
Sleep(50);//等待翻页
}
return 0;
}


//demo
#include<iostream>
#include<windows.h>
 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的 
 
using namespace std;
 
int main(){
	while(1){
		printf("鼠标左键是否按下：");
		if(KEY_DOWN(VK_LBUTTON))printf("是");
		else printf("否");
		printf("\n");
		
		printf("鼠标右键是否按下：");
		if(KEY_DOWN(VK_RBUTTON))printf("是");
		else printf("否");
		printf("\n");
		
		printf("鼠标滚轮键是否按下：");
		if(KEY_DOWN(VK_MBUTTON))printf("是");
		else printf("否");
		printf("\n");
		
		Sleep(20);//循环时间间隔，防止太占内存 
		system("cls");//清屏 
	}
 
	return 0;
}


//multithread

#include <iostream>
// 必须的头文件
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS 5
 
// 线程的运行函数
void* say_hello(void* args)
{
    cout << "Hello Runoob！" << endl;
    return 0;
}
 
int main()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}

//获取桌面的所有句柄
#include <iostream>
#include <Windows.h>

using namespace std;

BOOL CALLBACK EnumChildProc(HWND   hwnd,LPARAM lParam)
{
    char szTitle[MAX_PATH] = {0};
    char szClass[MAX_PATH] = {0};
    int nMaxCount = MAX_PATH;

    LPSTR lpClassName = szClass;
    LPSTR lpWindowName = szTitle;

    GetWindowTextA(hwnd, lpWindowName, nMaxCount);
    GetClassNameA(hwnd, lpClassName, nMaxCount);
    cout << "[Child window] window handle: " << hwnd << " window name: "
         << lpWindowName << " class name " << lpClassName << endl;

    return TRUE;
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{

    /*
     * Remarks
        The EnumWindows function does not enumerate child windows,
        with the exception of a few top-level windows owned by the
        system that have the WS_CHILD style.
     */
    char szTitle[MAX_PATH] = {0};
    char szClass[MAX_PATH] = {0};
    int nMaxCount = MAX_PATH;

    LPSTR lpClassName = szClass;
    LPSTR lpWindowName = szTitle;

    GetWindowTextA(hwnd, lpWindowName, nMaxCount);
    GetClassNameA(hwnd, lpClassName, nMaxCount);
    cout << "[Parent window] window handle: " << hwnd << " window name: "
         << lpWindowName << " class name " << lpClassName << endl;

    EnumChildWindows(hwnd, EnumChildProc, lParam);

    return TRUE;
}


int main(int argc, char *argv[])
{
    EnumWindows(EnumWindowsProc, 0);
    return 0;
}
