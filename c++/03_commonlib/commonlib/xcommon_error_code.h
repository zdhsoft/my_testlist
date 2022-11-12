///ͨ�ÿ��У���Ҫ�Ĵ����붨��
#ifndef _X_COMMON_ERROR_CODE_H_
#define _X_COMMON_ERROR_CODE_H_
namespace zdh
{
    enum EnumCommonErrorCode
    {
        ECEC_BEGIN  = 100000,       ///<��������ʼֵ
        ECEC_HAS_ALREADY_BEEN_INITIALIZED = ECEC_BEGIN + 1,   ///<1000001 �Ѿ���ʼ������
        ECEC_POLL_CREATE_FAIL             = ECEC_BEGIN + 2,   ///<1000002 Pollִ��Createʧ��
        ECEC_SERVICE_REGISTER_FAIL        = ECEC_BEGIN + 3,   ///<1000003 Serviceע�ᵽpollʧ��
        ECEC_HAS_NOT_BEEN_INITIALISED     = ECEC_BEGIN + 4,   ///<1000004 ��û�г�ʼ��
        ECEC_OPEN_LISTEN_SOCKET_FAIL      = ECEC_BEGIN + 5,   ///<1000005 ��listen��socket����ʧ��
        ECEC_SOCKET_SET_BLOCK_STATUS_FAIL = ECEC_BEGIN + 6,   ///<1000006 socket����block״̬ʧ��
        ECEC_NOT_DEFINED_ON_ACCEPT_EVENT  = ECEC_BEGIN + 7,   ///<1000007 û�ж���OnAcceptEvent�¼�
        ECEC_SOCKET_BIND_FAIL             = ECEC_BEGIN + 8,   ///<1000008 socket��ip��ַ��portʧ��
        ECEC_LISTEN_FAIL                  = ECEC_BEGIN + 9,   ///<1000009 ��ʼlistenʧ��
        ECEC_REGISTER_SOCKET_FAIL         = ECEC_BEGIN + 10,  ///<1000010 ע��socket��pollʧ��
        ECEC_UNREGISTER_SOCKET_FAIL       = ECEC_BEGIN + 11,  ///<1000011 ��poll��ע��socketʧ��
        ECEC_SOCKET_IS_OPEDED             = ECEC_BEGIN + 12,  ///<1000012 socket�Ѿ��Ǵ򿪹���
        ECEC_SOCKET_INVALID               = ECEC_BEGIN + 13,  ///<1000013 socket����Ч��
        ECEC_SOCKET_OPEN_FAIL             = ECEC_BEGIN + 14,  ///<1000014 ��socketʧ��
        ECEC_SOCKET_SET_BLOCK_FAIL        = ECEC_BEGIN + 15,  ///<1000015 ����״̬Ϊ����ʧ��
        ECEC_SOCKET_SET_NONBLOCK_FAIL     = ECEC_BEGIN + 16,  ///<1000016 ����״̬Ϊ������ʧ��
        ECEC_SOCKET_IS_USED               = ECEC_BEGIN + 17,  ///<1000017 Socket�Ĺ����Ѿ�ȷ����
        ECEC_SHM_CREATE_FAIL              = ECEC_BEGIN + 18,  ///<1000018 �����ڴ洴��ʧ��
        ECEC_SOCKET_CONNECED_FAIL         = ECEC_BEGIN + 19,  ///<1000019 socket����Ŀ��ʧ��

        ECEC_NEW_FAIL                     = ECEC_BEGIN + 20,  ///<1000020 newһ���ڴ�ʧ��
        
    };
}
#endif
