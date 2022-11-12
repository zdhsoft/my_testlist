///通用库中，主要的错误码定义
#ifndef _X_COMMON_ERROR_CODE_H_
#define _X_COMMON_ERROR_CODE_H_
namespace zdh
{
    enum EnumCommonErrorCode
    {
        ECEC_BEGIN  = 100000,       ///<错误码起始值
        ECEC_HAS_ALREADY_BEEN_INITIALIZED = ECEC_BEGIN + 1,   ///<1000001 已经初始化过了
        ECEC_POLL_CREATE_FAIL             = ECEC_BEGIN + 2,   ///<1000002 Poll执行Create失败
        ECEC_SERVICE_REGISTER_FAIL        = ECEC_BEGIN + 3,   ///<1000003 Service注册到poll失败
        ECEC_HAS_NOT_BEEN_INITIALISED     = ECEC_BEGIN + 4,   ///<1000004 还没有初始化
        ECEC_OPEN_LISTEN_SOCKET_FAIL      = ECEC_BEGIN + 5,   ///<1000005 打开listen的socket对象失败
        ECEC_SOCKET_SET_BLOCK_STATUS_FAIL = ECEC_BEGIN + 6,   ///<1000006 socket设置block状态失败
        ECEC_NOT_DEFINED_ON_ACCEPT_EVENT  = ECEC_BEGIN + 7,   ///<1000007 没有定义OnAcceptEvent事件
        ECEC_SOCKET_BIND_FAIL             = ECEC_BEGIN + 8,   ///<1000008 socket绑定ip地址和port失败
        ECEC_LISTEN_FAIL                  = ECEC_BEGIN + 9,   ///<1000009 开始listen失败
        ECEC_REGISTER_SOCKET_FAIL         = ECEC_BEGIN + 10,  ///<1000010 注册socket到poll失败
        ECEC_UNREGISTER_SOCKET_FAIL       = ECEC_BEGIN + 11,  ///<1000011 从poll中注销socket失败
        ECEC_SOCKET_IS_OPEDED             = ECEC_BEGIN + 12,  ///<1000012 socket已经是打开过的
        ECEC_SOCKET_INVALID               = ECEC_BEGIN + 13,  ///<1000013 socket是无效的
        ECEC_SOCKET_OPEN_FAIL             = ECEC_BEGIN + 14,  ///<1000014 打开socket失败
        ECEC_SOCKET_SET_BLOCK_FAIL        = ECEC_BEGIN + 15,  ///<1000015 设置状态为阻塞失败
        ECEC_SOCKET_SET_NONBLOCK_FAIL     = ECEC_BEGIN + 16,  ///<1000016 设置状态为非阻塞失败
        ECEC_SOCKET_IS_USED               = ECEC_BEGIN + 17,  ///<1000017 Socket的功能已经确定了
        ECEC_SHM_CREATE_FAIL              = ECEC_BEGIN + 18,  ///<1000018 共享内存创建失败
        ECEC_SOCKET_CONNECED_FAIL         = ECEC_BEGIN + 19,  ///<1000019 socket连接目标失败

        ECEC_NEW_FAIL                     = ECEC_BEGIN + 20,  ///<1000020 new一块内存失败
        
    };
}
#endif
