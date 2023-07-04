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

#ifndef MIKAI_MIKAI_READER_H
#define MIKAI_MIKAI_READER_H

#include <stdlib.h>

typedef struct MyKey MyKey;

/*
 * Export functions from DLL in Windows
 * https://docs.microsoft.com/cpp/build/exporting-from-a-dll-using-declspec-dllexport
 */
#if defined _WIN32 && !defined _WINDLL
#define MIKAI_EXPORT __declspec(dllexport)
#else
#define MIKAI_EXPORT
#endif

#ifdef __cplusplus
extern  "C" {
#endif /* __cplusplus */

/**
 * Update internal register of available readers.
 * @param key pointer to MyKey instance where save readers
 * @return number of available readers
 */
MIKAI_EXPORT size_t MyKeyGetReadersCount(MyKey *key);

/**
 * Get the description of a reader.
 * @param key pointer to MyKey instance where readers are saved
 * @param reader offset of reader to get
 * @return string description of reader
 */
MIKAI_EXPORT char *MyKeyGetReaderDescription(MyKey *key, int reader);

/**
 * Write all modified blocks to SRIX4K.
 * @param key pointer to MyKey instance where reader is initialized
 * @return 0 = success: if it's another value, use MikaiGetLatestError()
 */
MIKAI_EXPORT int MyKeyWriteAll(MyKey *key);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* MIKAI_MIKAI_H */
