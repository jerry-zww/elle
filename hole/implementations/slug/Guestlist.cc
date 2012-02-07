//
// ---------- header ----------------------------------------------------------
//
// project       hole
//
// license       infinit
//
// author        julien quintard   [mon nov  7 12:39:09 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <hole/implementations/slug/Guestlist.hh>

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
      /// XXX
      ///
      Guestlist::~Guestlist()
      {
        Guestlist::Scoutor      scoutor;

        // go through the entries.
        for (scoutor = this->container.begin();
             scoutor != this->container.end();
             scoutor++)
          {
            // delete the neighbour.
            delete scoutor->second;
          }

        // clear the container.
        this->container.clear();
      }

//
// ---------- methods ---------------------------------------------------------
//

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Add(elle::TCPSocket*         socket,
                                       Host*                    host)
      {
        std::pair<Guestlist::Iterator, elle::Boolean>   result;

        ;

        // insert the host in the container.
        result = this->container.insert(Guestlist::Value(socket, host));

        // check if the insertion was successful.
        if (result.second == false)
          escape("unable to insert the host in the container");

        return elle::StatusOk;
      }

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Exist(elle::TCPSocket*       socket) const
      {
        Guestlist::Scoutor      scoutor;

        ;

        // try to locate the socket.
        if (this->Locate(socket, scoutor) == elle::StatusTrue)
          return elle::StatusTrue;

        return elle::StatusFalse;
      }

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Retrieve(elle::TCPSocket*    socket,
                                            Host*&              host)
        const
      {
        Guestlist::Scoutor      scoutor;

        ;

        // try to locate the socket.
        if (this->Locate(socket, scoutor) == elle::StatusFalse)
          escape("unable to locate the given socket");

        // return the associated host.
        host = scoutor->second;

        return elle::StatusOk;
      }

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Remove(elle::TCPSocket*      socket)
      {
        Guestlist::Iterator     iterator;

        ;

        // try to locate the socket.
        if (this->Locate(socket, iterator) == elle::StatusFalse)
          escape("unable to locate the given socket");

        // erase the iterator.
        this->container.erase(iterator);

        return elle::StatusOk;
      }

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Locate(elle::TCPSocket*      socket,
                                          Scoutor&              scoutor) const
      {
        Guestlist::Scoutor      s;

        ;

        // try to locate the host.
        if ((s = this->container.find(socket)) != this->container.end())
          {
            // return the scoutor.
            scoutor = s;

            return elle::StatusTrue;
          }

        return elle::StatusFalse;
      }

      ///
      /// XXX
      ///
      elle::Status      Guestlist::Locate(elle::TCPSocket*      socket,
                                          Iterator&             iterator)
      {
        Guestlist::Iterator     i;

        ;

        // try to locate the host.
        if ((i = this->container.find(socket)) != this->container.end())
          {
            // return the iterator.
            iterator = i;

            return elle::StatusTrue;
          }

        return elle::StatusFalse;
      }

//
// ---------- dumpable --------------------------------------------------------
//

      ///
      /// this function dumps a routing table object.
      ///
      elle::Status      Guestlist::Dump(elle::Natural32         margin) const
      {
        elle::String            alignment(margin, ' ');
        Guestlist::Scoutor      scoutor;

        ;

        // display the name.
        std::cout << alignment << "[Guestlist]" << std::endl;

        // go through the entries.
        for (scoutor = this->container.begin();
             scoutor != this->container.end();
             scoutor++)
          {
            std::cout << alignment << elle::Dumpable::Shift
                      << "[Guest]" << std::endl;

            // dump the socket's address.
            std::cout << alignment << elle::Dumpable::Shift
                      << elle::Dumpable::Shift
                      << "[TCPSocket] " << scoutor->first << std::endl;

            // dump the host.
            if (scoutor->second->Dump(margin + 4) == elle::StatusError)
              escape("unable to dump the host");
          }

        return elle::StatusOk;
      }

    }
  }
}
