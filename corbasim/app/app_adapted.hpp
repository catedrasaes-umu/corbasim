#ifndef APP_ADAPTED_HPP
#define APP_ADAPTED_HPP

#include "appC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>

// StructDef: corbasim::app::ObjrefConfig
BOOST_FUSION_ADAPT_STRUCT(
        corbasim::app::ObjrefConfig,
        ( ::TAO::String_Manager, id)
        ( ::TAO::String_Manager, fqn)
        ( ::TAO::String_Manager, entry)
        ( ::CORBA::Object_var, ref)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::ObjrefConfig& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("id", t.id);
            ar & boost::serialization::make_nvp("fqn", t.fqn);
            ar & boost::serialization::make_nvp("entry", t.entry);
            ar & boost::serialization::make_nvp("ref", t.ref);
        }

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::ObjrefConfig_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, corbasim::app::ObjrefConfigSeq& t,
                const unsigned int version)
        {
            ::corbasim::serialization::sequence::serialize( ar, t, version);
        }

        template< class Archive >
        void serialize(Archive& ar, corbasim::app::ObjrefConfigSeq_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< corbasim::app::ObjrefConfigSeq > : public cs_mpl::true_
        {
            typedef corbasim::app::ObjrefConfig slice_type;
        };

    } // adapted
} // corbasim


// StructDef: corbasim::app::ServantConfig
BOOST_FUSION_ADAPT_STRUCT(
        corbasim::app::ServantConfig,
        ( ::TAO::String_Manager, id)
        ( ::TAO::String_Manager, fqn)
        ( ::TAO::String_Manager, entry)
        ( ::TAO::String_Manager, behaviour)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::ServantConfig& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("id", t.id);
            ar & boost::serialization::make_nvp("fqn", t.fqn);
            ar & boost::serialization::make_nvp("entry", t.entry);
            ar & boost::serialization::make_nvp("behaviour", t.behaviour);
        }

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::ServantConfig_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, corbasim::app::ServantConfigSeq& t,
                const unsigned int version)
        {
            ::corbasim::serialization::sequence::serialize( ar, t, version);
        }

        template< class Archive >
        void serialize(Archive& ar, corbasim::app::ServantConfigSeq_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< corbasim::app::ServantConfigSeq > : public cs_mpl::true_
        {
            typedef corbasim::app::ServantConfig slice_type;
        };

    } // adapted
} // corbasim


// StructDef: corbasim::app::Configuration
BOOST_FUSION_ADAPT_STRUCT(
        corbasim::app::Configuration,
        ( corbasim::app::ServantConfigSeq, servants)
        ( corbasim::app::ObjrefConfigSeq, objects)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::Configuration& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("servants", t.servants);
            ar & boost::serialization::make_nvp("objects", t.objects);
        }

        template < class Archive >
        void serialize(Archive& ar, corbasim::app::Configuration_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


namespace _corbasim_corbasim
{
    namespace app
    {
        struct ObjrefConfig
        {
            typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 0 >
                    id_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 1 >
                    fqn_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 2 >
                    entry_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 3 >
                    ref_corbasim_member;

        };

        struct ServantConfig
        {
            typedef corbasim::adapted::member< ::corbasim::app::ServantConfig,
                    0 > id_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ServantConfig,
                    1 > fqn_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ServantConfig,
                    2 > entry_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::ServantConfig,
                    3 > behaviour_corbasim_member;

        };

        struct Configuration
        {
            typedef corbasim::adapted::member< ::corbasim::app::Configuration,
                    0 > servants_corbasim_member;
            typedef corbasim::adapted::member< ::corbasim::app::Configuration,
                    1 > objects_corbasim_member;

        };

    } // app

} // _corbasim_corbasim


#endif // APP_ADAPTED_HPP

