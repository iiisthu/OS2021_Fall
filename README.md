# Operating System 2021 Fall

This public repository holds the projects of this semester. See the `README`
in each project for details.

## Note

1. submit方法调整：每组提交一个diff文件到网络学堂，diff文件命名方式为学号1_学号2.diff，diff的生成方式见文档
2. 答疑文档：关于project 1的相关问题请大家更新到共享文档https://docs.qq.com/doc/DQkpGelpuTlZJaWRB，我们会定期解答文档上的问题
3. 关于slow_function：在最终版本的提交中请大家打开utils中的slow_function，以保证通过所有的library test。（IMPORTANT：在library test中因为没有打开slow_function导致测试fail将被扣除50%的项目分数）
4. 关于item更新：为了简单我们在之前的实现中省略了对item的更新（实际系统中item和user的更新频率和方式都有差异），然而这样隐式地移除了大部分数据间依赖，因此我们要求在更新时同时更新user和item的embedding，最后输出两个EmbeddingHolder，先user后item（注意输出也需要thread-safety）。
5. 关于大家在project 1中问的比较多的问题，我们这里统一回复一下：一是前两题的正确性，由于q1 q2指令之间没有执行依赖，因此最后的答案可能有多种，大家只要在保证thread safty的前提下得出任意一种答案即可通过测试；二是关于efficiency，我们会统计所有人的完成时间，排名后30%且慢于我们的参考实现（基础的并行实现，运行时间不公开）的提交我们会酌情扣分；三是关于test case，我们在这个project中不会提供auto test和benchmark，请大家自行设计case来验证代码的正确性