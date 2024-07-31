/****************************************************************************
** Meta object code from reading C++ file 'customgraphicsview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../customgraphicsview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomGraphicsView_t {
    QByteArrayData data[19];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomGraphicsView_t qt_meta_stringdata_CustomGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CustomGraphicsView"
QT_MOC_LITERAL(1, 19, 13), // "UndoTriggered"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "RedoTriggered"
QT_MOC_LITERAL(4, 48, 14), // "PublishOldData"
QT_MOC_LITERAL(5, 63, 4), // "data"
QT_MOC_LITERAL(6, 68, 14), // "PublishNewData"
QT_MOC_LITERAL(7, 83, 15), // "PublishUndoData"
QT_MOC_LITERAL(8, 99, 15), // "PublishRedoData"
QT_MOC_LITERAL(9, 115, 18), // "updateLinePosition"
QT_MOC_LITERAL(10, 134, 12), // "onActionSave"
QT_MOC_LITERAL(11, 147, 14), // "onActionDelete"
QT_MOC_LITERAL(12, 162, 10), // "onSetValue"
QT_MOC_LITERAL(13, 173, 15), // "onAddCustomText"
QT_MOC_LITERAL(14, 189, 9), // "onCopyVal"
QT_MOC_LITERAL(15, 199, 10), // "onPasteVal"
QT_MOC_LITERAL(16, 210, 10), // "saveToFile"
QT_MOC_LITERAL(17, 221, 8), // "fileName"
QT_MOC_LITERAL(18, 230, 12) // "loadFromFile"

    },
    "CustomGraphicsView\0UndoTriggered\0\0"
    "RedoTriggered\0PublishOldData\0data\0"
    "PublishNewData\0PublishUndoData\0"
    "PublishRedoData\0updateLinePosition\0"
    "onActionSave\0onActionDelete\0onSetValue\0"
    "onAddCustomText\0onCopyVal\0onPasteVal\0"
    "saveToFile\0fileName\0loadFromFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomGraphicsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    1,   91,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       7,    1,   97,    2, 0x06 /* Public */,
       8,    1,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  103,    2, 0x08 /* Private */,
      10,    0,  104,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    1,  110,    2, 0x0a /* Public */,
      18,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void CustomGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UndoTriggered(); break;
        case 1: _t->RedoTriggered(); break;
        case 2: _t->PublishOldData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->PublishNewData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->PublishUndoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->PublishRedoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->updateLinePosition(); break;
        case 7: _t->onActionSave(); break;
        case 8: _t->onActionDelete(); break;
        case 9: _t->onSetValue(); break;
        case 10: _t->onAddCustomText(); break;
        case 11: _t->onCopyVal(); break;
        case 12: _t->onPasteVal(); break;
        case 13: _t->saveToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->loadFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomGraphicsView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::UndoTriggered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::RedoTriggered)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::PublishOldData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::PublishNewData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::PublishUndoData)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CustomGraphicsView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomGraphicsView::PublishRedoData)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_CustomGraphicsView.data,
    qt_meta_data_CustomGraphicsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int CustomGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CustomGraphicsView::UndoTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CustomGraphicsView::RedoTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CustomGraphicsView::PublishOldData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CustomGraphicsView::PublishNewData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CustomGraphicsView::PublishUndoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CustomGraphicsView::PublishRedoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
