//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// file          /home/mycure/infinit/elle/utility/Parser.hh
//
// created       julien quintard   [wed apr 28 11:11:05 2010]
// updated       julien quintard   [mon jun 27 22:18:45 2011]
//

#ifndef ELLE_UTILITY_PARSER_HH
#define ELLE_UTILITY_PARSER_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/core/Natural.hh>
#include <elle/core/Character.hh>
#include <elle/core/String.hh>
#include <elle/core/Type.hh>

#include <elle/radix/Status.hh>
#include <elle/radix/Entity.hh>

#include <elle/io/Format.hh>
#include <elle/io/Uniquable.hh>
#include <elle/io/Unique.hh>

#include <elle/idiom/Close.hh>
# include <vector>
# include <unistd.h>
# include <getopt.h>
#include <elle/idiom/Open.hh>

namespace elle
{
  using namespace core;
  using namespace radix;

  namespace utility
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class wraps the command line parser.
    ///
    class Parser:
      public Entity
    {
    public:
      //
      // constants
      //
      static const Natural32		Alignment;

      //
      // enumeration
      //
      ///
      /// this enumeration types every basic element settings are composed of.
      ///
      enum Type
	{
	  TypeUnknown = 0,
	  TypeNull,
	  TypeBoolean,
	  TypeCharacter,
	  TypeReal,
	  TypeInteger8,
	  TypeInteger16,
	  TypeInteger32,
	  TypeInteger64,
	  TypeNatural8,
	  TypeNatural16,
	  TypeNatural32,
	  TypeNatural64,
	  TypeString
	};

      enum Kind
	{
	  KindNone,
	  KindOptional,
	  KindRequired
	};

      enum State
	{
	  StateDeactivated,
	  StateActivated
	};

      //
      // classes
      //
      class Option:
	public Entity
      {
      public:
	//
	// constructors & destructors
	//
	Option(const String&,
	       const Character&,
	       const String&,
	       const String&,
	       const Kind&);

	//
	// attributes
	//
	String		name;

	Character	character;
	String		string;
	String		description;
	Kind		kind;

	State		state;
	String*		value;

	//
	// interfaces
	//

	// dumpable
	Status		Dump(const Natural32 = 0) const;
      };

      //
      // types
      //
      typedef std::vector<Option*>		Container;
      typedef Container::iterator		Iterator;
      typedef Container::const_iterator		Scoutor;

      //
      // constructors & destructors
      //
      Parser(Natural32,
	     Character**);
      ~Parser();

      //
      // methods
      //
      Status		Description(const String&);

      Status		Register(const String&,
				 const Character&,
				 const String&,
				 const String&,
				 const Kind);

      Status		Locate(const String&,
			       Option*&);
      Status		Locate(const Character&,
			       Option*&);

      Status		Parse();

      Status		Test(const String&);
      Status		Argument(const String&);

      template <typename T>
      Status		Value(const String&,
			      T&);
      template <typename T>
      Status		Value(const String&,
			      T&,
			      const T&);

      //
      // behaviours
      //
      template <typename T, Boolean C>
      struct		Behaviour
      {
	static Status	Value(Parser&,
			      const String&,
			      T&);
	static Status	Value(Parser&,
			      const String&,
			      T&,
			      const T&);
      };

      template <typename T>
      struct		Behaviour<T, true>
      {
	template <const Format F>
	static Status	Value(Parser&,
			      const String&,
			      Uniquable<F>&);
	template <const Format F>
	static Status	Value(Parser&,
			      const String&,
			      Uniquable<F>&,
			      const Uniquable<F>&);
      };

      Void		Usage();

      //
      // interfaces
      //

      // dumpable
      Status		Dump(const Natural32 = 0) const;

      //
      // attributes
      //
      Natural32		argc;
      Character**	argv;

      String		description;

      Container		options;

      String		shorts;
      struct ::option*	longs;
    };

  }
}

//
// ---------- templates -------------------------------------------------------
//

#include <elle/utility/Parser.hxx>

#endif
