/*
 * \file DataStreaming.c
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *                            IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#include "DataStreaming.h"
#include "PmsmFoc.h"

#define SYNCPROTOCOL_MESSAGE_ID_DATASTREAMING_DATA_0 (0x4000)    /**< \see Oscilloscope_MessageAssignedChannel */
#if defined(__HIGHTEC__)
typedef struct __attribute__ ((__packed__))
#elif defined(__TASKING__)
typedef struct
#else
typedef struct
#endif
{
	float32 refSpeed;
	float32 measSpeed;
	float32 idRef;
	float32 idMeas;
}DataStreaming_Data_0;
#define SYNCPROTOCOL_MESSAGE_ID_DATASTREAMING_DATA_0_CMD_SIZE (16)




boolean        DataStreaming_init(DataStreaming* dataStreaming, Ifx_TickTime period, SyncProtocol* protocol, SyncProtocol_Port localPort, SyncProtocol_Port remotePort)
{
	dataStreaming->period = period;
	dataStreaming->deadline   = getDeadLine(period);
    return SyncProtocol_addClient(protocol, &dataStreaming->_bbClient, localPort, remotePort, dataStreaming->_bbClientMessagePayloadRx, sizeof(dataStreaming->_bbClientMessagePayloadRx));
}

static void DataStreaming_sendData(DataStreaming* dataStreaming)
{
	DataStreaming_Data_0* m = (DataStreaming_Data_0*)dataStreaming->_bbClientMessagePayloadTx;

    if (SyncProtocol_setSendMessageBuffer(
            &dataStreaming->_bbClient,
			SYNCPROTOCOL_MESSAGE_ID_DATASTREAMING_DATA_0,
			dataStreaming->_bbClientMessagePayloadTx,
            sizeof(DataStreaming_Data_0)))
    {
        m->refSpeed = g_motorCtrl.pmsmFoc.speedControl.refSpeed;
        m->measSpeed = g_motorCtrl.pmsmFoc.speedControl.measSpeed;
        m->idRef = g_motorCtrl.pmsmFoc.idqRef.imag;
        m->idMeas = g_motorCtrl.pmsmFoc.idqMeas.imag;
        SyncProtocol_sendMessage(&dataStreaming->_bbClient);
    }
}

void DataStreaming_processMessages(DataStreaming* dataStreaming)
{

    if (dataStreaming->_bbClient.receive.messageValid)
    {
        SyncProtocol_MessageId id;
        uint32                 length;
        uint8*                 payloadRx;

        if (SyncProtocol_getReadMessageBuffer(&dataStreaming->_bbClient, &id, &payloadRx, &length))
        {

            SyncProtocol_releaseReadMessageBuffer(&dataStreaming->_bbClient);
        }
    }

	if (!isDeadLine(dataStreaming->deadline))
	{
		return;
	}
    if (SyncProtocol_isSendBusy(&dataStreaming->_bbClient))
    {
        return;
    }

	dataStreaming->deadline   = dataStreaming->deadline + dataStreaming->period;


    DataStreaming_sendData(dataStreaming);
}


