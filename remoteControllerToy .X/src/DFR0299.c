/*
 * File:   DFR0299.c
 * Author: Teruyuki
 *
 * Created on 2022/11/21, 6:59
 */


#include <xc.h>
#include "DFR0299.h"

uint8_t DFR0299Initialize(void)
{
    // 初期設定
    /*
     * 1. リセットコマンドを発行して返信を待つ
     * 2. IOで電源ON/OFFできるよにして返信を待つ
     * 
     * どちらにしろ一定時間内(100-1500msec)に返信がなければエラー
     * UARTの受信があるのでその処理をどう分割するか?
     */
    
    return 0;
}

void makeChecksum(uint8_t *cmd, uint8_t *checkMSB, uint8_t *checkLSB, uint8_t index)
{
    // チェックサム生成
    uint16_t sum = 0x0000, ret = 0x0000;
    
    // indexはPara_LSBまで
    for(uint8_t i = 1; i < index; i++)
    {
        sum += cmd[i];
    }
    
    ret = 0xFFFF - sum + 1;
    
    *checkMSB = (uint8_t)(ret >> 8);
    *checkLSB = (uint8_t)(ret & 0x00FF);
}
