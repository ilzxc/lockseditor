//
//  Snapshots.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/11/14.
//
//

#include "Snapshots.h"

using namespace ci;

Snapshots::Snapshots()
{
    house_snapshots.reserve( 10 );
    for ( int i = 0; i < 10; ++i ) {
        house_snapshots.push_back( nullptr );
    }
}

void Snapshots::draw() const
{
    gl::pushMatrices();
    gl::translate( app::getWindowSize() - Vec2f( 155, 20 ) );
    for ( auto& s : house_snapshots ) {
        if ( s == nullptr ) {
            gl::color( 0.f, 0.f, 0.f );
        } else {
            gl::color( 0.f, 0.4f, 0.9f );
        }
        gl::drawSolidRect( Rectf( 0., 0., 10., 10. ) );
        gl::translate( 15.f, 0.f );
    }
    gl::popMatrices();
}