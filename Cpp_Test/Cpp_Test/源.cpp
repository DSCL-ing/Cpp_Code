#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

void mouse_keep_click_right() //右键连点
{
    cout << "UP启动当前位置鼠标连击，DOWN关闭鼠标连击；Home回到菜单。" << endl;
    POINT p;
    HWND hdc;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            cout << "鼠标点击开始！" << endl;
            GetCursorPos(&p);
            hdc = WindowFromPoint(p);
            ScreenToClient(hdc, &p);
            while (1) {
                PostMessage(hdc, WM_RBUTTONDOWN, MK_RBUTTON, MAKELONG(p.x, p.y));
                Sleep(10);
                PostMessage(hdc, WM_RBUTTONUP, 0, MAKELONG(p.x, p.y));
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    cout << "鼠标点击结束！" << endl;
                    break;
                }
            }
        }
        if (GetAsyncKeyState(VK_HOME) & 0x8000) {
            system("cls");
            cout << "选择模式:←方向键为左键连点模式,→方向键为右键连点模式" << endl;
            break;
        }
        Sleep(20);
    }
}

void mouse_keep_click() //左键连点
{
    cout << "UP启动当前位置鼠标连击，DOWN关闭鼠标连击；Home回到菜单。" << endl;
    POINT p;
    HWND hdc;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            cout << "鼠标点击开始！" << endl;
            GetCursorPos(&p);
            hdc = WindowFromPoint(p);
            ScreenToClient(hdc, &p);
            while (1) {
                PostMessage(hdc, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(p.x, p.y));
                Sleep(10);
                PostMessage(hdc, WM_LBUTTONUP, 0, MAKELONG(p.x, p.y));
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    cout << "鼠标点击结束！" << endl;
                    break;
                }
            }
        }
        if (GetAsyncKeyState(VK_HOME) & 0x8000) {
            system("cls");
            cout << "选择模式:←方向键为左键连点模式,→方向键为右键连点模式" << endl;
            break;
        }
        Sleep(20);
    }
}

int main()
{

#if 0
    cout << "鼠标连击程序开始启动...." << endl;
    cout << "UP启动当前位置鼠标连击，DOWN关闭鼠标连击；Home回到菜单。" << endl;
    thread t1(mouse_keep_click);
    t1.join();
#endif

#if 1
    cout << "鼠标连击程序开始启动...." << endl;
    cout << "选择模式:←方向键为左键连点模式,→方向键为右键连点模式" << endl;
    while (1)
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            std::cout << "左键连点模式" << std::endl;
            thread t1(mouse_keep_click);
            t1.join();
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            std::cout << "右键连点模式" << std::endl;
            thread t2(mouse_keep_click_right);
            t2.join();
        }
        else if (GetAsyncKeyState(VK_END) & 0x8000) {
            cout << "程序结束！" << endl;
            break;
        }
        //Sleep(20);
    }
#endif

    return 0;
}

