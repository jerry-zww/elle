#ifndef NUCLEUS_PROTON_BLOCK_HH
# define NUCLEUS_PROTON_BLOCK_HH

# include <elle/concept/Fileable.hh>
# include <elle/serialize/SerializableMixin.hh>

# include <nucleus/proton/Address.hh>
# include <nucleus/proton/Network.hh>
# include <nucleus/proton/Family.hh>
# include <nucleus/proton/State.hh>

# include <nucleus/neutron/Component.hh>


namespace nucleus
{
  namespace proton
  {

    ///
    /// this class abstracts the notion of storable block of data.
    ///
    /// note that every block is identified by an address.
    ///
    /// the state attribute indicates whether the block has
    /// been modified. therefore, this indicator is never serialized.
    ///
    /// the reader will notice that only the Erase() method is provided
    /// from the Fileable interface. this comes from the fact that the
    /// other methods depend on the nature of the block: mutable or
    /// immutable.
    ///
    class Block
      : public elle::radix::Object
      , public elle::serialize::SerializableMixin<Block>
      , public elle::concept::AbstractFileable<> // XXX let only Erase method public
    {
    public:
      //
      // constants
      //
      static const elle::String         Extension;

      //
      // constructors & destructors
      //
      Block();
      Block(const Family,
            const neutron::Component);

      //
      // methods
      //
      virtual elle::Status      Bind(Address&) const;
      virtual elle::Status      Validate(const Address&) const;

      //
      // interfaces
      //

      // object
# include <elle/idiom/Open.hh>
      declare(Block);
# include <elle/idiom/Close.hh>

      // dumpable
      elle::Status              Dump(const elle::Natural32 = 0) const;

      //// archivable
      //elle::Status              Serialize(elle::Archive&) const;
      //elle::Status              Extract(elle::Archive&);

      // fileable
      // ELLE_CONCEPT_FILEABLE_ABSTRACT_METHODS();
      // XXX: remove the following with the previous line when
      //      elle::network::Procedure is out (it breaks the contract).
      // <XXX>
      virtual elle::Status Load(elle::io::Path const&) { throw false; };
      virtual elle::Status Store(elle::io::Path const&) const { throw false; };
      // </XXX>


      virtual elle::Status      Erase(const Network&,
                                      const Address&) const;

      //
      // attributes
      //
      Network                   network; // XXX seems to be always empty??? it should not! must be added to the constructor.
      Family                    family;
      neutron::Component        component;

      State                     state;
    };

  }
}


# include <nucleus/proton/Block.hxx>

#endif
