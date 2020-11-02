/**
 * 有桥如下图所示，车流方向如箭头所示，回答下列问题：
 * (1)假设桥上每次只能有一辆车行驶，试用信号灯的P，V操作实现交通管理
 * (2)假设桥上不允许辆车交会，但允许同方向多辆车一次通过（即桥上可以有多辆同方向行驶的车）。试用信号灯的P，V操作实现桥上的交通管理。
 * */

/**
 * (1)分析：
 * 桥上每次只能有一辆车行驶，所以只要设置一个信号量bridge就可判断桥是否可用，若在使用中，等待；若无人使用，则执行P操作进入；
 * 出桥后，执行V操作。
 * */

semaphore bridge = 1; //用于互斥地访问桥
NtoS
{ //从北向南
    P(bridge);
    通过桥；
    V(bridge);
}

StoN
{
    //从南向北
    P(bridge);
    通过桥；
    V(bridge);
}

/**
 * (2)分析：
 * 桥上可以同方向多车行驶，需要设置bridge,还需要对同方向车辆进行计数。为了防止同方向计数中同时申请bridge造成同方向不可同时行车的问题，
 * 要对计数过程加以保护，因此设置信号量mutexNtoS,mutexStoN;
 * */

semaphore bridge = 1;                   //用于互斥地访问桥
int countNtoS = 0, countStoN = 0;       //分别表示从北向南和从南向北的汽车数量
semaphore mutexStoN = 1, mutexNtoS = 1; //用于保护计数变量
StoN
{
    //从南向北
    P(mutexStoN);
    if (countStoN == 0)
        P(bridge);
    countStoN++;
    V(mutexStoN);
    通过桥;

    P(mutexStoN);
    countStoN--;
    V(mutexStoN);
    if(countStoN==0)
        V(bridge);
    
}
