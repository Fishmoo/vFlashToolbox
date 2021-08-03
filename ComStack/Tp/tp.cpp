#include "tp.h"
#include <QDebug>
#include <algorithm>

Tp::Tp(t_AddrFormatType addressingFormat = TP_ADDR_NORMAL)
{
    /* from .ini/.xml import configuration.*/

    m_rxResId = 0x615U;
    m_txPhyId = 0x715U;
    m_txFunId = 0x7FFU;

    m_dlcToTx = 0U;
    m_dlcToRx = 0U;


    m_tpTxInfo.state = TX_IDLE;
    m_PaddingValue = 0xAAU;


    m_Dlc2Can_DL_table = new vector<unsigned char> {
         2U,  3U,  4U,  5U,  6U,  7U,  8U,
        12U, 16U, 20U, 24U, 32U, 48U, 64U
    };
}

Tp::~Tp()
{
    delete m_Dlc2Can_DL_table;
}

void Tp::Tp_MainTask(void)
{
    Tp_TxChannelHandler(m_tpTxInfo);
}

void Tp::Tp_TxChannelHandler(t_tpTxInfo &tpTxChannel)
{
    uint8 i = 0U, txBuff[8] = { 0u };
    uint8 b_print_req = 1u;
    /* For tx channel.*/
    switch (tpTxChannel.state)
    {
    case TX_SF:
        txBuff[0] = (uint8)(PCI_TYPE_SF << 4U | (uint8)tpTxChannel.bytesTotal2Trans);
        /* From byte 1.*/
        while (++i < 8U)
        {
            if (i <= tpTxChannel.bytesTotal2Trans) {
                txBuff[i] = tpTxChannel.Sdu[tpTxChannel.bytesHasTrans++];
            } else {
                txBuff[i] = m_PaddingValue;
            }
        }

        tpTxChannel.state = TX_IDLE;
        break;

    case TX_FF:
        txBuff[0] = (uint8)(PCI_TYPE_FF << 4U | (uint8)(tpTxChannel.bytesTotal2Trans >> 8U));
        txBuff[1] = (uint8)(tpTxChannel.bytesTotal2Trans);
        /* From byte 2.*/
        while (i < 6U)
        {
            txBuff[2+i] = tpTxChannel.Sdu[tpTxChannel.bytesHasTrans++];
            ++i;
        }

        tpTxChannel.Sn    = 0U;
        tpTxChannel.state = TX_WAIT_FC;
        break;

    /* 等待流控帧信息.*/
    case TX_WAIT_FC:
        tpTxChannel.Bs    = 0x20U;
        tpTxChannel.counter4Bs = 0U;
        tpTxChannel.state = TX_CF;

        b_print_req = 0u;
        break;
    
    case TX_CF:
        ++tpTxChannel.Sn;
        tpTxChannel.Sn = (tpTxChannel.Sn > 0xFU) ? 0U : tpTxChannel.Sn;
        txBuff[0] = (uint8)(PCI_TYPE_CF << 4U | (uint8)(tpTxChannel.Sn));
        /* From byte 1.*/
        while (++i < 8U)
        {
            if (tpTxChannel.bytesHasTrans <= tpTxChannel.bytesTotal2Trans) {
                txBuff[i] = tpTxChannel.Sdu[tpTxChannel.bytesHasTrans++];
            } else {
                txBuff[i] = m_PaddingValue;
            }
        }

        if (tpTxChannel.bytesHasTrans < tpTxChannel.bytesTotal2Trans)
        {
            ++tpTxChannel.counter4Bs;
            tpTxChannel.state = (tpTxChannel.counter4Bs < tpTxChannel.Bs)
                ? TX_CF : TX_WAIT_FC;
        } else {
            tpTxChannel.state = TX_IDLE;
        }

        break;

    default:
        b_print_req = 0u;
        break;
    }

    /* 打印结果.*/
//    qDebug() << tpTxChannel.state;
    if (b_print_req) {
    qDebug("%2x %2x %2x %2x %2x %2x %2x %2x", txBuff[0],txBuff[1],txBuff[2],txBuff[3],
            txBuff[4],txBuff[5],txBuff[6],txBuff[7]);
//    qDebug() << endl;
    }
}


void Tp::Tp_RxChannelHandler(t_tpRxInfo &tpRxChannel)
{
    Std_ReturnType  checkResult = E_OK;
    uint8 i = 0U, index = 0U, txBuff[8];
    uint8 b_print_req = 1u;

    const t_PCItype  N_PCItype = (t_PCItype)(tpRxChannel.Sdu[0] >> 4U);
    uint32 N_PCIlength = 0U;

    if (tpRxChannel.state == RX_IDLE)
    {
        switch (N_PCItype)
        {
        case PCI_TYPE_SF:
            /**
             * NWL status: Segmented receive in progress & Rx SF N_PDU.
             * Terminate the current reception, report an N_USData.indication, with <N_Result> 
             * set to N_UNEXP_PDU, to the upper layer, and process the SF N_PDU as the start
             * of a new reception.
             */
            if (tpRxChannel.state != RX_IDLE) {
                //todo: Init
                PduR_TpRxIndication(0U, E_NOT_OK);
            }

            /* For CAN_DL <= 8, classicCAN.*/
            if (m_tpRxInfo.CAN_DL <= 8U)
            {
                N_PCIlength = (uint32)(tpRxChannel.Sdu[0] & 0x0FU);
                if (N_PCIlength <= 7U)  // todo: for normal addressing.
                {
                    tpRxChannel.bytesTotal2Trans = N_PCIlength;
                } else {
                    checkResult = E_NOT_OK;
                }
            }
            /* For CAN_DL  > 8, CAN FD.*/
            else
            {
                //todo:
            }
            
            if (checkResult == E_OK)
            {
                if (BUFREQ_OK == PduR_TpStartOfReception(0U, nullptr, N_PCIlength, nullptr)) {
                    (void)PduR_TpCopyRxData(0U, nullptr, nullptr);
                    PduR_TpRxIndication(0U, checkResult);
                }
            }

            tpRxChannel.state = RX_IDLE;
            break;
        
        case PCI_TYPE_FF:
            /**
             * NWL status: Segmented receive in progress & Rx SF N_PDU.
             * Terminate the current reception, report an N_USData.indication, with <N_Result> 
             * set to N_UNEXP_PDU, to the upper layer, and process the FF N_PDU as the start 
             * of a new reception.
             */
            if (tpRxChannel.state != RX_IDLE) {
                //todo: Init
                PduR_TpRxIndication(0U, E_NOT_OK);
            }

            /* Valid RX_DL for CAN FD: 2~8, 12U, 16U, 20U, 24U, 32U, 48U, 64U.*/ 
//            boolean isValid_RX_DL = find(m_Dlc2Can_DL_table->begin(),
//                            m_Dlc2Can_DL_table->end(), m_tpRxInfo.CAN_DL);
//            if (isValid_RX_DL)
//            {
//                N_PCIlength  = (uint32)((tpRxChannel.Sdu[index++] & 0x0FU) << 8U);
//                N_PCIlength += (uint32)((tpRxChannel.Sdu[index++]));

//                /* FF_DL  > 4095.*/
//                if (N_PCIlength == 0UL) {
//                    while (i++ < 4U) {
//                        N_PCIlength <<= 8U;
//                        N_PCIlength  += (uint32)((tpRxChannel.Sdu[index++]));
//                    }
//                /* FF_DL <= 4095.*/
//                } else {

//                }

//                //todo: FF_DLmin check
//                tpRxChannel.bytesTotal2Trans = N_PCIlength;
//                /* Check connection acceptence and prepare FC.*/
//                if (BUFREQ_OK == PduR_TpStartOfReception(0U, nullptr, N_PCIlength, nullptr))
//                {
//                    /* Copy FF data to upper loyer.*/
//                    (void)PduR_TpCopyRxData(0U, nullptr, nullptr);
//                }
//            }

            tpRxChannel.state = RX_TX_FC;
            break;
        case PCI_TYPE_CF:
            
            break;

        default:
            break;
        }
    }

    /* 打印结果.*/
//    qDebug() << tpTxChannel.state;
    if (b_print_req) {
    qDebug("%2x %2x %2x %2x %2x %2x %2x %2x", txBuff[0],txBuff[1],txBuff[2],txBuff[3],
            txBuff[4],txBuff[5],txBuff[6],txBuff[7]);
//    qDebug() << endl;
    }
}

Std_ReturnType Tp::Tp_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    (void)TxPduId;
    if (m_tpTxInfo.state == TX_IDLE)
    {
        m_tpTxInfo.bytesHasTrans    = 0U;
        m_tpTxInfo.bytesTotal2Trans = (PduInfoPtr->SduLength < 1024U) 
            ? PduInfoPtr->SduLength : 1024U;
        for (uint32 i = 0U; i < m_tpTxInfo.bytesTotal2Trans; ++i)
        {
            m_tpTxInfo.Sdu[i] = PduInfoPtr->SduDataPtr[i];
        }

        //todo: 传统CAN,单帧最长7Bytes;
        m_tpTxInfo.state = (PduInfoPtr->SduLength <= 7U) ? TX_SF : TX_FF;
        return E_OK;
    } else {
        return E_NOT_OK;
    }
}

void Tp::Tp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    (void)TxPduId;
    (void)result;
}

void Tp::Tp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    (void)RxPduId;
    (void)PduInfoPtr;
    if (RxPduId == 0U)
    {
        for (uint8 i = 0u; i < PduInfoPtr->SduLength; ++i)
        {
            m_tpRxInfo.Sdu[i] = PduInfoPtr->SduDataPtr[i];
        }
        m_tpRxInfo.CAN_DL = PduInfoPtr->SduLength;
        Tp_RxChannelHandler(m_tpRxInfo);
    }
    else
    {
        Tp_TxChannelHandler(m_tpTxInfo);    /* which channel.*/
    }
}


BufReq_ReturnType
Tp::PduR_TpStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{
        return BUFREQ_OK;
}

BufReq_ReturnType
Tp::PduR_TpCopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{

    return BUFREQ_OK;
}

void Tp::PduR_TpRxIndication(PduIdType id, Std_ReturnType result)
{
    (void)id;
    (void)result;
}
