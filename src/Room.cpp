//
//  Room.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#include "Room.h"

Room::Room()
: Room::Room( "null" )
{
}

Room::Room( const std::string& id )
: roomId( id )
{
    for ( int i = 0; i < 4; ++i ) {
        doors.push_back( Lock( true ) );
    }
}

Room::Room( const Room& other )
: doors( other.doors ),
  roomId( other.roomId )
{ }

Room::~Room() { }

std::pair< int, int > Room::attemptMove( int direction )
{
    if ( doors[ direction ].isVoid() ) return std::pair< int, int >( MOVEABORT, ROOMDOESNOTSHIFT );
    
    if ( doors[ direction ].isLocked() ) {
        int roomShiftDirection = doors[ direction ].unlock();
        return std::pair< int, int >( MOVEFAILURE, roomShiftDirection );
    }
    
    return std::pair< int, int >( MOVESUCCESS, ROOMDOESNOTSHIFT );
}

void Room::toggleLock( const int direction )
{
    doors[ direction ].toggle();
    
/*
    if ( doors[ direction ].isVoid() ) {
        doors[ direction ] = Lock( false );
    } else {
        doors[ direction ] = Lock( true );
    }
*/
}