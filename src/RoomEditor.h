//
//  RoomEditor.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#ifndef __MetaLocksEditor__RoomEditor__
#define __MetaLocksEditor__RoomEditor__

#include "Room.h"
#include "LockEditor.h"
#include "cinder/Rect.h"

class RoomEditor
{
  friend class HouseEditor;
    
  public:
    RoomEditor();
    RoomEditor( const int size );
    RoomEditor( const RoomEditor& other );
    ~RoomEditor();
    
    void setSize( const int size );
    void draw( const Room& room, bool isBeingEdited, const ci::gl::Texture& label ) const;
    void drawLocks( const Room& room, const ci::gl::Texture& label ) const;
    
  private:
    ci::Rectf roomDimensions, doorDimensions;
    float roomSize;
    std::vector< ci::Vec2f > lockOffsets;
    LockEditor lockEditor;    
};

#endif /* defined(__MetaLocksEditor__RoomEditor__) */
