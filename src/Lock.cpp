//
//  Lock.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#include "Lock.h"

Lock::Lock()
: Lock( false ) { }

Lock::Lock( bool makeVoid )
: voidLock( makeVoid ),
  currentLock( 0 )
{
    numLocks = 1; // default
    for ( int i = 0; i < numLocks; ++i ) {
        directions.push_back( LEFT );
    }
    assert( numLocks == directions.size() );
}

Lock::Lock( const Lock& other )
: numLocks( other.numLocks ),
  currentLock( other.currentLock ),
  directions( other.directions ),
  voidLock( other.voidLock )
{ }

Lock::~Lock() { }

int Lock::unlock()
{
    int result = directions[ currentLock ];
    ++currentLock;
    return result;
}

void Lock::toggleDirection( int index )
{
    if ( ( index < directions.size() ) && ( index > -1 ) ) {
        directions[ index ] = ( directions[ index ] + 1 ) % 4;
    }
}

void Lock::addLock()
{
    ++numLocks;
    directions.push_back( LEFT );
    assert( numLocks == directions.size() );
}

void Lock::removeLock()
{
    if ( numLocks == 0 ) return;
    
    --numLocks;
    directions.pop_back();
    assert( numLocks == directions.size() );
}