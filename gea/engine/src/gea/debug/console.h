#ifndef __GEA_CONSOLE_H__
#define __GEA_CONSOLE_H__

#ifndef DEBUG
    #error console.h is only available in debug mode!
#endif

#include <string>
#include <map>

#include <gea/engine/core/idstring.h>

namespace gea {
namespace debug {

class csl_args {
public:
    csl_args() : m_index(0) {}

    csl_arg& front() const;
    csl_args& tail() const;
private:
    // args
    mutable size_t m_index;
};

class csl_arg {
public:

    //
    bool is_number() const;
    bool is_flag() const;

    idstring id() const;

    // named entity
    bool has_name() const;
    inline const std::string& get_name() const;

private:
    std::string m_name;
    std::string m_value;
};

class ConsoleArgs {
public:

private:
};


class command_handler {
public:
    virtual void console_func(const csl_args& args) = 0;
};

class branch_command_handler : public command_handler {
    typedef std::map<idstring, command_handler*> Handlers;
public:
    virtual void console_func(const csl_args& args) {
        csl_arg top = args.front();
        
        Handlers::const_iterator it = m_handlers.find( top.id() ), end = m_handlers.end();
        if ( it != end) {
            it->second->console_func( args.tail() );
        }
    }
private:
    Handlers m_handlers;
};

class console_manager {
public:
    static console_manager& get();
    void register_cmd(const char* cmd, command_handler* handler);
private:
};

} // namespace debug //
} // namespace gea //

#include "console.inl"

#endif // __GEA_CONSOLE_H__ //
