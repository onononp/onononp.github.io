/**
 * 某工厂有两个生产车间和一个装配车间，两个生产车间分别生产A，B两种零件，装配车间的任务是把A，B两种零件组装成产品。
 * 两个生产车间每生成一个零件后，都要分别把它们送到专配车间的货架F1，F2上。
 * F1存放零件A，F2存放零件B，F1和F2的容量均可存放10个零件。
 * 装配工人每次从货架上取一个零件A和一个零件B后组装成产品。
 * 请用P，V操作进行正确管理。
 * */

/**
 * 分析：
 * 六个信号量。
 * A和装配车间共享货架F1，B和装配车间共享货架F2.empty,full
 * 货架F1，货架F2都是临界资源mutex_1,mutex_2，每一个时刻只允许一个进程访问。
 * */

semaphore mutex_1=1,mutex_2=1;
semaphore empty_1=10,empty_2=10,full_1=0,full_2=0;
A车间(){
    while(1){
        生产一个A产品;
        P(empty_1); //判断F1货架是不是还有空位
        P(mutex_1); //互斥访问货架1
        将A产品放入货架1;
        V(mutex_1);
        V(full_1);
    }
}

B车间(){
    while(1){
        生产一个B产品;
        P(empty_2);
        P(mutex_2);
        将B产品放入2货架;
        V(mutex_2);
        V(full_2);
    }
}

装配车间(){
    while(1){
        //货架上有A
        P(full_1);
       
        P(mutex_1);
        取一个A;
        V(mutex_1);
        V(empty_1);

        //货架上有B
        P(full_2);

        P(mutex_2);
        取一个B;
        V(mutex_2);
        V(empty_2);
        将取得的A和B组装成一个产品;
    }
}