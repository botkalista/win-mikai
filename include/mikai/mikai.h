/*
 * @author      Lilz <https://telegram.me/Lilz73>
 * @copyright   2020-2021 Lilz <https://telegram.me/Lilz73>
 * @license     MIKAI X License
 *
 * This file is part of MIKAI X.
 *
 * MIKAI X is free software: you can redistribute it and/or modify
 * it under the terms of the MIKAI X License, as published by
 * Lilz along with this program and available on "MIKAI X Download" Telegram channel
 * <https://telegram.me/mikaidownload>.
 *
 * MIKAI X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 *
 * You should have received a copy of the MIKAI X License along
 * with MIKAI X.
 * If not, see <https://telegram.me/mikaidownload>.
 */

#ifndef MIKAI_MIKAI_H
#define MIKAI_MIKAI_H

#include <stdbool.h>
#include <stdint.h>
#include <mikai/mikai-reader.h>

#define SRIX_BLOCK_LENGTH  4
#define SRIX_UID_LENGTH    8
#define SRIX4K_BLOCKS      128
#define SRIX4K_BYTES       512

#ifdef __cplusplus
extern  "C" {
#endif /* __cplusplus */

/**
 * Get current version of mikai as string.
 * @return version as a string
 */
MIKAI_EXPORT const char *MikaiVersion();

/**
* Create a new MyKey instance. Chip id of an uninitialized MyKey is 00 00 00 00.
* @return pointer to MyKey instance
*/
MIKAI_EXPORT MyKey *MikaiNew();

/**
 * Initialize a MyKey.
 * @param target if it points to a null MyKey struct pointer, a new MyKey instance will be created, else an existing struct will be modified.
 * @param dump If it isn't null, the struct will be initialize in FILE DUMP mode
 * @param selection If dump isn't null, it's the uid, else it's the Reader selection (element of the readers array)
 * @return string that represent an error, NULL if success
 */
MIKAI_EXPORT const char *MikaiInit(MyKey **target, uint32_t dump[SRIX4K_BLOCKS], uint64_t selection);

/**
 * Delete a MyKey.
 * @param key pointer to instance to delete
 */
MIKAI_EXPORT void MikaiDelete(MyKey *key);

/**
 * Get a text description of latest error occured and reset it.
 * @param key pointer to MyKey instance
 * @return string description of error, "" if there is no error in memory
 */
MIKAI_EXPORT const char *MikaiGetLatestError(MyKey *key);

/**
 * Get MyKey encryption key. If its value is 0, block 6 has value 0.
 * @param key pointer to MyKey instance
 * @return uint32 value of encryption key
 */
MIKAI_EXPORT uint32_t MyKeyGetEncryptionKey(MyKey *key);

/**
 * Check if a MyKey is reset (if it hasn't an associated vendor code).
 * @param key pointer to MyKey struct
 * @return boolean value, true = there isn't a vendor bound
 */
MIKAI_EXPORT bool MyKeyIsReset(MyKey *key);

/**
 * Return true if MyKey has lock id and checksum of credit is wrong.
 * @param key pointer to MyKey instance
 * @return boolean value (true = there is lock id)
 */
MIKAI_EXPORT bool MyKeyCheckLockID(MyKey *key);


/**
 * Get the value of a specific block.
 * @param key pointer to MyKey instance
 * @param blockNum number of block to get
 * @return uint32 value of the block
 */
MIKAI_EXPORT uint32_t MyKeyGetBlock(MyKey *key, uint8_t blockNum);

/**
 * Modify a MyKey block manually.
 * @param key pointer to MyKey instance
 * @param block value of block to write to blockNum
 * @param blockNum number of block to write
 */
MIKAI_EXPORT void MyKeyModifyBlock(MyKey *key, uint32_t block, uint8_t blockNum);

/**
 * Import vendor code and recalculate encryption key.
 * @param key pointer to MyKey instance
 * @param vendor vendor code decrypted value
 */
MIKAI_EXPORT void MyKeyImportVendor(MyKey *key, uint32_t vendor);

/**
 * Decrypt vendor code and save it to vendor pointer.
 * @param key pointer to MyKey instance
 * @param vendor location where save vendor code
 * @return 0 = success: if it's another value, use MikaiGetLatestError()
 */
MIKAI_EXPORT int MyKeyExportVendor(MyKey *key, uint32_t *vendor);

/**
 * Export SRIX data to specified memory locations.
 * @param key pointer to MyKey instance
 * @param dump pointer where copy SRIX EEPROM
 * @param uid pointer where save SRIX UID
 */
MIKAI_EXPORT void MyKeyExportMemory(MyKey *key, uint32_t dump[SRIX4K_BLOCKS], uint64_t *uid);

/**
 * Reset a MyKey to associate it with another vendor.
 * @param key pointer to MyKey instance
 */
MIKAI_EXPORT void MyKeyReset(MyKey *key);

/**
 * Extract current credit from block 21.
 * @param key pointer to MyKey instance
 * @return credit in cents
 */
MIKAI_EXPORT uint16_t MyKeyGetCurrentCredit(MyKey *key);

/**
 * Add N cents to MyKey actual credit.
 * @param key pointer to MyKey instance
 * @param cents cents to add
 * @param day day number in the month (1-31)
 * @param month month number in the year (1-12)
 * @param year year number from 2000 (0-127)
 * @return 0 = success: if it's another value, use MikaiGetLatestError()
 */
MIKAI_EXPORT int MyKeyAddCents(MyKey *key, uint16_t cents, uint8_t day, uint8_t month, uint8_t year);

/**
* Reset credit history and charge N cents.
* @param key pointer to MyKey instance
* @param cents cents to add
* @param day day number in the month (1-31)
* @param month month number in the year (1-12)
* @param year year number from 2000 (0-127)
* @return 0 = success: if it's another value, use MikaiGetLatestError()
*/
MIKAI_EXPORT int MyKeySetCents(MyKey *key, uint16_t cents, uint8_t day, uint8_t month, uint8_t year);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* MIKAI_MIKAI_H */