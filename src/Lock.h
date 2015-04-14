//
//  Lock.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#ifndef __MetaLocksEditor__Lock__
#define __MetaLocksEditor__Lock__

#include <vector>
#include "Directions.h"


class Lock
{
  friend class LockEditor;
  friend class RoomEditor;
    
  public:
    Lock();
    Lock( bool makeVoid );
    Lock( const Lock& other );
    ~Lock();
    
    int unlock();
    bool isLocked() const { return ! ( currentLock == numLocks ); }
    bool isVoid() const { return voidLock; }
    float getOpacity() const { return ( 1.0f * currentLock ) / numLocks; }
    void toggleDirection( int index );
    void toggle() { voidLock = ! voidLock ; }
    void addLock();
    void removeLock();
    void resetLock() { currentLock = 0; }
    
  private:
    int numLocks, currentLock;
    std::vector< int > directions;
    bool voidLock;
};

#endif /* defined(__MetaLocksEditor__Lock__) */
