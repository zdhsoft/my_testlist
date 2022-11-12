这个库是一个跨linux和windows的库，开发环境主要是VC2008。
支持的编译器有GCC 4.x和VC2005,VC2008等编译器。
使用者，可以修改和无偿使用。但保留所以版权!

这个库的开发，将严格按照开发规范，支持用doxygen生成文档。
												zdhsoft
												2011-10-07 

跨平台socket实现方案，参考redis中的实现，在windows实现一个类似linux下epoll相同接口的函数定义。
主要文件有xsocket.h