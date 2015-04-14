//
//  House.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#include "House.h"

House::House( const int numX, const int numY )
: numRooms( numX, numY ),
  position( 0, 0 ) 
{
    int totalRooms = numRooms.first * numRooms.second;
    
    for ( int i = 0; i < totalRooms; ++i )
    {
        roomIndices.push_back( i );
        rooms.push_back( Room( std::to_string( i ) ) );
    }
}

House::House( const House& other )
: rooms( other.rooms ),
  roomIndices( other.roomIndices ),
  numRooms( other.numRooms ),
  position( other.position )
{ }

House::~House() { }

void House::setPlayer( const int room )
{
    for ( int i = 0; i < numRooms.first; ++i )
    {
        for ( int j = 0; j < numRooms.second; ++j )
        {
            if ( ( j * numRooms.first + i ) == room )
            {
                position.first  = i;
                position.second = j;
            }
        }
    }
}


void House::movePlayer( const int direction )
{
    if ( ( direction < 0 ) || ( direction > 4 ) ) return;
    
    NextRoom other = getOtherRoom( direction, position );
    int currentRoomIndex = getIndex( position );
    int otherRoomIndex = getIndex( other.newPosition );
    
    std::pair< int, int > moveResults = rooms[ roomIndices[ currentRoomIndex ] ].attemptMove( direction );
    
    if ( moveResults.first != MOVEABORT )
    {
        if ( ( rooms[ roomIndices[ otherRoomIndex ] ].attemptMove( other.otherSide ).first == MOVESUCCESS )
             && ( moveResults.first == MOVESUCCESS ) )
        {
            position = other.newPosition;
        }
        else
        {
            if ( moveResults.second != ROOMDOESNOTSHIFT )
            {
                moveRoom( moveResults.second );
            }
        }
    }
}


void House::moveRoom( const int direction )
{
    if ( ( direction < 0 ) || ( direction > 3 ) ) return;
    
    Neighbors n = getNeighbors();
    NextRoom other = getOtherRoom( direction, position ); 
    
    switch ( direction ) {
        case LEFT  :
            swap( n.left, getOtherRoom( direction, n.left ).newPosition );
            swap( position, other.newPosition );
            position = other.newPosition;
            swap( n.right, getOtherRoom( direction, n.right ).newPosition );
            swap( n.top, getOtherRoom( direction, n.top ).newPosition );
            swap( n.bot, getOtherRoom( direction, n.bot ).newPosition );
            break;
        case UP    :
            swap( n.top, getOtherRoom( direction, n.top ).newPosition );
            swap( position, other.newPosition );
            position = other.newPosition;
            swap( n.bot, getOtherRoom( direction, n.bot ).newPosition );
            swap( n.right, getOtherRoom( direction, n.right ).newPosition );
            swap( n.left, getOtherRoom( direction, n.left ).newPosition );
            break;
        case RIGHT :
            swap( n.right, getOtherRoom( direction, n.right ).newPosition );
            swap( position, other.newPosition );
            position = other.newPosition;
            swap( n.left, getOtherRoom( direction, n.left ).newPosition );
            swap( n.top, getOtherRoom( direction, n.top ).newPosition );
            swap( n.bot, getOtherRoom( direction, n.bot ).newPosition );
            break;
        case DOWN  :
            swap( n.bot, getOtherRoom( direction, n.bot ).newPosition );
            swap( position, other.newPosition );
            position = other.newPosition;
            swap( n.top, getOtherRoom( direction, n.top ).newPosition );
            swap( n.right, getOtherRoom( direction, n.right ).newPosition );
            swap( n.left, getOtherRoom( direction, n.left ).newPosition );
            break;
    }
}


void House::resetIndices()
{
    for ( int i = 0; i < roomIndices.size(); ++i ) {
        roomIndices[ i ] = i;
        for ( int j = 0; j < 4; ++j ) {
            rooms[ i ].getLock( j )->resetLock();
        }
    }
}


void House::swap( const std::pair< int, int >& one, const std::pair< int, int >& two )
{
    std::iter_swap( roomIndices.begin() + getIndex( one ), roomIndices.begin() + getIndex( two ) );
}


House::NextRoom House::getOtherRoom( const int direction, const std::pair< int, int >& from ) const
{
    std::pair< int, int > newPosition = from;
    int otherSide = 0;
    
    switch ( direction ) {
        case LEFT  :
            newPosition.first  = decrement( from.first,   numRooms.first );
            otherSide = RIGHT;
            break;
        case UP    :
            newPosition.second = decrement( from.second, numRooms.second );
            otherSide = DOWN;
            break;
        case RIGHT :
            newPosition.first  = increment( from.first,   numRooms.first );
            otherSide = LEFT;
            break;
        case DOWN  :
            newPosition.second = increment( from.second, numRooms.second );
            otherSide = UP;
            break;
    }
    
    return House::NextRoom( newPosition, otherSide );
}

House::Neighbors House::getNeighbors() const
{
    Neighbors result;
    result.setTop  ( position.first, decrement( position.second, numRooms.second ) );
    result.setLeft ( decrement( position.first, numRooms.first ), position.second  );
    result.setBot  ( position.first, increment( position.second, numRooms.second ) );
    result.setRight( increment( position.first, numRooms.first ), position.second  );
    return result;
}

