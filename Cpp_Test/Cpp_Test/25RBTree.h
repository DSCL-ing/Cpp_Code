﻿#pragma once

//红黑树 Red-Black Tree
/**
 * 简称RBT
 * 
 * 红黑树是2-3-4树的特殊实现
 * 
 * 红黑树的性质/规则
 * 1. 每个结点不是红色就是黑色
 * 2. 根节点是黑色的 -- (root点要转成黑色)
 * 3. 如果一个节点是红色的，则它的两个孩子结点是黑色的 -- (不存在两个连续的红结点)
 * 4. 对于每个结点，从该结点到其所有后代叶结点的简单路径上，均 包含相同数目的黑色结点
 * 5. 每个叶子结点都是黑色的(此处的叶子结点指的是空结点 -- NIL结点,不影响黑节点的数量) -- 为了与3不矛盾
 * 
 * ?如何保证最长路径为最短路径的两倍及以内? 
 * $ 最短是全黑
 * $ 最长是黑中插入不连续的红(规则3) -- 插满后是全黑(最短)的两倍
 * $ 由根结点和NIL结点为黑色(规则2和规则5)限制
 * 因此得以保证
 * 
 * ($ 走到空才算一条路径)
 * 
 * $ 结点和路径信息:
 * 设全部的黑色结点有N个,则最短路径长度为logN,
 * 整棵树的结点数量:[N,2N]之间,最长路径为2logN  -- 
 * 解释:是一种理想状态--插入红节点,并不填满树,插满后红节点数量等于黑结点数量--红黑相间的情况
 * 
 * $ 最长路径上的黑节点的数目和最短路径上的黑节点的数目相等
 * 
 * 理想情况下,AVL查找10个结点需要30次,RB最多查找60,两倍,但是对于计算机来说基本没有区别
 * 
 * 红黑树对比AVL树优点:
 * $ 旋转更少了 --红黑树的平衡性能比AVL的略差些，但是经过大量试验(别人)证明，实际上红黑树的效率还是很不错了，仍能达到O(logN)
 * 
 * C++/JAVA的容器底层需要的平衡搜索树基本都是红黑树,AVL树很少使用
 * 
 * 红黑树应用很广，大量应用在底层数据结构中，主要用于存储和查找。平日开发很少自己去写红黑树，
 * 因为我们大部分都是使用别人封装后的接口而已，但是深入了解数据结构和算法是非常必要的。
 * 
 */


/** 红黑树的实现 -- 插入
 * 
 * 
 * 
 * 红黑树默认插入的结点为红色 -- 规则3更容易实现,不冲突规则
 * 注:不许修改新插入结点的颜色,规定吧,满足红黑树,待研究
 * 
 * 1.如果插入位置的父亲是红色的处理:
 * 插入后根据规则3,因为插入的结点是红色,所以parent必须变黑 -- 上黑下红规律
 * $ 如果父亲变黑了,且叔叔存在且为红,则将叔叔也要跟则变黑(规则4),然后再将爷爷变红(规则4)
 * -- 如果爷爷的父亲是黑的,则处理结束 . 否则循环,直至到根
 * $ 如果经过处理后,根变为红色,则最终需要将根置为黑色
 * 
 * 2.如果插入的位置没有叔叔的处理:旋转 -- 将祖父旋下来
 * $ 插入在父亲的左边,则右旋
 * 
 * 如果插入位置的父亲是黑色,则不需要处理
 * 
 * 
 *  直接变色情形
 *             g
 *    u(红)          p(红) 
 *                        c(红)
 * 
 * 情形1：该树为空树，直接插入根结点的位置，违反性质1，把节点颜色有红改为黑即可。
 * 情形2：插入节点N的父节点P为黑色，不违反任何性质，无需做任何修改。
 * 情形3: 插入结点N的父节点P为红色,叔叔u为红色
 * 
 * $ 需要旋转的情形(为了保持规则4(一样多的黑结点):
 * 在不修改新插入结点颜色的情况下,无论怎么变色都不平衡,即不能维持规则4的情况下,只能进行旋转操作
 * 
 * 
 * 单旋情形
 *            g
 *   u(黑)         p(红) 
 *                       c(红)
 * 
 * 双旋情形
 *            g
 *   u(黑)             p(红) 
 *                 c(红)
 * 
 * 情形4: p为红,u为黑/或u不存在 
 * 操作: 旋转,直线单旋,折现双旋
 * 
 * $ 注: 
 * 1.u为黑的情况是由子结点向上调整产生的(因为每次插入的结点都是红色,调整才能变黑) , 且cur结点原来是黑色的,红色是由下面结点调整的
 * 2.u不存在(叔叔路径会缺一个黑),说明cur一定是新增结点, -- ,插在红p则平衡不了,需要旋转
 * 
 * 继续调整的跨度为cur->grandfather
 * 
 */








