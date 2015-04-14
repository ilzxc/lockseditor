//
//  LockEditor.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#include "LockEditor.h"

using namespace ci;

LockEditor::LockEditor()
: directionButton( 0.f, 0.f, 30.f, 30.f ),
  arrowColor( 1.f, 1.f, 1.f ),
  buttonLockedColor( Color::hex( 0xFF1A2E40 ) ),
  buttonUnlockedColor( Color::hex( 0xFF3F735B ) ),
  buttonInactiveColor( Color::gray( 0.99f ) )
{ }

LockEditor::LockEditor( const LockEditor& other )
: directionButton( other.directionButton ),
  arrowColor( other.arrowColor ),
  buttonLockedColor( other.buttonLockedColor ),
  buttonInactiveColor( other.buttonInactiveColor ),
  buttonUnlockedColor( other.buttonUnlockedColor )
{ }

LockEditor::~LockEditor() { }

void LockEditor::draw( const Lock& lock ) const
{
    // Should be transformed to room center prior to drawing...
    gl::pushMatrices();
    float x = lock.directions.size() * ( directionButton.getWidth() + ( 10.f / lock.directions.size() ) ) * -0.5f;
    float y = directionButton.getHeight() * -0.5f;
    gl::translate( x, y );
    int enumerator = 0; // check if lock is locked...
    for ( auto d : lock.directions )
    {
        gl::color( lock.isVoid() ? buttonInactiveColor : ( lock.currentLock <= enumerator ) ? buttonLockedColor : buttonUnlockedColor  );
        ++enumerator;
        gl::drawSolidRect( directionButton );
        gl::color( lock.isVoid() ? buttonLockedColor : arrowColor );
        gl::lineWidth( 0.5f );
        switch ( d ) {
            case LEFT  : drawLeft();  break;
            case UP    : drawUp();    break;
            case RIGHT : drawRight(); break;
            case DOWN  : drawDown();  break;
        }
        gl::translate( 40.f, 0.f );
    }
    gl::popMatrices();
}


void LockEditor::drawRight() const
{
    gl::drawLine( Vec2f(  5, 15 ), Vec2f( 25, 15 ) );
    gl::drawLine( Vec2f( 25, 15 ), Vec2f( 20, 10 ) );
    gl::drawLine( Vec2f( 25, 15 ), Vec2f( 20, 20 ) );
}

void LockEditor::drawUp() const
{
    gl::drawLine( Vec2f( 15, 5 ), Vec2f( 15, 25 ) );
    gl::drawLine( Vec2f( 15, 5 ), Vec2f( 10, 10 ) );
    gl::drawLine( Vec2f( 15, 5 ), Vec2f( 20, 10 ) );
}

void LockEditor::drawLeft() const
{
    gl::drawLine( Vec2f(  5, 15 ), Vec2f( 25, 15 ) );
    gl::drawLine( Vec2f(  5, 15 ), Vec2f( 10, 10 ) );
    gl::drawLine( Vec2f(  5, 15 ), Vec2f( 10, 20 ) );
}

void LockEditor::drawDown() const
{
    gl::drawLine( Vec2f( 15,  5 ), Vec2f( 15, 25 ) );
    gl::drawLine( Vec2f( 15, 25 ), Vec2f( 10, 20 ) );
    gl::drawLine( Vec2f( 15, 25 ), Vec2f( 20, 20 ) );
}