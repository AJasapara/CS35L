Name: Arpit Jasapara, UID: 504742401

Issues:
1. I realized that in order to run my multithreaded function, I could not
print inside of it, since the threads would overlap and create garbage. Thus, 
I had to instead store the values in a global 3D array, and print them after 
joining my threads.

2. I received a compiler error saying that it could not find the scene variable 
in my threadRender function. I solved this issue by make scene global. However, I 
began receiving nonsensical output. Upon further investigation I noticed that I had 
not deleted the scene_t declaration in main, causing all kinds of issues. Upon 
resolving this issue, my program worked seamlessly.

Conclusions:
Multi-threading makes a clear difference in performance. As expected, from 1 to 2 to 
4 to 8 threads, the real time decreases by half when compared to the previous one. This 
is due to the doubling of the threads so twice the work is being done at the same time, 
thus taking only 50% as long. The user times are all similar, which also makes sense since 
the user time sums up the time across threads. Thus, it is clear that my implementation of 
SRT does the same thing that it did previously did, but now with a significant improvement 
in performance due to multi-threading. The time results are shown below:

One Thread:
real    0m52.100s
user    0m52.100s
sys     0m0.001s

Two Threads:
real    0m25.985s
user    0m51.724s
sys     0m0.002s

Four Threads:
real    0m13.660s
user    0m54.135s
sys     0m0.001s

Eight Threads:
real    0m7.275s
user    0m56.409s
sys     0m0.001s
