/****************************************************************************
** Meta object code from reading C++ file 'servermanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../servermanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13ServerManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ServerManager::qt_create_metaobjectdata<qt_meta_tag_ZN13ServerManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ServerManager",
        "loginResult",
        "",
        "success",
        "message",
        "userId",
        "registerResult",
        "msg",
        "adminLoginResult",
        "adaugaProdusResult",
        "idProdus",
        "alimentarePortofelResult",
        "soldNou",
        "schimbareMailResult",
        "schimbareParolaResult",
        "produseClientResult",
        "QJsonArray",
        "produse",
        "adaugaFavoritResult",
        "produseUtilizatorResult",
        "getFavoriteResult",
        "cumparaProdusResult",
        "getNotificariResult",
        "notificari",
        "marcheazaCititeResult",
        "notificareNoua",
        "tip",
        "mesaj",
        "produseCumparateResult",
        "notaVanzatorResult",
        "nota",
        "nrReview",
        "lasaReviewResult"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'loginResult'
        QtMocHelpers::SignalData<void(bool, QString, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 }, { QMetaType::Int, 5 },
        }}),
        // Signal 'registerResult'
        QtMocHelpers::SignalData<void(bool, QString, int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { QMetaType::Int, 5 },
        }}),
        // Signal 'adminLoginResult'
        QtMocHelpers::SignalData<void(bool, QString)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'adaugaProdusResult'
        QtMocHelpers::SignalData<void(bool, QString, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 }, { QMetaType::Int, 10 },
        }}),
        // Signal 'alimentarePortofelResult'
        QtMocHelpers::SignalData<void(bool, QString, double)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 }, { QMetaType::Double, 12 },
        }}),
        // Signal 'schimbareMailResult'
        QtMocHelpers::SignalData<void(bool, QString)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'schimbareParolaResult'
        QtMocHelpers::SignalData<void(bool, QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'produseClientResult'
        QtMocHelpers::SignalData<void(bool, QString, QJsonArray)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { 0x80000000 | 16, 17 },
        }}),
        // Signal 'adaugaFavoritResult'
        QtMocHelpers::SignalData<void(bool, QString)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'produseUtilizatorResult'
        QtMocHelpers::SignalData<void(bool, QString, QJsonArray)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { 0x80000000 | 16, 17 },
        }}),
        // Signal 'getFavoriteResult'
        QtMocHelpers::SignalData<void(bool, QString, QJsonArray)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { 0x80000000 | 16, 17 },
        }}),
        // Signal 'cumparaProdusResult'
        QtMocHelpers::SignalData<void(bool, QString)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'getNotificariResult'
        QtMocHelpers::SignalData<void(bool, QJsonArray)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { 0x80000000 | 16, 23 },
        }}),
        // Signal 'marcheazaCititeResult'
        QtMocHelpers::SignalData<void(bool)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'notificareNoua'
        QtMocHelpers::SignalData<void(QString, QString)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 26 }, { QMetaType::QString, 27 },
        }}),
        // Signal 'produseCumparateResult'
        QtMocHelpers::SignalData<void(bool, QString, QJsonArray)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { 0x80000000 | 16, 17 },
        }}),
        // Signal 'notaVanzatorResult'
        QtMocHelpers::SignalData<void(double, int)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 30 }, { QMetaType::Int, 31 },
        }}),
        // Signal 'lasaReviewResult'
        QtMocHelpers::SignalData<void(bool, QString)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ServerManager, qt_meta_tag_ZN13ServerManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ServerManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ServerManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ServerManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13ServerManagerE_t>.metaTypes,
    nullptr
} };

void ServerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ServerManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loginResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->registerResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->adminLoginResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->adaugaProdusResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->alimentarePortofelResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3]))); break;
        case 5: _t->schimbareMailResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->schimbareParolaResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->produseClientResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[3]))); break;
        case 8: _t->adaugaFavoritResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->produseUtilizatorResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[3]))); break;
        case 10: _t->getFavoriteResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[3]))); break;
        case 11: _t->cumparaProdusResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->getNotificariResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[2]))); break;
        case 13: _t->marcheazaCititeResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->notificareNoua((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->produseCumparateResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QJsonArray>>(_a[3]))); break;
        case 16: _t->notaVanzatorResult((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 17: _t->lasaReviewResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , int )>(_a, &ServerManager::loginResult, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , int )>(_a, &ServerManager::registerResult, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::adminLoginResult, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , int )>(_a, &ServerManager::adaugaProdusResult, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , double )>(_a, &ServerManager::alimentarePortofelResult, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::schimbareMailResult, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::schimbareParolaResult, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , QJsonArray )>(_a, &ServerManager::produseClientResult, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::adaugaFavoritResult, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , QJsonArray )>(_a, &ServerManager::produseUtilizatorResult, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , QJsonArray )>(_a, &ServerManager::getFavoriteResult, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::cumparaProdusResult, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QJsonArray )>(_a, &ServerManager::getNotificariResult, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool )>(_a, &ServerManager::marcheazaCititeResult, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(QString , QString )>(_a, &ServerManager::notificareNoua, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString , QJsonArray )>(_a, &ServerManager::produseCumparateResult, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(double , int )>(_a, &ServerManager::notaVanzatorResult, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (ServerManager::*)(bool , QString )>(_a, &ServerManager::lasaReviewResult, 17))
            return;
    }
}

const QMetaObject *ServerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ServerManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ServerManager::loginResult(bool _t1, QString _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void ServerManager::registerResult(bool _t1, QString _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void ServerManager::adminLoginResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void ServerManager::adaugaProdusResult(bool _t1, QString _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void ServerManager::alimentarePortofelResult(bool _t1, QString _t2, double _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2, _t3);
}

// SIGNAL 5
void ServerManager::schimbareMailResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void ServerManager::schimbareParolaResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void ServerManager::produseClientResult(bool _t1, QString _t2, QJsonArray _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void ServerManager::adaugaFavoritResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void ServerManager::produseUtilizatorResult(bool _t1, QString _t2, QJsonArray _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2, _t3);
}

// SIGNAL 10
void ServerManager::getFavoriteResult(bool _t1, QString _t2, QJsonArray _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2, _t3);
}

// SIGNAL 11
void ServerManager::cumparaProdusResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void ServerManager::getNotificariResult(bool _t1, QJsonArray _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1, _t2);
}

// SIGNAL 13
void ServerManager::marcheazaCititeResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void ServerManager::notificareNoua(QString _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1, _t2);
}

// SIGNAL 15
void ServerManager::produseCumparateResult(bool _t1, QString _t2, QJsonArray _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1, _t2, _t3);
}

// SIGNAL 16
void ServerManager::notaVanzatorResult(double _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1, _t2);
}

// SIGNAL 17
void ServerManager::lasaReviewResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 17, nullptr, _t1, _t2);
}
QT_WARNING_POP
