#encoding=utf8
import os
import time
import json
import settings as config
import sqlite3
import sys
import os
from win32comext.shell import shell, shellcon
import winerror

db_path = os.path.join(config.UTILS_PATH, "my_local.db")

import ctypes,sys
def is_admin():
    try:
        return ctypes.windll.shell32.IsUserAnAdmin()
    except:
        return False

class IconOverlay1:
    _reg_clsid_ = '{512AE200-F075-41E6-97DD-48ECA4311F2E}'
    _reg_progid_ = 'Python OverlayHandler1'
    _reg_desc_ = 'Icon Overlay Handler to indicate Python packages'
    _public_methods_ = ['GetOverlayInfo', 'GetPriority', 'IsMemberOf']
    _com_interfaces_ = [shell.IID_IShellIconOverlayIdentifier]

    def GetOverlayInfo(self):
        #图标路径
        return os.path.join(config.ICO_PATH, "a.ico"), 0, shellcon.ISIOI_ICONFILE

    def GetPriority(self):
      #优先级
        return 0

    def IsMemberOf(self, fname, attributes):
        #覆盖图标的路径
        conn = sqlite3.connect(db_path, check_same_thread=False)
        cursor = conn.cursor()
        cursor.execute(f'select path,id from loacl_path where is_delete=0')
        res = cursor.fetchall()
        for file_lists in res:
            if file_lists[0] == fname:
            #满足以上条件，覆盖
                return winerror.S_OK
        cursor.close()
        conn.close()
        return winerror.S_FALSE



if __name__ == '__main__':
    import win32api
    import win32con
    import win32com.server.register

    if is_admin():
        # 注册表注册
        win32com.server.register.UseCommandLine(IconOverlay1)
        # 空格代表优先级。https://blog.csdn.net/lushangqiushui/article/details/125739480
        keyname1 = r'Software\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\ PyPackageOy2'
        key1 = win32api.RegCreateKey(win32con.HKEY_LOCAL_MACHINE, keyname1)
        win32api.RegSetValue(key1, None, win32con.REG_SZ, IconOverlay1._reg_clsid_)
    else:
        ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, __file__, None, "")
        os.system('taskkill /f /im explorer.exe & start explorer.exe ')


# 满足条件，下面的可以刷新文件路径【更新图标】
# 刷新该路径
if False:
    shell.SHChangeNotify(shellcon.SHCNE_ATTRIBUTES,
            shellcon.SHCNF_PATH | shellcon.SHCNF_FLUSHNOWAIT,
            bytes(path, "gbk"), None)
