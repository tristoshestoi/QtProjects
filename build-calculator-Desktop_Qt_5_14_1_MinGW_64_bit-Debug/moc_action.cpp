/****************************************************************************
** Meta object code from reading C++ file 'action.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QTCalculator/action.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'action.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_action_t {
    QByteArrayData data[18];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_action_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_action_t qt_meta_stringdata_action = {
    {
QT_MOC_LITERAL(0, 0, 6), // "action"
QT_MOC_LITERAL(1, 7, 9), // "setResult"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "result"
QT_MOC_LITERAL(4, 25, 12), // "SetOperator1"
QT_MOC_LITERAL(5, 38, 9), // "operator1"
QT_MOC_LITERAL(6, 48, 12), // "SetOperator2"
QT_MOC_LITERAL(7, 61, 9), // "operator2"
QT_MOC_LITERAL(8, 71, 8), // "initPLus"
QT_MOC_LITERAL(9, 80, 9), // "initMinus"
QT_MOC_LITERAL(10, 90, 8), // "initMult"
QT_MOC_LITERAL(11, 99, 7), // "initDiv"
QT_MOC_LITERAL(12, 107, 7), // "initPow"
QT_MOC_LITERAL(13, 115, 8), // "initRoot"
QT_MOC_LITERAL(14, 124, 6), // "initLn"
QT_MOC_LITERAL(15, 131, 7), // "initSin"
QT_MOC_LITERAL(16, 139, 7), // "initCos"
QT_MOC_LITERAL(17, 147, 7) // "initTan"

    },
    "action\0setResult\0\0result\0SetOperator1\0"
    "operator1\0SetOperator2\0operator2\0"
    "initPLus\0initMinus\0initMult\0initDiv\0"
    "initPow\0initRoot\0initLn\0initSin\0initCos\0"
    "initTan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_action[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   82,    2, 0x0a /* Public */,
       6,    1,   85,    2, 0x0a /* Public */,
       8,    0,   88,    2, 0x0a /* Public */,
       9,    0,   89,    2, 0x0a /* Public */,
      10,    0,   90,    2, 0x0a /* Public */,
      11,    0,   91,    2, 0x0a /* Public */,
      12,    0,   92,    2, 0x0a /* Public */,
      13,    0,   93,    2, 0x0a /* Public */,
      14,    0,   94,    2, 0x0a /* Public */,
      15,    0,   95,    2, 0x0a /* Public */,
      16,    0,   96,    2, 0x0a /* Public */,
      17,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void action::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<action *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SetOperator1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SetOperator2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->initPLus(); break;
        case 4: _t->initMinus(); break;
        case 5: _t->initMult(); break;
        case 6: _t->initDiv(); break;
        case 7: _t->initPow(); break;
        case 8: _t->initRoot(); break;
        case 9: _t->initLn(); break;
        case 10: _t->initSin(); break;
        case 11: _t->initCos(); break;
        case 12: _t->initTan(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (action::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&action::setResult)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject action::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_action.data,
    qt_meta_data_action,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *action::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *action::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_action.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int action::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void action::setResult(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
