#include "ConnBDD.h"

int ConnBDD::ConnecterBDD() {
    // 1. Initialiser l'environnement ODBC
    std::wcout << L"Initialisation de l'environnement ODBC..." << std::endl;
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::wcerr << L"Erreur d'initialisation de l'environnement ODBC !" << std::endl;
        return -1;
    }
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // 2. Connecter à la base de données
    std::wcout << L"Connexion a la base de donnees..." << std::endl;
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::wcerr << L"Erreur lors de l'allocation du handle de connexion !" << std::endl;
        return -1;
    }

    // Chaîne de connexion ODBC (version Unicode)
    SQLWCHAR connectionString[] =
        L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=Gestion_Reservation_Client_paiements;Trusted_Connection=yes;";

    ret = SQLDriverConnectW(hDbc, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Connexion reussie !" << std::endl;
    }
    else {
        SQLWCHAR sqlState[6], message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        // Récupérer les détails de l'erreur
        SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, 1, sqlState, &nativeError, message, sizeof(message), &textLength);
        std::wcerr << L"Erreur de connexion : " << message << std::endl;
        std::wcerr << L"Code d'erreur SQL : " << sqlState << std::endl;
        std::wcerr << L"Erreur native : " << nativeError << std::endl;
        return -1;
    }

    // Libérer les ressources
    std::wcout << L"Liberation des ressources..." << std::endl;
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}