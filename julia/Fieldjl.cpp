// Julia wrapper for Field.h

#include <type_traits>

#include <jlcxx/jlcxx.hpp>

#include "chomp/Field.h"

namespace jlcxx {

using namespace chomp;

// Helper for wrapping template class Zp
template <Prime p>
struct BuildParameterList<Zp<p>>
{
    typedef ParameterList<std::integral_constant<Prime, p>> type;
};

} // namespace jlcxx

namespace chomp {

JLCXX_MODULE define_Field_module(jlcxx::Module& mod)
{
    using namespace jlcxx;

    mod.add_type<Parametric<TypeVar<1>>>("Zp")
        .apply<
        // Further primes can be implemented here.
            Zp<2>, Zp<3>, Zp<5>, Zp<7>, Zp<11>, Zp<13>, Zp<17>, Zp<19>, Zp<23>, Zp<29>

        >([](auto wrapped)
        {
            // Fetch wrapped type.
            typedef typename decltype(wrapped)::type WrappedT;

            // Declare nonstandard constructor.
            wrapped.template constructor<int>();

            // Declare methods.
            wrapped.method("invertible", &WrappedT::invertible);
            wrapped.method("balanced_value", &WrappedT::balanced_value);
            wrapped.method("value", [](const WrappedT& d){return d.value();});
            wrapped.method("inverse", [](const WrappedT& d){return inverse(d);});

            // Overload base module operations.
            wrapped.module().set_override_module(jl_base_module);
            wrapped.method("==", [](const WrappedT& lhs, const WrappedT& rhs){return lhs == rhs;});
            wrapped.method("==", [](const WrappedT& lhs, const int& rhs){return lhs == rhs;});
            wrapped.method("==", [](const int& lhs, const WrappedT& rhs){return rhs == lhs;});
            wrapped.method("-", [](const WrappedT& d){return -d;});
            wrapped.method("+", [](const WrappedT& lhs, const WrappedT& rhs){return lhs + rhs;});
            wrapped.method("-", [](const WrappedT& lhs, const WrappedT& rhs){return lhs - rhs;});
            wrapped.method("*", [](const WrappedT& lhs, const WrappedT& rhs){return lhs * rhs;});
            wrapped.method("/", [](const WrappedT& lhs, const WrappedT& rhs){return lhs / rhs;});
            wrapped.module().unset_override_module();
        });
}

} // namespace chomp