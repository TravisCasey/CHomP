// Julia wrapper for Ring.h

#include <jlcxx/jlcxx.hpp>

#include "chomp/Ring.h"

namespace chomp {

JLCXX_MODULE define_Ring_module(jlcxx::Module& mod)
{
    using namespace jlcxx;

    mod.add_type<Long>("Long")
        .constructor<int64_t>()
        .method("invertible", &Long::invertible)
        .method("balanced_value", &Long::balanced_value);
    mod.set_override_module(jl_base_module);
    mod.method("==", [](const Long& lhs, const Long& rhs){return lhs.balanced_value() == rhs.balanced_value();});
    mod.method("==", [](const Long& lhs, const int& rhs){return lhs.balanced_value() == rhs;});
    mod.method("==", [](const int& lhs, const Long& rhs){return lhs == rhs.balanced_value();});
    mod.method("-", [](const Long& d){return -d;});
    mod.method("+", [](const Long& lhs, const Long& rhs){return lhs + rhs;});
    mod.method("-", [](const Long& lhs, const Long& rhs){return lhs - rhs;});
    mod.method("*", [](const Long& lhs, const Long& rhs){return lhs * rhs;});
    mod.method("/", [](const Long& lhs, const Long& rhs){return lhs / rhs;});
    mod.method("<", [](const Long& lhs, const Long& rhs){return lhs < rhs;});
    mod.unset_override_module();
}

} // namespace chomp