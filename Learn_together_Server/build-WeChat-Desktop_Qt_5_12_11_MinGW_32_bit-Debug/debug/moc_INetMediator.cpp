/****************************************************************************
** Meta object code from reading C++ file 'INetMediator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WeChat/netapi/mediator/INetMediator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'INetMediator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_INetMediator_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_INetMediator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_INetMediator_t qt_meta_stringdata_INetMediator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "INetMediator"
QT_MOC_LITERAL(1, 13, 13), // "SIG_ReadyData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "lSendIP"
QT_MOC_LITERAL(4, 36, 5), // "char*"
QT_MOC_LITERAL(5, 42, 3), // "buf"
QT_MOC_LITERAL(6, 46, 4), // "nlen"
QT_MOC_LITERAL(7, 51, 14) // "SIG_disConnect"

    },
    "INetMediator\0SIG_ReadyData\0\0lSendIP\0"
    "char*\0buf\0nlen\0SIG_disConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_INetMediator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       7,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,
    QMetaType::Void,

       0        // eod
};

void INetMediator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<INetMediator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_ReadyData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->SIG_disConnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (INetMediator::*)(unsigned int , char * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&INetMediator::SIG_ReadyData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (INetMediator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&INetMediator::SIG_disConnect)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject INetMediator::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_INetMediator.data,
    qt_meta_data_INetMediator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *INetMediator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *INetMediator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_INetMediator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int INetMediator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void INetMediator::SIG_ReadyData(unsigned int _t1, char * _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void INetMediator::SIG_disConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
