


# press key

import ctypes
import time
import threading
import sys


SendInput = ctypes.windll.user32.SendInput

# C struct redefinitions
PUL = ctypes.POINTER(ctypes.c_ulong)
class KeyBdInput(ctypes.Structure):
    _fields_ = [("wVk", ctypes.c_ushort),
                ("wScan", ctypes.c_ushort),
                ("dwFlags", ctypes.c_ulong),
                ("time", ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class HardwareInput(ctypes.Structure):
    _fields_ = [("uMsg", ctypes.c_ulong),
                ("wParamL", ctypes.c_short),
                ("wParamH", ctypes.c_ushort)]

class MouseInput(ctypes.Structure):
    _fields_ = [("dx", ctypes.c_long),
                ("dy", ctypes.c_long),
                ("mouseData", ctypes.c_ulong),
                ("dwFlags", ctypes.c_ulong),
                ("time",ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class Input_I(ctypes.Union):
    _fields_ = [("ki", KeyBdInput),
                 ("mi", MouseInput),
                 ("hi", HardwareInput)]

class Input(ctypes.Structure):
    _fields_ = [("type", ctypes.c_ulong),
                ("ii", Input_I)]

#keydown listen

# import pyHook
import pyWinhook
import pythoncom

prestr = ""
tag = False



def onKeyboardEvent(event):
    # print("MessageName:", event.MessageName)
    # print("Message:", event.Message)
    # print "Time:", event.Time
    # print "Window:", event.Window
    # print "WindowName:", event.WindowName
    global prestr
    global tag

    # print("Ascii:", event.Ascii)
    # print("Key:", event.Key)
    # print("KeyID:", event.KeyID)
    prestr += event.Key
    if "INPUT" in prestr:
        print("get it!!!")
        tag = True
        prestr = ""
    # print(pre)
    # print "ScanCode:", event.ScanCode
    # print "Extended:", event.Extended
    # print "Injected:", event.Injected
    # print "Ali:", event.Ali
    # print "Transition:", event.Transition
    return True

def keyDownListen():
    # hm = pyHook.HookManager()  # 创建钩子对象
    hm = pyWinhook.HookManager()


    hm.KeyDown = onKeyboardEvent  # 注册键盘回调函数
    hm.HookKeyboard()  # 监听所有键盘事件

    pythoncom.PumpMessages()  # 持续




# Actuals Functions

def PressKey(hexKeyCode):

    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( hexKeyCode, 0x48, 0, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))

def ReleaseKey(hexKeyCode):

    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( hexKeyCode, 0x48, 0x0002, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))



# import sys
# ss = sys.stdin.readline()
# print(ord(ss[-1]))

# read clipboard
import win32clipboard as w
import win32con

def get_text():
    w.OpenClipboard()
    d = w.GetClipboardData(win32con.CF_TEXT)
    w.CloseClipboard()
    return d.decode('GBK')


def set_text(aString):
    w.OpenClipboard()
    w.EmptyClipboard()
    w.SetClipboardData(win32con.CF_TEXT, aString)
    w.CloseClipboard()


# # 读取剪切板内容

# keyDownListen()
def main():
    pre = -1
    global tag
    while True:
        time.sleep(1)
        ss = get_text()
        ss = str(ss)
        # print(ss)
        print(tag)
        if ss.startswith("zuowen") and tag == True:
            print("gggg")
            prestr = ""
            # count += 1
            # if count <= 20:
            #     continue
            # time.sleep(10)
            count = 0
            pre = -1
            for chr in ss:
                # if count == 1:
                #     count = 0
                # else:
                if pre == 13:
                    pre = -1
                    continue
                key = ord(chr.upper())
                if(chr == ' '):
                    key = 32
                if(ord(chr) == 10):
                    key = 13
                    count += 1
                if(ord(chr) == 46):#.
                    key = 110
                if(ord(chr) == 44):#,
                    key = 188
                if(ord(chr) == 63):
                    key = 191
                print(str(chr),key)
                PressKey(key)
                pre = key
                ReleaseKey(key)
            break
    return
threading.Thread(target=keyDownListen).start()
threading.Thread(target=main).start()
