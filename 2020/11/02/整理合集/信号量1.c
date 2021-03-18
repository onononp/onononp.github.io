// 三个进程P1，P2，P3互斥使用一个包含N（N>0）个单元的缓冲区，P1每次用produce()生成一个正整数并用put()送入缓冲区的某一空单元；P2每次用getodd()从该缓冲区中取出一个奇数并用countodd（）统计奇数个数；P3每次用geteven()从该缓冲区中取出一个偶数并用counteven()统计偶数个数。请用信号量机制实现这三个进程的同步与互斥活动。并说明所定义的信号量的含义（要求用伪代码描述）。

// 答：互斥资源：缓冲区只能互斥访问，因此设置互斥信号量mutex

// 同步问题：P1，P2因为奇数的放置与取用而同步，设同步信号量odd;P1，P3因为偶数的放置与取用而同步，设置同步信号量even；P1，P2，P3因为共享缓冲区，设同步信号量为empty,初值为N，程序如下：
semaphore mutex = 1; //缓冲区操作互斥信号量

semaphore odd = 0, even = 0; //奇数、偶数进程的同步信号量

semaphore empty = N;

cobegin
{

    Process P1()
    {
        while (True)
        {

            x = produce(); //生成一个正整数

            P(empty);
            P(mutex);

            put(); //送入缓冲区

            V(mutex);

            if (x % 2 == 0)
            {

                V(even);
            }
            else
            {

                V(odd);
            }
        }
    }

    Process P2()
    {
        while (True)
        {
            P(odd);
            P(mutex);
            getodd();
            V(mutex);
            V(empty);
            countodd();
        }
    }

    Process P3()
    {
        while (True)
        {
            P(even);
            P(mutex);
            geteven();
            V(mutex);
            V(empty);
            counteven();
        }
    }
}