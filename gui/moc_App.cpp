/****************************************************************************
** Meta object code from reading C++ file 'App.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "App.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'App.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_App_t {
    QByteArrayData data[10];
    char stringdata[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_App_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_App_t qt_meta_stringdata_App = {
    {
QT_MOC_LITERAL(0, 0, 3),
QT_MOC_LITERAL(1, 4, 8),
QT_MOC_LITERAL(2, 13, 0),
QT_MOC_LITERAL(3, 14, 15),
QT_MOC_LITERAL(4, 30, 18),
QT_MOC_LITERAL(5, 49, 14),
QT_MOC_LITERAL(6, 64, 3),
QT_MOC_LITERAL(7, 68, 2),
QT_MOC_LITERAL(8, 71, 10),
QT_MOC_LITERAL(9, 82, 4)
    },
    "App\0slotOpen\0\0slotSetusername\0"
    "uiControlReadyRead\0slotnewmessage\0msg\0"
    "ip\0slotNewwnd\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_App[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       4,    0,   43,    2, 0x0a /* Public */,
       5,    2,   44,    2, 0x0a /* Public */,
       8,    2,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    9,

       0        // eod
};

void App::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        App *_t = static_cast<App *>(_o);
        switch (_id) {
        case 0: _t->slotOpen(); break;
        case 1: _t->slotSetusername((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->uiControlReadyRead(); break;
        case 3: _t->slotnewmessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->slotNewwnd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject App::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_App.data,
      qt_meta_data_App,  qt_static_metacall, 0, 0}
};


const QMetaObject *App::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *App::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_App.stringdata))
        return static_cast<void*>(const_cast< App*>(this));
    return QObject::qt_metacast(_clname);
}

int App::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
