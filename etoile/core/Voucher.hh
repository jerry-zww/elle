//
// ---------- header ----------------------------------------------------------
//
// project       infinit
//
// license       infinit (c)
//
// file          /home/mycure/infinit/etoile/core/Voucher.hh
//
// created       julien quintard   [mon feb 16 21:13:00 2009]
// updated       julien quintard   [thu jul 30 20:51:42 2009]
//

#ifndef ETOILE_COMPONENTS_VOUCHER_HH
#define ETOILE_COMPONENTS_VOUCHER_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <ostream>

namespace etoile
{
  namespace core
  {

//
// ---------- class -----------------------------------------------------------
//

    ///
    /// a voucher represents a certificate, generated by a delegate,
    /// proving that a consumer had the right the perform an operation
    /// at the time it has been carried out.
    ///
    class Voucher:
      public Dumpable, public Archivable
    {
    public:
      //
      // constructors & destructors
      //
      Voucher();
      ~Voucher();

      //
      // methods
      //
      // XXX Status		Generate(PublicKey&, ...);

      //
      // interfaces
      //

      // dumpable
      Status		Dump(const Natural32 = 0);

      // archivable
      Status		Serialize(Archive&) const;
      Status		Extract(Archive&);

      //
      // attributes
      //
      PublicKey		consumer;
      Signature		signature;
    };

  }
}

#endif
