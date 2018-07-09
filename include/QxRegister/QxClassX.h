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

#ifndef _QX_CLASS_X_H_
#define _QX_CLASS_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include "../../include/QxCommon/QxBool.h"

#include "../../include/QxRegister/IxClass.h"

#include "../../include/QxSingleton/QxSingleton.h"

#include "../../include/QxCollection/QxCollection.h"

#include "../../include/QxTraits/is_smart_ptr.h"

namespace qx {

class QX_DLL_EXPORT QxClassX : public QxSingleton<QxClassX>
{

   friend class QxSingleton<QxClassX>;
   friend class IxClass;

public:

   typedef IxFunction::type_any_params type_any_params;

protected:

   QxCollection<QString, IxClass *> m_lstClass;

private:

   QxClassX() : QxSingleton<QxClassX>("qx::QxClassX") { ; }
   virtual ~QxClassX() { ; }

   IxClass * get(const QString & sKey) const;
   bool exist(const QString & sKey) const;
   bool insert(const QString & sKey, IxClass * pClass);
   bool remove(const QString & sKey);
   void clear();

public:

   static boost::any create(const QString & sKey);
   static IxClass * getClass(const QString & sKey);
   static IxDataMemberX * getDataMemberX(const QString & sKey);
   static IxFunctionX * getFctMemberX(const QString & sKey);
   static IxDataMember * getDataMember(const QString & sClassKey, const QString & sDataKey, bool bRecursive = true);
   static IxFunction * getFctMember(const QString & sClassKey, const QString & sFctKey, bool bRecursive = true);

   template <class U>
   static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const QString & params = QString(), boost::any * ret = NULL)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<U>::value, QxClassX::invoke_ptr<U>, QxClassX::invoke_default<U> >::type type_invoke_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<U>::value, QxClassX::invoke_ptr<U>, type_invoke_1 >::type type_invoke_2;
      return type_invoke_2::invoke(sClassKey, sFctKey, pOwner, params, ret);
   }

   template <class U>
   static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const type_any_params & params, boost::any * ret = NULL)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<U>::value, QxClassX::invoke_ptr<U>, QxClassX::invoke_default<U> >::type type_invoke_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<U>::value, QxClassX::invoke_ptr<U>, type_invoke_1 >::type type_invoke_2;
      return type_invoke_2::invoke(sClassKey, sFctKey, pOwner, params, ret);
   }

private:

   template <class U>
   struct invoke_ptr
   {
      static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const QString & params = QString(), boost::any * ret = NULL)
      { return QxClassX::invokeVoidPtr(sClassKey, sFctKey, static_cast<void *>(& (* pOwner)), params, ret); }
      static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const type_any_params & params, boost::any * ret = NULL)
      { return QxClassX::invokeVoidPtr(sClassKey, sFctKey, static_cast<void *>(& (* pOwner)), params, ret); }
   };

   template <class U>
   struct invoke_default
   {
      static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const QString & params = QString(), boost::any * ret = NULL)
      { return QxClassX::invokeVoidPtr(sClassKey, sFctKey, static_cast<void *>(& pOwner), params, ret); }
      static inline qx_bool invoke(const QString & sClassKey, const QString & sFctKey, U & pOwner, const type_any_params & params, boost::any * ret = NULL)
      { return QxClassX::invokeVoidPtr(sClassKey, sFctKey, static_cast<void *>(& pOwner), params, ret); }
   };

   static qx_bool invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const QString & params = QString(), boost::any * ret = NULL);
   static qx_bool invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const type_any_params & params, boost::any * ret = NULL);

};

} // namespace qx

#endif // _QX_CLASS_X_H_