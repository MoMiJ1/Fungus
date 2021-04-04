import sys
if sys.version_info.major < 3:
    import Tkinter
else:
    import tkinter as Tkinter


'''
    【基本控件】
    1. Radiobutton(root, text, variable, value)
        :param root: Tk
        :param text: 选项的文本
        :param variable: 绑定选择的变量
        :param value: 该选项对应的值

    2. Button(root, text, command)
        :param root: Tk
        :param text: 选项的文本
        :param command: 点击时调用的函数

    3. Checkbutton(root, text, variable)
        :param root: Tk
        :param text: 选项的文本
        :param variable: 绑定选择变量

    4. Scale(root, label, length, from_, to, resolution, variable, orient)
        :param root: Tk
        :param label: 显示的名称
        :param length: 滑块长度
        :param from_: 左边界
        :param to: 右边界
        :param resolution: 步长
        :param variable: 绑定选择变量
        :param orient: 滑动方向
        
    5. Label(root, text, textvariable, font, justify, foreground, underline, anchor, width, height, bg)
        :param text: 静态文本
        :param textvariable: 动态文本
        :param font: 字体，格式为一个tuple (font_name, font_size)
        :param justify: 对齐方式，有:['center','left','right']
        :param foreground: 文本颜色
        :param underline: 单个字符添加下划线，传入值为目标字符串的索引
        :param anchor: 位置，可选(n,s,w,e,ne,nw,sw,se,center)，eswn对应东南西北
        
    6. grid(row, column)
        :param row: 控件所在的行位置
        :param column:控件所在的列位置  
'''
def basic_widget(method="pack"):
    def initUI(name='gui', size='900x600'):
        root = Tkinter.Tk()
        root.title(name)
        root.geometry(size)
        return root

    def click(i):
        if i == 1:
            print('选择：', choose_list[choose.get()])
        elif i == 2:
            selects = []
            for k, v in abcd.items():
                if v.get(): selects.append(k)
            print("选择：", selects)
        elif i == 3:
            print(factor.get())


    if __name__ == "__main__":
        root = initUI()

        # 单选
        choose_list = ['A', 'B', 'C', 'D']
        choose = Tkinter.IntVar()
        choose.set(0)
        for i, val in enumerate(choose_list):
            Tkinter.Radiobutton(root, text=val, variable=choose, value=i).pack()
        Tkinter.Button(root, text="单选", command=click(1)).pack()

        # 复选
        a, b, c, d = Tkinter.BooleanVar(), Tkinter.BooleanVar(), Tkinter.BooleanVar(), Tkinter.BooleanVar()
        abcd = {'A': a, 'B': b, 'C': c, 'D': d}
        for k, v in abcd.items():
            v.set(0)
            Tkinter.Checkbutton(root, text=k, variable=v).pack()
        Tkinter.Button(root, text="复选", command=click(2)).pack()

        # 滑块
        factor = Tkinter.DoubleVar()
        factor.set(0.800)
        Tkinter.Scale(root, label='滑块', length=200, from_=0., to=1.0, resolution=0.001,
                      variable=factor, orient=Tkinter.HORIZONTAL).pack()
        Tkinter.Button(root, text='输出', command=click(3)).pack()

        # 文本显示
        text = Tkinter.StringVar()
        text.set("This is a text;这是个文本。")
        label = Tkinter.Label(root,textvariable=text,font=('宋体',15),foreground='black',
                      underline=3,anchor='nw',width=30,height=2,bg='white')

        # 文本输入
        e = Tkinter.Entry(root)
        e.pack()
        Tkinter.Button(root, text="修改").pack()

        root.mainloop()



'''
    【画布】
    1. Canvas(root, bg, width, height)
        :param root: Tk
        :param bg: 画布背景颜色
        :param width: 画布宽
        :param heigth: 画布高
        
    2. create_line(point, arrow, arrowshape, dash, width)
        :param point: 要连线的点的坐标
        :param arrow: 箭头，first--箭头在起始点，last--箭头在目标点，both--双箭头
        :param arrowshape: 箭头大小，传入一个tuple，如--(3,4,5)
        :param dash: 是否绘制虚线，默认False
        :param width: 线的宽度
        :param tags: 标签
        
    3. create_oval(point, fill, outline, width)
        :param point: 椭圆的外接矩形的左上角和右下角坐标
        :param fill: 内部填充颜色
        :param outline: 边颜色
        :param width: 边宽
        :param tags: 标签
        
    4. create_text(point, text, font)
        :param point: 文字所在点
        :param text: 文本内容
        :param font: 使用字体，传入tuple，如：("宋体",12)
        
    5. bind(event, handler)
        :param event: 
            常用的:
            (1) 26个字母，如: 'n','s'等，直接按键盘对应的键就可
            (2) <Button-1>:鼠标左键点击, <Button-3>: 右键点击
                <Button-4>: 向上滚轮, <Button-5>: 向下滚轮
                <Double-Button-1>: 左键双击，右键同理
            (3) <Return>:回车；<BackSpace>:删除；<Escape>:esc
                <Left>,<Up>,<Right>,<Down>: 方向键
        :param handler: event发生后的操作，可以是一个函数
'''
# 画布
def tk_canvas():
    def initUI(name='windows', size='900x600', width=900, height=500, bg='white'):
        root = Tkinter.Tk()
        root.geometry(size)
        root.title(name)
        cv = Tkinter.Canvas(root, bg=bg, width=width, height=height)
        return root,cv


    if __name__ == "__main__":
        root,cv = initUI()
        p1 = [[100,100],[300,200]]

        cv.create_line(p1,arrow="first",arrowshape=(7,7,7),dash=True,width=5,tags="line")
        cv.create_oval(p1,outline='blue',fill="pink",width=10,tags="oval")
        cv.create_text((400,300),text="hello",font=("source code pro",12))
        cv.grid(row=0)

        Tkinter.Button(root,text="btn1").grid(row=1,column=0)
        Tkinter.Button(root,text="btn2").grid(row=2)

        root.mainloop()


if __name__ == "__main__":
    basic_widget()
    tk_canvas()

