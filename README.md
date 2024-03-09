# 数据结构课程设计

## 前端界面

主菜单：直接用了教程四的UI，但省去了它的联机对战。



![](https://1ees0n.oss-cn-qingdao.aliyuncs.com/GoBang/%E4%BA%94%E5%AD%90%E6%A3%8B-%E4%B8%BB%E8%8F%9C%E5%8D%95.jpg)

人机对战棋盘：点击人机对战后弹出，包括先后手的选择的弹窗和棋盘界面。这里有个小Bug，就是当你不点击确定按钮（只要你点击确定按钮就没事，即使没选择，也会再次弹出一个弹窗提醒你选择），而是直接点`×`号，也会进入棋盘，但实际上不应该能进入的，当你首次玩时，即使进去了也下不了棋，但玩了几局后，可能就有之前的“缓存”，导致也可以“完”。

![](https://1ees0n.oss-cn-qingdao.aliyuncs.com/GoBang/%E4%BA%94%E5%AD%90%E6%A3%8B-%E4%BA%BA%E6%9C%BA%E5%AF%B9%E6%88%98.jpg)

本地对战棋盘：比较直接，就进去，然后下棋。

![](https://1ees0n.oss-cn-qingdao.aliyuncs.com/GoBang/%E4%BA%94%E5%AD%90%E6%A3%8B-%E6%9C%AC%E5%9C%B0%E5%AF%B9%E6%88%98.jpg)

## 主要算法

极大极小值搜索、alpha-beta剪枝算法、启发式评估函数和局部搜索，并没有实现Zobrist缓存技术（所以代码中的就是障眼法罢了）以及迭代加深和算杀。

## 感想

作为一个究极缝合怪，缝合的并不好，代码真的成了“屎山”代码，唯一的优点就是能跑， ~~所以仅供参考学习~~。

## 参考资料

1. 自我感觉最好的五子棋算法教程：[lihongxun945/myblog#11](https://github.com/lihongxun945/myblog/issues/11)
2.  [https://github.com/lfr-not-yy/myfive](https://github.com/lfr-not-yy/myfive)
3. [https://github.com/DavinciEvans/gobang-Cpp](https://github.com/DavinciEvans/gobang-Cpp) 
4. 一个基于 QT 开发的联机五子棋：[https://github.com/senyucci/Gobang?tab=readme-ov-file](https://github.com/senyucci/Gobang?tab=readme-ov-file)
上述参考资料：
- 教程一很详细，使用了Js脚本语言，是我见过最全的五子棋算法教程，感谢大佬的无私奉献。
- 教程二在教程三基础上进行拓展，用他自己的话来说就是“我只是在算法的大厦上擦了两块玻璃”。
- 教程三是用C++写的一个五子棋项目，算法部分实现了极大极小值搜索算法，alpha-beta剪枝算法，局部搜索。
- 教程四基于QT开发，算法部分稍有欠缺，但具有联机功能且UI设计的很好（~~我偷懒直接用了他的UI~~）。
