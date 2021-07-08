#ifndef TP_H
#define TP_H

#include "../Common/Std_Types.h"
#include "../Common/ComStack_Types.h"
#include <vector>

using namespace std;

typedef enum 
{
    TX_IDLE,
    TX_SF,
    TX_FF,
    TX_WAIT_FC,
    TX_CF,
    TX_FC_4_RX
} t_TxStat;

typedef struct
{
    t_TxStat state;

    uint32  txTimer;
    uint32  bytesTotal2Trans;   /* total bytes to be transfered.*/
    uint32  bytesHasTrans;
    uint8   Sdu[1024];
    uint8   Sn;                 /* for FlowFrame.*/
    uint8   Bs;                 /* BlockSize.*/
    uint8   counter4Bs;
} t_tpTxInfo;

typedef enum 
{
    RX_IDLE,
    RX_SF,
    RX_FF,
    RX_TX_FC,
    RX_CF
} t_RxStat;

typedef struct
{
    t_RxStat state;

    uint32  rxTimer;
    uint32  bytesTotal2Trans;   /* total bytes to be transfered.*/
    uint32  bytesHasTrans;
    uint8   Sdu[1024];
    uint8   Sn;                 /* for FlowFrame.*/
    uint8   Bs;                 /* BlockSize.*/
    uint8   counter4Bs;
    uint8   CAN_DL;              /* DLC --> CAN_DL.*/
} t_tpRxInfo;



class Tp
{
public:
    typedef enum { TP_ADDR_NORMAL, TP_ADDR_EXTENDED, TP_ADDR_MIXED } t_AddrFormatType;
    typedef enum { TP_TYPE_LIN, TP_TYPE_CAN, TP_TYPE_CANFD } t_TpNetType;
    typedef enum { PCI_TYPE_SF, PCI_TYPE_FF, PCI_TYPE_CF, PCI_TYPE_FC} t_PCItype;
    typedef enum { TP_TX_DL_8BYTES, TP_TX_DL_} t_TxDLtype;

public:
    Tp(t_AddrFormatType addressingFormat);
    virtual ~Tp();

    void Tp_RxMain(void);
    void Tp_TxMain(void);      // for Tx Connection Channe
    void Tp_MainTask(void);

    Std_ReturnType Tp_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

    /* Callback.*/
    void Tp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
    void Tp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

    /* For Tp.*/
    BufReq_ReturnType PduR_TpStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);
    BufReq_ReturnType PduR_TpCopyRxData      (PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);
    void              PduR_TpRxIndication    (PduIdType id, Std_ReturnType result);

private:
    /* Protocol information.*/
    void Tp_TxChannelHandler(t_tpTxInfo &tpTxChannel);
    void Tp_RxChannelHandler(t_tpRxInfo &tpRxChannel);

    /* Channel state.*/
    t_tpTxInfo  m_tpTxInfo;
    t_tpRxInfo  m_tpRxInfo;

    /* 配置参数.*/
    uint32  m_rxResId;
    uint32  m_txPhyId;
    uint32  m_txFunId;

    uint32  m_dlcToTx;
    uint32  m_dlcToRx;

    uint32  m_N_As;
    uint32  m_N_Ar;
    uint32  m_N_Bs;
    uint32  m_N_Br;
    uint32  m_N_Cs;
    uint32  m_N_Cr;
    uint8   m_PaddingValue;

    /* 动态参数.*/
    uint16  m_STmin;    /* SeparationTime.*/
    uint8   m_N_WFTmax;
    uint8   m_BS;       /* Block Size.*/

    vector<unsigned char> *m_Dlc2Can_DL_table;
};

#endif // TP_H
