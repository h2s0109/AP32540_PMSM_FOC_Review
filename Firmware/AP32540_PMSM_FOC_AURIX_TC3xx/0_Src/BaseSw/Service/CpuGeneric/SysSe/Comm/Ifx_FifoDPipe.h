/**
 * \file Ifx_FifoDPipe.h
 * \brief FIFO DPipe
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
 * \defgroup library_sysse_hwindependant_comm_fifoDPipe Fifo DPipe
 * \ingroup library_sysse_hwindependant_comm
 *
 * \defgroup library_sysse_hwindependant_comm_fifoDPipe_cDriver C driver
 * \ingroup library_sysse_hwindependant_comm_fifoDPipe
 *
 * \defgroup library_sysse_hwindependant_comm_fifoDPipe_cppWrapper C++ wrapper
 * \ingroup library_sysse_hwindependant_comm_fifoDPipe
 */
#ifndef IFX_FIFODPIPE_H_
#define IFX_FIFODPIPE_H_

#include "StdIf/IfxStdIf_DPipe.h"
#include "_Lib/DataHandling/Ifx_Fifo.h"
#include "Ifx_Types.h"

/** \addtogroup library_sysse_hwindependant_comm_fifoDPipe_cDriver
 * \{ */

typedef struct
{
    Ifx_Fifo* tx;                             /**< \brief Transmit FIFO buffer */
    Ifx_Fifo* rx;                             /**< \brief Receive FIFO buffer */
    IfxStdIf_DPipe stdif;
}Ifx_FifoDPipe;

IFX_EXTERN boolean                   Ifx_FifoDPipe_write(Ifx_FifoDPipe* dPipe, void* data, Ifx_SizeT* count);
IFX_EXTERN void                      Ifx_FifoDPipe_writeFormatted(Ifx_FifoDPipe* dPipe, pchar format, ...);
IFX_EXTERN void                      Ifx_FifoDPipe_writeText(Ifx_FifoDPipe* dPipe, pchar text);
IFX_EXTERN boolean                   Ifx_FifoDPipe_read(Ifx_FifoDPipe* dPipe, void* data, Ifx_SizeT* count, Ifx_TickTime timeout);
IFX_EXTERN sint32                    Ifx_FifoDPipe_getReadCount(Ifx_FifoDPipe* dPipe);
IFX_EXTERN IfxStdIf_DPipe_ReadEvent  Ifx_FifoDPipe_getReadEvent(Ifx_FifoDPipe* dPipe);
IFX_INLINE uint32                    Ifx_FifoDPipe_getSendCount(Ifx_FifoDPipe* dPipe)
{ return 0; /* FIXME TODO */ }
IFX_INLINE Ifx_TickTime              Ifx_FifoDPipe_getTxTimeStamp(Ifx_FifoDPipe* dPipe)
{ return 0; /* FIXME TODO */ }
IFX_EXTERN sint32                    Ifx_FifoDPipe_getWriteCount(Ifx_FifoDPipe* dPipe);
IFX_EXTERN IfxStdIf_DPipe_WriteEvent Ifx_FifoDPipe_getWriteEvent(Ifx_FifoDPipe* dPipe);
IFX_EXTERN boolean                   Ifx_FifoDPipe_canReadCount(Ifx_FifoDPipe* dPipe, Ifx_SizeT count, Ifx_TickTime timeout);
IFX_EXTERN boolean                   Ifx_FifoDPipe_canWriteCount(Ifx_FifoDPipe* dPipe, Ifx_SizeT count, Ifx_TickTime timeout);
IFX_EXTERN boolean                   Ifx_FifoDPipe_flushTx(Ifx_FifoDPipe* dPipe, Ifx_TickTime timeout);
IFX_EXTERN void                      Ifx_FifoDPipe_clearRx(Ifx_FifoDPipe* dPipe);
IFX_EXTERN void                      Ifx_FifoDPipe_clearTx(Ifx_FifoDPipe* dPipe);
IFX_INLINE void                      Ifx_FifoDPipe_onReceive(Ifx_FifoDPipe* dPipe)
{ /* NOTHING TO DO  */ }
IFX_INLINE void                      Ifx_FifoDPipe_onTransmit(Ifx_FifoDPipe* dPipe)
{ /* NOTHING TO DO  */ }
IFX_INLINE void                      Ifx_FifoDPipe_onError(Ifx_FifoDPipe* dPipe)
{ /* NOTHING TO DO  */ }
IFX_INLINE void                      Ifx_FifoDPipe_resetSendCount(Ifx_FifoDPipe* dPipe)
{ /* FIXME TODO */ }

IFX_INLINE IfxStdIf_DPipe* Ifx_FifoDPipe_getStdIf(Ifx_FifoDPipe* dPipe)
{ return &dPipe->stdif; }

IFX_EXTERN void      Ifx_FifoDPipe_init(Ifx_FifoDPipe* dPipe, Ifx_SizeT rxBufferSize, Ifx_SizeT txBufferSize);
IFX_EXTERN void      Ifx_FifoDPipe_deInit(Ifx_FifoDPipe* dPipe);
/**
 * @return Returns a pointer on the TX FIFO
 */
IFX_INLINE Ifx_Fifo* Ifx_FifoDPipe_getTxFifo(Ifx_FifoDPipe* dPipe)
{ return dPipe->tx; }

/**
 * @return Returns a pointer on the RX FIFO
 */
IFX_INLINE Ifx_Fifo* Ifx_FifoDPipe_getRxFifo(Ifx_FifoDPipe* dPipe)
{ return dPipe->rx; }

IFX_INLINE void Ifx_FifoDPipe_disableTx(Ifx_FifoDPipe* dPipe)
{ IfxStdIf_DPipe_disableTx(&dPipe->stdif); }

IFX_INLINE void Ifx_FifoDPipe_enableTx(Ifx_FifoDPipe* dPipe)
{ IfxStdIf_DPipe_enableTx(&dPipe->stdif); }

IFX_INLINE Ifx_TickTime Ifx_FifoDPipe_getWriteTimeout(Ifx_FifoDPipe* dPipe)
{ return IfxStdIf_DPipe_getWriteTimeout(&dPipe->stdif); }

/**
 * @return Set the write timeout
 */
IFX_INLINE void Ifx_FifoDPipe_setWriteTimeout(Ifx_FifoDPipe* dPipe, Ifx_TickTime timeout)
{ IfxStdIf_DPipe_setWriteTimeout(&dPipe->stdif, timeout); }

IFX_INLINE boolean Ifx_FifoDPipe_isTxDisabled(Ifx_FifoDPipe* dPipe)
{ return IfxStdIf_DPipe_isTxDisabled(&dPipe->stdif); }

IFX_EXTERN boolean Ifx_FifoDPipe_initStdIf(Ifx_FifoDPipe* dPipe);

/** \} */
#endif /* IFX_FIFODPIPE_H_ */
