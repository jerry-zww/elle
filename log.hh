#ifndef  ELLE_LOG_HH
# define ELLE_LOG_HH

# include <elle/log/Logger.hh>
# include <elle/assert.hh>
# include <elle/printf.hh>

namespace elle
{
  namespace log
  {
# define ELLE_LOG_COMPONENT(component)                                  \
    static ::elle::log::detail::TraceComponent                          \
    __trace_component__(component)                                      \

# define ETC_LOG_FUNCTION __PRETTY_FUNCTION__


# define ELLE_LOG_LEVEL_SCOPE(Lvl, ...)                                 \
    auto BOOST_PP_CAT(__trace_ctx_, __LINE__) =                         \
      ::elle::log::detail::TraceContext                                 \
      (elle::log::Logger::Level::Lvl,                                   \
       __trace_component__,                                             \
       __FILE__, __LINE__, ETC_LOG_FUNCTION,                            \
       elle::sprintf(__VA_ARGS__))                                      \

# define ELLE_LOG_LEVEL(Level, ...)                                     \
    if (ELLE_LOG_LEVEL_SCOPE(Level, __VA_ARGS__))                       \
      {                                                                 \
        elle::unreachable();                                            \
      }                                                                 \
    else                                                                \

# define ELLE_LOG_SCOPE(...)  ELLE_LOG_LEVEL_SCOPE(log, __VA_ARGS__)
# define ELLE_TRACE_SCOPE(...) ELLE_LOG_LEVEL_SCOPE(trace, __VA_ARGS__)
# define ELLE_DEBUG_SCOPE(...) ELLE_LOG_LEVEL_SCOPE(debug, __VA_ARGS__)
# define ELLE_DUMP_SCOPE(...)  ELLE_LOG_LEVEL_SCOPE(dump, __VA_ARGS__)

# define ELLE_WARN(...)  ELLE_LOG(__VA_ARGS__)
# define ELLE_ERR(...)  ELLE_LOG(__VA_ARGS__)
# define ELLE_LOG(...)  ELLE_LOG_LEVEL(log, __VA_ARGS__)
# define ELLE_TRACE(...) ELLE_LOG_LEVEL(trace, __VA_ARGS__)
# define ELLE_DEBUG(...) ELLE_LOG_LEVEL(debug, __VA_ARGS__)
# define ELLE_DUMP(...)  ELLE_LOG_LEVEL(dump, __VA_ARGS__)

    namespace detail
    {

      struct TraceComponent
      {
        std::string const name;
        TraceComponent(std::string const& name);
      };

      struct TraceContext
      {
      public:
        TraceContext(elle::log::Logger::Level level,
                     TraceComponent const& component,
                     char const* file,
                     unsigned int line,
                     char const* function,
                     std::string const& message);
        ~TraceContext();
        operator bool() const;
      private:
        TraceComponent const& _component;
        void _send(elle::log::Logger::Level level,
                   char const* file,
                   unsigned int line,
                   char const* function,
                   const std::string& msg);
        void _send(elle::log::Logger::Level level,
                   std::string const& msg);
        void _indent();
        void _unindent();
      };

    }

  }
}

# include <elle/log.hxx>

#endif
