#ifndef ELLE_SERIALIZATION_JSON_SERIALIZERIN_HH
# define ELLE_SERIALIZATION_JSON_SERIALIZERIN_HH

# include <elle/json/json.hh>
# include <elle/serialization/SerializerIn.hh>

namespace elle
{
  namespace serialization
  {
    namespace json
    {
      class ELLE_API SerializerIn
        : public serialization::SerializerIn
      {
      /*------.
      | Types |
      `------*/
      public:
        typedef SerializerIn Self;
        typedef serialization::SerializerIn Super;

      /*-------------.
      | Construction |
      `-------------*/
      public:
        SerializerIn(std::istream& input, bool versioned = true);
        SerializerIn(std::istream& input,
                     Versions versions, bool versioned = true);
        SerializerIn(elle::json::Json input, bool versioned = true);
      private:
        void
        _load_json(std::istream& input);

      /*--------------.
      | Configuration |
      `--------------*/
      public:
        ELLE_ATTRIBUTE_RW(bool, partial);

      /*--------------.
      | Serialization |
      `--------------*/
      protected:
        virtual
        void
        _serialize(std::string const& name, int64_t& v) override;
        virtual
        void
        _serialize(std::string const& name, uint64_t& v) override;
        virtual
        void
        _serialize(std::string const& name, int32_t& v) override;
        virtual
        void
        _serialize(std::string const& name, uint32_t& v) override;
        virtual
        void
        _serialize(std::string const& name, int16_t& v) override;
        virtual
        void
        _serialize(std::string const& name, uint16_t& v) override;
        virtual
        void
        _serialize(std::string const& name, int8_t& v) override;
        virtual
        void
        _serialize(std::string const& name, uint8_t& v) override;
        virtual
        void
        _serialize(std::string const& name, double& v) override;
        virtual
        void
        _serialize(std::string const& name, bool& v) override;
        virtual
        void
        _serialize(std::string const& name, std::string& v) override;
        virtual
        void
        _serialize(std::string const& name, elle::Buffer& v) override;
        virtual
        void
        _serialize(std::string const& name,
                   boost::posix_time::ptime& v) override;
        virtual
        void
        _serialize_time_duration(std::int64_t& ticks,
                                 std::int64_t& num,
                                 std::int64_t& denom) override;
        virtual
        void
        _serialize_named_option(std::string const& name,
                                bool,
                                std::function<void ()> const& f) override;
        virtual
        void
        _serialize_option(std::string const& name,
                          bool,
                          std::function<void ()> const& f) override;
        virtual
        void
        _serialize_array(std::string const& name,
                         int size,
                         std::function<void ()> const& f) override;
        virtual
        void
        _deserialize_dict_key(
          std::function<void (std::string const&)> const& f) override;
        virtual
        bool
        _enter(std::string const& name) override;
        virtual
        void
        _leave(std::string const& name) override;

        ELLE_ATTRIBUTE(boost::any, json);
        ELLE_ATTRIBUTE(std::vector<boost::any*>, current);

      private:
        template <typename T, typename ... Alternatives>
        T&
        _check_type(std::string const& name);
        template <typename T>
        void
        _serialize_int(std::string const& name, T& v);
      };
    }
  }
}

#endif
