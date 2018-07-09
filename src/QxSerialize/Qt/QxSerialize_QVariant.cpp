/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../../include/QxPrecompiled.h"

#include "../../../include/QxSerialize/Qt/QxSerialize_QVariant.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QVariant & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iType = static_cast<int>(t.type());
   ar << boost::serialization::make_nvp("type", iType);

   QString sInvalid; bool b(false); int i(0); uint ui(0); long l(0); unsigned long ul(0);
   double d(0.0); QString s; QDate qdate; QDateTime qdatetime; QTime qtime; QByteArray qbytearray;
   QColor qcolor; QFont qfont; QImage qimage; QPixmap qpixmap; QPoint qpoint; QRect qrect; QSize qsize;
   QBrush qbrush; QRegExp qregexp; QRegion qregion; QUrl qurl;
   QString sDefault("unknown variant serialize type");
   const char * sTag = "value";

   switch (iType)
   {
      case QVariant::Bool:          b = t.toBool();                                    ar << boost::serialization::make_nvp(sTag, b); break;
      case QVariant::Int:           i = t.toInt();                                     ar << boost::serialization::make_nvp(sTag, i); break;
      case QVariant::UInt:          ui = t.toUInt();                                   ar << boost::serialization::make_nvp(sTag, ui); break;
      case QVariant::LongLong:      l = static_cast<long>(t.toLongLong());             ar << boost::serialization::make_nvp(sTag, l); break;
      case QVariant::ULongLong:     ul = static_cast<unsigned long>(t.toULongLong());  ar << boost::serialization::make_nvp(sTag, ul); break;
      case QVariant::Double:        d = t.toDouble();                                  ar << boost::serialization::make_nvp(sTag, d); break;
      case QVariant::String:        s = t.toString();                                  ar << boost::serialization::make_nvp(sTag, s); break;
      case QVariant::Date:          qdate = t.toDate();                                ar << boost::serialization::make_nvp(sTag, qdate); break;
      case QVariant::DateTime:      qdatetime = t.toDateTime();                        ar << boost::serialization::make_nvp(sTag, qdatetime); break;
      case QVariant::Time:          qtime = t.toTime();                                ar << boost::serialization::make_nvp(sTag, qtime); break;
      case QVariant::ByteArray:     qbytearray = t.toByteArray();                      ar << boost::serialization::make_nvp(sTag, qbytearray); break;
      case QVariant::Brush:         qbrush = t.value<QBrush>();                        ar << boost::serialization::make_nvp(sTag, qbrush); break;
      case QVariant::Color:         qcolor = t.value<QColor>();                        ar << boost::serialization::make_nvp(sTag, qcolor); break;
      case QVariant::Font:          qfont = t.value<QFont>();                          ar << boost::serialization::make_nvp(sTag, qfont); break;
      case QVariant::Image:         qimage = t.value<QImage>();                        ar << boost::serialization::make_nvp(sTag, qimage); break;
      case QVariant::Pixmap:        qpixmap = t.value<QPixmap>();                      ar << boost::serialization::make_nvp(sTag, qpixmap); break;
      case QVariant::Point:         qpoint = t.toPoint();                              ar << boost::serialization::make_nvp(sTag, qpoint); break;
      case QVariant::Rect:          qrect = t.toRect();                                ar << boost::serialization::make_nvp(sTag, qrect); break;
      case QVariant::Size:          qsize = t.toSize();                                ar << boost::serialization::make_nvp(sTag, qsize); break;
      case QVariant::RegExp:        qregexp = t.toRegExp();                            ar << boost::serialization::make_nvp(sTag, qregexp); break;
      case QVariant::Region:        qregion = t.value<QRegion>();                      ar << boost::serialization::make_nvp(sTag, qregion); break;
      case QVariant::Url:           qurl = t.toUrl();                                  ar << boost::serialization::make_nvp(sTag, qurl); break;

      case QVariant::Invalid:       ar << boost::serialization::make_nvp(sTag, sInvalid); break;
      default:                      ar << boost::serialization::make_nvp(sTag, sDefault); break;
   }
}

template <class Archive>
inline void qx_load(Archive & ar, QVariant & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iType = 0;
   ar >> boost::serialization::make_nvp("type", iType);

   QString sDefault; QString sInvalid; bool b(false); int i(0); uint ui(0); long l(0); unsigned long ul(0);
   double d(0.0); QString s; QDate qdate; QDateTime qdatetime; QTime qtime; QByteArray qbytearray;
   QColor qcolor; QFont qfont; QImage qimage; QPixmap qpixmap; QPoint qpoint; QRect qrect; QSize qsize;
   QBrush qbrush; QRegExp qregexp; QRegion qregion; QUrl qurl;
   const char * sTag = "value";

   switch (iType)
   {
      case QVariant::Bool:          ar >> boost::serialization::make_nvp(sTag, b);           t = QVariant(b); break;
      case QVariant::Int:           ar >> boost::serialization::make_nvp(sTag, i);           t = QVariant(i); break;
      case QVariant::UInt:          ar >> boost::serialization::make_nvp(sTag, ui);          t = QVariant(ui); break;
      case QVariant::LongLong:      ar >> boost::serialization::make_nvp(sTag, l);           t = QVariant(static_cast<qlonglong>(l)); break;
      case QVariant::ULongLong:     ar >> boost::serialization::make_nvp(sTag, ul);          t = QVariant(static_cast<qulonglong>(ul)); break;
      case QVariant::Double:        ar >> boost::serialization::make_nvp(sTag, d);           t = QVariant(d); break;
      case QVariant::String:        ar >> boost::serialization::make_nvp(sTag, s);           t = QVariant(s); break;
      case QVariant::Date:          ar >> boost::serialization::make_nvp(sTag, qdate);       t = QVariant(qdate); break;
      case QVariant::DateTime:      ar >> boost::serialization::make_nvp(sTag, qdatetime);   t = QVariant(qdatetime); break;
      case QVariant::Time:          ar >> boost::serialization::make_nvp(sTag, qtime);       t = QVariant(qtime); break;
      case QVariant::ByteArray:     ar >> boost::serialization::make_nvp(sTag, qbytearray);  t = QVariant(qbytearray); break;
      case QVariant::Brush:         ar >> boost::serialization::make_nvp(sTag, qbrush);      t = qbrush; break;
      case QVariant::Color:         ar >> boost::serialization::make_nvp(sTag, qcolor);      t = qcolor; break;
      case QVariant::Font:          ar >> boost::serialization::make_nvp(sTag, qfont);       t = qfont; break;
      case QVariant::Image:         ar >> boost::serialization::make_nvp(sTag, qimage);      t = qimage; break;
      case QVariant::Pixmap:        ar >> boost::serialization::make_nvp(sTag, qpixmap);     t = qpixmap; break;
      case QVariant::Point:         ar >> boost::serialization::make_nvp(sTag, qpoint);      t = QVariant(qpoint); break;
      case QVariant::Rect:          ar >> boost::serialization::make_nvp(sTag, qrect);       t = QVariant(qrect); break;
      case QVariant::Size:          ar >> boost::serialization::make_nvp(sTag, qsize);       t = QVariant(qsize); break;
      case QVariant::RegExp:        ar >> boost::serialization::make_nvp(sTag, qregexp);     t = QVariant(qregexp); break;
      case QVariant::Region:        ar >> boost::serialization::make_nvp(sTag, qregion);     t = qregion; break;
      case QVariant::Url:           ar >> boost::serialization::make_nvp(sTag, qurl);        t = QVariant(qurl); break;

      case QVariant::Invalid:       ar >> boost::serialization::make_nvp(sTag, sInvalid);    t = QVariant(); break;
      default:                      ar >> boost::serialization::make_nvp(sTag, sDefault);    t = QVariant(); break;
   }
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QVariant)