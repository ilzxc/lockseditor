//
//  Room.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#ifndef __MetaLocksEditor__Room__
#define __MetaLocksEditor__Room__

#include "Lock.h"
#include <vector>

class Room
{
  friend class RoomEditor;
  
  public:
    Room();
    Room( const std::string& id );
    Room( const Room& other );
    ~Room();
    
    std::pair< int, int > attemptMove( int direction );
    Lock* getLock( const int direction ) { return &doors[ direction ]; }
    const std::string& getId() const { return roomId; }
    void setNewName( const std::string& id ) { roomId = id; }
    void toggleLock( const int direction );
    
  private:
    std::vector< Lock > doors;
    std::string roomId;
};



#endif /* defined(__MetaLocksEditor__Room__) */
