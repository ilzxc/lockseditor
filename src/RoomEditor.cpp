//
//  RoomEditor.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#include "RoomEditor.h"

using namespace ci;

RoomEditor::RoomEditor()
{ }

RoomEditor::RoomEditor( const int size )
: lockEditor()
{
    setSize( size );
}

RoomEditor::RoomEditor( const RoomEditor& other )
: roomDimensions( other.roomDimensions ),
  doorDimensions( other.roomDimensions ),
  roomSize( other.roomSize ),
  lockOffsets( other.lockOffsets ),
  lockEditor( other.lockEditor )
{ }

RoomEditor::~RoomEditor() { }

void RoomEditor::setSize( const int size )
{
    roomSize = size / 2.f;
    roomDimensions = Rectf( -roomSize, -roomSize, roomSize, roomSize );
    
    float halfThickness = size / 20.0f; // thickness of the door is 1/10 of the size
    float halfHeight    = size /  6.0f;
    doorDimensions = Rectf(  roomSize - halfThickness,
                            -halfHeight,
                             roomSize,
                             halfHeight );
    
    lockOffsets.reserve( 4 );
    lockOffsets[ LEFT  ] = Vec2f( -size, 0.f );
    lockOffsets[ RIGHT ] = Vec2f(  size, 0.f );
    lockOffsets[ UP    ] = Vec2f( 0.f, -size );
    lockOffsets[ DOWN  ] = Vec2f( 0.f,  size );
}

void RoomEditor::draw( const Room& room, bool isBeingEdited, const gl::Texture& label ) const
{
    gl::color( 0.f, 0.f, 0.f, 1.f );
    gl::drawSolidRect( roomDimensions );
    gl::pushMatrices();
    gl::translate( -roomSize + 5, -roomSize + 5 );
    gl::color( 1.f, 1.f, 1.f, 1.f );
    gl::draw( label );
    gl::popMatrices();
    
    if ( isBeingEdited ) {
        gl::color( 0.5f, 0.5f, 0.5f );
        gl::lineWidth( 0.5f );
        gl::drawLine( Vec2f( -roomSize, -roomSize ), Vec2f( roomSize,  roomSize ) );
        gl::drawLine( Vec2f( -roomSize,  roomSize ), Vec2f( roomSize, -roomSize ) );
    }
    
    gl::pushMatrices();
    gl::rotate( -180.f );
    for ( int i = 0; i < 4; ++i ) {
        if ( ! room.doors[ i ].isVoid() ) {
            gl::color( 1.f, room.doors[ i ].getOpacity(), 1.f, 1.f  );
            gl::drawSolidRect( doorDimensions );
        }
        gl::rotate( 90.0f );
    }
    gl::popMatrices();
}

void RoomEditor::drawLocks( const Room& room, const gl::Texture& label ) const
{
    draw( room, true, label );
    for ( auto i = 0; i < 4; ++i ) {
        gl::pushMatrices();
        gl::translate( lockOffsets[ i ] );
        lockEditor.draw( room.doors[ i ] );
        gl::popMatrices();
    }
    
    
}