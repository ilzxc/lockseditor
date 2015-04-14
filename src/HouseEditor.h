//
//  HouseEditor.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/9/14.
//
//

#ifndef __MetaLocksEditor__HouseEditor__
#define __MetaLocksEditor__HouseEditor__

#include "House.h"
#include "RoomEditor.h"
#include "RoomTexts.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

class HouseEditor
{
  public:
    HouseEditor( const int pixelAreaX, const int pixelAreaY, const House& house );
    ~HouseEditor();
    
    void draw( const House& house ) const;
    void setup( const House& house );
    
    void mouse( House& house, const ci::Vec2i& mousePosition, const bool setPlayer );
    void toggleLockDirection( const int whichLock, House& house );
    
  private:
    int roomSize;
    std::vector< ci::Rectf > clickableRooms;
    std::vector< ci::Vec2f > roomPoints;
    int roomBeingEdited, directionBeingEdited;
    RoomEditor roomEditor;
    RoomTexts  labels;
    float offset;
    
    void toggleDoor( House& house, const ci::Vec2i& mouse, const int room );
};

#endif /* defined(__MetaLocksEditor__HouseEditor__) */
