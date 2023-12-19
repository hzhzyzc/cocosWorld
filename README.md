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

3.主要游戏场景（MainScene.cpp && MainScene.h）使用了paranote进行视差滚动。

4.五子棋游戏控制器（GobangController.cpp && GobangController.h）进行胜负判断的时候，要从当前下的棋子往8个方向进行延申，记录棋子数（循环8次）。之后从4个方向进行判断，将相反方向的棋子数相加，看看是否为5.（循环4次）。

5.带对话框的文字（textBox.cpp && textBox.h）使用九宫格精灵创建的对话框，这样无论有多少文字，对话框大小会随着文字数量/大小的变化而变化。

6.五子棋棋盘（chessBoard.cpp && chessBoard.h）中棋子的落点位置(x,y)和屏幕上实际的棋子的位置(x,y)进行坐标转换。


## 遇到的问题及解决方法（成功解决）


###  问题：
在从主要游戏场景（MainScene.cpp && MainScene.h）向五子棋场景（Gobang.cpp && Gobang.h）进行场景切换的时候，如果使用replaceScene的话，退出五子棋场景以后，会回到主要游戏场景最开始的地方。
###  解决方法：
使用pushScene和popScene，这样是将主要游戏场景暂停，然后进入的五子棋场景，当我把五子棋场景弹出以后，会继续我游玩到一半的主要游戏场景。

### 问题：
在程序运行到AudioEngine::play2d()的时候，有时候会出现卡顿。
### 解决方法：
将卡顿的音频文件使用AudioEngine::preload()进行预加载。


## 遇到的问题及解决方法（未成功解决，换了其他方法）


### 问题：
使用Tiled软件制作了主要游戏场景（MainScene.cpp && MainScene.h）中马路层的瓦片地图，发现导入的时候无法正常使用，放弃。（原本五子棋棋盘也打算使用瓦片地图的，因为可以节约资源）。
### 解决方法：
正常的使用了LayerColor来创建，可惜这样的话色彩单一，不够生动。

### 问题：
cocos2dx重载过的Vector使用pushback的时候出现问题，提示是空指针（我觉得可能和cocos2dx自己的内存管理机制有关，究竟是为什么还不知道）。
### 解决方法：
使用std::vector的push_back就没问题了。

### 问题：
当五子棋游戏开始新一盘游戏的时候，我要清空棋盘。我使用removeFromParent()，将棋子从棋盘上移除。第一次是没有问题的，当第二次游戏重新开始的时候，运行到removeFromParent()的时候，他提示是空指针（我使用std::vector来储存的这些棋子，不知道怎么回事啊），但是我打印他们的地址是存在的。
### 解决方法：
放弃使用removeFromParent()，使用setVisible(false)，隐藏了这些棋子，造成了资源的浪费。

## 待优化的地方
### 主要游戏场景（MainScene.cpp && MainScene.h）中精灵移动的算法。
我是使用了两个私有成员记录当前是左边按钮按下还是右边按钮按下，然后在update()中根据这两个私有成员的值控制精灵的移动。因为update()这个函数每帧都会运行，那当我按钮没有按下的时候，系统也一直在重复着复杂的逻辑判断，很浪费系统资源，应该有更好的算法，但是我目前想不到，如果有好的想法的话欢迎上传。
