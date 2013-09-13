/* -*- mode: c++; fill-column: 132; c-basic-offset: 4; indent-tabs-mode: nil -*- */

// =-=-=-=-=-=-=-
// eirods includes
#include "eirods_tcp_object.h"
#include "eirods_network_manager.h"

namespace eirods {
    // =-=-=-=-=-=-=-
    // public - ctor
    tcp_object::tcp_object() :
        network_object() {
   
    } // ctor

    // =-=-=-=-=-=-=-
    // public - ctor
    tcp_object::tcp_object(
        const rcComm_t& _comm ) : 
        network_object( _comm ) {

    } // ctor

    // =-=-=-=-=-=-=-
    // public - ctor
    tcp_object::tcp_object(
        const rsComm_t& _comm ) : 
        network_object( _comm ) {

    } // ctor

    // =-=-=-=-=-=-=-
    // public - cctor
    tcp_object::tcp_object( 
        const tcp_object& _rhs ) :
        network_object( _rhs ) {

    } // cctor

    // =-=-=-=-=-=-=-
    // public - dtor
    tcp_object::~tcp_object() {
    
    } // dtor

    // =-=-=-=-=-=-=-
    // public - assignment operator
    tcp_object& tcp_object::operator=( 
        const tcp_object& _rhs ) {
        network_object::operator=( _rhs );

        return *this;

    } // operator=

    // =-=-=-=-=-=-=-
    // public - assignment operator
    bool tcp_object::operator==( 
        const tcp_object& _rhs ) const {
        return network_object::operator==( _rhs );

    } // operator=

    // =-=-=-=-=-=-=-
    // public - resolver for tcp_manager
    error tcp_object::resolve( 
        const std::string& _interface,
        plugin_ptr&        _ptr ) {
        // =-=-=-=-=-=-=-
        // check the interface type and error out if it
        // isnt a network interface
        if( NETWORK_INTERFACE != _interface ) {
            std::stringstream msg;
            msg << "tcp_object does not support a [";
            msg << _interface;
            msg << "] plugin interface";
            return ERROR( SYS_INVALID_INPUT_PARAM, msg.str() );

        }

        // =-=-=-=-=-=-=-
        // ask the network manager for a tcp resource
        network_ptr net_ptr;
        error ret = netwk_mgr.resolve( TCP_NETWORK_PLUGIN, net_ptr );
        if( !ret.ok() ) {
            // =-=-=-=-=-=-=-
            // attempt to load the plugin, in this case the type,
            // instance name, key etc are all tcp as there is only
            // the need for one instance of a tcp object, etc.
            std::string empty_context( "" );
            ret = netwk_mgr.init_from_type( 
                      TCP_NETWORK_PLUGIN,
                      TCP_NETWORK_PLUGIN,
                      TCP_NETWORK_PLUGIN,
                      empty_context,
                      net_ptr );
            if( !ret.ok() ) {
                // =-=-=-=-=-=-=-
                // upcast for out variable
                _ptr = boost::dynamic_pointer_cast< plugin_base >( net_ptr );
               
                return PASS( ret );

            } else {
                return SUCCESS();

            }

        } // if !ok

        // =-=-=-=-=-=-=-
        // upcast for out variable
        _ptr = boost::dynamic_pointer_cast< plugin_base >( net_ptr );

        return SUCCESS();

    } // resolve
        
    // =-=-=-=-=-=-=-
    // accessor for rule engine variables
    error tcp_object::get_re_vars( 
        keyValPair_t& _kvp ) {
        return network_object::get_re_vars( _kvp );

    } // get_re_vars
 
}; // namespace eirods



