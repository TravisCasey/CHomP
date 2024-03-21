// Julia wrapper for Ring.h

#include <jlcxx/jlcxx.hpp>

#include "chomp/Ring.h"

namespace chomp {

JLCXX_MODULE define_Ring_module(jlcxx::Module& mod)
{
    using namespace jlcxx;

    mod.add_type<Long>("Long")

    // Declare nonstandard constructor.
        .constructor<int64_t>()

    // Declare methods.
        .method("invertible", &Long::invertible)
        .method("balanced_value", &Long::balanced_value);

    // Overload base module operations.
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

    mod.add_type<GMP_Integer>("GMP_Integer")

    // Declare nonstandard constructor.
        .constructor<int32_t>()

    // Declare methods.
        .method("invertible", &GMP_Integer::invertible);

    // New method relaying the value as a string. Later converted to BigInt on Julia side.
    mod.method("get_str", [](const GMP_Integer& d){return d.balanced_value().get_str();});

    // Overload base module operations.
    mod.set_override_module(jl_base_module);
    mod.method("==", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs == rhs;});
    mod.method("-", [](const GMP_Integer& d){return -d;});
    mod.method("+", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs + rhs;});
    mod.method("-", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs - rhs;});
    mod.method("*", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs * rhs;});
    mod.method("/", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs / rhs;});
    mod.method("<", [](const GMP_Integer& lhs, const GMP_Integer& rhs){return lhs < rhs;});
    mod.unset_override_module();
}

} // namespace chomp