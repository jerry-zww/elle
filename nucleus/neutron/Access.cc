#include <nucleus/neutron/Access.hh>
#include <nucleus/neutron/Index.hh>
#include <nucleus/neutron/Size.hh>
#include <nucleus/neutron/Subject.hh>

#include <elle/Buffer.hh>
#include <elle/cryptography/Digest.hh>
#include <elle/idiom/Open.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- constants -------------------------------------------------------
//

    const Component Access::component = ComponentAccess;

//
// ---------- constructors & destructors --------------------------------------
//

    Access::Access():
      proton::ContentHashBlock()
    {
    }

    Access::Access(proton::Network const& network,
                   elle::cryptography::PublicKey const& creator_K):
      proton::ContentHashBlock(network, ComponentAccess, creator_K)
    {
    }

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method adds the given record to the ACL.
    ///
    elle::Status        Access::Add(Record*                     record)
    {
      // add the record in the range.
      if (this->_range.Add(record) == elle::Status::Error)
        escape("unable to add the record in the range");

      // set the block as dirty.
      this->state(proton::StateDirty);

      return elle::Status::Ok;
    }

    ///
    /// this method tests if the given subject exists.
    ///
    elle::Status        Access::Exist(const Subject&            subject) const
    {
      // test.
      if (this->_range.Exist(subject) == false)
        return elle::Status::False;

      return elle::Status::True;
    }

    ///
    /// this method returns the record corresponding to the given subject.
    ///
    elle::Status        Access::Lookup(const Subject&           subject,
                                       Record const*& record) const
    {
      // look in the range.
      if (this->_range.Lookup(subject, record) == elle::Status::Error)
        escape("unable to retrieve the record");

      return elle::Status::Ok;
    }

    elle::Status        Access::Lookup(const Subject&           subject,
                                       Record*& record) const
    {
      // look in the range.
      if (this->_range.Lookup(subject, record) == elle::Status::Error)
        escape("unable to retrieve the record");

      return elle::Status::Ok;
    }

    ///
    /// this method returns the index location of the given subject.
    ///
    elle::Status        Access::Lookup(const Subject&           subject,
                                       Index&                   index) const
    {
      Range<Record>::Scoutor    scoutor;

      // go through the range.
      for (scoutor = this->_range.container.begin(), index = 0;
           scoutor != this->_range.container.end();
           scoutor++, index++)
        {
          Record*       record = *scoutor;

          // if found, stop.
          if (record->subject() == subject)
            return elle::Status::Ok;
        }

      escape("unable to locate the given subject");
    }

    ///
    /// this method returns the access record located at the given index.
    ///
    elle::Status        Access::Lookup(const Index&             index,
                                       Record*&                 record) const
    {
      Range<Record>::Scoutor    scoutor;
      Index                     i;

      // set the record to null.
      record = nullptr;

      // go through the range.
      for (scoutor = this->_range.container.begin(), i = 0;
           scoutor != this->_range.container.end();
           scoutor++, i++)
        {
          // if found, stop.
          if (i == index)
            {
              // return the record.
              record = *scoutor;

              return elle::Status::Ok;
            }
        }

      escape("unable to locate the record at the given index");
    }

    elle::Status
    Access::Update(Subject const& subject,
                   Permissions permissions,
                   Token const& token)
    {
      Record* record;

      // retrieve the record.
      if (this->Lookup(subject, record) == elle::Status::Error)
        escape("unable to retrieve the subject's record");

      record->permissions(permissions);
      record->token(token);

      // set the block as dirty.
      this->state(proton::StateDirty);

      return elle::Status::Ok;
    }

    ///
    /// this method returns a range representing a subset of the access
    /// control list delimited by the given index and size.
    ///
    elle::Status        Access::Consult(const Index&            index,
                                        const Size&             size,
                                        Range<Record>&          range) const
    {
      Range<Record>::Scoutor    scoutor;
      Index                     i;

      // first detach the data from the range.
      if (range.Detach() == elle::Status::Error)
        escape("unable to detach the data from the range");

      // go through the records.
      for (scoutor = this->_range.container.begin(), i = 0;
           scoutor != this->_range.container.end();
           scoutor++, i++)
        {
          Record*       record = *scoutor;

          // if this record lies in the selected range [index, index + size[
          if ((i >= index) && (i < (index + size)))
            {
              // add the record to the range.
              if (range.Add(record) == elle::Status::Error)
                escape("unable to add the record to the given range");
            }
        }

      return elle::Status::Ok;
    }

    ///
    /// this method removes the given record.
    ///
    elle::Status        Access::Remove(const Subject&           subject)
    {
      // remove the record from the range.
      if (this->_range.Remove(subject) == elle::Status::Error)
        escape("unable to remove the record");

      // set the block as dirty.
      this->state(proton::StateDirty);

      return elle::Status::Ok;
    }

    ///
    /// this method returns the size of the access control list.
    ///
    elle::Status        Access::Capacity(Size&                  size) const
    {
      // look at the size of the range.
      if (this->_range.Capacity(size) == elle::Status::Error)
        escape("unable to retrieve the range size");

      return elle::Status::Ok;
    }

    ///
    /// this method computes a hash of the (subject, permissions) tuples
    /// composing the access object.
    ///
    /// this is required by the object class for access control purposes.
    ///
    elle::Status Access::Fingerprint(elle::cryptography::Digest& digest) const
    {
      elle::Buffer buffer;

      try
        {
          auto it = this->_range.container.begin(),
               end = this->_range.container.end();
          for (; it != end; ++it)
            buffer.writer() << (*it)->subject()
                            << (*it)->permissions();
        }
      catch (std::exception const& err)
        {
          escape("Couldn't serialize a record: %s", err.what());
        }

      if (elle::cryptography::OneWay::Hash(buffer, digest) == elle::Status::Error)
        escape("unable to hash the set of archived tuples");

      return elle::Status::Ok;
    }

//
// ---------- operators -------------------------------------------------------
//

    elle::Boolean
    Access::operator ==(Access const& other) const
    {
      // check the address as this may actually be the same object.
      if (this == &other)
        return true;

      return (this->_range == other._range);
    }

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this function dumps the access.
    ///
    elle::Status        Access::Dump(elle::Natural32            margin) const
    {
      elle::String      alignment(margin, ' ');

      std::cout << alignment << "[Access]" << std::endl;

      // dump the range.
      if (this->_range.Dump(margin + 2) == elle::Status::Error)
        escape("unable to dump the range");

      return elle::Status::Ok;
    }

//
// ---------- printable -------------------------------------------------------
//

    void
    Access::print(std::ostream& stream) const
    {
      stream << "access("
             << this->_range
             << ")";
    }

//
// ---------- iterable --------------------------------------------------------
//

    typename Range<Record>::Scoutor
    Access::begin() const
    {
      return (this->_range.begin());
    }

    typename Range<Record>::Scoutor
    Access::end() const
    {
      return (this->_range.end());
    }

  }
}
