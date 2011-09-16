#include <corbasim/core/archives.hpp>

//
// Explicit instantiation of ...
// http://lists.boost.org/boost-users/2010/08/61470.php
//
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>

#include <boost/archive/impl/text_oarchive_impl.ipp>
#include <boost/archive/impl/text_iarchive_impl.ipp>

#include <boost/archive/impl/basic_text_oarchive.ipp>
#include <boost/archive/impl/basic_text_iarchive.ipp>

namespace boost
{
namespace archive
{

template class detail::archive_serializer_map< corbasim::core::text_iarchive >;
template class basic_text_iarchive< corbasim::core::text_iarchive >;
template class text_iarchive_impl< corbasim::core::text_iarchive >;

template class detail::archive_serializer_map< corbasim::core::text_oarchive >;
template class basic_text_oarchive< corbasim::core::text_oarchive >;
template class text_oarchive_impl< corbasim::core::text_oarchive >;

} // namespace serialization
} // namespace boost
