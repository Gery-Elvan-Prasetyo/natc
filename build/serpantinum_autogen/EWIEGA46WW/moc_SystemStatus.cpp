/****************************************************************************
** Meta object code from reading C++ file 'SystemStatus.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SystemStatus.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemStatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
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
struct qt_meta_tag_ZN12SystemStatusE_t {};
} // unnamed namespace

template <> constexpr inline auto SystemStatus::qt_create_metaobjectdata<qt_meta_tag_ZN12SystemStatusE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SystemStatus",
        "changed",
        "",
        "operationFinished",
        "operation",
        "success",
        "message",
        "ssid",
        "passwordRequired",
        "refresh",
        "setWifiEnabled",
        "enabled",
        "toggleWifi",
        "connectWifi",
        "password",
        "scanWifi",
        "disconnectWifi",
        "wifiConnection",
        "wifiEnabled",
        "bluetoothEnabled",
        "wifiNetworks",
        "QVariantList",
        "bluetoothDevices",
        "actionMessage",
        "wifiBusy"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'operationFinished'
        QtMocHelpers::SignalData<void(const QString &, bool, const QString &, const QString &, bool)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 }, { QMetaType::Bool, 5 }, { QMetaType::QString, 6 }, { QMetaType::QString, 7 },
            { QMetaType::Bool, 8 },
        }}),
        // Method 'refresh'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setWifiEnabled'
        QtMocHelpers::MethodData<void(bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Method 'toggleWifi'
        QtMocHelpers::MethodData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'connectWifi'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 14 },
        }}),
        // Method 'connectWifi'
        QtMocHelpers::MethodData<void(const QString &)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'scanWifi'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'disconnectWifi'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'wifiConnection'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'wifiEnabled'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'bluetoothEnabled'
        QtMocHelpers::PropertyData<bool>(19, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'wifiNetworks'
        QtMocHelpers::PropertyData<QVariantList>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'bluetoothDevices'
        QtMocHelpers::PropertyData<QVariantList>(22, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'actionMessage'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'wifiBusy'
        QtMocHelpers::PropertyData<bool>(24, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SystemStatus, qt_meta_tag_ZN12SystemStatusE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SystemStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SystemStatusE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SystemStatusE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12SystemStatusE_t>.metaTypes,
    nullptr
} };

void SystemStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SystemStatus *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->operationFinished((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[5]))); break;
        case 2: _t->refresh(); break;
        case 3: _t->setWifiEnabled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->toggleWifi(); break;
        case 5: _t->connectWifi((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->connectWifi((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->scanWifi(); break;
        case 8: _t->disconnectWifi(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SystemStatus::*)()>(_a, &SystemStatus::changed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SystemStatus::*)(const QString & , bool , const QString & , const QString & , bool )>(_a, &SystemStatus::operationFinished, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->wifiConnection(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->wifiEnabled(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->bluetoothEnabled(); break;
        case 3: *reinterpret_cast<QVariantList*>(_v) = _t->wifiNetworks(); break;
        case 4: *reinterpret_cast<QVariantList*>(_v) = _t->bluetoothDevices(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->actionMessage(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->wifiBusy(); break;
        default: break;
        }
    }
}

const QMetaObject *SystemStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SystemStatusE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SystemStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SystemStatus::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SystemStatus::operationFinished(const QString & _t1, bool _t2, const QString & _t3, const QString & _t4, bool _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3, _t4, _t5);
}
QT_WARNING_POP
