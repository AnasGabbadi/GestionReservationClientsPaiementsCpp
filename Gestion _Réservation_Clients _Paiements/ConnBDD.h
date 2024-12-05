#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream> 

class ConnBDD {
private:
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret; 
public:
    int ConnecterBDD();
};