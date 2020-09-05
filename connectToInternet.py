import requests

params = {
    "c": "Portal",
    "a": "login",
    "callback": "dr1003",
    "login_method": 1,
    "user_account": ",0,student_id@carrier", #todo edit student id and carrier
    "user_password": "password", #todo edit password
    "wlan_user_ip": "ipv4ip",  #todo edit it here
    "wlan_user_ipv6":"",
    "wlan_user_mac": "000000000000",
    "wlan_ac_ip":"",
    "wlan_ac_name":"",
    "jsVersion": "3.3.2",
    "v": 5584
}

headers = {    #定义请求头信息
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.83 Safari/537.36"
}

urlhead = "http://210.29.79.141:801/eportal/"

req = requests.get(urlhead, params=params,headers=headers)   #相当于 requests.get("http://www.baidu.com/s?wd=hello&rsv_spt=1")
