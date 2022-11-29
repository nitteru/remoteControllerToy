/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#pragma once

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"

// コマンド
#define DFPM_START_CODE (uint8_t)0x7E
#define DFPM_END_CODE (uint8_t)0xEF
#define DFPM_CMD_NEXT (uint8_t)0x01 // 次の曲
#define DFPM_CMD_PREVIOUS (uint8_t)0x02 // 前の曲
#define DFPM_CMD_SPECIFY_TRACKING (uint8_t)0x03 // 曲番号指定 0-2999
#define DFPM_CMD_VOLUME_UP (uint8_t)0x04 // ボリュームアップ
#define DFPM_CMD_VOLUME_DOWN (uint8_t)0x05 // ボリュームダウン
#define DFPM_CMD_SPECIFY_VOLUME (uint8_t)0x06 // ボリューム値指定 0-30
#define DFPM_CMD_SPECIFY_EQ (uint8_t)0x07 // イコライザ設定 0-5:Normal/Pop/Rock/Jazz/Classic/Base
#define DFPM_CMD_SPECIFY_PLAYBACK_MODE (uint8_t)0x08 // 再生モード設定 0-3:Repeat/Folder Repeat/Single Repeat/Random
#define DFPM_CMD_SPECIFY_PLAYBACK_SOURCE (uint8_t)0x09 // 再生ソース設定 0-4:U/TF/AUX/SLEEP/Flash
#define DFPM_CMD_ENTER_STANDBY (uint8_t)0x0A // スタンバイモード
#define DFPM_CMD_NORMAL_WORKING (uint8_t)0x0B // 通常動作
#define DFPM_CMD_RESET (uint8_t)0x0C // モジュールリセット
#define DFPM_CMD_PLAYBACK (uint8_t)0x0D // プレイ
#define DFPM_CMD_PAUSE (uint8_t)0x0E // 一時停止
#define DFPM_CMD_SPECIFY_FOLDER_PLAYBACK (uint8_t)0x0F // フォルダ内のファイル名を指定して再生
#define DFPM_CMD_VOLUME_AJUST_SET (uint8_t)0x10 // ボリュームアジャスト DH:1 Open volume ajust, DL: volume gain 0-31
#define DFPM_CMD_REPEAT_PLAY (uint8_t)0x11 // リピート再生 0:Stop play, 1:Start repeat play

// クエリ
#define DFP_QUERY_FINISH_PLAYBACK_UDISK (uint8_t)0x3C // 1曲再生終了 USBディスク
#define DFP_QUERY_FINISH_PLAYBACK_TFCARD (uint8_t)0x3D // 1曲再生終了 TFカード
#define DFP_QUERY_FINISH_PLAYBACK_FLASH (uint8_t)0x3E // 1曲再生終了 内蔵フラッシュ
#define DFPM_QUERY_INITIALIZED (uint8_t)0x3F // 初期化
#define DFPM_QUERY_ROR (uint8_t)0x40 // エラー

/*
 * パラメータ
 * 上位4ビットと下位4ビットをPara_MSB, Para_LSBに分割して使用する
 */
// 0x3F(電源投入･初期化)コマンド パラメータ
#define DFPM_PARA_NO_TFCARD (uint8_t)0x00 // TFカード未挿入
#define DFPM_PARA_UDISK_ONLINE (uint8_t)0x01 // USBディスクオンライン
#define DFPM_PARA_TFCARD_ONLINE (uint8_t)0x02 // TFカードオンライン
#define DFPM_PARA_UDISK_TFCARD_ONLINE (uint8_t)0x03 // USBディスクとTFカード両方オンライン
#define DFPM_PARA_PC_ONLINE (uint8_t)0x04 // PCオンライン
#define DFPM_PARA_FLASH_ONLINE (uint8_t)0x08 // 内蔵フラッシュオンライン


typedef union
{
    struct
    {
        // LSB
        uint8_t startCode; // スタートコード
        uint8_t version; // バージョン
        uint8_t length; // データ帳
        uint8_t command; // コマンド
        uint8_t feedback; // 返答の有無
        uint8_t parameterHigh; // パラメーター上位
        uint8_t parameterLow; // パラメーター下位
        uint8_t checksum; // チェックサム
        uint8_t endCode; // エンコード
        // MSB
    };
    uint8_t A[9]; // 一括アクセス用
} DFPMInstrution;
\
void DFR0299Initialize(void); // 初期設定
void makeChecksum(void); // チェックサム生成