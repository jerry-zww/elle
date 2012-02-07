//
// ---------- header ----------------------------------------------------------
//
// project       hole
//
// license       infinit
//
// author        julien quintard   [wed aug 31 14:49:56 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <hole/implementations/slug/Implementation.hh>
#include <hole/implementations/slug/Slug.hh>

namespace hole
{
  namespace implementations
  {
    namespace slug
    {

//
// ---------- constructors & destructors --------------------------------------
//

      ///
      /// default constructor.
      ///
      Implementation::Implementation(const nucleus::Network&    network):
        Holeable(network)
      {
      }

//
// ---------- holeable --------------------------------------------------------
//

      ///
      /// this method tries to connect to the server. if impossible, a server
      /// is author .
      ///
      elle::Status      Implementation::Join()
      {
        ;

        // allocate the machine.
        Slug::Computer = new Machine;

        // launch it.
        if (Slug::Computer->Launch() == elle::StatusError)
          escape("unable to launch the computer");

        return elle::StatusOk;
      }

      ///
      /// this method cleans the peer.
      ///
      elle::Status      Implementation::Leave()
      {
        ;

        // delete the machine.
        delete Slug::Computer;

        return elle::StatusOk;
      }

      ///
      /// this method stores an immutable block.
      ///
      elle::Status      Implementation::Put(
                          const nucleus::Address&               address,
                          const nucleus::ImmutableBlock&         block)
      {
        ;

        // forward the request to the machine.
        if (Slug::Computer->Put(address, block) == elle::StatusError)
          escape("unable to put the block");

        return elle::StatusOk;
      }

      ///
      /// this method stores a mutable block.
      ///
      elle::Status      Implementation::Put(
                          const nucleus::Address&               address,
                          const nucleus::MutableBlock&          block)
      {
        ;

        // forward the request to the machine.
        if (Slug::Computer->Put(address, block) == elle::StatusError)
          escape("unable to put the block");

        return elle::StatusOk;
      }

      ///
      /// this method retrieves an immutable block.
      ///
      elle::Status      Implementation::Get(
                          const nucleus::Address&               address,
                          nucleus::ImmutableBlock&              block)
      {
        ;

        // forward the request to the machine.
        if (Slug::Computer->Get(address, block) == elle::StatusError)
          escape("unable to get the block");

        return elle::StatusOk;
      }

      ///
      /// this method retrieves a mutable block.
      ///
      elle::Status      Implementation::Get(
                          const nucleus::Address&               address,
                          const nucleus::Version&               version,
                          nucleus::MutableBlock&                block)
      {
        ;

        // forward the request to the machine.
        if (Slug::Computer->Get(address,
                                version,
                                block) == elle::StatusError)
          escape("unable to get the block");

        return elle::StatusOk;
      }

      ///
      /// this method removes a block.
      ///
      elle::Status      Implementation::Kill(
                          const nucleus::Address&               address)
      {
        ;

        // forward the request to the machine.
        if (Slug::Computer->Kill(address) == elle::StatusError)
          escape("unable to kill the block");

        return elle::StatusOk;
      }

//
// ---------- dumpable --------------------------------------------------------
//

      ///
      /// this method dumps the implementation.
      ///
      elle::Status      Implementation::Dump(const elle::Natural32 margin)
        const
      {
        elle::String    alignment(margin, ' ');

        ;

        std::cout << alignment << "[Implementation] Slug" << std::endl;

        // dump the parent.
        if (Holeable::Dump(margin + 2) == elle::StatusError)
          escape("unable to dump the holeabl");

        // dump the machine.
        if (Slug::Computer->Dump(margin + 2) == elle::StatusError)
          escape("unable to dump the machine");

        return elle::StatusOk;
      }

    }
  }
}
