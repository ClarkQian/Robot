#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的


int getPixel(){
    HDC hDC = ::GetDC(NULL); //获取屏幕DC
    POINT pt;
    GetCursorPos(&pt);
    COLORREF clr = ::GetPixel(hDC,pt.x,pt.y);
    int res = clr;

    ::ReleaseDC(NULL, hDC);
    return clr;

}


void enter(int KeyCode){
    keybd_event(KeyCode, 0, 0, 0);
    keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
    Sleep(300);
}

void showupWindowAndFull(string software){
    if(software == "wechat") {
        // ctrl + alt + w -> show the window

        keybd_event(VK_CONTROL,(BYTE)0,0,0);
        keybd_event(VK_MENU,(BYTE)0,0,0);
        keybd_event(0x57,(BYTE)0,0,0);
        keybd_event(VK_CONTROL,(BYTE)0,KEYEVENTF_KEYUP,0);
        keybd_event(VK_MENU,(BYTE)0,KEYEVENTF_KEYUP,0);
        keybd_event(0x57,(BYTE)0,KEYEVENTF_KEYUP,0);
        Sleep(500);
        // full screen
        keybd_event(VK_LWIN,(BYTE)0,0,0);
        keybd_event(VK_UP,(BYTE)0,0,0);
        keybd_event(VK_UP,(BYTE)0,KEYEVENTF_KEYUP,0);
        keybd_event(VK_LWIN,(BYTE)0,KEYEVENTF_KEYUP,0);


    }
}
void moveCursor(int pointX,int pointY){
    SetCursorPos(pointX,pointY);//更改鼠标坐标
}

void clickLeftMouse(){
    mouse_event(MOUSEEVENTF_LEFTDOWN,0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP,0, 0, 0, 0);
}

void gtSeachAndInput(int pointX,int pointY,string key){
    SetCursorPos(pointX,pointY);//更改鼠标坐标
    //mouse left key down and up
    mouse_event(MOUSEEVENTF_LEFTDOWN,0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP,0, 0, 0, 0);
    Sleep(500);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    for(int i = 0; i < key.length(); i++){
        enter(key[i]);

    }
    Sleep(500);
    enter(VK_RETURN);
}

void getSit(){
    //click "zuowei"
    moveCursor(599,804);
    Sleep(500);
    clickLeftMouse();


    //get the sit;
    //370 758
    Sleep(1000);
    moveCursor(647, 563);
    clickLeftMouse();
    Sleep(100);
    clickLeftMouse();
    Sleep(100);
    clickLeftMouse();
    Sleep(100);
    Sleep(500);

    moveCursor(886, 567);
    clickLeftMouse();
    Sleep(100);
    clickLeftMouse();
    Sleep(100);
    clickLeftMouse();
    Sleep(100);
}

void detectMousPosition(){
    while(true){
        cout<<"Working"<<endl;
        if(KEY_DOWN(VK_LBUTTON)){
            POINT p;
            GetCursorPos(&p);
            cout<<p.x<<" "<<p.y<<endl;
        }
        if(KEY_DOWN(0x51)){
            break;
        }
        Sleep(500);
    }
}


int main() {
    showupWindowAndFull("wechat");
    gtSeachAndInput(117,30,"wqtsg");
    getSit();
//    370 758


//    detectMousPosition();
//    ::ReleaseDC(NULL, hDC); //释放屏幕DC
    return 0;

}
