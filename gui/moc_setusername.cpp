/****************************************************************************
** Meta object code from reading C++ file 'setusername.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setusername.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setusername.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SetUsername_t {
    QByteArrayData data[6];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetUsername_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetUsername_t qt_meta_stringdata_SetUsername = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 7),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 9),
QT_MOC_LITERAL(4, 31, 20),
QT_MOC_LITERAL(5, 52, 24)
    },
    "SetUsername\0signame\0\0sigcancel\0"
    "on_oksetname_clicked\0on_cancelsetname_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetUsername[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   38,    2, 0x08 /* Private */,
       5,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SetUsername::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetUsername *_t = static_cast<SetUsername *>(_o);
        switch (_id) {
        case 0: _t->signame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigcancel(); break;
        case 2: _t->on_oksetname_clicked(); break;
        case 3: _t->on_cancelsetname_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetUsername::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetUsername::signame)) {
                *result = 0;
            }
        }
        {
            typedef void (SetUsername::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetUsername::sigcancel)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SetUsername::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetUsername.data,
      qt_meta_data_SetUsername,  qt_static_metacall, 0, 0}
};


const QMetaObject *SetUsername::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetUsername::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetUsername.stringdata))
        return static_cast<void*>(const_cast< SetUsername*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetUsername::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SetUsername::signame(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetUsername::sigcancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
