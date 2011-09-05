//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// file          /home/mycure/infinit/elle/network/Parcel.hh
//
// created       julien quintard   [tue mar 16 12:04:48 2010]
// updated       julien quintard   [sun sep  4 12:41:47 2011]
//

#ifndef ELLE_NETWORK_PARCEL_HH
#define ELLE_NETWORK_PARCEL_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/core/Natural.hh>

#include <elle/radix/Status.hh>
#include <elle/radix/Entity.hh>

#include <elle/network/Data.hh>

namespace elle
{
  using namespace core;
  using namespace radix;

  namespace network
  {

//
// ---------- forward declarations --------------------------------------------
//

    ///
    /// these classes need to be forward declared to avoid conflicts.
    ///
    class Session;
    class Header;

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class is just a wrapper for packets freshly received.
    ///
    /// whenver a message is being receveid, a parcel is created. then
    /// the session associated with this message is recorded before extracting
    /// the header. finally knowing the message's constituent types, the
    /// data can be fetched and extracted.
    ///
    class Parcel:
      public Entity
    {
    public:
      //
      // constructors & destructors
      //
      Parcel();
      Parcel(Session*,
	     Header*,
	     Data*);
      ~Parcel();

      //
      // interfaces
      //

      // dumpable
      Status		Dump(const Natural32 = 0) const;

      //
      // attributes
      //
      Session*		session;

      Header*		header;
      Data*		data;
    };

  }
}

//
// ---------- includes --------------------------------------------------------
//

#include <elle/network/Session.hh>
#include <elle/network/Header.hh>

#endif
