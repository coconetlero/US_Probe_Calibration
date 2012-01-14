/****************************************************************************
** Meta object code from reading C++ file 'ProbeCalibrationWidget.h'
**
** Created: Fri Jan 13 20:15:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProbeCalibrationWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProbeCalibrationWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProbeCalibrationWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      31,   23,   23,   23, 0x08,
      48,   23,   23,   23, 0x08,
      60,   23,   23,   23, 0x08,
      80,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProbeCalibrationWidget[] = {
    "ProbeCalibrationWidget\0\0crop()\0"
    "getCoordinates()\0calibrate()\0"
    "loadRotationsFile()\0loadTranslationsFile()\0"
};

const QMetaObject ProbeCalibrationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProbeCalibrationWidget,
      qt_meta_data_ProbeCalibrationWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProbeCalibrationWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProbeCalibrationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProbeCalibrationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProbeCalibrationWidget))
        return static_cast<void*>(const_cast< ProbeCalibrationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProbeCalibrationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: crop(); break;
        case 1: getCoordinates(); break;
        case 2: calibrate(); break;
        case 3: loadRotationsFile(); break;
        case 4: loadTranslationsFile(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
