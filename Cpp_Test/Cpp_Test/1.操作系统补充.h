﻿#pragma once

/*

堆和栈的设计，最初不过是单纯希望尽可能充分利用内存空间而已。

堆，堆积也。越堆越高，但是不知道可能堆多高。
栈，栈房、货仓也。货仓储存物品时尽可能往里头塞，取出物品时则常常从外头取，先进后出，后进先出。这样存取物品，可以最省力、最快速。

当时的人们发现，堆和栈都是不可避免的。堆会持续增长而栈像单端固定另一端可伸缩的弹簧，并且人们无法预测堆和栈应分别分配多少内存。

某些项目的堆累积得很高而栈的最大长度很短，另一些项目的堆累积得不高而栈的最大长度很长。

为了充分利用有限的内存空间来适应这两种极端情况，当时的聪明大脑们，就决定从内存的两头往中间存放数据，一头放堆数据，从底端往上生长，另一头放栈数据，从顶端往下生长。
这个方案能够同时适应堆矮栈短、堆矮栈长、堆高栈短等三种情形；而当遇到堆高栈长的情形时，只需简单地扩内存即可。

*/







