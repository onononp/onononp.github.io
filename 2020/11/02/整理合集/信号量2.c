/*
在一个仓库中可以存放A和B两种商品，要求：
1. 每次只能存入一种商品
2. A产品数量-B产品数量<M
3. B产品数量-A产品数量<N
其中，M，N是正整数，试用P操作，V操作描述产品A与产品B的入库过程
*/

/**
 * 使用mutex控制两个进程互斥访问临界资源（仓库），使用同步信号量Sa和Sb（分表代表产品A与B的还可容纳的数量差，以及产品B与产品A的还可容纳的数量差），
 * 满足条件2和条件3.代码如下：
 **/

semaphore mutex=1;
semaphore Sa=M-1,Sb=N-1;

A(){
    while(True){
        P(Sa);
        P(mutex);
        A产品入库
        V(mutex);
        V(Sb);
    }
}

B(){
    while(True){
        P(Sb);
        P(mutex);
        B产品入库
        V(mutex);
        V(Sa);
    }
}