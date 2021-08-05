/*
 * Copyright (c) 2019 TAOS Data, Inc. <cli@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TDENGINE_MNODE_SDB_TABLE_H
#define TDENGINE_MNODE_SDB_TABLE_H

#include "mnodeSdb.h"

typedef enum mnodeSdbTableType {
  SDB_TABLE_HASH_TABLE,
  SDB_TABLE_LRU_CACHE,
} mnodeSdbTableType;

struct mnodeSdbTable;
typedef struct mnodeSdbTable mnodeSdbTable;

struct SWalHead;
struct SSdbRow;

typedef struct mnodeSdbTableOption {
  int32_t   hashSessions;
  ESdbKey   keyType;
  mnodeSdbTableType tableType;
  void* userData;
} mnodeSdbTableOption ;

mnodeSdbTable* mnodeSdbTableInit(mnodeSdbTableOption);
void mnodeSdbTableClear(mnodeSdbTable *pTable);

void *mnodeSdbTableGet(mnodeSdbTable *pTable, const void *key, size_t keyLen);
void mnodeSdbTablePut(mnodeSdbTable *pTable, SSdbRow* pRow);

void mnodeSdbTableSyncWalPos(mnodeSdbTable *pTable, SWalHead*, int64_t off);

void mnodeSdbTableRemove(mnodeSdbTable *pTable, const SSdbRow* pRow);

void *mnodeSdbTableIterate(mnodeSdbTable *pTable, void *p);
void* mnodeSdbTableIterValue(mnodeSdbTable *pTable,void *p);
void mnodeSdbTableCancelIterate(mnodeSdbTable *pTable, void *p);

void mnodeSdbTableFreeValue(mnodeSdbTable *pTable, void *p);

#endif // TDENGINE_MNODE_SDB_TABLE_H