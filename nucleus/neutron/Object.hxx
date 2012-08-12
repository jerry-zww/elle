#ifndef NUCLEUS_NEUTRON_OBJECT_HXX
# define NUCLEUS_NEUTRON_OBJECT_HXX

# include <cassert>
# include <stdexcept>

# include <elle/serialize/ArchiveSerializer.hxx>

ELLE_SERIALIZE_SIMPLE(nucleus::neutron::Object,
                      archive,
                      value,
                      version)
{
  assert(version == 0);

  archive & static_cast<nucleus::proton::ImprintBlock&>(value);

  archive & value._author;

  archive & value._meta.owner.permissions;
  archive & value._meta.owner.token;
  archive & value._meta.genre;
  archive & value._meta.stamp;
  archive & value._meta.attributes;
  archive & value._meta.access;
  archive & value._meta.version;
  archive & value._meta.signature;

  archive & value._data.contents;
  archive & value._data.size;
  archive & value._data.stamp;
  archive & value._data.version;
  archive & value._data.signature;
}

#endif
