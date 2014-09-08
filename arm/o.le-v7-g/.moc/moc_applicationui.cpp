/****************************************************************************
** Meta object code from reading C++ file 'applicationui.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/applicationui.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'applicationui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplicationUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      76,   41,   14,   14, 0x08,
     224,  184,   14,   14, 0x08,
     366,   41,   14,   14, 0x08,

 // methods: signature, parameters, type, tag, flags
     481,  471,   14,   14, 0x02,
     534,  517,  508,   14, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ApplicationUI[] = {
    "ApplicationUI\0\0onSystemLanguageChanged()\0"
    "accountId,conversationId,messageId\0"
    "onMessageAdded(bb::pim::account::AccountKey,bb::pim::message::Conversa"
    "tionKey,bb::pim::message::MessageKey)\0"
    "accountId,conversationId,messageId,data\0"
    "onMessageUpdated(bb::pim::account::AccountKey,bb::pim::message::Conver"
    "sationKey,bb::pim::message::MessageKey,bb::pim::message::MessageUpdate"
    ")\0"
    "analyzeThis(bb::pim::account::AccountKey,bb::pim::message::Conversatio"
    "nKey,bb::pim::message::MessageKey)\0"
    "key,value\0setValue(QString,QVariant)\0"
    "QVariant\0key,defaultValue\0"
    "value(QString,QVariant)\0"
};

void ApplicationUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplicationUI *_t = static_cast<ApplicationUI *>(_o);
        switch (_id) {
        case 0: _t->onSystemLanguageChanged(); break;
        case 1: _t->onMessageAdded((*reinterpret_cast< bb::pim::account::AccountKey(*)>(_a[1])),(*reinterpret_cast< bb::pim::message::ConversationKey(*)>(_a[2])),(*reinterpret_cast< bb::pim::message::MessageKey(*)>(_a[3]))); break;
        case 2: _t->onMessageUpdated((*reinterpret_cast< bb::pim::account::AccountKey(*)>(_a[1])),(*reinterpret_cast< bb::pim::message::ConversationKey(*)>(_a[2])),(*reinterpret_cast< bb::pim::message::MessageKey(*)>(_a[3])),(*reinterpret_cast< bb::pim::message::MessageUpdate(*)>(_a[4]))); break;
        case 3: _t->analyzeThis((*reinterpret_cast< bb::pim::account::AccountKey(*)>(_a[1])),(*reinterpret_cast< bb::pim::message::ConversationKey(*)>(_a[2])),(*reinterpret_cast< bb::pim::message::MessageKey(*)>(_a[3]))); break;
        case 4: _t->setValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 5: { QVariant _r = _t->value((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplicationUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplicationUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplicationUI,
      qt_meta_data_ApplicationUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicationUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicationUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicationUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationUI))
        return static_cast<void*>(const_cast< ApplicationUI*>(this));
    return QObject::qt_metacast(_clname);
}

int ApplicationUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
