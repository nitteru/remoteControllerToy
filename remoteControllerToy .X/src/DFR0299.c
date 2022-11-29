/*
 * File:   DFR0299.c
 * Author: Teruyuki
 *
 * Created on 2022/11/21, 6:59
 */


#include <xc.h>
#include "DFR0299.h"

void DFR0299Initialize(void)
{
    // 初期設定
    /*
     * 1. リセットコマンドを発行して返信を待つ
     * 2. IOで電源ON/OFFできるよにして返信を待つ
     * 
     * どちらにしろ一定時間内(100-1500msec)に返信がなければエラー
     * UARTの受信があるのでその処理をどう分割するか?
     */
}

void makeChecksum(void)
{
    // チェックサム生成
    // 返り値､引数は別途検討
}
