/*
 * File:   main.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 10:42 AM
 */


#include "DeviceConfig.h"
#include <xc.h>
#include "main.h"
#include "pin.h"
#include "interrupt.h"
#include "init.h"
#include "usart.h"
#include "eeprom.h"
#include "tmr0.h"
#include "tmr1.h"
#include "tmr2.h"
#include "ccp1.h"

void main(void) {
    
    disableGlobalInterrupt();
    disablePeripheralInterrupt();
    
    systemInitialize();
    
    enableGlobalInterrupt();
    enablePeripheralInterrupt();
    
    while(1)
    {
        CLRWDT();
#if 0
/*
         * SLEEPを使う場合
         * 1. 必要なら復帰に使わないペリフェラルのPIEを0にする
         *    (クロックが必要なペリフェラルを除く)
         * 2. 割り込みを行わない場合は事前にGIEを0にする
         * 3. SLEEPの次がプリフェッチされている｡実行したくない場合はNOPを置く｡
         * 4. WDTを確実にクリアするためにSLEEP直前にCLRWDTを置く
         */
        SLEEP();
        NOP();
        
        if(STATUSbits.nPD == 0)
        {
            // nPD: 電源ONまたはSLEEPの実行で0
            
            if(STATUSbits.nTO == 0)
            {
                // nTO: WDTタイムアウト発生で0 → WDTタイムアウトで復帰
                // 例えばカウンタを用意して一定期間後に処理をする､など
            }
            else
            {
                // その他の割り込み要因で復帰
            }
        }
#endif

        // Todo CCPの設定を追加したい
        
#ifdef ENABLE_USART
        if(RCSTAbits.OERR)
        {
            // オーバーランエラー
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
#endif
        
        // 本処理
        
    }
    return;
}
