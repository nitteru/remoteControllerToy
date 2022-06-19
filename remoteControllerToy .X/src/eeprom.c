/*
 * File:   eeprom.c
 * Author: Teruyuki
 *
 * Created on June 16, 2022, 4:57 PM
 */


#include <xc.h>

void EEPROMInitialize(void) {
    PIE2bits.EEIE = 0;
    PIR2bits.EEIF = 0;
    
    /*
     * 書き込み完了をポーリングから割り込みに変更するとき用
     * あとでマクロを使って変更できるようにする
     */
    
    //PIE2bits.EEIE = 1;
}

void EEPROMWrite(uint8_t address, uint8_t data)
{
    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    
    /*
     * 書き込み完了をポーリングで待つ
     * マクロを使って割り込みにできるようにする
     */
    while(EECON1bits.WR == 1)
    {
        NOP();
    }
    EECON1bits.WREN = 0; // エラー処理､ベリファイは今後追加予定
}

uint8_t EEPROMRead(uint8_t address)
{
    EEADR = address;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;

    return EEDATA; // 次のサイクルで読み込み可能
}

void FlashWrite(uint16_t address, uint16_t data)
{
    EEADRH = (uint8_t)(address >> 8);
    EEADR = (uint8_t)(address & 0x00FF);
    EECON1bits.EEPGD = 1;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    
    NOP(); // これは無視される
    NOP(); // ここから再開
    // 書き込み完了まで動作を停止
    
    EECON1bits.WREN = 0; // エラー処理､ベリファイ､CPへの影響は今後追加予定
}

uint16_t FlashRead(uint16_t address)
{   
    EEADRH = (uint8_t)(address >> 8);
    EEADR = (uint8_t)(address & 0x00FF);
    EECON1bits.EEPGD = 1;
    EECON1bits.RD = 1;
    NOP(); // RD実行後の2命令は無視される
    NOP();

    return (uint16_t)(EEDATH << 8 | EEDATA);
}