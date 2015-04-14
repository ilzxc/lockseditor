//
//  House.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#ifndef __MetaLocksEditor__House__
#define __MetaLocksEditor__House__

#include "Room.h"

class House
{
  friend class HouseEditor;
    
  public:
    House( const int numX, const int numY );
    House( const House& other );
    ~House();
    
    void setPlayer( const int room );
    void movePlayer( const int direction );
    void moveRoom( const int direction );
    void resetIndices();
    
  private:
    std::vector< Room > rooms;
    std::vector< int  > roomIndices;
    std::pair< int, int > numRooms;
    std::pair< int, int > position;
    
    void swap( const std::pair< int, int >& one, const std::pair< int, int >& two );
    int getIndex( const std::pair< int, int > position ) const { return ( numRooms.first * position.second ) + position.first; }
    
    struct NextRoom {
        std::pair< int, int > newPosition;
        int otherSide;
        
        NextRoom() { }
        NextRoom( std::pair< int, int >np, const int os )
        : newPosition( np ), otherSide( os ) { }
    };
    
    struct Neighbors {
        std::pair< int, int > top, left, right, bot;
        
        void setTop  ( const int x, const int y ) { top   = std::pair< int, int >( x, y ); }
        void setLeft ( const int x, const int y ) { left  = std::pair< int, int >( x, y ); }
        void setRight( const int x, const int y ) { right = std::pair< int, int >( x, y ); }
        void setBot  ( const int x, const int y ) { bot   = std::pair< int, int >( x, y ); }
    };
    
    NextRoom getOtherRoom( const int direction, const std::pair< int, int >& from ) const;
    Neighbors getNeighbors() const;
    
    int increment( const int coordinate, const int wrapAround ) const { return ( coordinate + 1 ) % wrapAround; }
    int decrement( const int coordinate, const int wrapAround ) const { return ( coordinate + ( wrapAround - 1 ) ) % wrapAround; }
};

#endif /* defined(__MetaLocksEditor__House__) */
