# 实验报告

## ——德州扑克游戏

### 一、 实验题目

德州扑克及决策系统

### 二、 实验目的

1. 学会将实际问题抽象为算法模型，提升逻辑思维和代码实现能力；
2. 设计并实现一个具备基础决策能力的德州扑克 AI，能够处理多组牌局数据，通过算法选择 “弃牌”“跟注” 或 “加注”，最终实现筹码总量最大化；
3. 对比不同决策算法的性能，理解策略选择对最终结果的影响。

### 三、 实验内容（功能概述）

1. 核心规则模块
   - 扑克牌与牌堆的抽象与初始化
   - 手牌组合判断
   - 牌力比较算法

2. 游戏流程控制
   - 玩家状态管理（弃牌、全下、跟注、加注）
   - 筹码池管理与边池计算

3. AI玩家系统
   - 基于手牌强度的基本策略
   - 考虑胜率的简单决策树

4. 用户界面
   - 交互式操作菜单

### 四、 系统设计

#### **4.1 数据结构设计**

```c
// 牌型判断类
typedef enum {
    STRAIGHT_FLUSH = 8,
    ...
    HIGH_CARD = 0
} HandType;

typedef enum {
    C = 0b0001, D = 0b0010, 
    H = 0b0100, S = 0b1000 
} Suit;

typedef struct {
    Suit suit;
    int rank;
} Card;

// 对局信息类
typedef struct {
    Card player1[CONSIDER_SIZE];
    Card player2[CONSIDER_SIZE];
    long long pot;
    int result;
    int weight1;
    int weight2;
    int count;
} RoundInfo;

typedef struct {
    int weight;         
    Card best_hand[5];
    HandType hand_type;
} HandResult;

// ai 决策类
typedef enum {
    FOLD, CALL, RAISE
} Action;

typedef struct{
    Action act;
    long long amt;
    double pp;
} React;
```

#### **4.2 核心模块划分**

```markdown
Texas-holdem/
├──game/
│    ├── main.c           // 游戏入口
│    ├── card.c           // 读取信息
│    ├── judgement.c      // 牌型权重判断
│    ├── library.c        // 胜率计算
│    ├── m_ai.c           // 算法
│    ├── action.c         // 处理广播动作
│    ├── var_global.c     // 重要全局变量
│    └── procedure.c      // 文件处理
├──welcoe/
│    ├── menu_ANSI.C      // 用户界面
│    └── posix_getch.c    // 特殊函数替换
├──round_info/            
│    └── *.csv            // 牌局数据
└──round_result/          
     └── *.csv            // 输出
```

#### **4.3 关键算法设计**
牌力评级：
```c
HandResult judge(const Card o_hand[7]) {
    1. 检查同花顺 
    2. ... // 依次检查所有牌型
    3. 剩余高牌
    4. 返回牌力分数（十六进制六位数）
}
```

AI决策：
```c
React ai(RoundInfo info) {
    計算勝率:
     0  - 32  FOLD
     32 - 78  CALL
     78 - 100 RAISE -> 百分比換算到加注 0 - 60
    return affordable_check()
}
```

### 五、 实现难点与解决方案
1. 牌力精确比较

    *踢脚比较与牌型比较的逻辑关系*

        直出一个权重数统一比较

2. 数据输入

    *CSV文件特殊格式*

        处理 CRLF，
        处理前置 UTF-8 BOM
                0xEF 0xBB 0xBF

3. AI平衡策略
    
    *线性算法面对随机数据有时无力*

        前期脆弱，受随机性影响大，不能只期望判断
        後期穩定性高，也不需要100%效率
        故調高CALL閾值

    *线性算法前期穩定性太差*

        前八輪借用保守函數
   
    

### 六、 测试结果


| 数据集\风格\存活 | 1 |  2 | 3 | master |
|----------------------|---|----|---|--------|
| **repeater**         | 6 | 28 | 24 | 5 |
| **gambler**          | 4 | 29 | 25 | 5 |
| **conservative**     | 6 | 27 | 27 | 31 |
| **rational**         | 6 |100(full)|100(full)| out of limit |
> starting with chips of 1000



### **七、 程序运行示例**
```
=== 德州扑克欢迎您 ===

请选择AI策略：

> 1. 复读机
  2. 赌徒
  3. 保守
  4. 算法
  5. 退出程序

=== 游戏内容 ===

请选择AI处理对象：

> 1. games_1.csv
  2. games_2.csv
  3. games_3.csv
  4. games_master.csv
  5. real-time play
  6. 返回主菜单

AI初始筹码:1000
ai lose in round 5 ...
```

### 八、 实验总结与改进方向
收获总结：
- 加深了对C语言结构的理解
- 锻炼了将复杂规则转化为逻辑代码的能力
- 理解了戏开发的基本规则

可扩展功能：
1. AI大模型调用
2. 实时对战 / 联机
3. 图形界面（考虑迁移）

代码优化点：
- 牌型判断算法可利用数据结构优化
- 精简结构体与函数接口

### 九、 源代码说明
1. 总行数统计：约1000行
2. **编译方式**：使用makefile
3. **运行环境**：Linux

