/****************************************************************************
** Meta object code from reading C++ file 'Worker.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Worker.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN6WorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto Worker::qt_create_metaobjectdata<qt_meta_tag_ZN6WorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Worker",
        "statusUpdate",
        "",
        "text",
        "estimationUpdate",
        "error",
        "what",
        "finished",
        "progressBarUpdate",
        "value",
        "progressBarShow",
        "progressBarHide",
        "process",
        "stop"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'statusUpdate'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'estimationUpdate'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'error'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'finished'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'progressBarUpdate'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'progressBarShow'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'progressBarHide'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'process'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stop'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Worker, qt_meta_tag_ZN6WorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6WorkerE_t>.metaTypes,
    nullptr
} };

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Worker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->statusUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->estimationUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->finished(); break;
        case 4: _t->progressBarUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->progressBarShow(); break;
        case 6: _t->progressBarHide(); break;
        case 7: _t->process(); break;
        case 8: _t->stop(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Worker::*)(const QString & )>(_a, &Worker::statusUpdate, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)(const QString & )>(_a, &Worker::estimationUpdate, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)(const QString & )>(_a, &Worker::error, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)()>(_a, &Worker::finished, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)(int )>(_a, &Worker::progressBarUpdate, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)()>(_a, &Worker::progressBarShow, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Worker::*)()>(_a, &Worker::progressBarHide, 6))
            return;
    }
}

const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}

// SIGNAL 0
void Worker::statusUpdate(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Worker::estimationUpdate(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Worker::error(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Worker::progressBarUpdate(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Worker::progressBarShow()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Worker::progressBarHide()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
