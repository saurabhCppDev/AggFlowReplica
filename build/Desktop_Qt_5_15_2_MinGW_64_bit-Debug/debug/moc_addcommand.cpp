/****************************************************************************
** Meta object code from reading C++ file 'addcommand.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../addcommand.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addcommand.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddCommand_t {
    QByteArrayData data[7];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddCommand_t qt_meta_stringdata_AddCommand = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AddCommand"
QT_MOC_LITERAL(1, 11, 19), // "NotifyUndoCompleted"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "NotifyRedoCompleted"
QT_MOC_LITERAL(4, 52, 15), // "PublishUndoData"
QT_MOC_LITERAL(5, 68, 4), // "data"
QT_MOC_LITERAL(6, 73, 15) // "PublishRedoData"

    },
    "AddCommand\0NotifyUndoCompleted\0\0"
    "NotifyRedoCompleted\0PublishUndoData\0"
    "data\0PublishRedoData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void AddCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddCommand *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotifyUndoCompleted(); break;
        case 1: _t->NotifyRedoCompleted(); break;
        case 2: _t->PublishUndoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->PublishRedoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCommand::NotifyUndoCompleted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AddCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCommand::NotifyRedoCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AddCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCommand::PublishUndoData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AddCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCommand::PublishRedoData)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AddCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AddCommand.data,
    qt_meta_data_AddCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AddCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddCommand.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QUndoCommand"))
        return static_cast< QUndoCommand*>(this);
    return QObject::qt_metacast(_clname);
}

int AddCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void AddCommand::NotifyUndoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AddCommand::NotifyRedoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AddCommand::PublishUndoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AddCommand::PublishRedoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_RemoveCommand_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RemoveCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RemoveCommand_t qt_meta_stringdata_RemoveCommand = {
    {
QT_MOC_LITERAL(0, 0, 13), // "RemoveCommand"
QT_MOC_LITERAL(1, 14, 19), // "NotifyUndoCompleted"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 19), // "NotifyRedoCompleted"
QT_MOC_LITERAL(4, 55, 15), // "PublishUndoData"
QT_MOC_LITERAL(5, 71, 4), // "data"
QT_MOC_LITERAL(6, 76, 15) // "PublishRedoData"

    },
    "RemoveCommand\0NotifyUndoCompleted\0\0"
    "NotifyRedoCompleted\0PublishUndoData\0"
    "data\0PublishRedoData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RemoveCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void RemoveCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RemoveCommand *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotifyUndoCompleted(); break;
        case 1: _t->NotifyRedoCompleted(); break;
        case 2: _t->PublishUndoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->PublishRedoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RemoveCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RemoveCommand::NotifyUndoCompleted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RemoveCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RemoveCommand::NotifyRedoCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RemoveCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RemoveCommand::PublishUndoData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RemoveCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RemoveCommand::PublishRedoData)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RemoveCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RemoveCommand.data,
    qt_meta_data_RemoveCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RemoveCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RemoveCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RemoveCommand.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QUndoCommand"))
        return static_cast< QUndoCommand*>(this);
    return QObject::qt_metacast(_clname);
}

int RemoveCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void RemoveCommand::NotifyUndoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RemoveCommand::NotifyRedoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RemoveCommand::PublishUndoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RemoveCommand::PublishRedoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_MoveCommand_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MoveCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MoveCommand_t qt_meta_stringdata_MoveCommand = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MoveCommand"
QT_MOC_LITERAL(1, 12, 19), // "NotifyUndoCompleted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "NotifyRedoCompleted"
QT_MOC_LITERAL(4, 53, 15), // "PublishUndoData"
QT_MOC_LITERAL(5, 69, 4), // "data"
QT_MOC_LITERAL(6, 74, 15) // "PublishRedoData"

    },
    "MoveCommand\0NotifyUndoCompleted\0\0"
    "NotifyRedoCompleted\0PublishUndoData\0"
    "data\0PublishRedoData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MoveCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void MoveCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MoveCommand *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotifyUndoCompleted(); break;
        case 1: _t->NotifyRedoCompleted(); break;
        case 2: _t->PublishUndoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->PublishRedoData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MoveCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MoveCommand::NotifyUndoCompleted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MoveCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MoveCommand::NotifyRedoCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MoveCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MoveCommand::PublishUndoData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MoveCommand::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MoveCommand::PublishRedoData)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MoveCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MoveCommand.data,
    qt_meta_data_MoveCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MoveCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MoveCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MoveCommand.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QUndoCommand"))
        return static_cast< QUndoCommand*>(this);
    return QObject::qt_metacast(_clname);
}

int MoveCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MoveCommand::NotifyUndoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MoveCommand::NotifyRedoCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MoveCommand::PublishUndoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MoveCommand::PublishRedoData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
