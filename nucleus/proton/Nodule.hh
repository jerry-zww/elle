//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// author        julien quintard   [mon sep 12 05:46:11 2011]
//

#ifndef NUCLEUS_PROTON_NODULE_HH
#define NUCLEUS_PROTON_NODULE_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

namespace nucleus
{
  namespace proton
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// XXX
    ///
    class Nodule:
      public elle::Object
    {
    public:
      //
      // enumerations
      //
      enum Type
	{
	  TypeSeam,
	  TypeQuill
	};

      //
      // constructors & destructors
      //
      Nodule(const Type);

      //
      // attributes
      //
      Type		type;

      Nodule*		parent;
      Nodule*		left;
      Nodule*		right;
    };

  }
}

#endif
