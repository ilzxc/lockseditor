//
//  HouseEditor.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/9/14.
//
//

#include "HouseEditor.h"

using namespace ci;

HouseEditor::HouseEditor( const int pixelAreaX, const int pixelAreaY, const House& house )
: roomBeingEdited( 0 ),
  directionBeingEdited( LEFT ),
  labels(),
  roomEditor()
{
    int scarceArea = ( pixelAreaX <= pixelAreaY ) ? pixelAreaX : pixelAreaY;
    int mostRooms  = ( house.numRooms.first >= house.numRooms.second ) ? house.numRooms.first : house.numRooms.second;
    int size = ( scarceArea - ( mostRooms * 5 ) ) / mostRooms;
    
    roomSize = size + 5;
    offset = size / 2.f + 5;
    roomEditor.setSize( size );
    
    for ( int j = 0; j < house.numRooms.second; ++j ) {
        for ( int i = 0; i < house.numRooms.first; ++i ) {
            Vec2f buttonOffset = Vec2f( roomSize * i + offset, roomSize * j + offset );
            clickableRooms.push_back( roomEditor.roomDimensions.getOffset( buttonOffset ) );
            
            roomPoints.push_back( Vec2f( clickableRooms[ clickableRooms.size() - 1 ].getCenter() ) );
        }
    }
    
    std::vector< std::string > roomIds;
    for ( auto& room : house.rooms ) {
        roomIds.push_back( room.getId() );
    }
    
    labels.setup( roomIds );
}

HouseEditor::~HouseEditor() { }

void HouseEditor::draw( const House& house ) const
{
    gl::pushMatrices();
    gl::translate( offset, offset );  
    for ( int i = 0; i < house.numRooms.first; ++i ) {
        for ( int j = 0; j < house.numRooms.second; ++j ) {
            gl::pushMatrices();
            gl::translate( roomSize * i, roomSize * j );
            int index = house.getIndex( std::pair< int, int >( i, j ) );
            roomEditor.draw( house.rooms[ house.roomIndices[ index ] ], ( index == roomBeingEdited ), labels.getText( house.roomIndices[ index ] ) );
            
            if ( ( house.position.first == i ) && ( house.position.second == j ) ) {
                gl::color( 0.88f, 0.88f, 0.88f, 1.0f );
                gl::drawSolidCircle( Vec2f::zero(), 10.0f );
            }
            
            gl::popMatrices();
        }
    }
    gl::popMatrices();
    
    // ROOMEDITOR:
    gl::pushMatrices();
    gl::translate( 505.f, 5.f );
    gl::color( 0.888f, 0.888f, 0.888f );
    gl::drawSolidRect( Rectf( 0.f, 0.f, app::getWindowWidth() - 510, app::getWindowHeight() - 10 ) );
    
    gl::pushMatrices();
    gl::color( 0.f, 0.f, 0.f );
    gl::translate( 0.5f * ( app::getWindowWidth() - 510 ), 0.5f * ( app::getWindowHeight() - 10 ) );
//    roomEditor.draw( house.rooms[ house.roomIndices[ roomBeingEdited ] ], true, labels.getText( house.roomIndices[ roomBeingEdited ] ) );
    roomEditor.drawLocks( house.rooms[ house.roomIndices[ roomBeingEdited ] ], labels.getText( house.roomIndices[ roomBeingEdited ] ) );
    
//    lockEditor.draw( *house.rooms[ roomBeingEdited ].getLock( directionBeingEdited ) );
    gl::popMatrices();
    gl::popMatrices();
}

void HouseEditor::setup( const House& house )
{
    
}

void HouseEditor::mouse( House& house, const Vec2i& mousePosition, const bool setPlayer )
{
    if ( mousePosition.x < 500 ) {
        int counter = 0;
        for ( auto& rect : clickableRooms ) {
            if ( rect.contains( mousePosition ) ) {
                if ( roomBeingEdited == counter ) {
                    if ( setPlayer ) {
                        house.setPlayer( counter );
                    } else {
                        toggleDoor( house, mousePosition, roomBeingEdited );
                    }
                } else {
                    roomBeingEdited = counter;
                }
                break;
            }
            ++counter;
        }
    }
}

void HouseEditor::toggleLockDirection( const int whichLock, House& house )
{
    house.rooms[ house.roomIndices[ roomBeingEdited ] ].getLock( whichLock )->toggleDirection( 0 );
}

void HouseEditor::toggleDoor( House& house, const ci::Vec2i& mouse, const int room )
{
    int r = house.roomIndices[ room ];
    Vec2f origin = roomPoints[ room ];
    
    if ( abs( mouse.x - origin.x ) > abs( mouse.y - origin.y ) ) {
        if ( ( mouse.x - origin.x ) > 0 ) {
            directionBeingEdited = RIGHT;
        } else {
            directionBeingEdited = LEFT;
        }
    } else {
        if ( ( mouse.y - origin.y ) > 0 ) {
            directionBeingEdited = DOWN;
        } else {
            directionBeingEdited = UP;
        }
    }
    
    house.rooms[ r ].toggleLock( directionBeingEdited );
}


