# 项目流程视频：https://www.bilibili.com/video/BV1KQ4y137Nc/?spm_id_from=333.999.0.0&vd_source=cd63df8900a120533b99a58a012c8f83

# 项目组成


## 场景


1.开场动画场景 （BeginGame.cpp && BeginGame.h）

2.开始游戏场景（Interface.cpp && Interface.h）

3.主要游戏场景（MainScene.cpp && MainScene.h）

4.五子棋场景（Gobang.cpp && Gobang.h）

## 层


1.继续游戏（continueLayer.cpp && continueLayer.h）

2.开场动画（openingShowLayer.cpp && openingShowLayer.h）

## 控件


1.带文字的按钮（buttonWithText.cpp && buttonWithText.h）

2.五子棋棋盘（chessBoard.cpp && chessBoard.h）

3.五子棋棋子（chessPiece.cpp && chessPiece.h）

4.五子棋游戏控制器（GobangController.cpp && GobangController.h）

5.带对话框的文字（textBox.cpp && textBox.h）

6.会行走的coco精灵（walkingCoco.cpp && walkingCoco.h）  

# 项目介绍


## 亮点/难点


1.五子棋游戏控制器（GobangController.cpp && GobangController.h）使用的是单例模式。

2.主要游戏场景（MainScene.cpp && MainScene.h）中精灵移动的方式是通过左右按钮移动：精灵只会在屏幕的中间一部分移动(我设置的是距离屏幕左右边缘110像素的范围)，当超过这个范围，精灵只会显示原地踏步的动画不再移动，同时地图进行反方向移动，这样看起来就像精灵继续移动一样。

3.主要游戏场景（MainScene.cpp && MainScene.h）使用了paraNode进行视差滚动。

4.五子棋游戏控制器（GobangController.cpp && GobangController.h）进行胜负判断的时候，要从当前下的棋子往8个方向进行延申，记录棋子数（循环8次）。之后从4个方向进行判断，将相反方向的棋子数相加，看看是否为5.（循环4次）。

5.带对话框的文字（textBox.cpp && textBox.h）使用九宫格精灵创建的对话框，这样无论有多少文字，对话框大小会随着文字数量/大小的变化而变化。

6.五子棋棋盘（chessBoard.cpp && chessBoard.h）中棋子的落点位置(x,y)和屏幕上实际的棋子的位置(x,y)进行坐标转换。

