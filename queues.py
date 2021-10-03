#!/usr/bin/python3
 
import tkinter
from tkinter import * 
import time
import threading

NUM_QUEUES = 8 # 皇后数目
BLOCK_SIZE = 50 # 每个格子的大小

x_WIDTH = NUM_QUEUES * BLOCK_SIZE # 界面宽度
x_HEIGHT = NUM_QUEUES * BLOCK_SIZE # 界面高度
X = 0
Y = 0

STEP_COLOR = "black" # 搜索中的颜色
ANS_COLOR = "green" # 找到答案的颜色
WRONG_COLOR = "red" # 错误时的颜色

SPEED = 0.05 # 每一步睡眠的时间

# https://blog.csdn.net/qq_42402648/article/details/109822589
root = tkinter.Tk()
root.geometry(str(x_WIDTH) + "x" + str(x_HEIGHT) + "+" + str(X) + "+" + str(Y)) 
cv = Canvas(root,bg = 'white',height=x_HEIGHT,width=x_WIDTH)

def draw(state_map,color):
    for i in range(len(state_map)):
        for j in range(len(state_map[0])):
            ly = i * BLOCK_SIZE
            lx = j * BLOCK_SIZE
            ry = (i + 1) * BLOCK_SIZE
            rx = (j + 1) * BLOCK_SIZE
            if state_map[i][j] == 0:
                cv.create_rectangle(lx,ly,rx,ry,fill="white")
            else:
                cv.create_rectangle(lx,ly,rx,ry,fill=color)        
    cv.pack()   
    time.sleep(SPEED)

def init_state_map():
    state_map = []
    for i in range(NUM_QUEUES):
        line = []
        for j in range(NUM_QUEUES):
            line.append(0)
        state_map.append(line)
    return state_map

def conflict(state_map,row,column):
    for i in range(row):
        j = state_map[i].index(1)
        if abs(row - i) == 0:
            return True
        if abs(column - j) == 0:
            return True
        if abs(row - i) == abs(column - j):
            return True
    return False

def solve(state_map,row):
    draw(state_map,STEP_COLOR)
    for column in range(NUM_QUEUES):
        state_map[row][column] = 1
        if not conflict(state_map,row,column):
            if row == (NUM_QUEUES - 1):
                draw(state_map,ANS_COLOR)
            else:
                solve(state_map,row+1)
        else:
            draw(state_map,WRONG_COLOR)
        state_map[row][column] = 0

def solve_in_thread():
    time.sleep(0.5)
    state_map = init_state_map()
    solve(state_map,0)

t = threading.Thread(target=solve_in_thread,args=())
t.setDaemon(True)
t.start()

root.mainloop()

t.join()
