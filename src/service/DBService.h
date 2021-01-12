#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "config/config.h"
#define FORMAT_SPIFFS_IF_FAILED true
#define MAX_FILE_NAME_LEN 100
#define MAX_STR_LEN 500
#define DEBUG_ON 1

class DBService
{
public:
    int rc;
    char *zErrMsg;
    DBService();
    virtual void CreateTable() = 0;
    virtual int DropTable() = 0;
    sqlite3 *_db = NULL;
    int Db_open(char name[]);

protected:
    char _db_name[MAX_FILE_NAME_LEN];
    
    
};


#endif
