# 辉光钟--By drinow
## 条目解释
- MyNixie/Version2.0为工程文件，其余为一些资料或者测试数据

## 实物图
![image](https://github.com/drinow/MyNixieClock/blob/master/MyNixie/Version2.0/picture/nixietube1.jpg)
![image](https://github.com/drinow/MyNixieClock/blob/master/MyNixie/Version2.0/picture/FunctionDefine.jpg)

## 硬件错误
- IRF740的封装画的有些小了，有点难焊，其余没有问题；
- CH340串口电路封装错误导致无法使用DTR、RTS，但可正常通信；

## 重要变化
- 已支持湿度检测功能(传感器SHT20),但需要改装硬件（拆下R3、C3,SHT20占用[KEY GND 3V3 LAMP]排针孔）,同时
未添加湿度传感器自检代码因此对于未改装的电路烧录此程序会运行异常。
- 你可以通过全局搜索来屏蔽/删除相关变量：SHT20.TEMP_POLL, SHT20.HUMI_POLL，以使得无SHT20的钟正常运行。

## 支持的功能
	1.时分显示
	2.日期显示
	3.温湿度显示
	4.8种单色灯+1种彩色灯
	5.氛围灯呼吸、常亮、关闭功能
	6.防阴极中毒
	7.一组闹铃
	8.遥控器控制
	9.整点报时
	10.自动夜间免打扰
