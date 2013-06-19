/****************************************************************************
** Meta object code from reading C++ file 'spacewars.h'
**
** Created: Wed Nov 28 14:11:47 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "spacewars.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spacewars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpaceWars[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   11,   10,   10, 0x0a,
      45,   11,   10,   10, 0x0a,
      69,   10,   10,   10, 0x0a,
      82,   10,   10,   10, 0x0a,
      92,   11,   10,   10, 0x0a,
     115,   11,   10,   10, 0x0a,
     141,   11,   10,   10, 0x0a,
     171,   10,   10,   10, 0x0a,
     180,   10,   10,   10, 0x0a,
     197,   10,   10,   10, 0x0a,
     217,   10,   10,   10, 0x0a,
     237,   10,   10,   10, 0x0a,
     260,   10,   10,   10, 0x0a,
     278,   10,   10,   10, 0x0a,
     304,   10,   10,   10, 0x0a,
     321,   10,   10,   10, 0x0a,
     346,   10,   10,   10, 0x0a,
     368,   10,   10,   10, 0x0a,
     393,   10,   10,   10, 0x0a,
     423,   10,   10,   10, 0x0a,
     448,   10,   10,   10, 0x0a,
     469,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpaceWars[] = {
    "SpaceWars\0\0modelIndex\0logInUser(QModelIndex)\0"
    "deleteUser(QModelIndex)\0tryAddUser()\0"
    "refocus()\0addFriend(QModelIndex)\0"
    "deleteFriend(QModelIndex)\0"
    "findShortestPath(QModelIndex)\0logOff()\0"
    "goBack2StartUp()\0goBack2UserScreen()\0"
    "addUserButtonSlot()\0deleteUserButtonSlot()\0"
    "logOnButtonSlot()\0listAllScoresButtonSlot()\0"
    "quitButtonSlot()\0listAllUsersButtonSlot()\0"
    "addFriendButtonSlot()\0deleteFriendButtonSlot()\0"
    "listFriendsScoresButtonSlot()\0"
    "shortestPathButtonSlot()\0playGameButtonSlot()\0"
    "restartGameButtonSlot()\0"
};

void SpaceWars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SpaceWars *_t = static_cast<SpaceWars *>(_o);
        switch (_id) {
        case 0: _t->logInUser((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->deleteUser((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->tryAddUser(); break;
        case 3: _t->refocus(); break;
        case 4: _t->addFriend((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->deleteFriend((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 6: _t->findShortestPath((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: _t->logOff(); break;
        case 8: _t->goBack2StartUp(); break;
        case 9: _t->goBack2UserScreen(); break;
        case 10: _t->addUserButtonSlot(); break;
        case 11: _t->deleteUserButtonSlot(); break;
        case 12: _t->logOnButtonSlot(); break;
        case 13: _t->listAllScoresButtonSlot(); break;
        case 14: _t->quitButtonSlot(); break;
        case 15: _t->listAllUsersButtonSlot(); break;
        case 16: _t->addFriendButtonSlot(); break;
        case 17: _t->deleteFriendButtonSlot(); break;
        case 18: _t->listFriendsScoresButtonSlot(); break;
        case 19: _t->shortestPathButtonSlot(); break;
        case 20: _t->playGameButtonSlot(); break;
        case 21: _t->restartGameButtonSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SpaceWars::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SpaceWars::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SpaceWars,
      qt_meta_data_SpaceWars, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpaceWars::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpaceWars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpaceWars::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpaceWars))
        return static_cast<void*>(const_cast< SpaceWars*>(this));
    return QWidget::qt_metacast(_clname);
}

int SpaceWars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
